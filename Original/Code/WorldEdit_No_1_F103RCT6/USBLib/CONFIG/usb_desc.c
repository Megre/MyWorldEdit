/**
  ******************************************************************************
  * @file    usb_desc.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Descriptors for Joystick Mouse Demo
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* USB Standard Device Descriptor */
//const uint8_t Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC] =
//  {
//    0x12,                       /*bLength */
//    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
//    0x00,                       /*bcdUSB */
//    0x02,
//    0x00,                       /*bDeviceClass*/
//    0x00,                       /*bDeviceSubClass*/
//    0x00,                       /*bDeviceProtocol*/
//    0x40,                       /*bMaxPacketSize 64*/
//    0x83,                       /*idVendor (0x0483)*/
//    0x04,
//    0x10,                       /*idProduct = 0x5710*/
//    0x57,
//    0x00,                       /*bcdDevice rel. 2.00*/
//    0x02,
//    1,                          /*Index of string descriptor describing
//                                                  manufacturer */
//    2,                          /*Index of string descriptor describing
//                                                 product*/
//    3,                          /*Index of string descriptor describing the
//                                                 device serial number */
//    0x01                        /*bNumConfigurations*/
//  }
//  ; /* Joystick_DeviceDescriptor */
const uint8_t Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC] =
  {
      0x12, 		         /*bLength�����ȣ��豸�������ĳ���Ϊ18�ֽ�*/
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType�����ͣ��豸�������ı����0x01*/
    0x00,                       /*bcdUSB����ʹ�õ�USB�汾Ϊ2.0*/
    0x02,
    0x00,                       /*bDeviceClass���豸��ʹ�õ������*/
    0x00,                       /*bDeviceSubClass���豸��ʹ�õ��������*/
    0x00,                       /*bDeviceProtocol���豸��ʹ�õ�Э��*/
    0x40,                       /*bMaxPacketSize����������Ϊ8�ֽ�*/
    0x78,                       /*idVendor������IDΪ0x7788*/
    0x67,
    0x12,                      	/*idProduct����ƷIDΪ0x1122*/
    0x01,
    0x00,                       /*bcdDevice���豸�İ汾��Ϊ2.00*/
    0x02,
    1,                          /*iManufacturer:�����ַ���������*/
    2,                          /*iProduct����Ʒ�ַ���������*/
    3,                          /*iSerialNumber���豸�����к��ַ�������*/
    0x01                        /*bNumConfiguration���豸��1������*/
}; /* keyboard�豸������ */

/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
//const uint8_t Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC] =
//  {
//    0x09, /* bLength: Configuration Descriptor size */
//    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
//    JOYSTICK_SIZ_CONFIG_DESC,
//    /* wTotalLength: Bytes returned */
//    0x00,
//    0x01,         /*bNumInterfaces: 1 interface*/
//    0x01,         /*bConfigurationValue: Configuration value*/
//    0x00,         /*iConfiguration: Index of string descriptor describing
//                                     the configuration*/
//    0xE0,         /*bmAttributes: Self powered */
//    0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/

//    /************** Descriptor of Joystick Mouse interface ****************/
//    /* 09 */
//    0x09,         /*bLength: Interface Descriptor size*/
//    USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface descriptor type*/
//    0x00,         /*bInterfaceNumber: Number of Interface*/
//    0x00,         /*bAlternateSetting: Alternate setting*/
//    0x01,         /*bNumEndpoints*/
//    0x03,         /*bInterfaceClass: HID*/
//    0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
//    0x02,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
//    0,            /*iInterface: Index of string descriptor*/
//    /******************** Descriptor of Joystick Mouse HID ********************/
//    /* 18 */
//    0x09,         /*bLength: HID Descriptor size*/
//    HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
//    0x00,         /*bcdHID: HID Class Spec release number*/
//    0x01,
//    0x00,         /*bCountryCode: Hardware target country*/
//    0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
//    0x22,         /*bDescriptorType*/
//    JOYSTICK_SIZ_REPORT_DESC,/*wItemLength: Total length of Report descriptor*/
//    0x00,
//    /******************** Descriptor of Joystick Mouse endpoint ********************/
//    /* 27 */
//    0x07,          /*bLength: Endpoint Descriptor size*/
//    USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:*/

//    0x81,          /*bEndpointAddress: Endpoint Address (IN)*/
//    0x03,          /*bmAttributes: Interrupt endpoint*/
//    0x04,          /*wMaxPacketSize: 4 Byte max */
//    0x00,
//    0x20,          /*bInterval: Polling Interval (32 ms)*/
//    /* 34 */
//  }
//  ; /* MOUSE_ConfigDescriptor */

/* USB��������������(���á��ӿڡ��˵㡢�ࡢ����)(Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC] =
{
    0x09, 		  	/*bLength�����ȣ��豸�ַ����ĳ���Ϊ9�ֽ�*/
    USB_CONFIGURATION_DESCRIPTOR_TYPE, 	/*bDescriptorType�����ͣ����������������ͱ��Ϊ0x2*/
    JOYSTICK_SIZ_CONFIG_DESC,	   		/*wTotalLength���������������ܳ���Ϊ41�ֽ�*/    
    0x00,
    0x01,         	/*bNumInterfaces��������֧�ֵĽӿ�����1��*/
    0x01,         	/*bConfigurationValue�������õ�ֵ*/
    0x00,         	/*iConfiguration�������õ��ַ���������ֵ����ֵΪ0��ʾû���ַ���*/              
    0xC0,         	/* bmAttributes:�豸��һЩ���ԣ�0xc0��ʾ�Թ��磬��֧��Զ�̻���
						D7:��������Ϊ1��D6:�Ƿ��Թ��磬D5���Ƿ�֧��Զ�̻��ѣ�D4~D0����������Ϊ0*/
    0x32,         	/*�������ϻ�õ�������Ϊ100mA */
//    0x96,         /*MaxPower���豸��Ҫ�������ϻ�ȡ���ٵ�������λΪ2mA��0x96��ʾ300mA*/

    /************** �ӿ�������****************/
	/* 09 */
    0x09,         	/*bLength�����ȣ��ӿ��������ĳ���Ϊ9�ֽ� */
    USB_INTERFACE_DESCRIPTOR_TYPE,/* bDescriptorType���ӿ�������������Ϊ0x4 */
    0x00,         	/*bInterfaceNumber���ýӿڵı��*/
    0x00,        	/*bAlternateSetting���ýӿڵı��ñ�� */
    0x02,         	/*bNumEndpoints���ýӿ���ʹ�õĶ˵���*/
    0x03,         	/*bInterfaceClass�ýӿ���ʹ�õ���ΪHID*/
    0x01,         	/*bInterfaceSubClass���ýӿ����õ����� 1=BOOT, 0=no boot */
    0x01,         	/*nInterfaceProtocol :�ýӿ�ʹ�õ�Э��0=none, 1=keyboard, 2=mouse */
    0,            	/*iInterface: �ýӿ��ַ��������� */

    /*****************HID������ ********************/
	/* 18 */
    0x09,         	/*bLength: HID�������ĳ���Ϊ9�ֽ� */
    HID_DESCRIPTOR_TYPE, /* bDescriptorType: HID������������Ϊ0x21 */
    0x10,         	/*bcdHID: HIDЭ��İ汾Ϊ1.1 */
    0x01,
    0x21,         	/*bCountryCode: ���Ҵ��� */
    0x01,         	/*bNumDescriptors: �¼�������������*/
    0x22,         	/*bDescriptorType���¼�������������*/
    JOYSTICK_SIZ_REPORT_DESC,/* wItemLength: ��һ���������ĳ���*/
    0x00,

    /********************����˵�������******************/
	/* 27 */
    0x07,         	/* bLength: �˵��������ĳ���Ϊ7�ֽ�*/
    USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: �˵�������������Ϊ0x05*/
    0x81,         	/* bEndpointAddress: �ö˵�(����)�ĵ�ַ,D7:0(OUT),1(IN),D6~D4:����,D3~D0:�˵��*/               
    0x03,         	/* bmAttributes: �˵������ΪΪ�ж϶˵�.
			D0~D1��ʾ��������:0(���ƴ���),1(��ʱ����),2(��������),3(�жϴ���)
			�ǵ�ʱ����˵�:D2~D7:����Ϊ0
			��ʱ����˵㣺
			D2~D3��ʾͬ��������:0(��ͬ��),1(�첽),2(����),3(ͬ��)
			D4~D5��ʾ��;:0(���ݶ˵�),1(�����˵�),2(�������������ݶ˵�),3(����)��D6~D7:����,*/
    0x08,         	/* wMaxPacketSize: �ö˵�֧�ֵ���������Ϊ8�ֽ�*/
    0x00,
    0x0A,         	/* bInterval: ��ѯ���(32ms) */

	/********************����˵�������*******************/
	/* 34 */
	0x07,         	/* bLength: �˵��������ĳ���Ϊ7�ֽ�*/
    USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: �˵�������������Ϊ0x05*/
    0x01,         	/* bEndpointAddress: �ö˵�(����)�ĵ�ַ,D7:0(OUT),1(IN),D6~D4:����,D3~D0:�˵��*/               
    0x03,         	/* bmAttributes: �˵������ΪΪ�ж϶˵�.
			D0~D1��ʾ��������:0(���ƴ���),1(��ʱ����),2(��������),3(�жϴ���)
			�ǵ�ʱ����˵�:D2~D7:����Ϊ0
			��ʱ����˵㣺
			D2~D3��ʾͬ��������:0(��ͬ��),1(�첽),2(����),3(ͬ��)
			D4~D5��ʾ��;:0(���ݶ˵�),1(�����˵�),2(�������������ݶ˵�),3(����)��D6~D7:����,*/
    0x01,         	/* wMaxPacketSize: �ö˵�֧�ֵ���������Ϊ�ֽ�*/
    0x00,
    0x0A,         	/* bInterval: ��ѯ���(32ms) */
   /* 41 */
}; 

//const uint8_t Joystick_ReportDescriptor[JOYSTICK_SIZ_REPORT_DESC] =
//  {
//    0x05,          /*Usage Page(Generic Desktop)*/
//    0x01,
//    0x09,          /*Usage(Mouse)*/
//    0x02,
//    0xA1,          /*Collection(Logical)*/
//    0x01,
//    0x09,          /*Usage(Pointer)*/
//    0x01,
//    /* 8 */
//    0xA1,          /*Collection(Linked)*/
//    0x00,
//    0x05,          /*Usage Page(Buttons)*/
//    0x09,
//    0x19,          /*Usage Minimum(1)*/
//    0x01,
//    0x29,          /*Usage Maximum(3)*/
//    0x03,
//    /* 16 */
//    0x15,          /*Logical Minimum(0)*/
//    0x00,
//    0x25,          /*Logical Maximum(1)*/
//    0x01,
//    0x95,          /*Report Count(3)*/
//    0x03,
//    0x75,          /*Report Size(1)*/
//    0x01,
//    /* 24 */
//    0x81,          /*Input(Variable)*/
//    0x02,
//    0x95,          /*Report Count(1)*/
//    0x01,
//    0x75,          /*Report Size(5)*/
//    0x05,
//    0x81,          /*Input(Constant,Array)*/
//    0x01,
//    /* 32 */
//    0x05,          /*Usage Page(Generic Desktop)*/
//    0x01,
//    0x09,          /*Usage(X axis)*/
//    0x30,
//    0x09,          /*Usage(Y axis)*/
//    0x31,
//    0x09,          /*Usage(Wheel)*/
//    0x38,
//    /* 40 */
//    0x15,          /*Logical Minimum(-127)*/
//    0x81,
//    0x25,          /*Logical Maximum(127)*/
//    0x7F,
//    0x75,          /*Report Size(8)*/
//    0x08,
//    0x95,          /*Report Count(3)*/
//    0x03,
//    /* 48 */
//    0x81,          /*Input(Variable, Relative)*/
//    0x06,
//    0xC0,          /*End Collection*/
//    0x09,
//    0x3c,
//    0x05,
//    0xff,
//    0x09,
//    /* 56 */
//    0x01,
//    0x15,
//    0x00,
//    0x25,
//    0x01,
//    0x75,
//    0x01,
//    0x95,
//    /* 64 */
//    0x02,
//    0xb1,
//    0x22,
//    0x75,
//    0x06,
//    0x95,
//    0x01,
//    0xb1,
//    /* 72 */
//    0x01,
//    0xc0
//  }
//  ; /* Joystick_ReportDescriptor */


/* HID�ı���������*/
/*������8�ֽڷ��ͣ�
**  ��һ�ֽڱ�ʾ������Ƿ��£�D0:Ctrl D1:Shift D2:Alt
**  �ڶ��ֽڱ�����ֵΪ0
**  ����~�ڰ��ֽ�:��ͨ����ֵ������,�����ͬʱ����6����
**������1�ֽڽ���:��Ӧ�����ϵ�LED��,����ֻ��������λ��
**	D0:Num Lock   D1:Cap Lock   D2:Scroll Lock   D3:Compose   D4:Kana*/
const uint8_t Joystick_ReportDescriptor[JOYSTICK_SIZ_REPORT_DESC] = 
{ 	
	/*short Item   D7~D4:bTag;D3~D2:bType;D1~D0:bSize
	**bTag ---����Ŀ  	1000:����(Input) 1001:���(Output) 1011:����(Feature)	1010:����(Collection) 1100:�ؼ���(End Collection) 
	**		  ȫ����Ŀ 	0000:��;ҳ(Usage Page) 0001:�߼���Сֵ(Logical Minimum) 0010:�߼����ֵ(Logical Maximum) 0011:������Сֵ(Physical Minimum)
	**					0100:�������ֵ(Physical Maximum) 0101:��Ԫָ��(Unit Exponet) 0110:��Ԫ(Unit) 0111:�������С(Report Size)
	**					1000:����ID(Report ID) 1001:����������(Report Count) 1010:ѹջ(Push) 1011:��ջ(Pop) 1100~1111:����(Reserved)
	**		  �ֲ���Ŀ	0000:��;(Usage) 0001:��;��Сֵ(Usage Minimum) 0010:��;���ֵ(Usage Maximum) 0011:��ʶ������(Designator Index)
	**					0100:��ʶ����Сֵ(Designator Minimum) 0101:��ʶ�����ֵ(Designator Maximum) 0111:�ַ�������(String Index) 1000:�ַ�����Сֵ(String Minimum)   
	**					1001:�ַ������ֵ(String Maximum) 1010:�ָ���(Delimiter) ����������(Reserved)
	**bType---00:����Ŀ(main)  01:ȫ����Ŀ(globle)  10:�ֲ���Ŀ(local)  11:����(reserved)
	**bSize---00:0�ֽ�  01:1�ֽ�  10:2�ֽ�  11:4�ֽ�*/
	
	//0x05:0000 01 01 ���Ǹ�ȫ����Ŀ����;ҳѡ��Ϊ��ͨ����ҳ
	0x05, 0x01, // USAGE_PAGE (Generic Desktop)
	//0x09:0000 10 01 ���Ǹ�ȫ����Ŀ����;ѡ��Ϊ����
	0x09, 0x06, // USAGE (Keyboard)
	//0xa1:1010 00 01 ���Ǹ�����Ŀ��ѡ��ΪӦ�ü��ϣ�
	0xa1, 0x01, // COLLECTION (Application)
	//0x05:0000 01 11 ���Ǹ�ȫ����Ŀ����;ҳѡ��Ϊ����/����
	0x05, 0x07, // USAGE_PAGE (Keyboard/Keypad)

	//0x19:0001 10 01 ���Ǹ��ֲ���Ŀ����;����СֵΪ0xe0����Ӧ�����ϵ���ctrl��
	0x19, 0xe0, // USAGE_MINIMUM (Keyboard LeftControl)
	//0x29:0010 10 01 ���Ǹ��ֲ���Ŀ����;�����ֵΪ0xe7����Ӧ�����ϵ���GUI(WIN)��
	0x29, 0xe7, // USAGE_MAXIMUM (Keyboard Right GUI)
	//0x15:0001 01 01 ���Ǹ�ȫ����Ŀ��˵�����ݵ��߼�ֵ��СֵΪ0
	0x15, 0x00, // LOGICAL_MINIMUM (0)
	//0x25:0010 01 01 ���Ǹ�ȫ����Ŀ��˵�����ݵ��߼�ֵ���ֵΪ1
	0x25, 0x01, // LOGICAL_MAXIMUM (1)

	//0x95:1001 01 01 ���Ǹ�ȫ����Ŀ�������������Ϊ8��
	0x95, 0x08, // REPORT_COUNT (8)
	//0x75:0111 01 01 ���Ǹ�ȫ����Ŀ��ÿ��������ĳ���Ϊ1λ
	0x75, 0x01, // REPORT_SIZE (1)	   
	//0x81:1000 00 01 ���Ǹ�����Ŀ����8*1bit��������Ϊ���룬����Ϊ:Data,Var,Abs
	0x81, 0x02, // INPUT (Data,Var,Abs)

	//0x95:1001 01 01 ���Ǹ�ȫ����Ŀ,�����������Ϊ1��
	0x95, 0x01, // REPORT_COUNT (1)
	//0x75:0111 01 01 ���Ǹ�ȫ����Ŀ��ÿ��������ĳ���Ϊ8λ
	0x75, 0x08, // REPORT_SIZE (8)
	//0x81:1000 00 01 ���Ǹ�����Ŀ����1*8bit��������Ϊ���룬����Ϊ:Cnst,Var,Abs
	0x81, 0x03, // INPUT (Cnst,Var,Abs)

	//0x95:1001 01 01 ���Ǹ�ȫ����Ŀ�������������Ϊ6��
	0x95, 0x06, // REPORT_COUNT (6)
	//0x75:0111 01 01 ���Ǹ�ȫ����Ŀ��ÿ��������ĳ���Ϊ8λ
	0x75, 0x08, // REPORT_SIZE (8)
	//0x25:0010 01 01 ���Ǹ�ȫ����Ŀ���߼����ֵΪ255
	0x25, 0xFF, // LOGICAL_MAXIMUM (255)
	//0x19:0001 10 01 ���Ǹ��ֲ���Ŀ����;����СֵΪ0
	0x19, 0x00, // USAGE_MINIMUM (Reserved (no event indicated))
	//0x29:0010 10 01 ���Ǹ��ֲ���Ŀ����;�����ֵΪ0x65
	0x29, 0x65, // USAGE_MAXIMUM (Keyboard Application)
	//0x81:1000 00 01 ���Ǹ�����Ŀ����6*8bit����������Ϊ���룬����Ϊ����Ϊ:Data,Var,Abs
	0x81, 0x00, // INPUT (Data,Ary,Abs)

	//0x25:0010 01 01 ���Ǹ�ȫ����Ŀ���߼������ֵΪ1
	0x25, 0x01, // LOGICAL_MAXIMUM (1)
	//0x95:1001 01 01 ���Ǹ�ȫ����Ŀ�������������Ϊ2
	0x95, 0x02, // REPORT_COUNT (2)
	//0x75:0111 01 01 ���Ǹ�ȫ����Ŀ��ÿ��������ĳ���Ϊ1λ
	0x75, 0x01, // REPORT_SIZE (1)
	//0x05:0000 01 01 ���Ǹ�ȫ����Ŀ����;ҳѡ��ΪLEDҳ
	0x05, 0x08, // USAGE_PAGE (LEDs)
	//0x19:0001 10 01 ���Ǹ��ֲ���Ŀ����;����СֵΪ0x01,��Ӧ�����ϵ�Num Lock
	0x19, 0x01, // USAGE_MINIMUM (Num Lock)
	//0x29:0010 10 01 ���Ǹ��ֲ���Ŀ����;�����ֵΪ0x02,��Ӧ�����ϵ�Caps Lock
	0x29, 0x02, // USAGE_MAXIMUM (Caps Lock)
	//0x91:1001 00 01 ���Ǹ�����Ŀ����2*1bit����������Ϊ���������Ϊ:Data,Var,Abs
	0x91, 0x02, // OUTPUT (Data,Var,Abs)

	//0x95:1001 01 01 ���Ǹ�ȫ����Ŀ�������������Ϊ1��
	0x95, 0x01, // REPORT_COUNT (1)
	//0x75:0111 01 01 ���Ǹ�ȫ����Ŀ��ÿ��������ĳ���Ϊ6bit,������ǰ���2bit���1�ֽ�
	0x75, 0x06, // REPORT_SIZE (6)
	//0x91:1001 00 01 ���Ǹ�����Ŀ����1*6bit��������Ϊ���������Ϊ:Cnst,Var,Abs
	0x91, 0x03, // OUTPUT (Cnst,Var,Abs)

	0xc0        // END_COLLECTION
}; 

/* USB String Descriptors (optional) */
const uint8_t Joystick_StringLangID[JOYSTICK_SIZ_STRING_LANGID] =
  {
    JOYSTICK_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }
  ; /* LangID = 0x0409: U.S. English */

const uint8_t Joystick_StringVendor[JOYSTICK_SIZ_STRING_VENDOR] =
  {
    JOYSTICK_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
    'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
    'c', 0, 's', 0
  };

const uint8_t Joystick_StringProduct[JOYSTICK_SIZ_STRING_PRODUCT] =
{
	JOYSTICK_SIZ_STRING_PRODUCT,          /* bLength */
	USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
	'L', 0, 'X', 0, 'G', 0, '-', 0, 'W', 0, 'O', 0, 'R', 0, 'L', 0, 'D', 0, ' ', 0, 'E', 0, 'D', 0, 'I', 0, 'T', 0,
	' ', 0, 
	0X1B,0X52,//
	0x16,0X4E,//
	0X00,0X4E,//��
	0XF7,0X53,//�� 
};

uint8_t Joystick_StringSerial[JOYSTICK_SIZ_STRING_SERIAL] =
  {
    JOYSTICK_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0
  };

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

