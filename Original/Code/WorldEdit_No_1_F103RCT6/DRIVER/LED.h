#ifndef __LED_H_
#define __LED_H_
#include "main.h"
#define LED_LOGO_GPIOClock		RCC_APB2Periph_GPIOB
#define LED_LOGO_GPIOPort		GPIOB
#define LED_LOGO_GPIOPin		GPIO_Pin_0

#define LED_HTK_I2C				I2C1
#define LED_HTK_PIN_GPIOPort	GPIOB
#define LED_HTK_SDA_GPIOPin		GPIO_Pin_7
#define LED_HTK_SCL_GPIOPin		GPIO_Pin_6

 



//HTK��ַ��0x1110 0000   ;1 1 1 0 A2 A1 A0 R/W B
//�� 	0x1110 0001 B
//д 	0x1110 0000 B
//�� A2~A0  ����ʱ�� A2~A0  ������Ϊ ��0�� 
#define LED_HTK_Address_Base	0xE0
#define LED_HTK_Address_Wirte	LED_HTK_Address_Base | 0x00
#define LED_HTK_Address_Read	LED_HTK_Address_Base | 0x01


#define LED_HTK_CMD_START			0x21//����оƬʱ��
#define LED_HTK_CMD_SLEEP			0x20//�ر�оƬʱ��


//����λ��������A0~A3������������ַָ�����ڶ��� 16 ����ʾRAM ��ַ֮һ
//����ʾ���ݼĴ�����ַ An �ķ�Χ�� 0x00H~ 0x0FH��������洢����ַ 0x0FH ʱ����ַָ�뷵��0x00H��
#define LED_HTK_CMD_SetRamAddr		0x00   //����ram��ַָ��Ϊ0x00

#define LED_HTK_CMD_DisplayOff		0x80	
#define LED_HTK_CMD_DisplayOn		0x81
#define LED_HTK_CMD_SetROWOut	 	0xA0 //����λROW ���ģʽ
#define LED_HTK_CMD_SetPWM100		0xEF //�������ռ�ձ�Ϊ100


// 16��8 λ��̬ RAM ���ڴ洢 LED ��ʾ����
//COM  	ROW0-7  ROW8-15
//COM0 	00H 	01H
//COM1 	02H 	03H
//COM2 	04H 	05H
//COM3 	06H 	07H
//COM4 	08H 	09H
//COM5 	0AH 	0BH
//COM6 	0CH 	0DH
//COM7 	0EH 	0FH

//��·������6��COM��16��ROW   ��12���ֽڱ�ʾ
//6��16��  12���ֽ�
extern unsigned char LED_Ram[6][2];
extern unsigned char LED_BreathEfectFlag;
extern unsigned char LED_Brightness;
extern unsigned char LED_FlashSwitchFlag;
extern unsigned char LED_Status ;
//extern unsigned char LED_FlashSwitchFlag;

//0:�ر���˸   1����˸2Hz  2��1Hz  3��0.5Hz
typedef enum 
{
	LED_FLASH_OFF = 0,
	LED_FLASH_2Hz = 1,
	LED_FLASH_1Hz = 2,
	LED_FLASH_HalfHz = 3
	
}LED_FlashPreqTypedef;




void LED_DrawPoint(unsigned char x, unsigned char y, unsigned char color);
void LED_RamClearWith(unsigned char ledSwitch);

void LED_FreashRam(void);//��ģ���Դ�����д��HT16K33оƬ
void LED_SetFlash(void);//��˸����
void LED_SetBreathEfect(void);//�����ƿ���
void LED_Off(void);//�ص�
void LED_Mode1(void);//ȫ��
void LED_Mode2(void);//��WASD ��������
void LED_Mode3(void);//
void LED_ESCOFF(void);

void LED_BreathProcess(void);//�����ƴ�����
void LED_AllLightOn(void);//test
void LED_GoToSleep(void);//�ر�ʱ��
void LED_WakeUp(void);//����ʱ��
void LED_SetDisplay(unsigned char displaySwitch, LED_FlashPreqTypedef displayFlashPreq)	;//��ʾ����
void LED_SetBrightness(unsigned char brightness);//����ռ�ձ� ��������


void LED_HT16K33_Init(void);//��ʼ��оƬ
void LED_LOGO_GPIO_Init(void);
//void I2C_WriteByte(uint8_t addr,uint8_t data);
void LED_I2C_Configuration(void);



//********************************************************************************************************
//IIC	
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}
#define READ_SDA   GPIO_ReadInputDataBit(LED_HTK_PIN_GPIOPort, LED_HTK_SDA_GPIOPin)  //����SDA 
#define IIC_SCL_H	GPIO_SetBits(LED_HTK_PIN_GPIOPort, LED_HTK_SCL_GPIOPin)
#define IIC_SDA_H	GPIO_SetBits(LED_HTK_PIN_GPIOPort, LED_HTK_SDA_GPIOPin)
#define IIC_SCL_L	GPIO_ResetBits(LED_HTK_PIN_GPIOPort, LED_HTK_SCL_GPIOPin)
#define IIC_SDA_L	GPIO_ResetBits(LED_HTK_PIN_GPIOPort, LED_HTK_SDA_GPIOPin)
void I2C_WriteByte(uint8_t addr,uint8_t data);
void LED_I2C_Configuration(void);       //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�
 






#endif


