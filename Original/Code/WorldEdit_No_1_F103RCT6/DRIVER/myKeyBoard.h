#ifndef __MYKEYBOARD_H_
#define __MYKEYBOARD_H_
//#include "main.h"



typedef enum 
{
	KEYUNPRESSED= 0,
	KEYPRESSED  = ~KEYUNPRESSED
}KeyState_enumTypedef;

//extern KeyState_enumTypedef myKeyBoard_KeyState[6][16];
extern unsigned char g_myKeyBoard_DataWaitForUploadFlag;//���ݵȴ��ϴ���־
extern unsigned char ATKeyControlByte5 ;//״̬���Ƽ��ֽ� ��Shift Ctrl����


void myKeyBoard_GPIO_Init(void);//����IO��ʼ��
void myKeyBoard_KeyScan(void);//��������״̬ɨ�裬�����Ƿ񱻰��� 

void myKeyBoard_JudgeKeyStateChange(void);//�жϼ���״̬�Ƿ��б仯��������λmyKeyBoard_KeyStateChangedFlag��־
void myKeyBoard_UpdataATDataPack(void);//����AT���ݰ�����
void myKeyBoard_ScanKeyAndUpdataATBuffer(void);//����ɨ�貢����Key���ݰ�
unsigned char myKeyBoard_JudgeKeyPressWithName(const char* keyName);
void myKeyBoard_Process_All(void);//�������ĳ���
#endif


