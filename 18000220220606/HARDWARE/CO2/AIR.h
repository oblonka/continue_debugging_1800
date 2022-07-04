#ifndef __AIR_H
#define __AIR_H



#include "includes.h"	
#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "sram.h"
#include "malloc.h"
#include "ILI93xx.h"

#include "WIFI.h"//�����Զ��崮�ڵĺ���



//�����ṹ��union �ģ���ֹ�������屨��
#if defined ( __CC_ARM   )
#pragma anon_unions
#endif



//����������̼�������ݵĽṹ��ĺ���
#define CO2_RX_BUF_MAX_LEN    1024       //����ֽ���     1024


#define CO2_USART(fmt, ...)    USART_printf (USART1, fmt, ##__VA_ARGS__) 






//��غ궨��
#define    Data_Head1           0x16     //����֡ͷ1Ϊ0xFF
#define    Data_Head2           0x05     //����֡ͷ2Ϊ0x86
#define    Data_Head3           0x01     //����֡ͷ2Ϊ0x86
#define	   Data_Length            8      //һ֡��9������





extern uint16_t    CO2_Measure_data;










extern struct STRUCT_USART_Fram_CO2   //CO2����֡      �ṹ��
						{
								char Data_RX_BUF_CO2[CO2_RX_BUF_MAX_LEN];//�������ݵ�buffer��������    ����
								union 
								{
										__IO u16 InfAll_CO2;
										struct 
												{
												__IO u16 FramLength_CO2       :15;                               // 14:0 
												__IO u16 FramFinishFlag_CO2   :1;                                // 15 
												}InfBit_CO2;
								}; 
						}CO2_Fram_Record_Struct;


						
						
						
#define DE_CO2_NoRX_Num 15            //3��
#define DE_CO2_Rest_Time 100          //100*5ms = 500ms

						

void CO2_VCC_CTR_Init(void);          //CO2��Դ�Ŀ�������
extern void uart1_init_CO2(u32 bound);//usart�ϵĴ��ڳ�ʼ��
void CO2_Sensor_VCC_Contrl(uint8_t n);//��Դ���ſ���
void CO2_Send_Data(void);	            //���Ͳ��������ݣ�����CO2Ũ����ֵ   11,01,01,ed
void Read_CO2_ppm(void);

void CO2_Tx();

uint8_t SINGLE_CO2_Calibration(uint16_t Data);
uint8_t CO2_AUTO_CONTRL_Cal_ON_OFF(uint8_t ON_OFF);





uint8_t  Fifo_RXInsert(uint8_t Fifo_Data);








/*
//����ͷ�ļ� 

#include "sys.h"  

// ��غ궨�� 
#define    USART2_RX_EN 			   1			 //0,������;1,����.
#define    USART_REC_LEN  			200 


//�ⲿ���� 
extern  u16  CO2_data;
extern  u16  USART_BUF[USART_REC_LEN]; 

//��������
//void send_code(void);
void CO2_Tx(void);                  //���ͼ������
void USART1_Init(u32 bound);				//����2��ʼ�� 
*/










#endif




