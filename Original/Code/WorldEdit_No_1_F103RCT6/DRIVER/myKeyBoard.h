#ifndef __MYKEYBOARD_H_
#define __MYKEYBOARD_H_
//#include "main.h"

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
#define myKeyBoard_col4_GPIOPin		GPIO_Pin_6
#define myKeyBoard_col5_GPIOPin		GPIO_Pin_7
#define myKeyBoard_col6_GPIOPin		GPIO_Pin_8
#define myKeyBoard_col7_GPIOPin		GPIO_Pin_9
#define myKeyBoard_col8_GPIOPin		GPIO_Pin_4
#define myKeyBoard_col9_GPIOPin		GPIO_Pin_5
#define myKeyBoard_col10_GPIOPin	GPIO_Pin_10
#define myKeyBoard_col11_GPIOPin	GPIO_Pin_0
#define myKeyBoard_col12_GPIOPin	GPIO_Pin_1
#define myKeyBoard_col13_GPIOPin	GPIO_Pin_2
#define myKeyBoard_col14_GPIOPin	GPIO_Pin_3
#define myKeyBoard_col15_GPIOPin	GPIO_Pin_11


typedef enum 
{
	KEYUNPRESSED= 0,
	KEYPRESSED  = ~KEYUNPRESSED
}KeyState_enumTypedef;

//extern KeyState_enumTypedef myKeyBoard_KeyState[6][16];
extern unsigned char g_myKeyBoard_DataWaitForUploadFlag;//数据等待上传标志
extern unsigned char ATKeyControlByte5 ;//状态控制键字节 如Shift Ctrl键等


void myKeyBoard_GPIO_Init(void);//按键IO初始化
void myKeyBoard_KeyScan(void);//物理层键盘状态扫描，按键是否被按下 

void myKeyBoard_JudgeKeyStateChange(void);//判断键盘状态是否有变化，有则置位myKeyBoard_KeyStateChangedFlag标志
void myKeyBoard_UpdataATDataPack(void);//键盘AT数据包更新
void myKeyBoard_ScanKeyAndUpdataATBuffer(void);//键盘扫描并更新Key数据包
unsigned char myKeyBoard_JudgeKeyPressWithName(const char* keyName);
void myKeyBoard_Process_All(void);//键盘中心程序
void clear_keyboard_state(void);
#endif


