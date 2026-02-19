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
#include "stm32f10x.h"
#include "misc.h"

static uint8_t g_InDeepSleep = 0;  // 记录是否处于休眠状态

/**
 * @brief 进入STOP模式，任意按键唤醒
 * @note 硬件连接：行PA0-PA5，列PB12-PB15 + PC0-PC10，
 *			 二极管阳极接列、阴极接行。
 *       睡眠时所有列输出高，行下拉输入并使能上升沿中断；
 *       验证引脚PB8在睡眠时输出低，唤醒后拉高
 */
void Enter_Deep_Sleep(void)
{
    if (g_InDeepSleep) return;
    g_InDeepSleep = 1;

    // ----- 配置验证引脚 PB8 为推挽输出低 -----
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef gpio_pb8;
    gpio_pb8.GPIO_Pin = GPIO_Pin_8;
    gpio_pb8.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_pb8.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &gpio_pb8);
    GPIO_ResetBits(GPIOB, GPIO_Pin_8); // 输出低

    __enable_irq();

    // ========== 配置所有列引脚为推挽输出高 ==========
    // 使能时钟
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;

		// 列引脚：全部推挽输出高（用于唤醒）
		// PB12-PB15 (CRH[31:16])
		GPIOB->CRH &= ~(0xFFFFU << 16);
		GPIOB->CRH |= (0x2222U << 16);
		GPIOB->ODR |= GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

		// PC0-PC7 (CRL)
		GPIOC->CRL = 0x22222222U; // 全部设为推挽输出2MHz

		// PC8-PC10 (CRH[11:0])
		GPIOC->CRH &= ~0xFFFU;    // 清除低12位
		GPIOC->CRH |= 0x222U;     // PC8=0x2, PC9=0x2, PC10=0x2

		// 设置 PC0-PC10 输出高
		GPIOC->ODR |= (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
									 GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |
									 GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);

		// 行引脚：PA0-PA5 下拉输入
		// CRL: PA0-PA5 = 0x8 each
		GPIOA->CRL = (GPIOA->CRL & 0xFF000000) | 0x888888U;
		GPIOA->ODR &= ~(GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |
										GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);

    // ========== 配置 EXTI 中断 ==========
    // 清除原有配置
    EXTI->IMR &= ~(EXTI_IMR_MR0 | EXTI_IMR_MR1 | EXTI_IMR_MR2 | EXTI_IMR_MR3 |
                   EXTI_IMR_MR4 | EXTI_IMR_MR5);
    EXTI->RTSR &= ~(EXTI_RTSR_TR0 | EXTI_RTSR_TR1 | EXTI_RTSR_TR2 | EXTI_RTSR_TR3 |
                    EXTI_RTSR_TR4 | EXTI_RTSR_TR5);
    EXTI->PR = EXTI_PR_PR0 | EXTI_PR_PR1 | EXTI_PR_PR2 | EXTI_PR_PR3 |
               EXTI_PR_PR4 | EXTI_PR_PR5; // 清挂起

    // 设置 EXTI 线映射到 PA0-PA5
    AFIO->EXTICR[0] = 0x0000; // PA0,PA1,PA2,PA3
    AFIO->EXTICR[1] &= ~0x00FF; // 清除 EXTI4-5 的位，设为 0 即 PA4,PA5

    // 使能上升沿触发
    EXTI->RTSR |= EXTI_RTSR_TR0 | EXTI_RTSR_TR1 | EXTI_RTSR_TR2 | EXTI_RTSR_TR3 |
                  EXTI_RTSR_TR4 | EXTI_RTSR_TR5;
    EXTI->IMR |= EXTI_IMR_MR0 | EXTI_IMR_MR1 | EXTI_IMR_MR2 | EXTI_IMR_MR3 |
                 EXTI_IMR_MR4 | EXTI_IMR_MR5;

    // 再次清除挂起
    EXTI_ClearITPendingBit(EXTI_Line0 | EXTI_Line1 | EXTI_Line2 | EXTI_Line3 |
                           EXTI_Line4 | EXTI_Line5);

    // 配置 NVIC 中断
    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;

    nvic.NVIC_IRQChannel = EXTI0_IRQn;   NVIC_Init(&nvic);
    nvic.NVIC_IRQChannel = EXTI1_IRQn;   NVIC_Init(&nvic);
    nvic.NVIC_IRQChannel = EXTI2_IRQn;   NVIC_Init(&nvic);
    nvic.NVIC_IRQChannel = EXTI3_IRQn;   NVIC_Init(&nvic);
    nvic.NVIC_IRQChannel = EXTI4_IRQn;   NVIC_Init(&nvic);
    nvic.NVIC_IRQChannel = EXTI9_5_IRQn; NVIC_Init(&nvic); // 用于 EXTI5

    // ========== 将无关引脚设为模拟输入（AIN）以降低功耗 ==========
		{
			// 使能所有需要的时钟（包括 AFIO！）
			RCC_APB2PeriphClockCmd(
					RCC_APB2Periph_GPIOA |
					RCC_APB2Periph_GPIOB |
					RCC_APB2Periph_GPIOC |
					RCC_APB2Periph_AFIO, 
					ENABLE
			);

			GPIO_InitTypeDef gpio_ain;
			gpio_ain.GPIO_Mode = GPIO_Mode_AIN;
			gpio_ain.GPIO_Speed = GPIO_Speed_2MHz;

			// PA6-PA15 → AIN
			// 会影响蓝牙数据传输造成打不出字
//    gpio_ain.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 |
//                            GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 |
//                            GPIO_Pin_14 | GPIO_Pin_15;
//    GPIO_Init(GPIOA, &gpio_ain);

			// PB: 除 PB8,12-15 外 → AIN
			gpio_ain.GPIO_Pin = GPIO_Pin_All & ~(GPIO_Pin_8 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
			GPIO_Init(GPIOB, &gpio_ain);

			// PC11-PC15 → AIN
			gpio_ain.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
			GPIO_Init(GPIOC, &gpio_ain);
		}

    // ========== 关闭 HSE，切换到 HSI ==========
    RCC->CFGR &= ~RCC_CFGR_SW; // 切换到 HSI
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);
    RCC->CR &= ~RCC_CR_HSEON; // 关闭 HSE

    // ========== 进入 STOP 模式 ==========
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

		// ========== 恢复键盘 GPIO 到正常工作状态 ==========
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
		
		// PB12-PB15: 先写 ODR=0，再设为推挽输出
		GPIOB->ODR &= ~(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		{
				GPIO_InitTypeDef gpio_init;
				gpio_init.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
				gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
				gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
				GPIO_Init(GPIOB, &gpio_init);
			GPIO_ResetBits(GPIOB, gpio_init.GPIO_Pin);
		}

		// PC0-PC10: 先写 ODR=0，再设为推挽输出
		uint16_t pc_col_pins = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
													 GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 |
													 GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
		GPIOC->ODR &= ~pc_col_pins;
		{
				GPIO_InitTypeDef gpio_init;
				gpio_init.GPIO_Pin = pc_col_pins;
				gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
				gpio_init.GPIO_Speed = GPIO_Speed_2MHz;
				GPIO_Init(GPIOC, &gpio_init);
			  GPIO_ResetBits(GPIOC, pc_col_pins);
		}

    // ========== 禁用所有 EXTI 中断 ==========
		// 先清除挂起（此时 IMR 还是使能的！）
		EXTI->PR = EXTI_PR_PR0 | EXTI_PR_PR1 | EXTI_PR_PR2 | EXTI_PR_PR3 |
							 EXTI_PR_PR4 | EXTI_PR_PR5;
    EXTI->IMR &= ~(EXTI_IMR_MR0 | EXTI_IMR_MR1 | EXTI_IMR_MR2 | EXTI_IMR_MR3 |
                   EXTI_IMR_MR4 | EXTI_IMR_MR5);
    EXTI->RTSR &= ~(EXTI_RTSR_TR0 | EXTI_RTSR_TR1 | EXTI_RTSR_TR2 | EXTI_RTSR_TR3 |
                    EXTI_RTSR_TR4 | EXTI_RTSR_TR5);
    NVIC_DisableIRQ(EXTI0_IRQn);
    NVIC_DisableIRQ(EXTI1_IRQn);
    NVIC_DisableIRQ(EXTI2_IRQn);
    NVIC_DisableIRQ(EXTI3_IRQn);
    NVIC_DisableIRQ(EXTI4_IRQn);
    NVIC_DisableIRQ(EXTI9_5_IRQn);

    clear_keyboard_state();

    // 唤醒后拉高 PB8 作为验证
    GPIOB->BSRR = GPIO_Pin_8;

    g_InDeepSleep = 0;
}

void Enter_Deep_Sleep_IPD(void)
{
    if (g_InDeepSleep) return;
    g_InDeepSleep = 1;

    // 拉低PB8作为唤醒前标志（注意：后续AIN设置会排除PB8，使其保持输出）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = GPIO_Pin_8;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &gpio);
    GPIO_ResetBits(GPIOB, GPIO_Pin_8); // 输出低

    __enable_irq();

    // ========== 配置唤醒 GPIO ==========
    // 唤醒列：PC7 设为推挽输出高
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIOC->CRL &= ~(0xFU << 28);     // 清除 PC7 配置（位[31:28]）
    GPIOC->CRL |= (0x2 << 28);       // 推挽输出 2MHz (0x2 = MODE=10, CNF=00)
    GPIOC->ODR |= GPIO_Pin_7;        // 输出高

    // 唤醒行：PA5 保持下拉输入（IPD）并配置EXTI上升沿
    // 注意：正常工作模式已经是IPD，这里只需确保模式不变，并配置EXTI
    // 但为了保险，显式配置为IPD（0x8表示CNF=10, MODE=00，且ODR位为0）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    GPIOA->CRL &= ~(0xF << 20);      // 清除 PA5 配置（位[23:20]）
    GPIOA->CRL |= (0x8 << 20);       // 下拉输入 (0x8 = CNF=10, MODE=00)
    GPIOA->ODR &= ~GPIO_Pin_5;       // 确保下拉（ODR=0）

    // ========== 配置 EXTI ==========
    AFIO->EXTICR[1] = (AFIO->EXTICR[1] & ~0xF0) | 0x00; // PA5 映射到 EXTI5
    EXTI->IMR |= EXTI_IMR_MR5;
    EXTI->RTSR |= EXTI_RTSR_TR5;     // 上升沿触发
    EXTI->PR = EXTI_PR_PR5;          // 清除挂起标志
    EXTI_ClearITPendingBit(EXTI_Line5);

    NVIC_InitTypeDef nvic = {
        .NVIC_IRQChannel = EXTI9_5_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 0,
        .NVIC_IRQChannelCmd = ENABLE
    };
    NVIC_Init(&nvic);

    // ========== 将无关引脚设为模拟输入（AIN）以降低功耗 ==========
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

        GPIO_InitTypeDef gpio_ain;
        gpio_ain.GPIO_Speed = GPIO_Speed_2MHz;
        gpio_ain.GPIO_Mode = GPIO_Mode_AIN;

        // PB: 除 PB8 外全部设为 AIN（保留PB8作为输出低）
        gpio_ain.GPIO_Pin = GPIO_Pin_All & ~GPIO_Pin_8;
        GPIO_Init(GPIOB, &gpio_ain);

        // PC: 除 PC7 外设为 AIN
        gpio_ain.GPIO_Pin = GPIO_Pin_All & ~GPIO_Pin_7;
        GPIO_Init(GPIOC, &gpio_ain);

        // 重新确认 PC7 状态（防止 GPIO_Init 覆盖）
        GPIOC->CRL &= ~(0xFU << 28);
        GPIOC->CRL |= (0x2 << 28);    // 推挽输出 2MHz
        GPIOC->ODR |= GPIO_Pin_7;     // HIGH

        // 重新确认 PB8 状态（保持输出低）
        GPIOB->CRH &= ~(0xF << 0); // 清除 PB8 配置
			  GPIOB->CRH |= (0x2 << 0);  // 设置为推挽输出 2MHz

        GPIO_InitTypeDef gpio_pb8;
        gpio_pb8.GPIO_Pin = GPIO_Pin_8;
        gpio_pb8.GPIO_Mode = GPIO_Mode_Out_PP;
        gpio_pb8.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_Init(GPIOB, &gpio_pb8);
        GPIO_ResetBits(GPIOB, GPIO_Pin_8); // 保持低
    }

    // ========== 关闭 HSE，切换到 HSI ==========
    RCC->CFGR &= ~RCC_CFGR_SW; // 切换到 HSI
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

    // ========== 恢复键盘 GPIO 为正常工作模式 ==========
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

    // PC0-PC10: PP Output LOW
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

    // 唤醒后拉高PB8作为标志
    GPIOB->BSRR = GPIO_Pin_8;

    g_InDeepSleep = 0;
}

void Enter_Deep_Sleep_Menu(void)
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
	  // PA5+PC7 = Menu键
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

    // PC0-PC10: PP Output LOW
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

