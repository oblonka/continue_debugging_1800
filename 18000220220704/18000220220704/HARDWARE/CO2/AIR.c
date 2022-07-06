#include "includes.h"	
#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "sram.h"
#include "malloc.h"
#include "ILI93xx.h"

#include "AIR.h"

#include "KEYa.h"
#include "KEYAA.h"

#include "KEYnum.h"

#include "WIFIcon.h"

#include "ButtonUse.h"


#include "WIFI.h"//���д��ڵ��Զ���  


/*
����1
TX  PA9
RX  PA10


1�� �����ʣ�9600, DataBits: 8, StopBits: 1, Parity: No, Flow Control: No
2�� ��Э�����ݣ���Ϊ16 �������ݡ��硰46��Ϊʮ���Ƶ�[70]��
3�� [xx]Ϊ���ֽ�����(�޷��ţ�0-255)��˫�ֽ����ݸ��ֽ���ǰ�����ֽ��ں�

TX ���ڷ��Ͷˣ�+3.3V��
RX ���ڽ��նˣ�+3.3V��

��λ�����͸�ʽ
��ʼ���������������1 ���� ����n У���
HEAD LEN CMD DATA1 ���� DATAn CS
11H XXH XXH XXH ���� XXH XXH

Э���ʽ��ϸ˵��
��ʼ����λ�����͹̶�Ϊ[11H]��ģ��Ӧ��̶�Ϊ[16H]
����֡�ֽڳ��ȣ�=���ݳ���+1������CMD+DATA��
�����ָ���
���ݶ�ȡ����д������ݣ����ȿɱ�
У��������ۼӺͣ�=256-(HEAD+LEN+CMD+DATA)

��Ź������������
1 ��ȡCO2 �������0x01
2 CO2 Ũ��ֵ����У׼0x03
3 ��ȡ����汾��0x1E
4 ����/�ر������У׼�Լ������У׼��������0x10
5 ��ѯ�������0x1F






4.1 ��ȡCO2 �������


���ͣ�11 01 01 ED
Ӧ��16 05 01 DF1- DF4 [CS]

���ܣ���ȡCO2 �����������λ��ppm��
˵����CO2 ����ֵ= DF1*256 + DF2


ע�⣺DF3-DF4 Ԥ��

Ӧ��ʵ����
Ӧ��16 05 01 02 58 00 00 8B


˵����
ʮ�����ƻ���Ϊʮ���ƣ�02 ��02��58 ��88
CO2 ����ֵ= 02*256 + 88=600ppm








4.2 CO2 Ũ��ֵ����У׼

���ͣ�11 03 03 DF1 DF2 CS

Ӧ��16 01 03 E6
���ܣ�CO2 Ũ��ֵ����У׼


˵����
1������У׼Ŀ��ֵ= DF1*256 + DF2����λΪppm����ΧΪ��400 �� 1500 ppm��
2������CO2 ����У׼֮ǰ����ȷ�ϵ�ǰ����CO2 ֵΪ����У׼Ŀ��ֵ���ȶ�ʱ������2 �������ϡ�


���磺
����Ҫ��ģ�鵥��У׼��600ppm ʱ���������11 03 03 02 58 8F
ʮ�����ƻ���Ϊʮ���ƣ�02 ��02��58 ��88
CO2 ����ֵ= 02*256 + 88=600ppm


˵����
�ַ�˵��
DF1 Ԥ����Ĭ��100��
DF2 У׼ʹ�ܣ�0��������2���رգ�
DF3 У׼���ڣ�1����15 ��ѡ��һ��Ĭ��Ϊ7��
DF4 ��׼ֵ��λ��2 ���ֽڣ�
DF5 ��׼ֵ��λ��2 ���ֽڣ�
DF6 Ԥ����һ��Ĭ��100��
ע�⣺DF4 ��DF5 Ĭ��ֵΪ400����DF4��01��DF5��90


4.4.1 ���������У׼�����ò���
���ͣ�11 07 10 64 00 07 01 90 64 78
Ӧ��16 01 10 D9


4.4.2 �ر������У׼
���ͣ�11 07 10 64 02 07 01 90 64 76
Ӧ��16 01 10 D9


*/






///* ˽�б��� ------------------------------------------------------------------*/
//u16  CO2_data;
//u16  USART_BUF_co2[USART_REC_LEN];
//uint16_t  CO2_TxBuffer[4]={0x11,0x01,0x01,0xed};
// 




// struct STRUCT_USART_Fram_CO2 CO2_Fram_Record_Struct = { 0 };  //�����˴��ڽ���CO2�����ݽṹ�壬һ������֡�ṹ��

////char RX_buffer_CO2_data[CO2_RX_BUF_MAX_LEN];//�������ݵ�buffer��������    ����

//uint8_t         CO2_WorkMode = 0;   //��ȡ��ֵ   0����������״̬    1��У׼����״̬
//uint8_t               RX_Num = 0;
//uint16_t              RX_CRC = 0;
//uint16_t    CO2_Measure_data = 0;
//uint8_t            RS232_One = 0;



////uint8_t RX_buffer_CO2_data[16];

// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 

///*��Ҫ���͵����ݣ����ڵ����ݷ��ͣ��������㷵�ص�����*/

////��ȡCO2 �������
//uint8_t AIR_CO2_Read_data[4] = {0x11,0x01,0x01,0xed};        

////CO2Ũ�ȵ���У׼��
//uint8_t AIR_CO2_Cali_data[6] = {0x11,0x03,0x03,0x01,0x90,0x58};


////���������У׼�����ò���
//uint8_t  AIR_CO2_AutoCali_data_On[10] = {0x11,0x07,0x10,0x64,0x00,0x07,0x01,0x90,0x64,0x78}; 
////�ر������У׼
//uint8_t AIR_CO2_AutoCali_data_OFF[10] = {0x11,0x07,0x10,0x64,0x02,0x07,0x01,0x90,0x64,0x76};



///*




//*/





//uint8_t AIR_CO2_transmit_txrx_ERR = 0;   //CO2����������  1:Ϊ����������E1   2:Ϊ�ظ���
//uint8_t AIR_CO2_transmit_NoRX_Num = 0;   //�ж��ٴ�û�н��յ�CO2����ֵ��ʱ��   ��ʾE1


//uint16_t  AIR_CO2_Rest_Time  = 0;  //����ʱ��
//uint8_t  AIR_CO2_Rest_Flag  = 0;  //������ʶ





//void CO2_VCC_CTR_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);     //ʹ��GPIOD��ʱ��
//	
//	GPIO_InitStructure.GPIO_Pin    =  GPIO_Pin_6;
//	GPIO_InitStructure.GPIO_Mode   =  GPIO_Mode_OUT;         //���
//	GPIO_InitStructure.GPIO_OType  =  GPIO_OType_PP;         //�������
//	GPIO_InitStructure.GPIO_PuPd   =  GPIO_PuPd_NOPULL;      //�������
//	GPIO_InitStructure.GPIO_Speed  =  GPIO_Speed_100MHz;     //����GPIO
//	GPIO_Init(GPIOD,&GPIO_InitStructure);
//	
//	//GPIO_SetBits(GPIOD,GPIO_Pin_6);               //GPIOD �ߵ�ƽ
//}



///*
//void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
//uint16_t USART_ReceiveData(USART_TypeDef* USARTx);
//*/





///*
//uint8_t  Fifo_RXInsert(uint8_t Fifo_Data)    //���ղ�������
//				{
//					HAL_UART_Receive_IT(&huart2, &RS232_One, 1);
//					RX_Shuzu[RX_Num] =  Fifo_Data;
//					RX_Num++;
//					if(RX_Num > sizeof(RX_Shuzu))
//					{
//					RX_Num = 0;
//					}
//					return 1;	
//				}
//*/


////CO2��Դ�Ŀ����͹رյĺ�������λCO2�������ĵ�Դ
//void CO2_Sensor_VCC_Contrl(uint8_t n)
//		{
//			if(n == 1)
//			  {	GPIO_SetBits(GPIOD,GPIO_Pin_6);}   //�򿪿��أ���CO2�������ṩ��Դ 	
//      else if(n == 0)
//			  {	GPIO_ResetBits(GPIOD,GPIO_Pin_6);} //�رտ��أ���CO2�������Ͽ���Դ    	
//			
//		}

//		
//		
//		

//		
//		
//		
//		
//		//����CO2��ָ�ȷ�Ϸ������      ���ڷ���ָ��
//void CO2_Send_Data(void)
//		{	
//		  //USARTX_Send_data(USART_TypeDef * USARTx,u8 *s);  ����ԭ��
//			
//			
//			//CO2_USART("%s", AIR_CO2_Read_data);
//			//delay_ms(5000);
//			
//			USARTX_Send_data(USART1,AIR_CO2_Read_data);//����Ƕ��ֽڵķ��ͺ�������ģ��޸ĵĶ��ֽڵĺ�������
//			while(USART_GetFlagStatus(USART1,USART_FLAG_TC )==RESET)
//						{
//						}
//				
////USART_ClearFlag(USART1, USART_FLAG_TC);

//						
//			//HAL_UART_Receive_IT(&huart2, &RS232_One, 1);
//			//while(HAL_UART_Transmit(&huart2,CO2_ReadCon,4,0xFFFF) != HAL_OK )
//			//{		
//			//}
//						
//		}

////
////���ͣ�11 01 01 ED
////Ӧ��16 05 01 DF1- DF4 [CS]

////���ܣ���ȡCO2 �����������λ��ppm��
////˵����CO2 ����ֵ=  DF1*256 + DF2
////		
//		
//		
//		
////���ڶ�ȡ  ������ָ��ķ�������		
//void Read_CO2_ppm(void)
//{
//	//uint8_t j = 0;
//	
//	   char j = 0;
//	uint8_t i = 0;
//	
//	
//	
//	char* CO2_str_buffer=NULL;
//	
//	
//	
//	CO2_Send_Data(); 
//	//delay_ms(50000);
//  //delay_ms(50000);
//	
//	CO2_Fram_Record_Struct.InfBit_CO2.FramLength_CO2 = 0; //���½����µ����ݰ�
//				
//	CO2_Fram_Record_Struct.Data_RX_BUF_CO2[CO2_Fram_Record_Struct.InfBit_CO2.FramLength_CO2] = '\0';
//	
//	CO2_str_buffer= CO2_Fram_Record_Struct.Data_RX_BUF_CO2;
//	
//	
//	
//	
//	//ESP32S_Fram_Record_Struct.Data_RX_BUF[ESP32S_Fram_Record_Struct.InfBit.FramLength] = '\0';
//	
//	//if(AIR_CO2_transmit_txrx_ERR != 1)
//	//{
//	//	AIR_CO2_transmit_NoRX_Num++;
//	
//	for(j = 0;j<sizeof(CO2_str_buffer);j++)
//		{			
//			if((CO2_str_buffer[j] == 0x16)&&(CO2_str_buffer[j+1] == 0x05)&&(CO2_str_buffer[j+2] == 0x01))
//			{
//				RX_CRC = 0;
//				for(i= 0;i<7;i++)
//						{
//						RX_CRC = RX_CRC + CO2_str_buffer[j+i];
//						}
//						
//				RX_CRC = (unsigned int)0x100 - (unsigned char)RX_CRC;
//						
//				if(RX_CRC == CO2_str_buffer[j+7])
//						{
//							CO2_Measure_data = CO2_str_buffer[j+3] * 256 + CO2_str_buffer[j+4];  		
//							//AIR_CO2_transmit_NoRX_Num = 0;	
//							//AIR_CO2_transmit_txrx_ERR = 0;	
//							
//							printf("\r\n CO2_Measure_data:%d \r\n",CO2_Measure_data);	//2022.06
//							
//							
//						}
//			}	
//			
//			/*
//			if(CO2_NoRX_Num >= DE_CO2_NoRX_Num)   //�������ﵽ��ʱ��  ��ʾE1
//			{
//				CO2_TXRX_ERR = 1;
//				CO2_Rest_Time = 0;        //����ʱ��
//				CO2_Rest_Flag = 1;        //������ʶ		
//				CO2Sensor_VCCContrl(0);   //����CO2
//				CO2_NoRX_Num = 0;
//			}
//      */
//			
//		}
//		//RX_Num = 0;
//		//CO2_Send_Data(); 
//	}
////}






///*
//void Read_CO2Concentration(void)
//{
//	uint8_t j = 0;
//	uint8_t i = 0;

//	for(j = 0;j<sizeof(RX_buffer_data);j++)
//	{
//		if((RX_buffer_data[j] == 0x16)&&(RX_buffer_data[j+1] == 0x05)&&(RX_buffer_data[j+2] == 0x01))
//		{
//			RX_CRC = 0;
//			for(i= 0;i<7;i++)
//			{
//				RX_CRC = RX_CRC + RX_buffer_data[j+i];
//			}
//			
//			RX_CRC = (unsigned int)0x100 - (unsigned char)RX_CRC;
//			
//			if(RX_CRC == RX_buffer_data[j+7])
//			{
//				GasCO2_Measure = RX_buffer_data[j+3] * 256 + RX_buffer_data[j+4];  				
//			}
//		}	
//	}


//	RX_Num = 0;
//	Read_CO2_ppm(); 
//}
//*/


//uint8_t SINGLE_CO2_Calibration(uint16_t Data)
//{
//uint8_t CRC_Data = 0;
//uint8_t i = 0;
////uint8_t j = 0;
//char j = 0;
//	
//	
//uint8_t k = 0;
//	
//uint8_t CO2_Calibration_Com[6] = {0x11,0x03,0x03,0x01,0x90,0x58};
//	
//CO2_Calibration_Com[3] = Data/256;
//CO2_Calibration_Com[4] = Data%256;
//	
//CO2_WorkMode = 1;
//	
////HAL_UART_Receive_IT(&huart2, &RS232_One, 1);
//	
//	
//for(i = 0;i<5;i++)
//		{
//		CRC_Data = CRC_Data + CO2_Calibration_Com[i];
//		}
//	CO2_Calibration_Com[5] = 0x100 - (uint16_t)CRC_Data;
//		
//for(k = 0;k <10;k++)
//	{
//				RX_Num = 0;
//				
//		
//				//HAL_UART_Receive_IT(&huart2, &RS232_One, 1);		
//				//while(HAL_UART_Transmit(&huart2,CO2_CalibrationCom,6,0xFFFF) != HAL_OK )
//				//{		}
//				//Wait_Operation_Delay(50);
//		
//		
//				delay_ms(1000);//50
//				
//	for(j = 0;j<sizeof(CO2_Fram_Record_Struct .Data_RX_BUF_CO2)-1;j++)
//		{	
//		if((CO2_Fram_Record_Struct .Data_RX_BUF_CO2[j] == 0x16)\
//			&&(CO2_Fram_Record_Struct .Data_RX_BUF_CO2[j+1] == 0x01)\
//		  &&(CO2_Fram_Record_Struct .Data_RX_BUF_CO2[j+2] == 0x03)\
//		  &&(CO2_Fram_Record_Struct .Data_RX_BUF_CO2[j+3] == 0xe6))\
//		
//		  {	
//			return 1;
//			}
//		}	
//	}
//	return 0;	
//}


//				
//				
//				
//				
//				
///*				
//uint8_t CO2_AUTO_CONTRL_Cal_ON_OFF(uint8_t ON_OFF)
//				{	
//					uint8_t j = 0;
//					
//					if(ON_OFF == 0)  //���Զ�У׼
//						{
//							//while(HAL_UART_Transmit(&huart2,CO2_AutoCalibrationOn,10,0xFFFF) != HAL_OK )
//							{		
//							}
//						}
//					else//���Զ�У׼
//						{
//							//while(HAL_UART_Transmit(&huart2,CO2_AutoCalibrationOFF,10,0xFFFF) != HAL_OK )
//							{		
//							}
//						}		
//					
//					for(j = 0;j<sizeof(RX_Shuzu);j++)
//						{
//							if((RX_Shuzu[j] == 0x16)&&(RX_Shuzu[j+1] == 0x01)&&(RX_Shuzu[j+2] == 0x10)&&(RX_Shuzu[j+3] == 0xd9))
//							{
//								return 1;
//							}	
//						}
//						
//					return 0;	
//				}
//*/












/*********************************************************************************
 * �ļ���  ��CO2.c
 * ����    ��MCUͨ������USART2���ͼ��ָ�CO2ģ�飬ģ����յ�����������
             MCU���ղ���������
 * ʵ��ƽ̨��STM32F103C8T6
 * ����    ��2018.07.19
 * �ӿ�    ��PA3-USART2_RXD  PA2-USART2_TXD  
**********************************************************************************/

/* ����ͷ�ļ� ----------------------------------------------------------------*/

#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "led.h"

/* ��غ궨�� ----------------------------------------------------------------*/
#define    Data_Head1           0x16     //����֡ͷ1Ϊ0xFF
#define    Data_Head2           0x05     //����֡ͷ2Ϊ0x86
#define	   Data_Length            8      //һ֡��9������

/* ˽�б��� ------------------------------------------------------------------*/
u16  CO2_data;
u16  USART_BUF[USART_REC_LEN];
uint16_t  CO2TxBuffer[4]={0x11,0x01,0x01,0xed};
 

void CO2_Tx()
{
	int i;
  for(i = 0; i < 4; i++) 
   { 
			USART_ClearFlag(USART1,USART_FLAG_TC);
			USART_SendData(USART1,CO2TxBuffer[i]);  		  	
			while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
      
   } 
 
 }


void USART1_Init(u32 bound)
{  

//GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		 
	
		//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); //ʹ��UART2����GPIOA��ʱ��
		//RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //ʹ�ܴ��ڵ�RCCʱ��

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);     //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); 
	
	
	
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;              //����USART2��RX�ӿ���PA3
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
//    GPIO_Init(GPIOA, &GPIO_InitStructure); 

//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;              //����USART2��TX�ӿ���PA2
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	       //�����������
//    GPIO_Init(GPIOA, &GPIO_InitStructure);  



//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA2��GPIOA3
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;            //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	       //�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //���츴�����
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;            //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);                    //��ʼ��PA2��PA3




   //USART2 ��ʼ������
		USART_InitStructure.USART_BaudRate = bound;           //һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;   //����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART1, &USART_InitStructure);             //��ʼ������
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);        //����ENABLE/�ر�DISABLE�ж�
    USART_Cmd(USART1, ENABLE);                            //ʹ�ܴ��� 
  
	//Usart2 NVIC ����
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	                      //����ָ���Ĳ�����ʼ��VIC�Ĵ���  	

}


void USART1_IRQHandler(void)
{	
	static u8 seri_count=0;
//	u16 check_sum=0;         //У���
//	u8 i;
	static 	u8 flag;         //����״̬���	  
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{
		
			if(USART_ReceiveData(USART1) == Data_Head1)        //���յ�֡ͷ
			{
				flag = 1;
			}
			
			if(flag)
			{	
				USART_BUF[seri_count++] = USART_ReceiveData(USART1);  //���һ֡����
				if(seri_count == Data_Length)	
				{
					if(USART_BUF[0]==Data_Head1 && USART_BUF[1]==Data_Head2)
					{
//						for( i = 1; i < 8; i++)
//						{
//							check_sum += USART_BUF[i];        //����У���
// 					  }
//						check_sum = 0xff - (check_sum & 0xFF);
//            check_sum += 1;
//						if(check_sum == USART_BUF[8])		
//						{
							CO2_data = USART_BUF[4] + USART_BUF[3]* 256;
							CO2_data = CO2_data+(CO2_data*0.05+30);
					//	}						
						seri_count = 0;
						flag=0;
					
					}
							
				}	
			}
   } 
} 
		
/******************* (C) COPYRIGHT 2018 NTU *****END OF FILE****/










