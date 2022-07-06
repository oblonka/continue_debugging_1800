#ifndef __HTIIC_H
#define __HTIIC_H
						 
#include "sys.h"
#include "delay.h"	
#include "usart.h" 
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8; 
						 
//IO��������
#define HTIIC_SDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9����ģʽ
#define HTIIC_SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9���ģʽ

//IO��������	 
#define HTIIC_SCL        PBout(8) //SCL
#define HTIIC_SDA        PBout(9) //���SDA	 
#define HTIIC_READ_SDA   PBin(9)  //����SDA 

//IIC���в�������
void HTIIC_Init(void);                   //��ʼ��IIC��IO��				 
void HTIIC_Start(void);				           //����IIC��ʼ�ź�
void HTIIC_Stop(void);	  			         //����IICֹͣ�ź�
void HTIIC_Send_Byte(u8 txd);			       //IIC����һ���ֽ�
  u8 HTIIC_Read_Byte(unsigned char ack); //IIC��ȡһ���ֽ�
  u8 HTIIC_Wait_Ack(void); 				       //IIC�ȴ�ACK�ź�
void HTIIC_Ack(void);					           //IIC����ACK�ź�
void HTIIC_NAck(void);				           //IIC������ACK�ź�

void HTIIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
  u8 HTIIC_Read_One_Byte(u8 daddr,u8 addr);	  



#endif

