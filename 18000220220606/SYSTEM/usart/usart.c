#include "sys.h"
#include "usart.h"	

#include "WIFI.h"
#include "MQTT.h"
#include "TCP.h"
#include "includes.h"	
#include "AIR.h"



//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucosiii ʹ��	  
#endif
 	  
 

 
//USART6   ����6  
//   PC6   TXD
//   PC7   RXD




extern u16  CO2_data;
extern u16  USART_BUF_co2[USART_REC_LEN];
extern uint16_t  CO2_TxBuffer[4];













//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	printfͨ��usart6����ӡ���Ե�log 
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    



void _sys_exit(int x) 
{ 
	x = x; 
} 



//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART6->SR&0X40)==0);//     USART6  ѭ������,ֱ���������   
	USART6->DR = (u8) ch;       //     USART6
	return ch;
}
#endif
 


//���Դ��ڵĳ�ʼ��     ����6
/*******************************************************************************************/
/**********************����6   DEBUG********************************************************/
/*******************************************************************************************/
#if EN_USART6_RX   //���ʹ���˽���     ��ʼ������6  
//����6�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];      //���ջ���,���USART_REC_LEN���ֽ�.

//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	


//��ʼ��IO ����6
//bound:������
void uart_init(u32 bound)
	{
   //GPIO�˿�����
  GPIO_InitTypeDef   GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);     //ʹ��GPIOCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);    //ʹ��USART6ʱ��   ����6
 
	//����6��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6);  //GPIOA9����ΪUSART6
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);  //GPIOA10����ΪUSART6
	
	//USART6�˿�����
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7; //GPIOC6��GPIOC7
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;            //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	       //�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //���츴�����
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;            //����
	GPIO_Init(GPIOC,&GPIO_InitStructure);                    //��ʼ��PC6��PC7

  //USART6 ��ʼ������
	USART_InitStructure.USART_BaudRate            = bound;                           //����������
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;             //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;                //һ��ֹͣλ
	USART_InitStructure.USART_Parity              = USART_Parity_No;                 //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //��Ӳ������������
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;	 //�շ�ģʽ
  USART_Init(USART6, &USART_InitStructure);                                        //��ʼ������6
	
  USART_Cmd(USART6, ENABLE);                                                       //ʹ�ܴ���6
	
	//USART_ClearFlag(USART6, USART_FLAG_TC);
	
	
	
	
#if EN_USART6_RX	
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart6 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel                   = USART6_IRQn;   //����6�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;             //��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;		          //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;			  //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	                                      //����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif
	
}


//����6�жϷ������

void USART6_IRQHandler(void)                	//����6�жϷ������
{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART6);//(USART1->DR);	//��ȡ���յ�������
		
		if((USART_RX_STA&0x8000)==0)//����δ���
		{
			if(USART_RX_STA&0x4000)//���յ���0x0d
			{
				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else USART_RX_STA|=0x8000;	//��������� 
			}
			else //��û�յ�0X0D
			{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}   		 
  } 
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
#endif	

 








//wifi�Ĵ��ڳ�ʼ��   wifi
/*******************************************************************************************/
/*****************************USART2�ĳ�ʼ��   WIFI*****************************************/
/*******************************************************************************************/
#if EN_USART2_RX   //���ʹ���˽���     ��ʼ������2
//����6�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART2_RX_BUF[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
//u16 USART2_RX_STA=0;                //����״̬���	

u16 USART2_RX_STA_WIFI=0;             //����״̬���	


//��ʼ��IO ����2 
//bound:������
void uart2_init_wifi(u32 bound)
	{
  //GPIO�˿�����
  GPIO_InitTypeDef   GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);     //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);    //ʹ��USART2ʱ��   ����2��ʱ���ǲ�һ����   RCC_APB1Periph_USART2   2022-4-14 17:46:34
  //���ʱ�ӵ��޸�ǰ��Ҫһ��     APB1�����ʱ�����Ľӿ�    APB1
		
		
	//����2��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);  //GPIOA2����ΪUSART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);  //GPIOA3����ΪUSART2
	
	//USART2�˿�����
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2��GPIOA3
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;            //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	       //�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //���츴�����
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;            //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);                    //��ʼ��PA2��PA3

  //USART2��ʼ������
	USART_InitStructure.USART_BaudRate            = bound;                           //����������
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;             //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;                //һ��ֹͣλ
	USART_InitStructure.USART_Parity              = USART_Parity_No;                 //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //��Ӳ������������
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;	 //�շ�ģʽ
  USART_Init(USART2, &USART_InitStructure);                   //��ʼ������2
	
	//2022-4-18 11:24:46     �����жϺ����߿����ж�
	USART_ITConfig(USART2, USART_IT_RXNE|USART_IT_IDLE, ENABLE);//�����˽����жϺ����߿����ж�
	
	
  USART_Cmd(USART2, ENABLE);                                  //ʹ�ܴ���2
	
	//USART_ClearFlag(USART2, USART_FLAG_TC);
	
	
	
	
#if EN_USART2_RX	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart2 NVIC ����
	//������и����ж����ȼ��Ĳ��ԣ�����Ӹߵ�����һ��3��2��1��0
  //����ԽС�����ȼ�Խ��
	
  NVIC_InitStructure.NVIC_IRQChannel                   = USART2_IRQn;//����2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�3   0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;//�����ȼ�3  0
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	                         //����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif
	
}



















void USART2_IRQHandler(void)                	//����2�жϷ������
{
	 u8 Res_USART2;
	
	
	 u8 ucCh;
	
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	
	
	
	
	/*
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res_USART2 =USART_ReceiveData(USART2);//(USART1->DR);	//��ȡ���յ�������
		
		if((USART2_RX_STA_WIFI&0x8000)==0)//����δ���
		{
			if(USART2_RX_STA_WIFI&0x4000)//���յ���0x0d
			{
				if(Res_USART2!=0x0a)USART2_RX_STA_WIFI=0;//���մ���,���¿�ʼ
				else USART2_RX_STA_WIFI|=0x8000;	//��������� 
			}
			else //��û�յ�0X0D
			{	
				if(Res_USART2==0x0d)USART2_RX_STA_WIFI|=0x4000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA_WIFI&0X3FFF]=Res_USART2 ;
					USART2_RX_STA_WIFI++;
					
					if(USART2_RX_STA_WIFI>(USART2_REC_LEN-1))    
						USART2_RX_STA_WIFI=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}   		 
  } 
	*/
	
	
//2022.04   ����2�Ľ����ж�
//�ú����������жϱ�־λ�Ƿ���1��ͬʱ�����ж��Ƿ�ʹ������Ӧ���жϡ�
//�����ڴ����жϺ����У����Ҫ��ȡ�жϱ�־λ��ͨ��ʹ�øú�����
//------�����жϺ�����ʹ�á�
if(USART_GetITStatus( USART2, USART_IT_RXNE ) != RESET )
	{
	ucCh  = USART_ReceiveData( USART2 );
	USART_SendData(USART6,ucCh);//��Ϊ����6  ���Է��ͽӿ�   ��ʱ���ε�  2022��5��28��
		
	if(ESP32S_Fram_Record_Struct.InfBit.FramLength < ( RX_BUF_MAX_LEN - 1 ) ) 
		{
		 ESP32S_Fram_Record_Struct.Data_RX_BUF[ESP32S_Fram_Record_Struct.InfBit.FramLength ++]  = ucCh;   
		}                      
	}


//2022.04	  ����2���տ����ж�
//������߿���   ���ú����������жϱ�־λ�Ƿ���1��
//ͬʱ�����ж��Ƿ�ʹ������Ӧ���жϡ�
//�����ڴ����жϺ����У����Ҫ��ȡ�жϱ�־λ��ͨ��ʹ�øú�����
//------�����жϺ�����ʹ�á�
if( USART_GetITStatus( USART2, USART_IT_IDLE ) == SET )  
	{
	 ESP32S_Fram_Record_Struct.InfBit.FramFinishFlag = 1;

	 ucCh = USART_ReceiveData( USART2 );                                                              //�������������жϱ�־λ���ȶ�USART_SR,Ȼ���USART_DR��
	 USART_SendData(USART6,ucCh);//��Ϊ����6   ���Է��ͽӿ�  ��ʱ���ε� 2022��5��28��
	 TcpClosedFlag = strstr(ESP32S_Fram_Record_Struct.Data_RX_BUF, "CLOSED\r\n") ? 1 : 0;
	}  

	
	
	
	
	

#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
#endif	















//������̼�Ĵ��ڳ�ʼ��    CO2
/*******************************************************************************************/
/*****************************USART1�ĳ�ʼ��   CO2******************************************/
/*******************************************************************************************/
#if EN_USART1_RX   //���ʹ���˽���     ��ʼ������1


//����6�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART1_RX_BUF[USART1_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
//u16 USART1_RX_STA_CO2=0;            //����״̬���	

u16 USART1_RX_STA_CO2=0;              //����״̬���	


//��ʼ��IO ����1
//bound:������
void uart1_init_CO2(u32 bound)
	{
   //GPIO�˿�����
  GPIO_InitTypeDef   GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);     //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);    //ʹ��USART1ʱ��   ����1��ʱ���ǲ�һ����   RCC_APB1Periph_USART1   2022-4-14 17:46:34
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);  //GPIOA2����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);  //GPIOA3����ΪUSART1
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA2��GPIOA3
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;            //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	       //�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //���츴�����
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;            //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);                    //��ʼ��PA2��PA3

  //USART1��ʼ������
	USART_InitStructure.USART_BaudRate            = bound;                           //����������
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;             //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;                //һ��ֹͣλ
	USART_InitStructure.USART_Parity              = USART_Parity_No;                 //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //��Ӳ������������
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;	 //�շ�ģʽ
  USART_Init(USART1, &USART_InitStructure);                //��ʼ������1
	
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�   2022.06
	USART_ITConfig(USART1, USART_IT_RXNE|USART_IT_IDLE, ENABLE);
	 //USART_GetFlagStatus(USART1,USART_FLAG_TC);
  USART_Cmd(USART1, ENABLE);                               //ʹ�ܴ���1
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
	
	
	
#if EN_USART1_RX	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //��ռ���ȼ�3    0   1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;		//�����ȼ�3      0   1
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif
	
}


//USART_ClearFlag(USART1,USART_FLAG_TC);   //�ڷ��͵�һ������֮ǰ����һ��
void USARTX_Send_data(USART_TypeDef * USARTx,u8 *s)
{
 while(*s!='\0')
 { 
  while(USART_GetFlagStatus(USARTx,USART_FLAG_TC )==RESET); 
  USART_SendData(USARTx,*s);
  s++;
 }
}






void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	
	u8 CO2_DATA_Receive;    //��������
	
	
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	
	
//2022.04   ����1�Ľ����ж�
//�ú����������жϱ�־λ�Ƿ���1��ͬʱ�����ж��Ƿ�ʹ������Ӧ���жϡ�
//�����ڴ����жϺ����У����Ҫ��ȡ�жϱ�־λ��ͨ��ʹ�øú�����
//------�����жϺ�����ʹ�á�

if(USART_GetITStatus( USART1, USART_IT_RXNE ) != RESET )//�����ж�
	{
		
	 //USART_ClearFlag(USART1, USART_FLAG_TC);
	 USART_ClearITPendingBit(USART1,USART_IT_RXNE); //����жϱ�־.
		
		
	 CO2_DATA_Receive  = USART_ReceiveData( USART1 );
	 //USART_SendData(USART6,CO2_DATA_Receive);//��Ϊ����6  ���Է��ͽӿ�   ��ʱ���ε�  2022��5��28��
		
	 //�ڹ涨�����鳤���£������յ������ݷŵ�����������档���յ�������������ָ��ķ��صĽ��գ�����
	if(CO2_Fram_Record_Struct.InfBit_CO2.FramLength_CO2 < ( CO2_RX_BUF_MAX_LEN - 1 ) ) 
		{
		 CO2_Fram_Record_Struct.Data_RX_BUF_CO2[ CO2_Fram_Record_Struct.InfBit_CO2.FramLength_CO2 ++ ]  = CO2_DATA_Receive;   
		}                      
	}


	
//2022.04	  ����1���տ����ж�
//������߿���   ���ú����������жϱ�־λ�Ƿ���1��
//ͬʱ�����ж��Ƿ�ʹ������Ӧ���жϡ�
//�����ڴ����жϺ����У����Ҫ��ȡ�жϱ�־λ��ͨ��ʹ�øú�����
//------�����жϺ�����ʹ�á�

/*
if( USART_GetITStatus( USART1, USART_IT_IDLE ) == SET )//�����ж�  
	{
	 CO2_Fram_Record_Struct.InfBit_CO2.FramFinishFlag_CO2 = 1;

	 CO2_DATA_Receive = USART_ReceiveData( USART1 ); //�������������жϱ�־λ���ȶ�USART_SR,Ȼ���USART_DR��
	 //USART_SendData(USART6,CO2_DATA_Receive);//��Ϊ����6   ���Է��ͽӿ�  ��ʱ���ε� 2022��5��28��
		
	 //TcpClosedFlag = strstr ( ESP32S_Fram_Record_Struct .Data_RX_BUF, "CLOSED\r\n" ) ? 1 : 0;
	}  
*/
		

	
	
	
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
#endif	




