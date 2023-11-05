#include "main.h"
#include "LED.h"
#define delay_ms DelayMs
#define delay_us DelayUs

unsigned char LED_Ram[6][2] = {0};
unsigned char LED_Brightness = 8;
unsigned char LED_FlashSwitchFlag = 0;
unsigned char LED_BreathEfectFlag = 0;
unsigned char LED_Delt_Flag = 0;
unsigned char LED_Status = 0;


void LED_ESCOFF()
{
	
	LED_RamClearWith(0);
	LED_FreashRam();
	//LED_SetBrightness(8);
	LED_SetDisplay(0,LED_FLASH_OFF);
	LED_Status = 0;
	LED_GoToSleep();
}


void LED_GoToSleep()
{
	I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_SLEEP);//�ر�оƬʱ��
	//LED_Status = 0;
}

void LED_WakeUp()
{
	//LED_Status = 1;
	I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_START);//����оƬʱ��
}


void LED_RamClearWith(unsigned char ledSwitch)
{
	unsigned char i,j,temp;
	if(ledSwitch == 1)temp = 0xff;
	else	temp = 0x00;
	
	for(i = 0; i < 6; i++)//��12�ֽ�RAM�Դ�д��оƬ
	{
		for(j = 0; j < 2; j++)
		{
			LED_Ram[i][j] = temp; 						   
		}	
	}
}
	
/*********************************************
Function	:LED_DrawPoint(unsigned char x, unsigned char y, unsigned char color);
Description:���㺯��
Input	: 	unsigned char x, 	�� 0-5
			unsigned char y, 	�� 0-15
			unsigned char color	= 0��Ϩ��  ��1������
Return	: void
Author	: firestaradmin
**********************************************/
//unsigned char LED_Ram[6][2] = {0};
void LED_DrawPoint(unsigned char x, unsigned char y, unsigned char color)
{
	unsigned char lieByte = y / 8;
	unsigned char temp = LED_Ram[x][lieByte];
	if(color)
	{
		temp = temp | (0x01 << (y % 8));
		LED_Ram[x][lieByte] |= temp;
	}
	else
	{
		temp = temp & ~(0x01 << (y % 8));
		LED_Ram[x][lieByte] &= temp;
	}
	
	
}

//def: 0x80
//1 0 0 0 X B1 B0 D
//{D}
//ֻд
//������ʾ���� / �ر�״̬
//�� {0}����ʾ�ر�
//�� {1}����ʾ����
//80H
//{B1,B0}
//ֻд
//������˸Ƶ��
//�� {0,0} = ��˸�ر�
//�� {0,1} = 2Hz
//�� {1,0} = 1Hz
//�� {1,1} = 0.5Hz
/*********************************************
Function	:void LED_SetDisplay(unsigned char displaySwitch, LED_FlashPreqTypedef displayFlashPreq)
Description:
Input	: 	unsigned char displaySwitch = 0���ر���ʾ �� 1��������ʾ , 
			unsigned char displayFlashPreq = 	
										{	
											LED_FLASH_OFF = 0, 
											LED_FLASH_2Hz = 1,
											LED_FLASH_1Hz = 2,
											LED_FLASH_HalfHz = 3
										}
Return	: void
Author	: firestaradmin
**********************************************/
void LED_SetDisplay(unsigned char displaySwitch, LED_FlashPreqTypedef displayFlashPreq)	
{
	if(displaySwitch != 0)
	{
		switch (displayFlashPreq)
		{
			case LED_FLASH_OFF:
				I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_DisplayOn);//������ʾ
				break;
			case LED_FLASH_1Hz:
				I2C_WriteByte(LED_HTK_Address_Wirte,(LED_HTK_CMD_DisplayOn|0x04));//������ʾ
				break;
			case LED_FLASH_2Hz:
				I2C_WriteByte(LED_HTK_Address_Wirte,(LED_HTK_CMD_DisplayOn|0x02));//������ʾ
				break;
			case LED_FLASH_HalfHz:
				I2C_WriteByte(LED_HTK_Address_Wirte,(LED_HTK_CMD_DisplayOn|0x06));//������ʾ
				break;
			default:
				I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_DisplayOn);//������ʾ
				break;
					
		}
		
		
	}
	else 
	{
		I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_DisplayOff);//�ر���ʾ
	}
}

//def: 0xEF
//1 1 1 0 P3 P2 P1 P0
//{P3~P0}
//ֻд
//���� ROW �����źŵ�����
//�� {0,0,0,0}��1/16duty
//�� {0,0,0,1}��2/16duty
//�� {0,0,1,0}��3/16duty
//�� {0,0,1,1}��4/16duty
//�� {0,1,0,0}��5/16duty
//�� {0,1,0,1}��6/16duty
//�� {0,1,1,0}��7/16duty
//�� {0,1,1,1}��8/16duty
//�� {1,0,0,0}��9/16duty
//�� {1,0,0,1}��10/16duty
//�� {1,0,1,0}��11/16duty
//�� {1,0,1,1}��12/16duty
//�� {1,1,0,0}��13/16duty
//�� {1,1,0,1}��14/16duty
//�� {1,1,1,0}��15/16duty
//�� {1,1,1,1}��16/16duty
/*********************************************
Function	:void LED_SetBrightness(unsigned char brightness)
Description:
Input	: unsigned char brightness = 1~16  ����Խ��Խ��
Return	: void
Author	: firestaradmin
**********************************************/
void LED_SetBrightness(unsigned char brightness)
{

	if(brightness > 15)	brightness = 15;
	
	I2C_WriteByte(LED_HTK_Address_Wirte,0xE0 | (brightness-1));
}

void LED_SetBreathEfect(void)
{
	if(LED_BreathEfectFlag == 1)
	{
		LED_BreathEfectFlag = 0;
		
	}
	else
	{
		LED_BreathEfectFlag = 1;
		LED_SetDisplay(1,LED_FLASH_OFF);
		LED_FlashSwitchFlag = 0;
	}
}

void LED_Mode3(void)
{
	LED_WakeUp();
	LED_RamClearWith(0);
	LED_DrawPoint(5,1,1);//W
	LED_DrawPoint(5,6,1);//Right
	LED_FreashRam();
	LED_SetBrightness(8);
	LED_SetDisplay(1,LED_FLASH_OFF);
	LED_Status = 1;
}
void LED_Mode2(void)
{
	LED_WakeUp();
	LED_RamClearWith(0);
	LED_DrawPoint(2,2,1);//W
	LED_DrawPoint(3,1,1);//A
	LED_DrawPoint(3,2,1);//S
	LED_DrawPoint(3,3,1);//D
	
	LED_DrawPoint(4,12,1);//Up
	LED_DrawPoint(5,8,1);//Left
	LED_DrawPoint(5,9,1);//Down
	LED_DrawPoint(5,10,1);//Right
	LED_FreashRam();
	LED_SetBrightness(8);
	LED_SetDisplay(1,LED_FLASH_OFF);
	LED_Status = 1;
}

void LED_Mode1(void)
{
	LED_WakeUp();
	LED_RamClearWith(1);
	LED_FreashRam();
	LED_SetBrightness(8);
	LED_SetDisplay(1,LED_FLASH_OFF);
	LED_Status = 1;
}

void LED_Off(void)
{
	LED_GoToSleep();
	LED_BreathEfectFlag = 0;
	LED_Brightness = 8;
	LED_FlashSwitchFlag = 0;
	LED_Status = 0;
}

void LED_BreathProcess(void)
{
	
	if(LED_Delt_Flag == 1)
	{
		if(LED_Brightness <= 16)
		{
			LED_SetBrightness(LED_Brightness);
			LED_Brightness ++;
		}
		else
		{
			LED_Brightness = 16;
			LED_Delt_Flag = 0;
		}
		
		
	}
	else if(LED_Delt_Flag == 0)
	{
		if(LED_Brightness >= 1)
		{
			LED_SetBrightness(LED_Brightness);
			LED_Brightness --;
		}
		else
		{
			LED_Brightness = 1;
			LED_Delt_Flag = 1;
		}
	}
}

void LED_SetFlash(void)
{
	if(LED_FlashSwitchFlag == 1)
	{
		LED_SetDisplay(1,LED_FLASH_OFF);
		LED_FlashSwitchFlag = 0;
	}
	else
	{
		LED_SetDisplay(1,LED_FLASH_1Hz);
		LED_FlashSwitchFlag = 1;
		LED_BreathEfectFlag = 0;
	}
}

//unsigned char LED_Ram[6][2]
void LED_FreashRam()//��ģ���Դ�����д��HT16K33оƬ
{
	u8 i,j;

	IIC_Start(); //IIC START��ʼ�ź� 
	IIC_Send_Byte(LED_HTK_Address_Wirte); //�� R/W λ�Ĵӻ���ַ
	if(!IIC_Wait_Ack())//�ȴ�ACK�ź�
	{
		return;
	}
	IIC_Send_Byte(LED_HTK_CMD_SetRamAddr); 	//����RAM��ַָ��CMD					   
    if(!IIC_Wait_Ack())
	{
		return;
	}  		
	for(i = 0; i < 6; i++)//��12�ֽ�RAM�Դ�д��оƬ
	{
		for(j = 0; j < 2; j++)
		{
			IIC_Send_Byte(LED_Ram[i][j]); 						   
			if(!IIC_Wait_Ack())
			{
				return;
			}  	
		}	
	}
	for(i = 0; i < 4 ; i++)//��Ϊ������ֻ������6��16��LED���У����Ժ����ĸ��ֽڵ�RAMֱ��д��0x00�ͺ��ˡ�
	{
		IIC_Send_Byte(0x00); 						   
		if(!IIC_Wait_Ack())
		{
			return;
		}  
	}
	
    IIC_Stop();
}



void LED_AllLightOn()
{
	u8 i;
	I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_START);
	I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_SetROWOut);
	
	I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_SetPWM100);
	I2C_WriteByte(LED_HTK_Address_Wirte,0x87);
	//I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_SetRamAddr);
	
	IIC_Start();  
	IIC_Send_Byte(LED_HTK_Address_Wirte); 
	if(!IIC_Wait_Ack())
	{
		return;
	}
	IIC_Send_Byte(LED_HTK_CMD_SetRamAddr); 						   
    if(!IIC_Wait_Ack())
	{
		return;
	}  		
	for(i = 0; i < 16; i++)
	{
		IIC_Send_Byte(0xff); 						   
		if(!IIC_Wait_Ack())
		{
			return;
		}  		
	}
	
    IIC_Stop();
	
}


void LED_HT16K33_Init()//��ʼ��оƬ
{
	I2C_WriteByte(LED_HTK_Address_Wirte,LED_HTK_CMD_SetROWOut);//����λROW ���ģʽ
	LED_RamClearWith(0);
	LED_FreashRam();
	LED_SetBrightness(LED_Brightness);
	LED_SetDisplay(0,LED_FLASH_OFF);
	
}
//********************************************************************************************************
//======================================LOGO����LED��IO�ڳ�ʼ��=======================================================


void LED_LOGO_GPIO_Init()
{
	
	GPIO_InitTypeDef GPIOType = {
		
			LED_LOGO_GPIOPin,
			GPIO_Speed_50MHz,
			GPIO_Mode_Out_PP		//�������
	};
	
	GPIO_Init(LED_LOGO_GPIOPort , &GPIOType);
}

//********************************************************************************************************
//======================================ģ��IIC=======================================================


void LED_I2C_Configuration()
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	//RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = LED_HTK_SCL_GPIOPin|LED_HTK_SDA_GPIOPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_HTK_PIN_GPIOPort, &GPIO_InitStructure);
	
	IIC_SCL_H;
	IIC_SDA_H;
 
}



//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA_H;	  	  
	IIC_SCL_H;
	delay_us(4);
 	IIC_SDA_L;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_L;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL_L;
	IIC_SDA_L;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_H; 
	IIC_SDA_H;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��0������Ӧ��ʧ��
//        1������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA_H;delay_us(1);	   
	IIC_SCL_H;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 0;
		}
	}
	IIC_SCL_L;//ʱ�����0 	   
	return 1;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_L;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_H;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
		SDA_OUT(); 	    
    IIC_SCL_L;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {
		if((txd&0x80)>>7)
		{
			IIC_SDA_H;
		}
		else{
			IIC_SDA_L;
		}
       
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_H;
		delay_us(2); 
		IIC_SCL_L;	
		delay_us(2);
    }	 
} 	    


//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
	for(i=0;i<8;i++ )
	{
    IIC_SCL_L; 
    delay_us(2);
	IIC_SCL_H;
    receive<<=1;
    if(READ_SDA)receive++;   
	delay_us(1); 
	}					 
	if (!ack)
		IIC_NAck();//����nACK
	else
		IIC_Ack(); //����ACK   
	return receive;
}
 

void I2C_WriteByte(uint8_t addr,uint8_t data)
{
	IIC_Start();  
	IIC_Send_Byte(addr); 
	if(!IIC_Wait_Ack())
	{
		return;
	}
	IIC_Send_Byte(data); 						   
    if(!IIC_Wait_Ack())
	{
		return;
	}  		    	   
    IIC_Stop();

}
 

//uint16_t I2C_ReadByte(uint16_t addr,uint8_t device_addr,uint8_t ByteNumToRead)  //���Ĵ����������
//{	
//		uint16_t data;
//		IIC_Start();  
//		if(device_addr==0xA0)
//			IIC_Send_Byte(0xA0 + ((addr/256)<<1));
//		else
//			IIC_Send_Byte(device_addr);	
//		IIC_Wait_Ack();
//		IIC_Send_Byte(addr&0xFF);   //���͵͵�ַ
//		IIC_Wait_Ack(); 
// 
//		IIC_Start();  	
//		IIC_Send_Byte(device_addr+1);	    //��������ַ
//		IIC_Wait_Ack();
//		if(ByteNumToRead == 1)//LM75�¶�����Ϊ11bit
//		{
//			data=IIC_Read_Byte(0);
//		}
//		else
//			{
//				data=IIC_Read_Byte(1);
//				data=(data<<8)+IIC_Read_Byte(0);
//			}
//		IIC_Stop();//����һ��ֹͣ����	    
//		return data;
//}


//********************************************************************************************************






