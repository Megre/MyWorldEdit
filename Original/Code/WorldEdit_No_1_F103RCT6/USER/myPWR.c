#include "myPWR.h"

void EXTI_Init(void)
{
	
}

void RCC_Configuration(void)
{
	sysInit();
}

void myPWR_EnterStopMode(void)
{
	RCC_APB2PeriphResetCmd(0X01FC, DISABLE);//��λ��������
	
	PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);//�͹��ģ��ȴ��ⲿ�ж�
	RCC_Configuration();  // ���Ѻ����½���ʱ������
	
	
}

void myPWR_PWR_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);	//ʹ��PWR����ʱ��
	
}












