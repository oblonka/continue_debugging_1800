#ifndef __USART_H
#define __USART_H

#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h"  

//����1   CO2        [PA9 TX]   [PA10 RX]
//����2   WiFi       [PA2 TX]   [PA3  RX]
//����6   ���Դ���   [PC6 TX]   [PC7  RX]



#define USART_REC_LEN  			  200   //�����������ֽ��� 200
#define USART2_REC_LEN  			200  	//�����������ֽ��� 200     00��37��                                                                               
#define USART1_REC_LEN  			200



#define EN_USART6_RX 			   1		//ʹ�ܣ�1��/��ֹ��0��     ����6����
#define EN_USART2_RX 			   1		//ʹ�ܣ�1��/��ֹ��0��     ����2����          2022-4-14 17:22:34
#define EN_USART1_RX 			   1		//ʹ�ܣ�1��/��ֹ��0��     ����1����          2022-4-17 15:00:07	



extern u8  USART_RX_BUF[USART_REC_LEN];   //6   ���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8  USART2_RX_BUF[USART2_REC_LEN]; //2   ���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8  USART1_RX_BUF[USART1_REC_LEN]; //1




extern u16 USART_RX_STA;         		        //6����״̬���	
extern u16 USART2_RX_STA_WIFI;         		  //2����״̬���    2022-4-14 17:42:03
extern u16 USART1_RX_STA_CO2;         		  //2����״̬���




//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);      //����6�ĳ�ʼ��
void uart2_init_wifi(u32 bound);//����2         2022-4-14 17:41:00
void uart1_init_CO2(u32 bound); //����1

//��׼��Ĭ�ϵ��ǵ��ַ��ķ��ͣ��޸�λ���ֽڵķ���
void USARTX_Send_data(USART_TypeDef * USARTx,u8 *s);//���ַ����ķ���

void CO2_Tx();



#endif








