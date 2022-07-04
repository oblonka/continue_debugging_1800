#include "ctiic.h"
#include "delay.h"	 
#include "cst148.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

//����I2C�ٶȵ���ʱ
void CST_Delay(void)
{
	delay_us(1);
} 


//���ݴ���оƬIIC�ӿڳ�ʼ��
void CST_IIC_Init(void)
		{					     
				GPIO_InitTypeDef  GPIO_InitStructure;
				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);      //ʹ��GPIOBʱ��

				GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11; //PB0����Ϊ�������
				GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;             //���ģʽGPIO_Mode_OUT
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;             //�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;          //100MHz
				GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;              //����
				GPIO_Init(GPIOB, &GPIO_InitStructure);                     //��ʼ��

			
			  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13;               //PB13 �ж�����   ����Ϊ��������  20220302
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;              //����ģʽ
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;             //�������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;         //100MHz
				GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;              //����
				GPIO_Init(GPIOB, &GPIO_InitStructure);                     //��ʼ��
					
			
			
				GPIO_SetBits(GPIOB,GPIO_Pin_10);						               //���1
				GPIO_SetBits(GPIOB,GPIO_Pin_11);					                 //���1
			
			
			
		}


//����IIC��ʼ�ź�
void CST_IIC_Start(void)
{
	CST_SDA_OUT();//sda�����
	CST_IIC_SDA=1;	  	  
	CST_IIC_SCL=1;
	CST_Delay();
 	CST_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	CST_Delay();
	CST_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  


//����IICֹͣ�ź�
void CST_IIC_Stop(void)
{ 
	CST_SDA_OUT();//sda�����
	CST_IIC_SCL=0;
	CST_IIC_SDA=0;
	CST_Delay();
	CST_IIC_SCL=1;
	CST_Delay();
	CST_IIC_SDA=1;//STOP:when CLK is high DATA change form low to high 
}


//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 CST_IIC_Wait_Ack(void)
{
	u16 ucErrTime=0;
	CST_SDA_IN();      //SDA����Ϊ����  
	CST_IIC_SDA=1;delay_us(1);	   
	while(CST_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>20000)
		{
			CST_IIC_Stop();
			return 1;
		} 
	}
	CST_IIC_SCL=1;delay_us(4);	 //20220118
	CST_IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 


//����ACKӦ��
void CST_IIC_Ack(void)
{
	CST_IIC_SCL=0;
	CST_SDA_OUT();
	CST_IIC_SDA=0;
	CST_Delay();
	delay_us(2);
	CST_IIC_SCL=1;
	CST_Delay();
	CST_IIC_SCL=0;
}


//������ACKӦ��		    
void CST_IIC_NAck(void)
{
	CST_IIC_SCL=0;
	CST_SDA_OUT();
	CST_IIC_SDA=1;
	CST_Delay();
	CST_IIC_SCL=1;
	CST_Delay();
	CST_IIC_SCL=0;
}					 				   


//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void CST_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
		CST_SDA_OUT(); 	    
    CST_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        CST_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	      
				CST_IIC_SCL=1;
				CST_Delay();
				CST_IIC_SCL=0;	
				CST_Delay();
    }	 
} 	


//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 CST_IIC_Read_Byte(unsigned char ack)
{
	u8 i,receive=0;
	CST_IIC_SCL=0;
 	CST_SDA_IN();//SDA����Ϊ����
	delay_us(1);
  for(i=0;i<8;i++ )
	{
    CST_IIC_SCL=0;
    CST_Delay();    
		CST_IIC_SCL=1; 
		delay_us(2);		
		receive<<=1;
		if(CST_READ_SDA)receive++;
	}	  				 
	if (!ack)CST_IIC_NAck();//����nACK
	else CST_IIC_Ack(); //����ACK
 	return receive;
}



u8 CST148_WR_Reg(u16 reg,u8 *buf,u8 len)//��148�Ĵ�����������ַ���洢������
{
	u8 i;
	u8 ret=0;
	
	CST_IIC_Start();	
	
 	CST_IIC_Send_Byte(CST148_CMD_WR);   //����д���� 	 
	CST_IIC_Wait_Ack();
	if(ret)
		{
		 printf("1 CT_IIC_Wait_Ack error . \r\r\n");
	  }
	else{
	printf("\r\n\r\n 1 ack ok. \r\r\n");
	};
	
	CST_IIC_Send_Byte(reg>>8);   	      //���͸�8λ��ַ
	CST_IIC_Wait_Ack(); 
  if(ret){
		printf("1 CT_IIC_Wait_Ack error . \r\r\n");
	} 	
	else{
	printf(" 2 ack ok. \r\r\n");
	};
	CST_IIC_Send_Byte(reg&0XFF);   	    //���͵�8λ��ַ
	CST_IIC_Wait_Ack();  
	if(ret){
		printf("1 CT_IIC_Wait_Ack error . \r\r\n");
	} 
	else{
	printf(" 3 ack ok. \r\r\n");
	};
	
	for(i=0;i<len;i++)
	{	   
    CST_IIC_Send_Byte(buf[i]);  	    //������
		ret=CST_IIC_Wait_Ack();
		if(ret)break;  
	}
    CST_IIC_Stop();					          //����һ��ֹͣ����	    
	return ret; 
}





void CST148_RD_Reg(u16 reg,u8 *buf,u8 len)//д148�Ĵ�����������ַ���洢������
{
	u8 i; 
 	CST_IIC_Start();	
 	CST_IIC_Send_Byte(CST148_CMD_WR);           //����д���� 	 
	CST_IIC_Wait_Ack();
 	CST_IIC_Send_Byte(reg>>8);   	              //���͸�8λ��ַ
	CST_IIC_Wait_Ack(); 	 										  		   
 	CST_IIC_Send_Byte(reg&0XFF);      	        //���͵�8λ��ַ
	CST_IIC_Wait_Ack();  
 	CST_IIC_Start();  	 	   
	CST_IIC_Send_Byte(CST148_CMD_RD);           //���Ͷ�����		   
	CST_IIC_Wait_Ack();	   
	for(i=0;i<len;i++)
	{	   
    buf[i]=CST_IIC_Read_Byte(i==(len-1)?0:1); //������	  
	} 
    CST_IIC_Stop();                           //����һ��ֹͣ����    
}




