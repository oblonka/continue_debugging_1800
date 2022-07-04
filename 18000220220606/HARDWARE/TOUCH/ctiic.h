#ifndef __CTIIC_H
#define __CTIIC_H


#include "sys.h"	    
#include "cst148.h"
				 
				 
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t   u8;	 
				  
					
//IO��������
#define  CST_SDA_IN()  {GPIOB->MODER&=~(3<<(2*11));GPIOB->MODER|=0<<2*11;}	//PB11����ģʽ
#define CST_SDA_OUT()  {GPIOB->MODER&=~(3<<(2*11));GPIOB->MODER|=1<<2*11;} 	//PB11���ģʽ


//��������IO�ڶ��� 
#define CST_IIC_SCL    PBout(10) 	//SCL     
#define CST_IIC_SDA    PBout(11) 	//SDA	 
#define CST_READ_SDA    PBin(11)  //����SDA 

#define CST_IIC_RST		 PAout(4)   //148��λ����		PA4   Ĭ���ǵ�Ƭ���ĸ�λ������   20220302
#define CST_IIC_INT 	 PBin(13)		//148�ж����� δʹ��   PB13                      20220302




//IIC���в�������
void CST_IIC_Init(void);                   //��ʼ��IIC��IO��		
void CST_IIC_Start(void);				           //����IIC��ʼ�ź�
void CST_IIC_Stop(void);	  				       //����IICֹͣ�ź�

void CST_IIC_Send_Byte(u8 txd);			       //IIC����һ���ֽ�
  u8 CST_IIC_Read_Byte(unsigned char ack); //IIC��ȡһ���ֽ�

  u8 CST_IIC_Wait_Ack(void); 				       //IIC�ȴ�ACK�ź�
void CST_IIC_Ack(void);					           //IIC����ACK�ź�
void CST_IIC_NAck(void);					         //IIC������ACK�ź�

  u8 CST148_WR_Reg(u16 reg,u8 *buf,u8 len);//���� д������          �Ĵ�����ַ  ����  ���ݳ���
void CST148_RD_Reg(u16 reg,u8 *buf,u8 len);//���� ��ȡ�Ĵ�����ַ    �Ĵ�����ַ  ����  ���ݳ���


#endif



