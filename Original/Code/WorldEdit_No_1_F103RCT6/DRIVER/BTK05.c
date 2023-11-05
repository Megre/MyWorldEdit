/************************************************************************************
*  Copyright (c), 2019, LXG.
*
* FileName		:BTK05.c
* Author		:firestaradmin
* Version		:1.0
* Date			:2019.
* Description	:��������ģ��Ĺ���
* History		:

2019.12.13		������ATָ��Ͳ�����OK  Ū�˰���Ĵ��ڷ��ͣ���Ϊ����ģ��Ĵ��ڽ���һ���ַ�����Ҫ��ʱһ�ᣬ��Ȼ��Ӧ��������
*
*
*************************************************************************************/
#include "main.h"
#include "BTK05.h"

unsigned char BTK05_ATKeyDataPack[12] = {
							BTK05_CMD_BYTE1	,
							BTK05_CMD_BYTE2	,
							BTK05_CMD_BYTE3	,
							BTK05_CMD_BYTE4	,
							0x00 ,
							BTK05_CMD_BYTE6	,
							0x00 ,
							0x00 ,
							0x00 ,
							0x00 ,
							0x00 ,
							0x00 		};

unsigned char ATReturnSuccessedFlag = 0;//AT���سɹ���־λ
unsigned char RxBuffer[50] ;
unsigned char RxBuffer_Tail = 0;
unsigned char RxBuffer_OK[10] ;//����ATָ��ص�OK
unsigned char RxBuffer_OK_Tail = 0;

unsigned char BTK05_ConsumerPack[8] = 	{	//Consumer��ֵ���ݰ�  �����Ӽ�֮��Ĺ��ܼ�
								0x08,
								0x00,
								0xA1,
								0x03,
								0x00,
								0x00,
								0x00,
								0x00,
	
										};							
							
enum BTK05_StatusTypedef BTK05_Status = BTK_SLEEP;					


void BTK05_UART_SendChar(unsigned char txChar);

void BTK05_Init()
{
	BTK05_UART_Init();
	BTK05_WAKEUP_Init();
	BTK05_ATMode_Init();
	BTK05_LowEnerageMode();//����ʡ��ģʽ
}


//return 1  AT���óɹ�
//return 0  AT����ʧ��
unsigned char BTK05_UART_SendATCmd(unsigned char* ATBuffer)
{
	unsigned char timeOutTemp = 0;
	while(*ATBuffer != '\0')
	{
		BTK05_UART_SendChar(*ATBuffer++);
		DelayUs(500);
	}
	BTK05_UART_SendChar(0x0D);
	DelayUs(500);
	BTK05_UART_SendChar(0x0A);
	DelayUs(500);
	while(!ATReturnSuccessedFlag)//�ȴ�����
	{
		DelayMs(1);
		timeOutTemp++;
		if(timeOutTemp == 200)return 0;//AT����ʧ��  TimeOut
	}
	
	if(RxBuffer_OK[0] == 'O' && RxBuffer_OK[1] == 'K')
	{
		ATReturnSuccessedFlag = 0;
		RxBuffer_OK_Tail = 0;
		return 1;//AT���óɹ�
	}
	ATReturnSuccessedFlag = 0;
	RxBuffer_OK_Tail = 0;
	return 0;//AT����ʧ��
}

void BTK05_UART_SendKeyData(unsigned char* KeyDataBuffer, unsigned char byte_lenth)
{
	unsigned char i;
	for(i = 0; i < byte_lenth; i++)
	{
		BTK05_UART_SendChar(*(KeyDataBuffer+i));
	}
}

void BTK05_UART_SendChar(unsigned char txChar)
{

	USART_SendData(BTK05_UART, txChar);	
	while(USART_GetFlagStatus(BTK05_UART, USART_FLAG_TC) == RESET);
	USART_ClearFlag(BTK05_UART,USART_FLAG_TC);

	
}


void BTK05_UART_SendString(unsigned char* txBuffer)
{
	//unsigned char txCharTemp;
	while(*txBuffer++ != '\0')
	{
		BTK05_UART_SendChar(*txBuffer);
	}
}


void BTK05_PairMode()//����ƥ��ģʽ
{
	if(BTK05_ATMode())
	{
		BTK05_UART_SendATCmd((unsigned char*)BTK05_AT_ENPairMode);
		DelayMs(500);
		BTK05_KEYMode();
	}
}

void BTK05_LowEnerageMode()//����ʡ��ģʽ
{
	if(BTK05_ATMode())
	{
		BTK05_UART_SendATCmd((unsigned char*)BTK05_AT_SLEEPMODE);
		DelayMs(500);
		BTK05_KEYMode();
	}
}
void BTK05_RESET()//��λ
{
	if(BTK05_ATMode())
	{
		BTK05_UART_SendATCmd((unsigned char*)BTK05_AT_RESET);
		DelayMs(500);
		BTK05_KEYMode();
	}
}

void BTK05_DeleteConnectInfo()//ɾ�� �Ѿ����ӵ�������Ϣ
{
	if(BTK05_ATMode())
	{
		BTK05_UART_SendATCmd((unsigned char*)BTK05_AT_DeletePaired);
		DelayMs(500);
		BTK05_KEYMode();
	}
}


//����BTK05
void BTK05_Wake()
{
	GPIO_SetBits(BTK05_WAKEUP_GPIOPort,BTK05_WAKEUP_GPIOPin);
	BTK05_Status = BTK_WAKE;
	DelayMs(20);
	
}
//����BTK05
void BTK05_Sleep()
{
	GPIO_ResetBits(BTK05_WAKEUP_GPIOPort,BTK05_WAKEUP_GPIOPin);
	BTK05_Status = BTK_SLEEP;
	DelayMs(20);
	
}

//����ATָ��ģʽ
unsigned char BTK05_ATMode()
{

	GPIO_SetBits(BTK05_ATMode_GPIOPort,BTK05_ATMode_GPIOPin);
	DelayMs(400);
	GPIO_ResetBits(BTK05_ATMode_GPIOPort,BTK05_ATMode_GPIOPin);
	return BTK05_UART_SendATCmd((unsigned char*)"AT");
}


//�˳�ATָ��ģʽ
unsigned char BTK05_KEYMode()
{
	 return BTK05_UART_SendATCmd((unsigned char*)"AT+EXIT");
}
















//BTK05_UART�����жϷ������
void USART1_IRQHandler(void)                    
{
	unsigned char temp;
    if(USART_GetITStatus(BTK05_UART, USART_IT_RXNE) != RESET)  //�����ж�
    {
		temp = USART_ReceiveData(BTK05_UART);
		RxBuffer_OK[RxBuffer_OK_Tail++] = temp;
		
		if(temp == '\n')
		{
			ATReturnSuccessedFlag = 1;
		}		
    } 

	
}





//********************************************************************************************************
//========================================��ʼ��=======================================================

//�������ų�ʼ��
void BTK05_WAKEUP_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = BTK05_WAKEUP_GPIOPin; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    
	GPIO_Init(BTK05_WAKEUP_GPIOPort, &GPIO_InitStructure); 
	
	GPIO_SetBits(BTK05_WAKEUP_GPIOPort,BTK05_WAKEUP_GPIOPin);
	
}
//ATģʽ���ų�ʼ��
//ƽʱ�͵�ƽ���ߵ�ƽ�����������ģʽ������ͨ�� AT ָ�����ò�����
void BTK05_ATMode_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = BTK05_ATMode_GPIOPin; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;    
	GPIO_Init(BTK05_WAKEUP_GPIOPort, &GPIO_InitStructure); 
	
	GPIO_ResetBits(BTK05_ATMode_GPIOPort,BTK05_ATMode_GPIOPin);
	
}



void BTK05_UART_Init()
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(BTK05_URAT_Clock, ENABLE);
	USART_DeInit(BTK05_UART);

	//USART1�˿�����
	//UASART_TX   PA9
	GPIO_InitStructure.GPIO_Pin = BTK05_URAT_TX_GPIOPin; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //�����������
	GPIO_Init(BTK05_URAT_GPIOPort, &GPIO_InitStructure); //��ʼ��PA9
	//USART1_RX      PA10
	GPIO_InitStructure.GPIO_Pin = BTK05_URAT_RX_GPIOPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(BTK05_URAT_GPIOPort, &GPIO_InitStructure);  //��ʼ��PA10

	//USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = BTK05_URAT_BaudRate;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //�շ�ģʽ     
	USART_Init(BTK05_UART, &USART_InitStructure); //��ʼ������1

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = BTK05_UART_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;        //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);    //����ָ���Ĳ�����ʼ��VIC�Ĵ���


	USART_ClearITPendingBit(BTK05_UART,USART_IT_TC);
	USART_ClearITPendingBit(BTK05_UART,USART_IT_TXE);//��������жϱ�־λ
	USART_ITConfig(BTK05_UART, USART_IT_RXNE, ENABLE);//��������ж�
	//USART_ITConfig(BTK05_UART, USART_IT_TXE, ENABLE);
	USART_ClearFlag(BTK05_UART,USART_FLAG_TC);
	
	USART_Cmd(BTK05_UART, ENABLE);  //ʹ��BTK05_UART����
}


//********************************************************************************************************





