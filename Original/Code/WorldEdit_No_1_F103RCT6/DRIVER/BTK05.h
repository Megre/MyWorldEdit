#ifndef __BTK05_H_
#define __BTK05_H_

//����Ĭ�ϲ����� ������ 9600�� 8 λ����λ�� 1 λֹͣλ�� ��У�飬 �����ء�
#define BTK05_URAT_Clock		RCC_APB2Periph_USART1
#define BTK05_UART				USART1
#define BTK05_URAT_GPIOPort		GPIOA
#define BTK05_URAT_RX_GPIOPin	GPIO_Pin_10
#define BTK05_URAT_TX_GPIOPin	GPIO_Pin_9
#define BTK05_URAT_BaudRate		9600
#define BTK05_UART_IRQn			USART1_IRQn


#define BTK05_ATMode_GPIOPort	GPIOA
#define BTK05_ATMode_GPIOPin	GPIO_Pin_6
#define BTK05_WAKEUP_GPIOPort	GPIOA
#define BTK05_WAKEUP_GPIOPin	GPIO_Pin_7
//*********************************************************************************************
//�������ݰ���ʽ  12���ֽ�
#define BTK05_CMD_BYTE1	0x0C
#define BTK05_CMD_BYTE2	0x00
#define BTK05_CMD_BYTE3	0xA1
#define BTK05_CMD_BYTE4	0x01
#define BTK05_CMD_BYTE6	0x00
extern unsigned char BTK05_ATKeyDataPack[12];
//BYTE5  �䶯ֵ��ALT��SHIFT��CTRL��GUI ����״ָ̬ʾ��
//BYTE5 ˵��:
//Bit  	Key
//0  	LEFT CTRL
//1  	LEFT SHIFT
//2  	LEFT ALT
//3  	LEFT GUI
//4  	RIGHT CTRL
//5  	RIGHT SHIFT
//6  	RIGHT ALT
//7  	RIGHT GUI

extern unsigned char BTK05_ConsumerPack[8];

enum BTK05_StatusTypedef
{
	BTK_SLEEP = 0,
	BTK_WAKE = 1,
	
};

extern enum BTK05_StatusTypedef BTK05_Status;
//*********************************************************************************************
//ATָ��	
//����ָ�����������ģʽ�²ſ��Է��ͣ� ���򲻻����κ���Ӧ�� ���� AT ָ��Իس����з���
//���� ����\r\n (0x0D 0x0A)�� ���ص�Ӧ��Ҳ�Իس����з�������

//-----------------------------------
//ģ��������״̬���߲��ɷ���״̬��ͨ�����ָ���ģ���������ƥ��״̬�����ָ���ɾ��֮ǰ
//��ƥ����Ϣ�������ڶ�������ƥ�䡣
#define BTK05_AT_ENPairMode			"AT+PAIR"	//����ƥ��ģʽ
//-----------------------------------
//ģ�������Ѿ�ƥ���������ͨ�����ָ����ƥ����Ϣ������ģ��Ϳ��Խ����µ���������ƥ�䡣
#define BTK05_AT_DeletePaired		"AT+UNPLUG"	//ɾ���Ѿ�ƥ�����Ϣ
//-----------------------------------
#define BTK05_AT_SLEEPMODE  		"AT+SLEEPMODE=1"//0 �����ߣ�������ʱ���Խ�������		1 �����Ƿ����ߣ��ܵ� PIO11 �Ŀ��ơ�
//-----------------------------------
#define BTK05_AT_RESET				"AT+RESET"

//return 1  AT���óɹ�
//return 0  AT����ʧ��
unsigned char BTK05_UART_SendATCmd(unsigned char* ATBuffer);


//���ͼ������ݰ�
void BTK05_UART_SendKeyData(unsigned char* KeyDataBuffer, unsigned char byte_lenth);


//-----------------------------------
//1�� �ⲿ��������PIO11 �ߵ�ƽ��
//2�� �� PIO11 �ߵ�ƽ��������ʱ 10ms ���ⲿ��������ʼ���� UART ���ݡ�
//3�� �ⲿ�������޷�������ʱ ��ʱ 10ms���� PIO11 �͵�ƽ���Խ���ʡ��ģʽ
void BTK05_Wake(void);
void BTK05_Sleep(void);
unsigned char BTK05_ATMode(void);//����ATָ��ģʽ
unsigned char BTK05_KEYMode(void);//�˳�ATָ��ģʽ
void BTK05_PairMode(void);//����ƥ��ģʽ
void BTK05_RESET(void);//��λ
void BTK05_DeleteConnectInfo(void);//ɾ�� �Ѿ����ӵ�������Ϣ
void BTK05_LowEnerageMode(void);//����ʡ��ģʽ


void BTK05_WAKEUP_Init(void);//WAKEIO �� ��ʼ�� 
void BTK05_ATMode_Init(void);//AT IO �� ��ʼ�� 
void BTK05_Init(void);//BTK����05��ʼ�� 
void BTK05_UART_Init(void);//���ڳ�ʼ��
//����1�жϷ������
void USART1_IRQHandler(void)  ;



#endif


