#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "myKeyBoard.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_pwr.h"
#include "main.h"
#include "deepSleep.h"
#include "stdio.h"

// 记录是否处于休眠状态
static uint8_t g_InDeepSleep = 0;

void Enter_Deep_Sleep(void)
{
    if (g_InDeepSleep) return;
    g_InDeepSleep = 1;

    __enable_irq();

    // ========== 配置唤醒 GPIO ==========
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIOC->CRL &= ~(0xFU << 28);
    GPIOC->CRL |= (0x2U << 28);   // PP Output
    GPIOC->ODR |= GPIO_Pin_7;     // HIGH

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    GPIOA->CRL &= ~0x0000F000;
    GPIOA->CRL |= 0x00004000;     // Floating Input

    // ========== 配置 EXTI ==========
    AFIO->EXTICR[1] = (AFIO->EXTICR[1] & ~0xF0) | 0x00; // PA5
    EXTI->IMR |= EXTI_IMR_MR5;
    EXTI->RTSR |= EXTI_RTSR_TR5;
    EXTI->PR = EXTI_PR_PR5;
    EXTI_ClearITPendingBit(EXTI_Line5);

    NVIC_InitTypeDef nvic = {
        .NVIC_IRQChannel = EXTI9_5_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 0,
        .NVIC_IRQChannelCmd = ENABLE
    };
    NVIC_Init(&nvic);

    // ========== 仅将 PB/PC 的无关引脚设为 AIN ==========
		{
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

				GPIO_InitTypeDef gpio;
				gpio.GPIO_Speed = GPIO_Speed_2MHz;
				gpio.GPIO_Mode = GPIO_Mode_AIN;

				// PB: 全部设为 AIN（STOP 中 PB12-15 不驱动，安全）
				gpio.GPIO_Pin = GPIO_Pin_All;
				GPIO_Init(GPIOB, &gpio);

				// PC: 除 PC7 外设为 AIN
				gpio.GPIO_Pin = GPIO_Pin_All & ~GPIO_Pin_7;
				GPIO_Init(GPIOC, &gpio);

				// 重新确认 PC7 状态（防止 GPIO_Init 覆盖）
				GPIOC->CRL &= ~(0xFU << 28);
				GPIOC->CRL |= (0x2U << 28);   // PP Output
				GPIOC->ODR |= GPIO_Pin_7;     // HIGH
		}

    // ========== 关闭 HSE，切换到 HSI ==========
    RCC->CFGR &= ~RCC_CFGR_SW; // Switch to HSI
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);
    RCC->CR &= ~RCC_CR_HSEON; // 关闭 HSE

    // ========== 进入 STOP ==========
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);

    // ========== 唤醒后恢复 ==========
    // 恢复 HSE + PLL
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));
    RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
    RCC->CFGR |= RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9;
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
    SystemCoreClock = 72000000;

    // ========== 恢复键盘 GPIO ==========
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;

    // PA0-PA5: IPD
    GPIOA->CRL = 0x88888888; // 0b1000 = IPD for PA0-PA7
    uint32_t crl = GPIOA->CRL;
    crl &= 0xFFFF0000; 
    GPIOA->CRL = (0x88888888 & 0x00FFFFFF) | (GPIOA->CRL & 0xFF000000); // PA0-PA5 = IPD

    {
        GPIO_InitTypeDef gpio_init;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        gpio_init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | 
                             GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
        gpio_init.GPIO_Mode = GPIO_Mode_IPD;
        gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_Init(GPIOA, &gpio_init);
    }

    // PB12-PB15: PP Output LOW
    {
        GPIO_InitTypeDef gpio_init;
        gpio_init.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
        gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
        gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_Init(GPIOB, &gpio_init);
        GPIO_ResetBits(GPIOB, gpio_init.GPIO_Pin);
    }

    // PC0-PC11: PP Output LOW
    {
        GPIO_InitTypeDef gpio_init;
        uint16_t pc_col_pins = 
            GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
            GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |
            GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
        gpio_init.GPIO_Pin = pc_col_pins;
        gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
        gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_Init(GPIOC, &gpio_init);
        GPIO_ResetBits(GPIOC, pc_col_pins);
    }

    // Disable EXTI
    EXTI->IMR &= ~EXTI_IMR_MR5;
    EXTI->RTSR &= ~EXTI_RTSR_TR5;
    NVIC_DisableIRQ(EXTI9_5_IRQn);

    clear_keyboard_state();

    g_InDeepSleep = 0;
}


void Enter_Deep_Sleep_Menu(void)
{
    if (g_InDeepSleep) return;
    g_InDeepSleep = 1;
	
		  // 拉低PB8，方便验证
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//		GPIO_InitTypeDef gpio;
//		gpio.GPIO_Pin = GPIO_Pin_8;
//		gpio.GPIO_Mode = GPIO_Mode_Out_PP;
//		gpio.GPIO_Speed = GPIO_Speed_2MHz;
//		GPIO_Init(GPIOB, &gpio);
//		GPIO_ResetBits(GPIOB, GPIO_Pin_8); // 默认低

    __enable_irq();

    // 将 COL5 (PC7) 设为输出 HIGH （Menu键）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIOC->CRL &= ~(0xFU << 28);     // Clear PC7 bits (bit 28-31 in CRL)
    GPIOC->CRL |= (0x2 << 28);       // PP Output mode for PC7
    GPIOC->ODR |= GPIO_Pin_7;        // Output HIGH!

    // 配置 PA5 (ROW5) 为浮空输入 + EXTI 上升沿（完全不变）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    GPIOA->CRL &= ~0x0000F000;
    GPIOA->CRL |=  0x00004000; // Floating Input (NO pull-up!)

    AFIO->EXTICR[1] = (AFIO->EXTICR[1] & ~0xF0) | 0x00; // PA5
    EXTI->IMR |= EXTI_IMR_MR5;
    EXTI->RTSR |= EXTI_RTSR_TR5; // RISING edge trigger!
    EXTI->PR = EXTI_PR_PR5;
    EXTI_ClearITPendingBit(EXTI_Line5);

    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannel = EXTI9_5_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    // ==============================
    // 进入 STOP 模式
    // ==============================
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);

    // ==============================
    // 唤醒后执行（完全复用原逻辑）
    // ==============================

    // 恢复 PA5 为 floating input
    GPIOA->CRL &= ~0x0000F000;
    GPIOA->CRL |=  0x00004000;

    // 恢复时钟 to 72MHz
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));
    RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
    RCC->CFGR |= RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9;
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
    SystemCoreClock = 72000000;

    // ========== 初始化键盘 GPIO ==========
    RCC_APB2PeriphClockCmd(
        RCC_APB2Periph_GPIOA |
        RCC_APB2Periph_GPIOB |
        RCC_APB2Periph_GPIOC,
        ENABLE
    );

    // ROWs: PA0-PA5 as IPD
    GPIO_InitTypeDef gpio_init;
    gpio_init.GPIO_Pin = 
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | 
        GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    gpio_init.GPIO_Mode = GPIO_Mode_IPD;
    gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &gpio_init);

    // COLs on PB
    gpio_init.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &gpio_init);
    GPIO_ResetBits(GPIOB, gpio_init.GPIO_Pin);

    // COLs on PC: PC0-PC10
    uint16_t pc_col_pins = 
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
        GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |
        GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    gpio_init.GPIO_Pin = pc_col_pins;
    GPIO_Init(GPIOC, &gpio_init);
    GPIO_ResetBits(GPIOC, pc_col_pins);

    // 禁用 EXTI
    EXTI->IMR &= ~EXTI_IMR_MR5;
    EXTI->RTSR &= ~EXTI_RTSR_TR5;
    NVIC_DisableIRQ(EXTI9_5_IRQn);

    clear_keyboard_state();
		
		// 验证唤醒
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//    GPIOB->BSRR = GPIO_Pin_8;

    g_InDeepSleep = 0;
}

