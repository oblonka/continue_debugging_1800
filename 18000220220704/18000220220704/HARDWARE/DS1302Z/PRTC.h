#ifndef __PRTC_H
#define __PRTC_H

/*

һ��Ӳ��������ܴ��ڵ�����


1����·���Ӵ������麸���Ӵ��ߡ�

2��DS1302�ǻ��ģ��ٵģ����ֿ����Բ���̫�����Թ����ֹ�����оƬ����ȫ�����õ���������
����Щֻ�ǲ��ȶ���������ѡ�


3����һ��������Ҫ�ģ�����32.768K�ľ����õĲ��ԣ�
DS1302Ҫʹ��ר�õľ��񣬼��ڲ��ĵ�����6P�ġ�
�������ж���32.768K�ľ��񣬵��ڲ�������12P��20P�ȣ�
��Щ��������DS1302���ǲ�������ģ��Ҿ�Ϊ����������ڹ��ܳ�ʱ�䣬
�����������飬��·��������飬DS1302���������
���ǲ��ߣ������ϸ��DS1302�Ĺ���飬�ŷ���Ҫ6P�ľ���
����ëǮ���˸�6P�ģ��Ա����е��ǣ��������������ˡ�
�������ʱ��Ҳ����������ָ��ס��·���Ͼ�����������㣬
��ʱ�ͻ����������ǿ��Կ϶��Ǿ��������ˡ�


�����������
1���в������ѵĴ����Ǵ����ϻ������µģ������ı����õģ�
������Ҫ�ر�ע��һ�����⣬���Ǹ������������ʱ������
����һ����ʱ����delay_ms(5); Ҫ����ʱ5MS,����ԭ���ĳ����ʹ�������ǵ�Ƭ����4M����
����ֲ������8M��Ƭ�������У�����ʱʱ��϶������ˣ�
��ʱDS1302�Ϳ��ܲ��ߡ��������Ҳ����������LCD��ʾ���У�
��������룬������ʾ�������ں���ң����Ҳ�������������
���ڴ����е���ʱʱ�䲻�ԣ�Ҳ�᲻�ܽ��յ�ң���źţ�
�������Ѵ�ң��ڽ��д�����ֲʱ��һ��Ҫע�⾧��Ĵ�С��
����Լ��ľ���ͬʱ��Ҫ�����޸���ʱ��������ʱʱ�䡣


2���״�ʹ��DS1302 ʱ��Ҫ�Ȱ�����Ĳ����飺�����ú÷֡��룬
Ȼ����ʾ��ʱ����Լ����õ�ʱ���Ƿ�һ�£����һ�£�
˵��ʱ���û�����⣬�ٿ��Ƿ���ʱ������ʱ��
���ְ�ס����ĺ��㿴��û�б仯���������ñ�Ľ������������������ţ�
Ӧ��2V���ϵĶ���������6P�ľ���


3��һ��Ҫ����ʱ�ӣ�DS1302����Ĵ�����
�ڳ����ʼ��ʱһ��Ҫ��l����write_ds 1302(0x80,0x00)����䣬
����0x80����Ĵ����ĵ�ַ��0x00 ��д������ݣ�
������ݵ����λһ��Ҫ��0����0 ���ܿ���ʱ����ʱ��


˵�߿��ˣ����ھ����ϲ�С���ݣ������˾ʹܸ�С����

�첢����


typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8; 

*/





////#define DS_SCLK_Pin         GPIO_Pin_3//GPIO_Pin_4
////#define DS_SCLK_GPIO_Port   GPIOE

////#define DS_IO_Pin           GPIO_Pin_4//GPIO_Pin_4
////#define DS_IO_GPIO_Port     GPIOE

////#define DS_CE_Pin           GPIO_Pin_4//GPIO_Pin_4
////#define DS_CE_GPIO_Port     GPIOE



//#include "sys.h"
//#include "delay.h"
//#include "usart.h" 
//#include "includes.h"	
//#include "stm32f4xx.h"

//typedef uint32_t u32;
//typedef uint16_t u16;
//typedef uint8_t u8; 




//#define BIT0    0x0001           
//#define BIT1    0x0002           
//#define BIT2    0x0004           
//#define BIT3    0x0008           
//#define BIT4    0x0010            
//#define BIT5    0x0020            
//#define BIT6    0x0040            
//#define BIT7    0x0080            
//#define BIT8    0x0100            
//#define BIT9    0x0200            
//#define BITA    0x0400           
//#define BITB    0x0800           
//#define BITC    0x1000            
//#define BITD    0x2000           
//#define BITE    0x4000          
//#define BITF    0x8000  




//typedef struct
//			{
//				uint16_t Year;
//				 uint8_t Month;
//				 uint8_t Day;
//				 uint8_t Hour;
//				 uint8_t Minute;	
//			}Canshu_Time;






////DS1302Z�ļ򻯰��SPI�Ľӿڳ�ʼ��
////�޸ļĴ�������
//			
//#define DS1302CLK_H         GPIO_WriteBit(GPIOE, GPIO_Pin_3, Bit_SET)        //ʱ�ӵĸ�  GPIO_WriteBit
//#define DS1302CLK_L         GPIO_WriteBit(GPIOE, GPIO_Pin_3, Bit_RESET)      //ʱ�ӵĵ�  GPIO_WriteBit

//#define DS1302IO_SDA_H      GPIO_WriteBit(GPIOE, GPIO_Pin_4, Bit_SET)        //���ݵĸ�  GPIO_WriteBit
//#define DS1302IO_SDA_L      GPIO_WriteBit(GPIOE, GPIO_Pin_4, Bit_RESET)      //���ݵĵ�  GPIO_WriteBit

//#define DS1302_SDA_READ     GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)          //���ݿڵĶ�     GPIO_ReadInputDataBit
//#define DS1302_SCL_READ     GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)          //ʱ�ӿڵĶ�     GPIO_ReadInputDataBit

//#define DS1302_CE_H         GPIO_WriteBit(GPIOE, GPIO_Pin_5, Bit_SET)        //GPIO_WriteBit
//#define DS1302_CE_L         GPIO_WriteBit(GPIOE, GPIO_Pin_5, Bit_RESET)      //GPIO_WriteBit






//void DS1302_Delay( int n);

//void DS1302_SDA_IN(void);
//void DS1302_SDA_OUT(void);

//void DS1302_SCK_OUT(void);
//void DS1302_SCK_IN(void);

//void DS1302_CE_OUT(void);
//void DS1302_CE_IN(void);


//void DS1302Z_WriteQ(void);  //һ��ȫд��
//void DS1302Z_Read(void);

//void Time_Init(void);

//uint8_t DS1302_ReadBYTE(uint8_t Adr,uint8_t Data,uint8_t CorR);
//void DS1302_WriteBYTE(uint8_t Adr,uint8_t Data,uint8_t CorR);










//�����Ĳ����2
// 
//#include "sys.h" 
//#include "delay.h"
//#include "usart.h" 
//#include "includes.h"	

//#include "stm32f4xx.h"


//typedef uint32_t u32;
//typedef uint16_t u16;
//typedef uint8_t u8; 



//#define CE_L    GPIO_ResetBits(GPIOE,GPIO_Pin_5)//E5����ʹ��λ
//#define CE_H      GPIO_SetBits(GPIOE,GPIO_Pin_5)//E5����ʹ��λ

//#define SCLK_L  GPIO_ResetBits(GPIOE,GPIO_Pin_3)//E3����ʱ����
//#define SCLK_H    GPIO_SetBits(GPIOE,GPIO_Pin_3)//E3����ʱ����

//#define DATA_L  GPIO_ResetBits(GPIOE,GPIO_Pin_4)//E4����������
//#define DATA_H    GPIO_SetBits(GPIOE,GPIO_Pin_4)//E4����������
// 
// 
// 
//struct TIMEData
//{
//	uint16_t year;
//	uint8_t  month;
//	uint8_t  day;
//	uint8_t  hour;
//	uint8_t  minute;
//	uint8_t  second;
//	uint8_t  week;
//};//����TIMEData�ṹ�巽��洢ʱ����������



//extern struct TIMEData TimeData;                     //ȫ�ֱ���

//void ds1302_gpio_init();                             //ds1302�˿ڳ�ʼ��
//void ds1302_write_onebyte(uint8_t data);             //��ds1302����һ�ֽ�����
//void ds1302_wirte_rig(uint8_t address,uint8_t data); //��ָ���Ĵ���дһ�ֽ�����
//uint8_t ds1302_read_rig(uint8_t address);            //��ָ���Ĵ�����һ�ֽ�����


//void ds1032_init();                                  //ds1302��ʼ������
//void ds1032_DATAOUT_init();                          //IO�˿�����Ϊ���
//void ds1032_DATAINPUT_init();                        //IO�˿�����Ϊ����

//void ds1032_read_time();                             //��ds1302��ȡʵʱʱ�䣨BCD�룩
//void ds1032_read_realTime();                         //��BCD��ת��Ϊʮ��������
// 








//����3


 /*
 
#include "sys.h" 
#include "delay.h"
#include "usart.h" 
#include "includes.h"	

#include "stm32f4xx.h"


typedef uint32_t u32;
typedef uint16_t u16;
typedef  uint8_t  u8; 



#define CE_L    GPIO_ResetBits(GPIOE,GPIO_Pin_5)  //����ʹ��λ  E5
#define CE_H      GPIO_SetBits(GPIOE,GPIO_Pin_5)  //����ʹ��λ

#define SCLK_L  GPIO_ResetBits(GPIOE,GPIO_Pin_3)  //����ʱ����  E3
#define SCLK_H    GPIO_SetBits(GPIOE,GPIO_Pin_3)  //����ʱ����

#define DATA_L  GPIO_ResetBits(GPIOE,GPIO_Pin_4)  //����������  E4
#define DATA_H    GPIO_SetBits(GPIOE,GPIO_Pin_4)  //����������
 
 
 
struct TIMEData
			{
				u16 year;
				u8  month;
				u8  day;
				u8  hour;
				u8  minute;
				u8  second;
				u8  week;
			};//����TIMEData�ṹ�巽��洢ʱ����������



extern struct TIMEData TimeData;//ȫ�ֱ���

void ds1302_gpio_init();//ds1302�˿ڳ�ʼ��
void ds1302_write_onebyte(u8 data);//��ds1302����һ�ֽ�����
void ds1302_wirte_rig(u8 address,u8 data);//��ָ���Ĵ���дһ�ֽ�����
u8 ds1302_read_rig(u8 address);//��ָ���Ĵ�����һ�ֽ�����
void ds1032_init();//ds1302��ʼ������
void ds1032_DATAOUT_init();//IO�˿�����Ϊ���
void ds1032_DATAINPUT_init();//IO�˿�����Ϊ����
void ds1032_read_time();//��ds1302��ȡʵʱʱ�䣨BCD�룩
void ds1032_read_realTime();//��BCD��ת��Ϊʮ��������
 
*/





//����4




#include "sys.h" 
#include "delay.h"
#include "usart.h" 
#include "includes.h"	

#include "stm32f4xx.h"


typedef uint32_t u32;
typedef uint16_t u16;
typedef  uint8_t  u8; 



#define uchar unsigned char
#define uint unsigned int
/***DS1302ʱ��оƬ****************************/
//CLK--->PE3
//IO---->PE4
//RES--->PE5
/****************************/

#define OUT   0x01
#define IN    0x00
extern uchar time_data[6];//ʱ��������

#define DS1302_PORT   GPIOE

#define CLK_Reset_0  GPIO_ResetBits(GPIOE,GPIO_Pin_3);          //GPIO_ResetBits(GPIOE,GPIO_Pin_4);
#define CLK_Set_1    GPIO_SetBits(GPIOE,GPIO_Pin_3);

#define IO_Reset_0   GPIO_ResetBits(GPIOE,GPIO_Pin_4);
#define IO_Set_1     GPIO_SetBits(GPIOE,GPIO_Pin_4);

#define RES_Reset_0  GPIO_ResetBits(GPIOE,GPIO_Pin_5);
#define RES_Set_1    GPIO_SetBits(GPIOE,GPIO_Pin_5);

#define IO_Read   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
/*************************/
#define Time_24_Hour      0x00       //24Сʱ��
#define Time_Start        0x00       //��ʼ��ʱ
//DS1302�Ĵ�������ָ���ʱ���ַ
#define ds1302_sec_addr   0x80       //��
#define ds1302_min_addr   0x82       //��
#define ds1302_hour_addr  0x84       //ʱ
#define ds1302_day_addr   0x86       //��
#define ds1302_month_addr 0x88       //��
#define ds1302_year_addr  0x8c       //��
/********************/
void DS1302_GPIOInit(void);
void DS1302_IO_GPIO(uchar FLAG);//����IO�ķ���
void DS1302_delay(u8 dd);
void DS1302_Write(uchar add,uchar dat);
uchar DS1302_Read(uchar add);
void DS1302_SetTime(uchar *ad);
void DS1302_OFF(void);
void DS1302_ON(void);
void DS1302_init(uchar *time);
void DS1302_Readtime(void);



#endif

