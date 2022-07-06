#include "beep.h" 

#include "sys.h"
#include "usart.h"	

#include "WIFI.h"
#include "MQTT.h"
#include "TCP.h"
#include "includes.h"	
#include "AIR.h"

//��ʼ��PB14Ϊ�����		    
//BEEP IO��ʼ��



void BEEP_Init(void)
{   
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��
  
  //��ʼ����������Ӧ����GPIOB14
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;        //��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;        //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;    //100MHz
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;       //����
  GPIO_Init(GPIOB, &GPIO_InitStructure);                //��ʼ��GPIO
	
	
//	GPIO_SetBits(GPIOB,GPIO_Pin_14);
//	delay_ms(500);
//  GPIO_ResetBits(GPIOB,GPIO_Pin_14);                    //��������Ӧ����GPIOF8���ͣ� 
	
	
}

