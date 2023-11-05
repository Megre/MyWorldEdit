#include "main.h"
#include "myKeyBoard.h"
#include <string.h>

#define myKeyBoard_row_GPIOPort		GPIOA
#define myKeyBoard_row0_GPIOPin		GPIO_Pin_0
#define myKeyBoard_row1_GPIOPin		GPIO_Pin_1
#define myKeyBoard_row2_GPIOPin		GPIO_Pin_2
#define myKeyBoard_row3_GPIOPin		GPIO_Pin_3
#define myKeyBoard_row4_GPIOPin		GPIO_Pin_4
#define myKeyBoard_row5_GPIOPin		GPIO_Pin_5

#define myKeyBoard_col3_0_GPIOPort	GPIOB
#define myKeyBoard_col0_GPIOPort	GPIOB
#define myKeyBoard_col1_GPIOPort	GPIOB
#define myKeyBoard_col2_GPIOPort	GPIOB
#define myKeyBoard_col3_GPIOPort	GPIOB
#define myKeyBoard_col15_4_GPIOPort	GPIOC
#define myKeyBoard_col4_GPIOPort	GPIOC
#define myKeyBoard_col5_GPIOPort	GPIOC
#define myKeyBoard_col6_GPIOPort	GPIOC
#define myKeyBoard_col7_GPIOPort	GPIOC
#define myKeyBoard_col8_GPIOPort	GPIOC
#define myKeyBoard_col9_GPIOPort	GPIOC
#define myKeyBoard_col10_GPIOPort	GPIOC
#define myKeyBoard_col11_GPIOPort	GPIOC
#define myKeyBoard_col12_GPIOPort	GPIOC
#define myKeyBoard_col13_GPIOPort	GPIOC
#define myKeyBoard_col14_GPIOPort	GPIOC
#define myKeyBoard_col15_GPIOPort	GPIOC
#define myKeyBoard_col0_GPIOPin		GPIO_Pin_12
#define myKeyBoard_col1_GPIOPin		GPIO_Pin_13
#define myKeyBoard_col2_GPIOPin		GPIO_Pin_14
#define myKeyBoard_col3_GPIOPin		GPIO_Pin_15
#define myKeyBoard_col4_GPIOPin		GPIO_Pin_0
#define myKeyBoard_col5_GPIOPin		GPIO_Pin_1
#define myKeyBoard_col6_GPIOPin		GPIO_Pin_2
#define myKeyBoard_col7_GPIOPin		GPIO_Pin_3
#define myKeyBoard_col8_GPIOPin		GPIO_Pin_4
#define myKeyBoard_col9_GPIOPin		GPIO_Pin_5
#define myKeyBoard_col10_GPIOPin	GPIO_Pin_6
#define myKeyBoard_col11_GPIOPin	GPIO_Pin_7
#define myKeyBoard_col12_GPIOPin	GPIO_Pin_8
#define myKeyBoard_col13_GPIOPin	GPIO_Pin_9
#define myKeyBoard_col14_GPIOPin	GPIO_Pin_10
#define myKeyBoard_col15_GPIOPin	GPIO_Pin_11

#define myKeyBoard_ControlKey 0x00
#define myKeyBoard_SpecialKey 0x00

#define xxCK	myKeyBoard_ControlKey 
#define xxSK	myKeyBoard_SpecialKey 

const char * myKeyBoard_KeyMap_Name[6][16] = 
{
	"Esc","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12","PrtSc","ScrollLock","PauseBreak",
	"~","!","@","#","$","%","^","&","*","(",")","-","+","BackSpace","Insert","Home",
	"Tab","Q","W","E","R","T","Y","U","I","O","P","{","}","|","Delete","End",
	"CapsLock","A","S","D","F","G","H","J","K","L",";","'","Enter","","","PageUp",
	"LShift","Z","X","C","V","B","N","M",",",".","/","RShift","Up","","","PageDown",
	"LCtrl","Win","LAlt","Space","RAlt","FN","Menu","RCtrl","Left","Down","Right","","","","",""
};


const unsigned char myKeyBoard_KeyMap_ATValue[6][16] = 
{
	0x29,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,
	0x35,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x2D,0x2E,0x2A,0x49,0x4A,
	0x2B,0x14,0x1A,0x08,0x15,0x17,0x1C,0x18,0x0C,0x12,0x13,0x2F,0x30,0x31,0x4C,0x4D,
	0x39,0x04,0x16,0x07,0x09,0x0A,0x0B,0x0D,0x0E,0x0F,0x33,0x34,0x28,0x00,0x00,0x4B,
	xxCK,0x1D,0x1B,0x06,0x19,0x05,0x11,0x10,0x36,0x37,0x38,xxCK,0x52,0x00,0x00,0x4E,
	xxCK,xxCK,xxCK,0x2C,xxCK,xxSK,xxSK,xxCK,0x50,0x51,0x4F,0x00,0x00,0x00,0x00,0x00,
};


//const unsigned char myKeyBoard_KeyMap_ATValue[6][16] = 
//{
//	0x29,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,
//	0x35,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x2D,0x2E,0x2A,0x49,0x4A,
//	0x2B,0x14,0x1A,0x08,0x15,0x17,0x1C,0x18,0x0C,0x12,0x13,0x2F,0x30,0x31,0x4C,0x4D,
//	0x39,0x04,0x16,0x07,0x09,0x0A,0x0B,0x0D,0x0E,0x0F,0x33,0x34,0x28,0x00,0x00,0x4B,
//	0xE1,0x1D,0x1B,0x06,0x19,0x05,0x11,0x10,0x36,0x37,0x38,0xE5,0x52,0x00,0x00,0x4E,
//	0xE0,0xE3,0xE2,0x2C,0xE6,0x00,0x76,0xE4,0x50,0x51,0x4F,0x00,0x00,0x00,0x00,0x00,
//};

const uint16_t key_Col_Pin[16] = 
{
	myKeyBoard_col0_GPIOPin,
	myKeyBoard_col1_GPIOPin,
	myKeyBoard_col2_GPIOPin,	
	myKeyBoard_col3_GPIOPin,	
	myKeyBoard_col4_GPIOPin,	
	myKeyBoard_col5_GPIOPin,	
	myKeyBoard_col6_GPIOPin,	
	myKeyBoard_col7_GPIOPin,	
	myKeyBoard_col8_GPIOPin,	
	myKeyBoard_col9_GPIOPin,	
	myKeyBoard_col10_GPIOPin,	
	myKeyBoard_col11_GPIOPin,	
	myKeyBoard_col12_GPIOPin,	
	myKeyBoard_col13_GPIOPin,	
	myKeyBoard_col14_GPIOPin,	
	myKeyBoard_col15_GPIOPin	
		
};

typedef struct 
{
	unsigned char ATKeyData;
	unsigned char rowN;
	unsigned char colN;
}ATKeyDataStructureTypedef;

//��ͨ�����ݴ�����
ATKeyDataStructureTypedef ATKeyData[6];
unsigned char ATKeyControlByte5 = 0x00;//״̬���Ƽ��ֽ� ��Shift Ctrl����
//6��x16�м��� ״̬����
KeyState_enumTypedef myKeyBoard_KeyState[6][16] = {KEYUNPRESSED};//��ǰ����״̬
KeyState_enumTypedef myKeyBoard_KeyState_Ex[6][16] = {KEYUNPRESSED};//�ϴΰ���״̬

u8 LOGO_LED_Status = 0;

unsigned char myKeyBoard_KeyStateChangedFlag = 0;//����״̬�ı��־
unsigned char myKeyBoard_KeyIsControl = 1;//���̿��ư�����־
unsigned char g_myKeyBoard_DataWaitForUploadFlag = 0;//���ݵȴ��ϴ���־


void myKeyBoard_ControlKeyProcess(u8 rowi, u8 colj);
void myKeyBoard_KeyScan_rowScan(GPIO_TypeDef * 		col_GPIOPort, 
								uint8_t 			col_GPIOPin_Index,
								const uint16_t *	p_col_GPIOPin);





//���̸���
void myKeyBoard_ScanKeyAndUpdataATBuffer()
{
	myKeyBoard_KeyScan();//��������״̬ɨ�裬�����Ƿ񱻰��� �� 
	myKeyBoard_JudgeKeyStateChange();//�жϼ���״̬�Ƿ��б仯��������λmyKeyBoard_KeyStateChangedFlag��־
	
	if(myKeyBoard_KeyStateChangedFlag)//�ж��Ƿ��б仯
	{
		myKeyBoard_KeyStateChangedFlag = 0;
		myKeyBoard_UpdataATDataPack();//����AT���ݰ�����
		g_myKeyBoard_DataWaitForUploadFlag = 1;//��λ���ݵȴ��ϴ���־
	}
}

/*
*/


//���� FN��ϼ���ö�٣����������ֵ����
enum{
	none = 0,
	Mute = 1,
	VolumeUp = 2,
	VolumeDown = 3,
	PlayORPause = 4,
	Stop = 5
}	specialKeyenum = none;

void ConsumerKeyProcess(void)//����FN��Ϲ��ܼ��������͸�BTK05
{
	BTK05_ConsumerPack[5] = 0x00;//����
	switch(specialKeyenum)
	{
		case Mute:
			//specialATKeyValueTemp = 0x7F;
			BTK05_ConsumerPack[5] |= (0x01 << 0); 
			break;
		case VolumeUp:
			BTK05_ConsumerPack[5] |= (0x01 << 2);
			break;
		case VolumeDown:
			BTK05_ConsumerPack[5] |= (0x01 << 1);
			break;
		case PlayORPause:
			BTK05_ConsumerPack[5] |= (0x01 << 3);
			break;
		case Stop:
			BTK05_ConsumerPack[5] |= (0x01 << 4);
			break;
		default:
			break;
	}
	
	BTK05_UART_SendKeyData(BTK05_ConsumerPack,8);
	BTK05_ConsumerPack[5] = 0x00;//����
	BTK05_UART_SendKeyData(BTK05_ConsumerPack,8);
}

void myKeyBoard_UpdataATDataPack()
{
	u8 i,j,k;
	u8 AlreadeyExistflag = 0;
	ATKeyControlByte5 = 0x00;//������ư�����ֵ
	//u8 specialKeyenum = 0;
	if(myKeyBoard_KeyState[5][5] == KEYPRESSED)//�ж�FN���Ƿ񱻰���
	{
		if(myKeyBoard_JudgeKeyPressWithName("F8"))
		{
			//specialKeyFlag = 1;
			specialKeyenum = VolumeUp;
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F7"))
		{
			specialKeyenum = VolumeDown;
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F9"))
		{
			specialKeyenum = Mute;
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F10"))
		{
			specialKeyenum = PlayORPause;
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F11"))
		{
			specialKeyenum = Stop;
		}
		if(specialKeyenum != none)
		{
			ConsumerKeyProcess();//����FN��Ϲ��ܼ��������͸�BTK05
			specialKeyenum = none;//
			//return;
		}			
	}
	
	if(myKeyBoard_KeyState[5][6] == KEYPRESSED)//�ж�Menu���Ƿ񱻰���
	{
		if(myKeyBoard_JudgeKeyPressWithName("PauseBreak"))
		{
			if(!g_USBModeFlag)
			{
				USB_Mode();
				LOGO_LED_Status = 0;
			}
			else 
				BLUETEETH_Mode();
			
//			LED_LOGO_FLASH_3TIMES();
		}
		else if(myKeyBoard_JudgeKeyPressWithName("ScrollLock"))
		{
			if(g_USBModeFlag)
			{
				if(!LOGO_LED_Status)
				{
					GPIO_SetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
					LOGO_LED_Status = 1;
				}else if(LOGO_LED_Status)
				{
					GPIO_ResetBits(LED_LOGO_GPIOPort,LED_LOGO_GPIOPin);
					LOGO_LED_Status = 0;
				}
			}
		}
		else if(myKeyBoard_JudgeKeyPressWithName("Delete"))
		{
			BTK05_DeleteConnectInfo();
		}
		else if(myKeyBoard_JudgeKeyPressWithName("Insert"))
		{
			BTK05_PairMode();
		}
		else if(myKeyBoard_JudgeKeyPressWithName("Home"))
		{
			BTK05_RESET();
		}
		else if(myKeyBoard_JudgeKeyPressWithName("End"))
		{
			BTK05_Sleep();
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F12"))
		{
			LED_SetFlash();//��˸����
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F11"))
		{
			LED_SetBreathEfect();//�����ƿ���	
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F4"))
		{
			//��˭��˭ģʽ
			//����ģʽ
		
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F3"))
		{
			LED_Mode3();
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F2"))
		{
			LED_Mode2();//��WASD ��������
		}
		else if(myKeyBoard_JudgeKeyPressWithName("F1"))
		{
			LED_Mode1();//ȫ��
		}

		else if(myKeyBoard_JudgeKeyPressWithName("+"))
		{
			LED_Brightness++;
			LED_SetBrightness(LED_Brightness);
			if(LED_Brightness > 16) LED_Brightness = 16;
		}
		else if(myKeyBoard_JudgeKeyPressWithName("-"))
		{
			if(LED_Brightness > 0)
				LED_Brightness--;
			LED_SetBrightness(LED_Brightness);
			
		}
		else if(myKeyBoard_JudgeKeyPressWithName("Esc"))
		{
			
			LED_ESCOFF();
			
		}
//		if(myKeyBoard_JudgeKeyPressWithName("ScrollLock"))
//		{
//			if(LED_LOGOENBreath_Flag)
//			{
//				LED_LOGOENBreath_Flag = 0;
//				TIM_Cmd(TIM3,DISABLE);
//			}
//			else
//			{
//				LED_LOGOENBreath_Flag = 1;
//				TIM_Cmd(TIM3,ENABLE);
//			}
//		}
	}
		
	for(i = 0; i < 6 ; i++)//�ж��ϴΰ��µİ��������Ƿ񻹱�����,������ATKeyData����������
	{
		if(ATKeyData[i].ATKeyData != 0x00)
		{
			if(myKeyBoard_KeyState[ATKeyData[i].rowN][ATKeyData[i].colN] == KEYUNPRESSED)
			{
				ATKeyData[i].ATKeyData = 0x00;
			}
		}
	}
	
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 16; j++)
		{
			if(myKeyBoard_KeyState[i][j] == KEYPRESSED)//�����������������������ݰ�
			{
				myKeyBoard_ControlKeyProcess(i,j);//���ư�������
				if(myKeyBoard_KeyIsControl == 0)
				{
					for(k = 0; k < 6; k++)//�ж�ATKeyData���ݰ����Ƿ��Ѿ��иü���ֵ�ˣ����Ƿ�֮ǰ�Ѿ���������
					{
						if(ATKeyData[k].ATKeyData == myKeyBoard_KeyMap_ATValue[i][j])
						{
							AlreadeyExistflag = 1;
							break;
						}
					}
					if(AlreadeyExistflag == 0)//���ATKeyData���ݰ�û�иü�ֵ�����
					{
						//ѭ��	ֻҪATKeyData���ݰ��п�λ�����ü�ֵ������break��
						//�������ѭ�����Ҳû�����Ч����Ϊһ��ֻ�ܰ�����������
						for(k = 0; k < 6; k++)
						{
							if(ATKeyData[k].ATKeyData == 0x00)//������ATֵ����ATKeyData  Buffer
							{
								ATKeyData[k].ATKeyData = myKeyBoard_KeyMap_ATValue[i][j];
								ATKeyData[k].rowN = i;
								ATKeyData[k].colN = j;
								break;
							}
						}
					}
					else {
						AlreadeyExistflag = 0;}
					myKeyBoard_KeyIsControl = 1;
				}
			}
			
		}
	}
	
	//������ֵ�ж���Ϻ󣬽��������ݰ�����
	BTK05_ATKeyDataPack[4] = ATKeyControlByte5;	//���¿��ư����ֽ�
	
//=========================================================˼·��ȷ�Ĵ��룬����������ʵ�ֵģ���������
//	//����FN��ϼ��ļ�ֵ����
//	u8 specialATKeyValueTemp = 0;
//	if(specialKeyenum != none)//���FN��ϼ���������
//	{
//		switch(specialKeyenum)
//		{
//			case Mute:
//				//specialATKeyValueTemp = 0x7F;
//				specialATKeyValueTemp = 0x04;
//				break;
//			case VolumeUp:
//				specialATKeyValueTemp = 0x80;
//				break;
//			case VolumeDown:
//				specialATKeyValueTemp = 0x81;
//				break;
//			default:
//				break;
//		}
//		//ѭ��	ֻҪATKeyData���ݰ��п�λ�����ü�ֵ������break��
//		//�������ѭ�����Ҳû�����Ч����Ϊһ��ֻ�ܰ�����������
//		for(k = 0; k < 6; k++)
//		{
//			if(ATKeyData[k].ATKeyData == 0x00)//������ATֵ����ATKeyData  Buffer
//			{
//				ATKeyData[k].ATKeyData = specialATKeyValueTemp;
//				ATKeyData[k].rowN = 5;	//�����еĵ�����16����Զ�����ܱ����£�����FN��ϼ���AT��ֵ����һ��ɨ��ʱ���ͻᱻ����
//				ATKeyData[k].colN = 15;	//�����Ż��ļ�ֵȡ����ʽ�������ڷ�����ATֵ����Ҫ���ATֵ�����е�FN��ϼ���ATֵ
//				break;
//			}
//		}
//		specialKeyenum = none;
//	}
//=========================================================˼·��ȷ�Ĵ��룬����������ʵ�ֵģ���������
	for(k = 0; k < 6; k++)
	{
		BTK05_ATKeyDataPack[6 + k] = ATKeyData[k].ATKeyData;//������ͨ����
	}
}


void myKeyBoard_ControlKeyProcess(u8 rowi, u8 colj)
{
	if(strcmp(myKeyBoard_KeyMap_Name[rowi][colj],"LShift") == 0)
	{
		ATKeyControlByte5 = ATKeyControlByte5 | (0x01 << 1);
	}
	else if(strcmp(myKeyBoard_KeyMap_Name[rowi][colj],"RShift") == 0)
	{
		ATKeyControlByte5 = ATKeyControlByte5 | (0x01 << 5);
	}
	else if(strcmp(myKeyBoard_KeyMap_Name[rowi][colj],"LCtrl") == 0)
	{
		ATKeyControlByte5 = ATKeyControlByte5 | (0x01 << 0);
	}
	else if(strcmp(myKeyBoard_KeyMap_Name[rowi][colj],"RCtrl") == 0)
	{
		ATKeyControlByte5 = ATKeyControlByte5 | (0x01 << 4);
	}
	else if(strcmp(myKeyBoard_KeyMap_Name[rowi][colj],"LAlt") == 0)
	{
		ATKeyControlByte5 = ATKeyControlByte5 | (0x01 << 2);
	}
	else if(strcmp(myKeyBoard_KeyMap_Name[rowi][colj],"RAlt") == 0)
	{
		ATKeyControlByte5 = ATKeyControlByte5 | (0x01 << 6);
	}
	else if(strcmp(myKeyBoard_KeyMap_Name[rowi][colj],"Win") == 0)
	{
		ATKeyControlByte5 = ATKeyControlByte5 | (0x01 << 3);
	}
	else//������϶�û���б�������ͨ��������λ���ư�����־
	{
		myKeyBoard_KeyIsControl = 0;
	}
}


void myKeyBoard_JudgeKeyStateChange()
{
	u8 i,j;
	//������״̬�Ƿ�ı�
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 16; j++)
		{
			if(myKeyBoard_KeyState_Ex[i][j] != myKeyBoard_KeyState[i][j])
			{
				myKeyBoard_KeyStateChangedFlag = 1;
				break;
			}
			
		}
		if(myKeyBoard_KeyStateChangedFlag)
			break;
	}
	
	//����ǰ�ļ���״̬���ݸ��ϴ�
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 16; j++)
		{
			myKeyBoard_KeyState_Ex[i][j] = myKeyBoard_KeyState[i][j];//����ǰ�ļ���״̬���ݸ��ϴ�
		}
	}
	
}


void myKeyBoard_KeyScan()
{
	u8 i;
	for(i = 0 ; i < 4 ;i ++)
	{
		myKeyBoard_KeyScan_rowScan(myKeyBoard_col3_0_GPIOPort, i, key_Col_Pin);
		//DelayUs(6);
	}
	for(i = 4 ; i < 16 ;i ++)
	{
		myKeyBoard_KeyScan_rowScan(myKeyBoard_col15_4_GPIOPort, i, key_Col_Pin);
		//DelayUs(6);
	}
}


void myKeyBoard_KeyScan_rowScan(GPIO_TypeDef * 		col_GPIOPort, 
								uint8_t 			col_GPIOPin_Index,
								const uint16_t *	p_col_GPIOPin)
{
	GPIO_SetBits(col_GPIOPort, *(p_col_GPIOPin + col_GPIOPin_Index));
	DelayUs(2);
	if(GPIO_ReadInputDataBit(myKeyBoard_row_GPIOPort, myKeyBoard_row0_GPIOPin)) 
		{myKeyBoard_KeyState[0][col_GPIOPin_Index] = KEYPRESSED;}
	else{myKeyBoard_KeyState[0][col_GPIOPin_Index] = KEYUNPRESSED;}
	DelayUs(50);
	if(GPIO_ReadInputDataBit(myKeyBoard_row_GPIOPort, myKeyBoard_row1_GPIOPin)) 
		{myKeyBoard_KeyState[1][col_GPIOPin_Index] = KEYPRESSED;}
	else{myKeyBoard_KeyState[1][col_GPIOPin_Index] = KEYUNPRESSED;}
	DelayUs(1);
	if(GPIO_ReadInputDataBit(myKeyBoard_row_GPIOPort, myKeyBoard_row2_GPIOPin)) 
		{myKeyBoard_KeyState[2][col_GPIOPin_Index] = KEYPRESSED;}
	else{myKeyBoard_KeyState[2][col_GPIOPin_Index] = KEYUNPRESSED;}
	DelayUs(1);
	if(GPIO_ReadInputDataBit(myKeyBoard_row_GPIOPort, myKeyBoard_row3_GPIOPin)) 
		{myKeyBoard_KeyState[3][col_GPIOPin_Index] = KEYPRESSED;}
	else{myKeyBoard_KeyState[3][col_GPIOPin_Index] = KEYUNPRESSED;}
	DelayUs(1);
	if(GPIO_ReadInputDataBit(myKeyBoard_row_GPIOPort, myKeyBoard_row4_GPIOPin)) 
		{myKeyBoard_KeyState[4][col_GPIOPin_Index] = KEYPRESSED;}
	else{myKeyBoard_KeyState[4][col_GPIOPin_Index] = KEYUNPRESSED;}
	DelayUs(1);	
	if(GPIO_ReadInputDataBit(myKeyBoard_row_GPIOPort, myKeyBoard_row5_GPIOPin)) 
		{myKeyBoard_KeyState[5][col_GPIOPin_Index] = KEYPRESSED;}
	else{myKeyBoard_KeyState[5][col_GPIOPin_Index] = KEYUNPRESSED;}
	
	GPIO_ResetBits(col_GPIOPort, *(p_col_GPIOPin + col_GPIOPin_Index));
	//DelayUs(10);
}

unsigned char myKeyBoard_JudgeKeyPressWithName(const char* keyName)
{
	
	unsigned char i,j;
	for(i = 0; i < 6; i++ )
	{
		for(j = 0; j < 16; j++)
		{
			if(strcmp(myKeyBoard_KeyMap_Name[i][j], keyName) == 0)
			{
				if(myKeyBoard_KeyState[i][j] == KEYUNPRESSED)
				{
					return 0;
				}
				else
				{
					myKeyBoard_KeyState[i][j] = KEYUNPRESSED;
					return 1;
				}
			}
				
		}
		
	}
	
	return 0;
}

//��ʼ������IO
void myKeyBoard_GPIO_Init()
{
	
	GPIO_InitTypeDef GPIOType;
	
	//��ʼ�� row0-row5 GPIO
	GPIOType.GPIO_Pin = myKeyBoard_row0_GPIOPin | 
						myKeyBoard_row1_GPIOPin | 
						myKeyBoard_row2_GPIOPin | 
						myKeyBoard_row3_GPIOPin | 
						myKeyBoard_row4_GPIOPin |
						myKeyBoard_row5_GPIOPin;
	
	GPIOType.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOType.GPIO_Mode = GPIO_Mode_IPD; //��������
	GPIO_Init(myKeyBoard_row_GPIOPort , &GPIOType);
	
	//��ʼ�� col0-col3 GPIO
	GPIOType.GPIO_Pin = myKeyBoard_col0_GPIOPin | 
						myKeyBoard_col1_GPIOPin | 
						myKeyBoard_col2_GPIOPin | 
						myKeyBoard_col3_GPIOPin ;

	GPIOType.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOType.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
	GPIO_Init(myKeyBoard_col3_0_GPIOPort , &GPIOType);
	
	//��ʼ�� col4-col15 GPIO
	GPIOType.GPIO_Pin = myKeyBoard_col4_GPIOPin | 
						myKeyBoard_col5_GPIOPin | 
						myKeyBoard_col6_GPIOPin | 
						myKeyBoard_col7_GPIOPin |
						myKeyBoard_col8_GPIOPin |
						myKeyBoard_col9_GPIOPin |
						myKeyBoard_col10_GPIOPin |
						myKeyBoard_col11_GPIOPin |
						myKeyBoard_col12_GPIOPin |
						myKeyBoard_col13_GPIOPin |
						myKeyBoard_col14_GPIOPin |
						myKeyBoard_col15_GPIOPin ;
						
	GPIOType.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOType.GPIO_Mode = GPIO_Mode_Out_PP;		//�������
	GPIO_Init(myKeyBoard_col15_4_GPIOPort , &GPIOType);

}



