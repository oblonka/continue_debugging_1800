#include "HTIIC.h"

#include "sys.h"
#include "delay.h"
#include "usart.h" 

//��ʼ��IIC
void HTIIC_Init(void)
			{			
				GPIO_InitTypeDef  GPIO_InitStructure;

				RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��

				//GPIOB8,B9��ʼ������
				GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_8 | GPIO_Pin_9;
				GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_OUT;          //��ͨ���ģʽ
				GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;          //�������
				GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_100MHz;      //100MHz
				GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_UP;           //����
				GPIO_Init(GPIOB, &GPIO_InitStructure);                   //��ʼ��
				HTIIC_SCL=1;
				HTIIC_SDA=1;
			}




//����IIC��ʼ�ź�
void HTIIC_Start(void)
			{
				HTIIC_SDA_OUT();     //sda�����
				HTIIC_SDA=1;	  	  
				HTIIC_SCL=1;
				delay_us(4);
				HTIIC_SDA=0;//START:when CLK is high,DATA change form high to low 
				delay_us(4);
				HTIIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
			}	  



//����IICֹͣ�ź�
void HTIIC_Stop(void)
			{
				HTIIC_SDA_OUT();//sda�����
				HTIIC_SCL=0;
				HTIIC_SDA=0;//STOP:when CLK is high DATA change form low to high
				delay_us(4);
				HTIIC_SCL=1; 
				HTIIC_SDA=1;//����I2C���߽����ź�
				delay_us(4);							   	
			}




//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 HTIIC_Wait_Ack(void)
			{
				u8 ucErrTime=0;
				HTIIC_SDA_IN();      //SDA����Ϊ����  
				HTIIC_SDA=1;delay_us(1);	   
				HTIIC_SCL=1;delay_us(1);	 
				while(HTIIC_READ_SDA)
				{
					ucErrTime++;
					if(ucErrTime>250)
					{
						HTIIC_Stop();
						return 1;
					}
				}
				HTIIC_SCL=0;//ʱ�����0 	   
				return 0;  
			} 





//����ACKӦ��
void HTIIC_Ack(void)
		{
			HTIIC_SCL=0;
			HTIIC_SDA_OUT();
			HTIIC_SDA=0;
			delay_us(2);
			HTIIC_SCL=1;
			delay_us(2);
			HTIIC_SCL=0;
		}




//������ACKӦ��		    
void HTIIC_NAck(void)
		{
			HTIIC_SCL=0;
			HTIIC_SDA_OUT();
			HTIIC_SDA=1;
			delay_us(2);
			HTIIC_SCL=1;
			delay_us(2);
			HTIIC_SCL=0;
		}					 				   





//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void HTIIC_Send_Byte(u8 txd)
		{                        
				u8 t;   
			HTIIC_SDA_OUT(); 	    
				HTIIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
				for(t=0;t<8;t++)
				{              
						HTIIC_SDA=(txd&0x80)>>7;
						txd<<=1; 	  
				delay_us(2);   //��TEA5767��������ʱ���Ǳ����
				HTIIC_SCL=1;
				delay_us(2); 
				HTIIC_SCL=0;	
				delay_us(2);
				}	 
		} 	    





//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 HTIIC_Read_Byte(unsigned char ack)
		{
			unsigned char i,receive=0;
			HTIIC_SDA_IN();//SDA����Ϊ����
				for(i=0;i<8;i++ )
			{
						HTIIC_SCL=0; 
						delay_us(2);
				HTIIC_SCL=1;
						receive<<=1;
						if(HTIIC_READ_SDA)receive++;   
				delay_us(1); 
				}					 
				if (!ack)
						HTIIC_NAck();//����nACK
				else
						HTIIC_Ack(); //����ACK   
				return receive;
		}


		
		
		
		
		