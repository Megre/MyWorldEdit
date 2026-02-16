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
	  if(g_InDeepSleep) return;
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
    
    // 将 COL4 (PC6) 设为输出 HIGH
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIOC->CRL &= ~(0xF << 24);
    GPIOC->CRL |= (0x2 << 24); // PP Output
    GPIOC->ODR |= GPIO_Pin_6;  // Output HIGH!

    // 配置 PA5 (ROW5) 为浮空输入 + EXTI 上升沿
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
    // 唤醒后执行
    // ==============================

    // 恢复 PA5 为 floating input (your scan code will handle it)
    GPIOA->CRL &= ~0x0000F000;
    GPIOA->CRL |=  0x00004000;       // Floating Input

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
    // 使能 GPIO 时钟
    RCC_APB2PeriphClockCmd(
        RCC_APB2Periph_GPIOA |  // Rows (PA0-PA5)
        RCC_APB2Periph_GPIOB |  // Cols (PB12-PB15)
        RCC_APB2Periph_GPIOC,   // Cols (PC0-PC11)
        ENABLE
    );

    // 初始化 ROWs: 下拉输入 (匹配 myKeyBoard.c)
    GPIO_InitTypeDef gpio_init;
    gpio_init.GPIO_Pin = 
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | 
        GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5; // PA0-PA5
    gpio_init.GPIO_Mode = GPIO_Mode_IPD;
    gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &gpio_init);

    // 初始化 COLs on GPIOB (PB12-PB15)
    gpio_init.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &gpio_init);
    GPIO_ResetBits(GPIOB, gpio_init.GPIO_Pin); // 默认输出低

    // 初始化 COLs on GPIOC (PC0-PC11)
    uint16_t pc_col_pins = 
        GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
        GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |
        GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    gpio_init.GPIO_Pin = pc_col_pins;
    GPIO_Init(GPIOC, &gpio_init);
    GPIO_ResetBits(GPIOC, pc_col_pins); // 默认输出低

    // 禁用 EXTI（避免与轮询扫描冲突）
    EXTI->IMR &= ~EXTI_IMR_MR5;
    EXTI->RTSR &= ~EXTI_RTSR_TR5;
    NVIC_DisableIRQ(EXTI9_5_IRQn);

    // 清除按键状态
    clear_keyboard_state();

    // 验证唤醒
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//    GPIOB->BSRR = GPIO_Pin_8;
		
		g_InDeepSleep = 0;
}
