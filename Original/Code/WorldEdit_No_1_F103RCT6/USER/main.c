

#include "main.h"

void TIM2_Int_Init(u16 arr,u16 psc);
void TIM3_CH3_PWM_init(u16 arr,u16 psc);
void myUSB_Init(void);
void sysInit(void);
static unsigned short sleepTime1SCounter = 0;
unsigned char sleepTime50MsCounter = 0;
unsigned char LED_breath_Flag = 0;
unsigned char LED_LOGOBreath_Flag = 0;
unsigned char LED_LOGOENBreath_Flag = 0;
unsigned char system_Status = 1;  //1:�����У�0��������
unsigned char g_Flag = 0;
uint8_t ledLogoPWM = 80;
int8_t ledLogoPWMDelt = 0;
bool g_USBModeFlag = FALSE;


int main()
{
	//sysInit();
	BTK05_Wake();//����BTK05
	

	while(1)
	{ 
		if(g_USBModeFlag)//USBģʽ��
		{
			if(sleepTime1SCounter <= 1000)
			{
				myKeyBoard_ScanKeyAndUpdataATBuffer();//�����¼�����
				if(g_myKeyBoard_DataWaitForUploadFlag == 1)
				{
					sleepTime1SCounter = 0;
					g_myKeyBoard_DataWaitForUploadFlag = 0;
					if(bDeviceState == CONFIGURED)//����������� USB
						Keyboard_Send(BTK05_ATKeyDataPack+4);
					//GPIO_SetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
					
				}
			}
			else if(system_Status == 0)
			{
				myKeyBoard_ScanKeyAndUpdataATBuffer();//�����¼�����
				if(g_myKeyBoard_DataWaitForUploadFlag == 1)
				{
					g_myKeyBoard_DataWaitForUploadFlag = 0;
					if(bDeviceState == CONFIGURED)//����������� USB
						Keyboard_Send(BTK05_ATKeyDataPack+4);
					//GPIO_SetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
					system_Status = 1;
					TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx	
					sleepTime1SCounter = 0;
					if(LED_Status)	
						LED_WakeUp();	
				}
			}
			else if(sleepTime1SCounter > 1000)
			{
				TIM_Cmd(TIM2, DISABLE);  //ʧ��TIMx		
				system_Status = 0;
				LED_GoToSleep();
			}
		}
		else//����ģ��ģʽ
		{
			//����������߼�ʱ��С��400���Ҽ��̴������ŵ�״̬
			if(sleepTime1SCounter <= 400 && BTK05_Status == BTK_WAKE)
			{
				myKeyBoard_ScanKeyAndUpdataATBuffer();//�����¼�����
				if(g_myKeyBoard_DataWaitForUploadFlag == 1)
				{
					g_myKeyBoard_DataWaitForUploadFlag = 0;
					//GPIO_ResetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
					BTK05_UART_SendKeyData(BTK05_ATKeyDataPack,12);
					sleepTime1SCounter = 0;

					if(ATKeyControlByte5 != 0) 
					{
						GPIO_SetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
					}
					else
					{
						GPIO_ResetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
					}
				}
			}
			//���������������״̬
			else if(BTK05_Status == BTK_SLEEP)
			{
				myKeyBoard_ScanKeyAndUpdataATBuffer();
				if(g_myKeyBoard_DataWaitForUploadFlag == 1)
				{
					system_Status = 1;
					BTK05_Wake();//����BTK05
					TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx	
					sleepTime1SCounter = 0;
					g_myKeyBoard_DataWaitForUploadFlag = 0;
					if(LED_Status)	
						LED_WakeUp();
					BTK05_UART_SendKeyData(BTK05_ATKeyDataPack,12);
				}
			}
			//��� �������߼�ʱ������600   ��600Sû�а����κΰ�����Ȼ���̽�������״̬
			else if(sleepTime1SCounter > 400)   
			{
				//��������ģʽ...
				BTK05_Sleep();//����BTK05
				TIM_Cmd(TIM2, DISABLE);  //ʧ��TIMx		
				system_Status = 0;
				LED_ESCOFF();	 
			}
		}
		
		if(LED_BreathEfectFlag && LED_breath_Flag)
		{
			LED_BreathProcess();
			LED_breath_Flag = 0;
		}
//		if(LED_LOGOBreath_Flag  && LED_LOGOENBreath_Flag)//logo�����ƴ����־
//		{
//			TIM_SetCompare3(TIM3, ledLogoPWM);
//			if(ledLogoPWMDelt == 0)
//			{
//				ledLogoPWM --;
//				if(ledLogoPWM <= 30)
//					ledLogoPWMDelt = 1;
//			}
//			else
//			{
//				ledLogoPWM ++;
//				if(ledLogoPWM == 98)
//					ledLogoPWMDelt = 0;
//			}
//			LED_LOGOBreath_Flag = 0;

//		}
			
	}

}


////��ʱ���жϷ������
void TIM2_IRQHandler(void)   //TIM�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM�����жϷ������
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
				
			sleepTime50MsCounter++;
			LED_LOGOBreath_Flag = 1;
			//LED_breath_Timer50ms++;
			if(sleepTime50MsCounter == 20)	
			{
				
				sleepTime50MsCounter = 0;                   
				sleepTime1SCounter++;
				
			}
			if(sleepTime50MsCounter % 4 == 0)
					LED_breath_Flag = 1;
			
			
		}
}


void sysInit()
{
	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOB);
	GPIO_DeInit(GPIOC);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	DelayInit();
	
	
	myKeyBoard_GPIO_Init();
	
	
	BTK05_Init();
	
	
	LED_LOGO_GPIO_Init();
	LED_I2C_Configuration();
	LED_HT16K33_Init();//��ʼ��оƬ
	
	
	
	//TIM3_CH3_PWM_init(100,0);
	TIM2_Int_Init(1000,3600);//50msһ���ж�
	myUSB_Init();
}



//ͨ�ö�ʱ��2�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//һ���жϵ�ʱ��Ϊt��t = (arr * psc / APB1*2) * 1000 ms
void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM�ж�,��������ж�
 
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ���
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ���
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx					 
}


void USB_Mode(void)
{

	g_USBModeFlag = TRUE;	
	
	//BTK05��������ģʽ...
	BTK05_Sleep();//����BTK05
	sleepTime1SCounter = 0;
	TIM_Cmd(TIM2, ENABLE);  		
	//system_Status = 1;
	//LED_GoToSleep();
	//GPIO_SetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
}

void BLUETEETH_Mode(void)
{
 
	g_USBModeFlag = FALSE;	
	
	BTK05_Wake();//����BTK05
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx	
	sleepTime1SCounter = 0;
	//GPIO_ResetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
}


void myUSB_Init(void)
{
	USB_Port_Set(1);	//����USB����
	//USB����
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();	 
}


void TIM3_CH3_PWM_init(u16 arr,u16 psc)
{
    //����TIM3
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//ע��ṹ������������ں����Ŀ�ͷ
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period=arr;
    TIM_TimeBaseStructure.TIM_Prescaler=psc;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);

    //����TIM3 Channel3 PWM

    TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
    TIM_OC3Init(TIM3,&TIM_OCInitStructure);//ע��˴��ĺ��������Լ���������ڲ���

    //����GPIO�ڣ��������óɸ��ù���

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
    //��TIM3������ӳ�䵽PB5
    //GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);

    //ʹ��TIM3ʱ��
    TIM_Cmd(TIM3,DISABLE);
}

//void LED_LOGO_FLASH_3TIMES()
//{
//	
////------------------------------------------------------
//	

//}


