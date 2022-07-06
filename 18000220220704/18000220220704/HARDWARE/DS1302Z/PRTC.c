
#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "sram.h"
#include "malloc.h"
#include "ILI93xx.h"

#include "PRTC.h"





/*
2022-4-11 14:47:32

DS1302Z_SCLK      PE3
DS1302Z_IO        PE4
DS1302Z_CE        PE5

io����˫����շ�����     ʵ����SPI ��ȫ˫���Ľӿ�

Ҫ��ds1302��ʱ�������Ƚ������㣬�����뵥Ԫ����0x80��һֱ���ߡ�


*/




//uint8_t Miao = 0;                   

//Canshu_Time DS1302_Time;
//Canshu_Time DS1302_SetTime;






//void Time_Init(void)
//		{
//			DS1302_SetTime.Year   = 2022;
//			DS1302_SetTime.Month  = 4;
//			DS1302_SetTime.Day    = 12;
//			
//			DS1302_SetTime.Hour   = 16;
//			DS1302_SetTime.Minute = 45;
//		 //DS1302_WriteBYTE(0x80,0x00,0);   //����ʱ�ӵĲ���
//		}






//void DS1302_Delay( int n)//�����ʱ��Ҫ�޸ĵ�ʱ��    ʱ�򲻶�
//		{
//			uint16_t i = 0;
//			uint16_t j = 0;

//			for(i = 0;i<n;i++)
//				{
//						for(j = 0;j<1000;j++);//��100�޸�Ϊ1000
//				}
//		}



///*********************************************ʱ��оƬ������λ�����룬����ĳ�ʼ������*************************************************/
//void DS1302_SDA_IN(void)
//{
//	
////	GPIO_InitTypeDef GPIO_InitStruct = {0};
////	 
////	GPIO_InitStruct.Pin = DS_IO_Pin;
////  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
////  GPIO_InitStruct.Pull = GPIO_NOPULL;
////  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
////  HAL_GPIO_Init(DS_IO_GPIO_Port, &GPIO_InitStruct);
//	 
//	
//	GPIO_InitTypeDef GPIO_InitStructure = {0};
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);     //ʹ��GPIOE��ʱ��
//	
//	GPIO_InitStructure.GPIO_Pin    =  GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode   =  GPIO_Mode_IN;          //�����ģʽ
//	//GPIO_InitStructure.GPIO_OType  =  GPIO_OType_PP;       //�������
//	GPIO_InitStructure.GPIO_PuPd   =  GPIO_PuPd_NOPULL;      //�������
//	GPIO_InitStructure.GPIO_Speed  =  GPIO_Speed_100MHz;     //����GPIO
//	GPIO_Init(GPIOE,&GPIO_InitStructure); 
//	 
//}




//void DS1302_SDA_OUT(void)
//{
////	GPIO_InitTypeDef GPIO_InitStruct = {0};
////	
////	GPIO_InitStruct.Pin = DS_IO_Pin;
////  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
////  GPIO_InitStruct.Pull = GPIO_NOPULL;
////  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
////  HAL_GPIO_Init(DS_IO_GPIO_Port, &GPIO_InitStruct);
//	
//	
//  GPIO_InitTypeDef GPIO_InitStructure  = {0};
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);     //ʹ��GPIOB��ʱ��
//	
//	GPIO_InitStructure.GPIO_Pin    =  GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode   =  GPIO_Mode_OUT;         //���
//	GPIO_InitStructure.GPIO_OType  =  GPIO_OType_PP;         //�������
//	GPIO_InitStructure.GPIO_PuPd   =  GPIO_PuPd_NOPULL;      //�������
//	GPIO_InitStructure.GPIO_Speed  =  GPIO_Speed_100MHz;     //����GPIO
//	GPIO_Init(GPIOE,&GPIO_InitStructure);
//	
//	
//}




///*********************************************ʱ��оƬ��ʱ�ӵ����룬����ĳ�ʼ������*************************************************/
//void DS1302_SCK_OUT(void)
//{
////	GPIO_InitTypeDef GPIO_InitStruct = {0};
////	
////	GPIO_InitStruct.Pin = DS_SCLK_Pin;
////  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
////  GPIO_InitStruct.Pull = GPIO_NOPULL;
////  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
////  HAL_GPIO_Init(DS_SCLK_GPIO_Port, &GPIO_InitStruct);
//	
//	
//	
//	GPIO_InitTypeDef GPIO_InitStructure = {0};
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);     //ʹ��GPIOB��ʱ��
//	
//	GPIO_InitStructure.GPIO_Pin    =  GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Mode   =  GPIO_Mode_OUT;         //���
//	GPIO_InitStructure.GPIO_OType  =  GPIO_OType_PP;         //�������
//	GPIO_InitStructure.GPIO_PuPd   =  GPIO_PuPd_NOPULL;      //�������
//	GPIO_InitStructure.GPIO_Speed  =  GPIO_Speed_100MHz;     //����GPIO
//	GPIO_Init(GPIOE,&GPIO_InitStructure);
//	
//}





//void DS1302_SCK_IN(void)
//{
////	GPIO_InitTypeDef GPIO_InitStruct = {0};
////	 
////	GPIO_InitStruct.Pin = DS_SCLK_Pin;
////  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
////  GPIO_InitStruct.Pull = GPIO_NOPULL;
////  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
////  HAL_GPIO_Init(DS_SCLK_GPIO_Port, &GPIO_InitStruct);
//	
//	
//	GPIO_InitTypeDef GPIO_InitStructure = {0};
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);     //ʹ��GPIOB��ʱ��
//	
//	GPIO_InitStructure.GPIO_Pin    =  GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Mode   =  GPIO_Mode_IN;         //���
//	//GPIO_InitStructure.GPIO_OType  =  GPIO_OType_PP;         //�������
//	GPIO_InitStructure.GPIO_PuPd   =  GPIO_PuPd_NOPULL;      //�������
//	GPIO_InitStructure.GPIO_Speed  =  GPIO_Speed_100MHz;     //����GPIO
//	GPIO_Init(GPIOE,&GPIO_InitStructure);
//	
//	
//	
//	
//}





///*********************************************ʱ��оƬ��CE�����룬����ĳ�ʼ������*************************************************/
//void DS1302_CE_OUT(void)
//{
////	GPIO_InitTypeDef GPIO_InitStruct = {0};
////	
////	GPIO_InitStruct.Pin = DS_CE_Pin;
////  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
////  GPIO_InitStruct.Pull = GPIO_NOPULL;
////  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
////  HAL_GPIO_Init(DS_CE_GPIO_Port, &GPIO_InitStruct);
//	
//	
//	GPIO_InitTypeDef GPIO_InitStructure = {0};
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);     //ʹ��GPIOB��ʱ��
//	
//	GPIO_InitStructure.GPIO_Pin    =  GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Mode   =  GPIO_Mode_OUT;         //���
//	GPIO_InitStructure.GPIO_OType  =  GPIO_OType_PP;         //�������
//	GPIO_InitStructure.GPIO_PuPd   =  GPIO_PuPd_NOPULL;      //�������
//	GPIO_InitStructure.GPIO_Speed  =  GPIO_Speed_100MHz;     //����GPIO
//	GPIO_Init(GPIOE,&GPIO_InitStructure);
//	
//	
//	
//}







//void DS1302_CE_IN(void)
//{
////	GPIO_InitTypeDef GPIO_InitStruct = {0};
////	 
////	GPIO_InitStruct.Pin = DS_CE_Pin;
////  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
////  GPIO_InitStruct.Pull = GPIO_NOPULL;
////  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
////  HAL_GPIO_Init(DS_CE_GPIO_Port, &GPIO_InitStruct);
//	
//	
//	
//	GPIO_InitTypeDef GPIO_InitStructure = {0};
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);     //ʹ��GPIOB��ʱ��
//	
//	GPIO_InitStructure.GPIO_Pin    =  GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Mode   =  GPIO_Mode_IN;         //���
////GPIO_InitStructure.GPIO_OType  =  GPIO_OType_PP;         //�������
//	GPIO_InitStructure.GPIO_PuPd   =  GPIO_PuPd_NOPULL;      //�������
//	GPIO_InitStructure.GPIO_Speed  =  GPIO_Speed_100MHz;     //����GPIO
//	GPIO_Init(GPIOE,&GPIO_InitStructure);

//}


///*********************************************ʱ��оƬ��ʱ�ӵ����룬����ĳ�ʼ������*************************************************/
///************************************************
//void DS1302_WriteBYTE(unsigned char Adr,unsigned char Data,unsigned char CorR)
//�������ܣ���DS1302����д�ֽ�
//����˵����
//1��Adr��ָʾ���Ǽĳ�����ַ��
//2��Data��д������ݣ�
//2��CorR: ָʾ��ʱ���������� ������ RAM����
//              0��ָʾ����ʱ����������
//              1��ָʾ����RAM����
//3��WorR: ָʾ���Ƕ���������д����
//               0��ָʾ����д����
//               1��ָʾ���Ƕ�����
//****************************************************************/
//void DS1302_WriteBYTE(uint8_t Adr,uint8_t Data,uint8_t CorR)
//{
//  uint8_t BL = 0;
//	uint8_t i  = 0;
//    
//	DS1302_SDA_OUT();
//	DS1302_SCK_OUT();
//	DS1302_CE_OUT();
//	
//	DS1302_CE_L;	
//	
//	DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�
//	
//	DS1302_CE_H;
//	
//	DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�

//	DS1302IO_SDA_L;
//	
//	DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�
//	
//	
//  //д��ַ
//	DS1302CLK_L;
//	
//	DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�	

//	for(i = 0; i<8; i++)
//	{
//		DS1302CLK_L;
//		DS1302_Delay(2);//�����ʱ��ʱ�����ʱ���޸�	
//			
//		BL = Adr>>i;
//			
//		if(BL & BIT0)
//			{
//			DS1302IO_SDA_H;
//		  }
//		else
//			{
//			DS1302IO_SDA_L;
//		  }
//			
//		DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�	
//		DS1302CLK_H;
//		DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�	
//			
//	}
//    
//	//д����
//	for(i = 0; i<8; i++)
//	{
//		DS1302CLK_L;
//		DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�	
//		
//		BL = Data>>i;
//		
//		if(BL & BIT0)
//			{
//				DS1302IO_SDA_H;
//		  }
//		else
//			{
//			DS1302IO_SDA_L;
//		  }
//		
//		DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�	
//			
//		DS1302CLK_H;
//			
//		DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�	
//			
//	}

//	DS1302CLK_L;
//	DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�	
//}

///************************************************
//void DS1302_ReadBYTE(unsigned char Adr,unsigned char Data,unsigned char CorR,unsigned char WorR)
//�������ܣ���DS1302����д�ֽ�
//����˵����
//1��Adr��ָʾ���Ǽĳ�����ַ��
//2��Data��д������ݣ�
//2��CorR: ָʾ��ʱ���������� ������ RAM����
//              0��ָʾ����ʱ����������
//              1��ָʾ����RAM����
//3��WorR: ָʾ���Ƕ���������д����
//               0��ָʾ����д����
//               1��ָʾ���Ƕ�����
//****************************************************************/
//uint8_t DS1302_ReadBYTE(uint8_t Adr,uint8_t Data,uint8_t CorR)
//{
//	uint8_t Data_BIT;
//	uint8_t BL = 0;
//	uint8_t i  = 0;
//    
//	DS1302_SDA_OUT();
//	DS1302_SCK_OUT();
//	DS1302_CE_OUT();

//	DS1302IO_SDA_L;
//	DS1302_CE_L;
//	DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�	
//	
//	DS1302_CE_H;

//  //д��ַ
//  DS1302CLK_L;    
//  DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�	
//    
//	for(i = 0; i<8; i++)
//	{
//		DS1302CLK_L;
//		DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�	

//		BL = Adr>>i;

//		if(BL & BIT0)
//			{
//			DS1302IO_SDA_H;
//		  }
//		else
//			{
//			DS1302IO_SDA_L;
//		  }

//		DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�	
//		DS1302CLK_H;
//		DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�	
//	}	
//	
//	
//	DS1302_SDA_IN();

//	Data = 0;
//    //������
//	for(i = 0; i<8; i++)
//	{
//		DS1302CLK_L;
//		DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�	
//		
//		if(DS1302_SDA_READ == 1) 
//			{ 
//				Data_BIT = 1;
//		  }
//		else 
//			  Data_BIT = 0;

//		BL = Data_BIT << i;

//		Data = BL + Data;

//		DS1302CLK_H;
//		DS1302_Delay(1);//�����ʱ��ʱ�����ʱ���޸�	
//	}
//    
//   DS1302CLK_L;
//    
//   return Data;
//}





//void DS1302Z_Read(void)
//{
//	  uint8_t temp = 0;

//		
//		//Сʱ  24Сʱ��
//		temp = DS1302_ReadBYTE(0x85,0,0);
//		DS1302_Time.Hour = ((temp>>4) &(0x0f))*10 + (temp &(0x0f));
//		
//		//��
//		temp = DS1302_ReadBYTE(0x83,0,0);
//		DS1302_Time.Minute = ((temp>>4) &(0x0f))*10 + (temp &(0x0f));
//		
//	  
//	  //��    2022-4-11 16:10:28
//		//temp = DS1302_ReadBYTE(0x81,0,0);
//		//DS1302_Time.Minute = ((temp>>4) &(0x0f))*10 + (temp &(0x0f));
//	  
//	
//		//��
//		temp = DS1302_ReadBYTE(0x87,0,0);
//		DS1302_Time.Day = ((temp>>4) &(0x0f))*10 + (temp &(0x0f));
//		
//		//��
//		temp = DS1302_ReadBYTE(0x89,0,0);
//		DS1302_Time.Month = ((temp>>4) &(0x0f))*10 + (temp &(0x0f));
//		
//		//��
//		temp = DS1302_ReadBYTE(0x8d,0,0);		
//		DS1302_Time.Year = 2000 + ((temp>>4) &(0x0f))*10 + (temp &(0x0f));
//		
//		
//			if(DS1302_Time.Year == 2000)
//			  {
//				Time_Init();
//				DS1302Z_WriteQ();
//			  }
//			
//			
//		//����ʱ�ӵ����   2022-4-11 15:39:24
//	  printf("\r\n DS1302_Time.Year:%d\r\n",DS1302_Time.Year);	
//		printf("\r\n DS1302_Time.Month:%d\r\n",DS1302_Time.Month);		
//		printf("\r\n DS1302_Time.Day:%d\r\n",DS1302_Time.Day);		
//		printf("\r\n DS1302_Time.Hour:%d\r\n",DS1302_Time.Hour);		
//		printf("\r\n DS1302_Time.Minute:%d \r\n\r\n ",DS1302_Time.Minute);	
//		//����ʱ�ӵ����   2022-4-11 15:39:24
//			
//}



//void DS1302Z_WriteQ(void)  //һ��ȫд��
//{
//	uint8_t temp = 0;

//	DS1302_WriteBYTE(0x8E,0x00,0);
//	DS1302_WriteBYTE(0x80,0x30,0);

//  //����
//	
//	temp = (DS1302_SetTime.Minute/10)<<4;
//	temp = temp + (DS1302_SetTime.Minute%10);		
//	DS1302_WriteBYTE(0x82,temp,0); 
//	
//	//Сʱ  24Сʱ��
//	temp = (DS1302_SetTime.Hour/10)<<4;
//	temp = temp + (DS1302_SetTime.Hour%10);		
//	DS1302_WriteBYTE(0x84,temp,0);
//	
//	//��
//	temp = (DS1302_SetTime.Day/10)<<4;
//	temp = temp + (DS1302_SetTime.Day%10);	
//	DS1302_WriteBYTE(0x86,temp,0);
//	
//	
//	//��
//	temp = (DS1302_SetTime.Month/10)<<4;
//	temp = temp + (DS1302_SetTime.Month%10);
//	DS1302_WriteBYTE(0x88,temp,0);
//	
//	//��
//	temp = ((DS1302_SetTime.Year/10)%10)<<4;
//	temp = temp + (DS1302_SetTime.Year%10);
//	DS1302_WriteBYTE(0x8C,temp,0);

//	
//	//д����
//	DS1302_WriteBYTE(0x8E,0x80,0);
//	DS1302_CE_L;
//}








//����3

/*
#include "includes.h"	
#include "stm32f4xx.h"
#include "PRTC.h"
#include "sys.h"
#include "delay.h"
 
 
typedef uint32_t u32;
typedef uint16_t u16;
typedef   uint8_t u8; 
 
 
 
 
struct TIMEData TimeData;

u8 read_time[7];
 
 
 
 
 
void ds1302_gpio_init()//CE,SCLK�˿ڳ�ʼ��    
		{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_5; //PE5   CE
		GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_100MHz;
		//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
		GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_OUT;         //���
		GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;         //�������	
		GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE 5
		GPIO_ResetBits(GPIOE,GPIO_Pin_5); 
		 
			
			
		GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_3; //PE3  SCLK
		GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_100MHz;
		//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
		GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_OUT;         //���
		GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;         //�������	
			
		GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE 3
		GPIO_ResetBits(GPIOE,GPIO_Pin_3); 
		}
 



void ds1032_DATAOUT_init()//����˫��I/O�˿�Ϊ���̬
		{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		 
		GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_4; //PE4 DATA
		GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_100MHz;
		//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_OUT;         //���
		GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;         //�������		
		GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE 4
		GPIO_ResetBits(GPIOE,GPIO_Pin_4);
		}
 



void ds1032_DATAINPUT_init()//����˫��I/O�˿�Ϊ����̬
		{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4; //PE4 DATA
		//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	
		GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE4
		}
 
		
		
		
 
void ds1302_write_onebyte(u8 data)//��DS1302����һ�ֽ�����
		{
		//ds1032_DATAOUT_init();
		u8 count=0;
		ds1032_DATAOUT_init();
			
		SCLK_L;
		//delay_us(2);	
		for(count=0;count<8;count++)
			{	
				SCLK_L;
				if(data&0x01)
				{
				DATA_H;
				}
				else
        {
				DATA_L;
				}        //��׼���������ٷ���
				SCLK_H;  //����ʱ���ߣ���������
				data>>=1;
			}
		}
 
		
		
		
void ds1302_wirte_rig(u8 address,u8 data)//��ָ���Ĵ�����ַ��������
		{
		u8 temp1 = address;
		u8 temp2 = data;
			
		CE_L;
		//delay_us(2);//2022-4-24 14:16:07	
		SCLK_L;
		delay_us(1);//1   
			
		CE_H;
		delay_us(2);
			
		ds1302_write_onebyte(temp1);
		ds1302_write_onebyte(temp2);
			
		CE_L;
		//delay_us(2);//1   2022-4-24 14:16:07		
		SCLK_L;
		delay_us(2);
			
		}
 
		
		
u8 ds1302_read_rig(u8 address)//��ָ����ַ��ȡһ�ֽ�����
		{
		u8 temp3=address;
		u8 count=0;
		u8 return_data=0x00;
			
		CE_L;
		//delay_us(3);//2022-4-24 14:16:07	
		SCLK_L;
		delay_us(3);
			
		CE_H;
		delay_us(3);
			
		ds1302_write_onebyte(temp3);
		ds1032_DATAINPUT_init();//����I/O��Ϊ����
		delay_us(2);
			
		for(count=0;count<8;count++)
			{
			delay_us(2);//ʹ��ƽ����һ��ʱ��
			return_data>>=1;
				
			SCLK_H;
			delay_us(4);//ʹ�ߵ�ƽ����һ��ʱ��4    
			SCLK_L;
			delay_us(14);//��ʱ14us����ȥ��ȡ��ѹ������׼ȷ
				
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4))
			  {
				return_data=return_data|0x80;
				}
			
			}
			
		delay_us(2);
		CE_L;
		delay_us(1);//2022-4-24 14:16:07
		DATA_L;
			
		return return_data;
		}
 


void ds1032_init()
		{
		ds1302_wirte_rig(0x8e,0x00);//�ر�д��������
			
		ds1302_wirte_rig(0x80,0x37);//seconds37��
		ds1302_wirte_rig(0x82,0x58);//minutes58��
		ds1302_wirte_rig(0x84,0x23);//hours23ʱ
		ds1302_wirte_rig(0x86,0x30);//date30��
		ds1302_wirte_rig(0x88,0x09);//months9��
		ds1302_wirte_rig(0x8a,0x07);//days������
		ds1302_wirte_rig(0x8c,0x20);//year2020��
			
		ds1302_wirte_rig(0x8e,0x80);//��д��������
		}
 
		
		
void ds1032_read_time()
		{
		read_time[0]=ds1302_read_rig(0x81);//����
		read_time[1]=ds1302_read_rig(0x83);//����
		read_time[2]=ds1302_read_rig(0x85);//��ʱ
		read_time[3]=ds1302_read_rig(0x87);//����
		read_time[4]=ds1302_read_rig(0x89);//����
		read_time[5]=ds1302_read_rig(0x8B);//������
		read_time[6]=ds1302_read_rig(0x8D);//����
			
		printf("\r\n ����:%d \r\n ",read_time[0]);		
		printf("\r\n ����:%d \r\n ",read_time[1]);		
		printf("\r\n ��ʱ:%d \r\n ",read_time[2]);		
		printf("\r\n ����:%d \r\n ",read_time[3]);		
		printf("\r\n ����:%d \r\n ",read_time[4]);		
		printf("\r\n ����:%d \r\n ",read_time[6]);	

			
		}
 
		
		
void ds1032_read_realTime()
		{
		ds1032_read_time();  //BCD��ת��Ϊ10����
				
			
		TimeData.second=(read_time[0]>>4)*10+(read_time[0]&0x0f);
		TimeData.minute=((read_time[1]>>4)&(0x07))*10+(read_time[1]&0x0f);
		TimeData.hour=(read_time[2]>>4)*10+(read_time[2]&0x0f);
		TimeData.day=(read_time[3]>>4)*10+(read_time[3]&0x0f);
		TimeData.month=(read_time[4]>>4)*10+(read_time[4]&0x0f);
		TimeData.week=read_time[5];
		TimeData.year=(read_time[6]>>4)*10+(read_time[6]&0x0f)+2000;
			
			
		printf("\r\n year:%d \r\n ",TimeData.year);		
		printf(" month:%d \r\n ",TimeData.month);		
		printf(" day:%d \r\n ",TimeData.day);		
		printf(" hour:%d \r\n ",TimeData.hour);		
		printf(" minute:%d \r\n\r\n ",TimeData.minute);		
		printf(" second:%d \r\n\r\n ",TimeData.second);	
		}


*/



//����4            

#include "includes.h"	
#include "stm32f4xx.h"
#include "PRTC.h"
#include "sys.h"
#include "delay.h"
 
 
typedef uint32_t u32;
typedef uint16_t u16;
typedef   uint8_t u8; 


uchar time_data[6]={0};//��ȡDS1302��ǰʱ�仺�����

 /*****************************************
 * ��������void DS1302_GPIOInit(void)
 * ����  ��    DS1302 GPIO����
 * ����  ��
 * ���  ����
 * ����  ��
        CLK---PB5,
        IO--->PB6,
        RES--->PB7,
 *************************************/
void DS1302_GPIOInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructre;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);            /*open GPIO  clock*/
  GPIO_InitStructre.GPIO_Pin= GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
  //GPIO_InitStructre.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructre.GPIO_Mode   = GPIO_Mode_OUT;         //���
	GPIO_InitStructre.GPIO_OType  = GPIO_OType_PP;         //�������
	
  GPIO_Init(DS1302_PORT, &GPIO_InitStructre);
}





 /*****************************************
 * ��������void DS1302_IO_GPIO(void)
 * ����  ��    DS1302 ֮ IO GPIO �����������
 * ����  ��FLAG��־λ
 * ���  ����
* ����  ��OUT:��ʾ�����IN:��ʾ����
          FLAG��
 *************************************/
void DS1302_IO_GPIO(uchar FLAG)
{
  GPIO_InitTypeDef GPIO_InitStructre;
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);            /*open GPIO  clock*/
    /**********��������IO�˿� ��� **********/
    if(FLAG==0x01)
  {
    GPIO_InitStructre.GPIO_Pin= GPIO_Pin_4;//����IO_GPIO
    GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
    //GPIO_InitStructre.GPIO_Mode=GPIO_Mode_Out_PP;
	  GPIO_InitStructre.GPIO_Mode   = GPIO_Mode_OUT;         //���
		GPIO_InitStructre.GPIO_OType  = GPIO_OType_PP;         //�������	
		
		
  GPIO_Init(DS1302_PORT, &GPIO_InitStructre);
  }
    /**********��������IO�˿� ����**********/
    else if(FLAG==0x00)
  {
     GPIO_InitStructre.GPIO_Pin= GPIO_Pin_4;//����IO_GPIO
   GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
   GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IN;  //������������  GPIO_Mode_IN      GPIO_Mode_IPU
   GPIO_Init(DS1302_PORT, &GPIO_InitStructre);
   }
}





  /*****************************************
 * ��������void DS1302_delay(u8 dd)
 * ����  ������ʱ
 * ����  ��
 * ���  ����
 * ����  ��
 *************************************/
void DS1302_delay(u8 dd)
{
    u8 i;
    for(;dd>0;dd--)
  for(i=110;i>0;i--);
}






  /*****************************************
 * ��������void DS1302_Write(uchar add,uchar dat)
 * ����  ��DS1302дָ�������
*  ����  ��add:���͵�ַ��dat����������
 * ���  ����
 * ����  ��
 *************************************/
 void DS1302_Write(uchar add,uchar dat)
 {
 uchar i,temp1,temp2;
 temp1=add;
 temp2=dat;
 RES_Set_1;//RET=1;
//���͵�ַ
for(i=0;i<8;i++)
 {
        if(temp1&0x01)
         {IO_Set_1;  }     //IO=1;
        else
        { IO_Reset_0;}   //�IIO=0;
        temp1=temp1>>1;
        CLK_Set_1;            //CLK=1;
        DS1302_delay(2);
        CLK_Reset_0;    //CLK=0;
  }

	
	
	
	
	
//��������
for(i=0;i<8;i++)
    {
        /*IO=(temp2>>i)&0x01;��һ������������ε�����  */
        if(temp2&0x01)
         {IO_Set_1;  }     //IO=1;
        else
         { IO_Reset_0;}    //�IIO=0;
            temp2=temp2>>1;
            CLK_Set_1;            //CLK=1;
            DS1302_delay(2);
            CLK_Reset_0;    //CLK=0;
    }
RES_Reset_0;// RET=0;
 }




 
/*****************************************
 * ��������uchar DS1302_Read(uchar add)
 * ����  ��DS1302������
 *  ����  ��add:�������ڵ�ַ
 * ���  ��
 * ����  ��
 *************************************/
uchar DS1302_Read(uchar add)
{
  uchar i,suf,temp,mm,nn,value;
   temp=add;
   RES_Set_1;//RET=1;
    //д��ַ
  for(i=0;i<8;i++)
      {
       if(temp&0x01)
       {IO_Set_1;  }     //IO=1;
      else
         { IO_Reset_0;}    //IO=0;
      temp=temp>>1;
        CLK_Set_1;            //CLK=1;
        DS1302_delay(2);
        CLK_Reset_0;    //CLK=0;
      }
 
			
			
			
//������
DS1302_IO_GPIO(IN);//����IOΪ����
  for(i=0;i<8;i++)
    {
     suf=suf>>1;//�����ݱ���
     if(IO_Read)    //IO=1
     {
         suf=suf|0x80;
     }
     else     //IO=0
     {
     suf=suf&0x7f;
     }

        CLK_Set_1;            //CLK=1;
        DS1302_delay(2);
        CLK_Reset_0;    //CLK=0;
    }
    RES_Reset_0;    // RET=0;

DS1302_IO_GPIO(OUT);//����IOΪ���,�ָ�����״̬
//���ݴ���ת��ʮ����
mm=suf/16;
nn=suf%16;
value=mm*10+nn;
return value;
}





/*****************************************
 * ��������void DS1302_SetTime(uchar *ad)
 * ����  ��DS1302 д������ʱ��
 *  ����  ��add:�������ڵ�ַ
 * ���  ��
 * ����  ��
 *************************************/
void DS1302_SetTime(uchar *ad)
    {
     DS1302_Write(0x8e,0x00);   //WP=0 ��������д��DS1302
		
     /**********���¶�ʱ����ĳ�ʼ��*************/
			
     DS1302_Write(ds1302_sec_addr,ad[5]/10*16+ad[5]%10);    //��
     DS1302_Write(ds1302_min_addr,ad[4]/10*16+ad[4]%10);    //��
     DS1302_Write(ds1302_hour_addr,ad[3]/10*16+ad[3]%10);   //ʱ
			
     /**********���¶������յĳ�ʼ��*************/
		
     DS1302_Write(ds1302_day_addr,ad[2]/10*16+ad[2]%10);    //��
     DS1302_Write(ds1302_month_addr,ad[1]/10*16+ad[1]%10);  //��
		 DS1302_Write(ds1302_year_addr,ad[0]/10*16+ad[0]%10);   //��   +2000  2022-4-26 14:29:27

     DS1302_Write(0x8e,0x80);   //0x8e�����ֽڵ�ַ,bit7=WP WP=1 ��ֹ����д��DS1302
    }


	
	
	
/*****************************************
 * �������� void DS1302_OFF(void)
 * ����  ��DS1302ʱ���ֹ��ʱ
 *  ����  ��
 * ���  ��
 * ����  ��
 *************************************/
  void DS1302_OFF(void)
  {
   uchar temp;
   temp=DS1302_Read(0x81);//��ȡ���ַʱ��
   DS1302_Write(0x8e,0x00);//WP=0 ��������д��DS1302
   temp=temp|(1<<7);
   DS1302_Write(0x80,temp);//WP=1 ��ֹ����д��DS1302

  }
	
	
	
	
	
/*****************************************
 * �������� void DS1302_ON(void)
 * ����  ��DS1302ʱ�俪ʼ���У���ʱ
 *  ����  ��
 * ���  ��
 * ����  ��
 *************************************/
  void DS1302_ON(void)
  {
   uchar temp;
   temp=DS1302_Read(0x81);
   DS1302_Write(0x8e,0x00);//WP=0 ��������д��DS1302
   temp=temp|(0<<7);
   DS1302_Write(0x80,temp);//WP=0 ��������д��DS1302

  }






 /*****************************************
 * ��������void DS1302_init(uchar *time)
 * ����  ��    DS1302��ʼ��
 * ����  ����
 * ���  ����
* ����  ��
 *************************************/
void DS1302_init(uchar *time)
{
    DS1302_GPIOInit();//GPIO��ʼ������
    DS1302_delay(2);
	
    RES_Reset_0;//RET=0;
    CLK_Reset_0;//CLK=0;
    //�����Ƕ�DS1302������أ�������   ����ʱ��
    DS1302_Write(0x8e,0x00);//WP=0 ��������д��DS1302
//    DS1302_Write(0x90,0xA7);//���(1��������+8K����)
//    DS1302_Write(0x8E,0X80);//�������� WP=1
    if(DS1302_Read(0X81)&0X80)//��ѯDS302ʱ���Ƿ�����,���ʱ��ֹͣ�߶�������ʱ��+��ʼ��ʱ��
    {
        DS1302_SetTime(time);//�������ó�ʼʱ��
    }
    //��������

}





 /*****************************************
 * ��������void DS1302_Readtime(void)
 * ����  ��    DS1302ʱ�����
 * ����  ����
 * ���  ����
* ����  ��
 *************************************/
void DS1302_Readtime(void)//
{
			time_data[0]=DS1302_Read( 0x8D);//��
			time_data[1]=DS1302_Read( 0x89);//��
			time_data[2]=DS1302_Read( 0x87);//��
	
			time_data[3]=DS1302_Read( 0x85);//ʱ
			time_data[4]=DS1302_Read( 0x83);//��
			time_data[5]=DS1302_Read( 0x81);//��
	
	
		printf("\r\n year:%d \r\n ",time_data[0]);		
		printf(" month:%d \r\n ",time_data[1]);		
		printf(" day:%d \r\n ",time_data[2]);		
		printf(" hour:%d \r\n ",time_data[3]);		
		printf(" minute:%d \r\n ",time_data[4]);		
		printf(" second:%d \r\n\r\n ",time_data[5]);	
	
}

