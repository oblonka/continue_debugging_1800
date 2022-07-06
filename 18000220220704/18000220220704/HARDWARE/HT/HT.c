#include "sys.h"
#include "delay.h"

//#include "sram.h"
#include "malloc.h"
#include "ILI93xx.h"

#include "HT.h"//   2022-4-7 15:00:20
#include "HTIIC.h"
#include "usart.h" //20220223  usart6�Ĵ�ӡ������Խӿ�     



/**************************************************�ϴβ��ԣ���ʱ����*************************************************************/

//float_data humidity;    //�洢��ʪ������
//float_data temperature; //�洢���¶�����


//u8 status[3];//״̬�Ĵ���
//u8 status_crc;//CRCУ�����
//u8 crc_check;//crc���
////�����ȡ�������ݣ��п����Ƕ�ȡ��ʱ�����̫�̵��£��������ʱ������С��ʵ�ֶ�ȡ��ʱ�䣡����


///*
//*********************************************************************************************************
//*	�� �� ��: i2c_Delay
//*	����˵��: I2C�����ӳ٣����400KHz
//*	��    �Σ���
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//static void i2c_Delay(void)
//{
//    __NOP();__NOP();__NOP();__NOP();    __NOP();__NOP();__NOP();__NOP();

//}

///*
//*********************************************************************************************************
//*	�� �� ��: i2c_Start
//*	����˵��: CPU����I2C���������ź�
//*	��    �Σ���
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//void i2c_Start(void)
//{
//    /* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź� */
//    I2C_SDA_1();
//    I2C_SCL_1();
//    i2c_Delay();
//    I2C_SDA_0();
//    i2c_Delay();
//    I2C_SCL_0();
//    i2c_Delay();
//}

///*
//*********************************************************************************************************
//*	�� �� ��: i2c_Start
//*	����˵��: CPU����I2C����ֹͣ�ź�
//*	��    �Σ���
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//void i2c_Stop(void)
//{
//    /* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */
//    I2C_SDA_0();
//    I2C_SCL_1();
//    i2c_Delay();
//    I2C_SDA_1();
//}

///*
//*********************************************************************************************************
//*	�� �� ��: i2c_SendByte
//*	����˵��: CPU��I2C�����豸����8bit����
//*	��    �Σ�_ucByte �� �ȴ����͵��ֽ�
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//void i2c_SendByte(uint8_t _ucByte)
//{
//    uint8_t i;

//    /* �ȷ����ֽڵĸ�λbit7 */
//    for (i = 0; i < 8; i++)
//    {
//        if (_ucByte & 0x80)
//        {
//            I2C_SDA_1();
//        }
//        else
//        {
//            I2C_SDA_0();
//        }
//        i2c_Delay();
//        I2C_SCL_1();
//        i2c_Delay();
//        I2C_SCL_0();
//        if (i == 7)
//        {
//            I2C_SDA_1(); // �ͷ�����
//        }
//        _ucByte <<= 1;	/* ����һ��bit */
//        i2c_Delay();
//    }
//}

///*
//*********************************************************************************************************
//*	�� �� ��: i2c_ReadByte
//*	����˵��: CPU��I2C�����豸��ȡ8bit����
//*	��    �Σ���
//*	�� �� ֵ: ����������
//*********************************************************************************************************
//*/
//uint8_t i2c_ReadByte(u8 ack)
//{
//    uint8_t i;
//    uint8_t value;

//    /* ������1��bitΪ���ݵ�bit7 */
//    value = 0;
//    for (i = 0; i < 8; i++)
//    {        
//        value <<= 1;
//        I2C_SCL_1();
//        i2c_Delay();
//        if (I2C_SDA_READ())
//        {
//            value++;
//        }
//        I2C_SCL_0();
//        i2c_Delay();
//    }
//    if(ack==0)
//        i2c_NAck();
//    else
//        i2c_Ack();
//    return value;
//}

///*
//*********************************************************************************************************
//*	�� �� ��: i2c_WaitAck
//*	����˵��: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
//*	��    �Σ���
//*	�� �� ֵ: ����0��ʾ��ȷӦ��1��ʾ��������Ӧ
//*********************************************************************************************************
//*/
//uint8_t i2c_WaitAck(void)
//{
//    uint8_t try_time = 100;//���ӳ�ʱ����

//    I2C_SDA_1();	        //CPU�ͷ�SDA����
//    i2c_Delay();
//    I2C_SCL_1();	        //CPU����SCL = 1, ��ʱ�����᷵��ACKӦ��
//    i2c_Delay(); 

//    while(I2C_SDA_READ())//�ȴ�SHT30Ӧ��
//    {
//        try_time--;
//        i2c_Delay(); 
//        if(try_time==0)//��ʱ������Ӧ
//        {
//            I2C_SCL_0();
//            i2c_Delay();
//            return 1;
//        }
//    }
//    I2C_SCL_0();
//    i2c_Delay();    
//    return 0;
//}

///*
//*********************************************************************************************************
//*	�� �� ��: i2c_Ack
//*	����˵��: CPU����һ��ACK�ź�
//*	��    �Σ���
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//void i2c_Ack(void)
//{
//    I2C_SDA_0();	/* CPU����SDA = 0 */
//    i2c_Delay();
//    I2C_SCL_1();	/* CPU����1��ʱ�� */
//    i2c_Delay();
//    I2C_SCL_0();
//    i2c_Delay();
//    I2C_SDA_1();	/* CPU�ͷ�SDA���� */
//}

///*
//*********************************************************************************************************
//*	�� �� ��: i2c_NAck
//*	����˵��: CPU����1��NACK�ź�
//*	��    �Σ���
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//void i2c_NAck(void)
//{
//    I2C_SDA_1();	/* CPU����SDA = 1 */
//    i2c_Delay();
//    I2C_SCL_1();	/* CPU����1��ʱ�� */
//    i2c_Delay();
//    I2C_SCL_0();
//    i2c_Delay();
//}

///*
//*********************************************************************************************************
//*	�� �� ��: i2c_GPIO_Config
//*	����˵��: ����I2C���ߵ�GPIO������ģ��IO�ķ�ʽʵ��
//*	��    �Σ���
//*	�� �� ֵ: ��
//*********************************************************************************************************
//*/
//void i2c_GPIO_Config(void)
//{
//    //���˾��ó����ʼ������Ҫͨ���׶�������ϰ���ÿ⺯������
//    //������ı�IIC���ŵ�ƽ״̬��������ҪƵ��������������û���ʹ�üĴ�������
//    //GPIO_InitTypeDef GPIO_InitStrcuture;
//    
//	  //RCC_AHB1PeriphClockCmd(IIC_CLOCK,ENABLE);//2022-4-7 13:58:23

//    //GPIO_InitStrcuture.GPIO_Mode = GPIO_Mode_Out_OD;//��©���
//    //GPIO_InitStrcuture.GPIO_Pin = IIC_SDA_PIN|IIC_SCL_PIN;
//    //GPIO_InitStrcuture.GPIO_Speed = GPIO_Speed_50MHz;
//    //GPIO_Init(IIC_GPIO,&GPIO_InitStrcuture);
//	
//	
//	
//	
//		GPIO_InitTypeDef  GPIO_InitStructure;
//		RCC_AHB1PeriphClockCmd(IIC_CLOCK, ENABLE);                 //ʹ��GPIOBʱ��     RCC_AHB1Periph_GPIOB

//		GPIO_InitStructure.GPIO_Pin   = IIC_SDA_PIN | IIC_SCL_PIN; //PB����Ϊ�������
//		GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;             //���ģʽGPIO_Mode_OUT
//		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;             //�������
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;          //50MHz
//		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;              //����
//		GPIO_Init(IIC_GPIO, &GPIO_InitStructure);                  //��ʼ��
//	
//	  //printf("\r\n HT_INIT \r\n");
//}
///*
//*********************************************************************************************************
//*	�� �� ��: i2c_CheckDevice
//*	����˵��: ���I2C�����豸��CPU�����豸��ַ��Ȼ���ȡ�豸Ӧ�����жϸ��豸�Ƿ����
//*	��    �Σ�_Address���豸��I2C���ߵ�ַ
//*	�� �� ֵ: ����ֵ 0 ��ʾ��ȷ�� ����1��ʾδ̽�⵽
//*********************************************************************************************************
//*/
//uint8_t i2c_CheckDevice(uint8_t _Address)
//{
//    uint8_t ucAck;
//    i2c_GPIO_Config();		/* ����GPIO */
//    i2c_Start();		/* ���������ź� */

//    /* �����豸��ַ+��д����bit��0 = w�� 1 = r) bit7 �ȴ� */
//    i2c_SendByte(_Address|I2C_WR);
//    ucAck = i2c_WaitAck();	/* ����豸��ACKӦ�� */

//    i2c_Stop();			/* ����ֹͣ�ź� */
//    return ucAck;
//}










////CRCУ��
//static u8 CRC_Check(u8 *check_data, u8 num, u8 check_crc)
//{
//    uint8_t bit;        // bit mask
//    uint8_t crc = 0xFF; // calculated checksum
//    uint8_t byteCtr;    // byte counter
//    
// // calculates 8-Bit checksum with given polynomial x8+x5+x4+1
//    for(byteCtr = 0; byteCtr < num; byteCtr++)
//    {
//        crc ^= (*(check_data+byteCtr));
//        //crcУ�飬���λ��1��^0x31
//        for(bit = 8; bit > 0; --bit)
//        {
//            if(crc & 0x80)
//                crc = (crc << 1) ^ 0x31;
//            else
//                crc = (crc << 1);
//        }
//    }
//    if(crc==check_crc)
//        return 1;
//    else 
//        return 0;
//}

////������ѡ��ȡ���ݵķ�ʽ��ʼ��
//void SHT30_Init(void)
//{
//    i2c_GPIO_Config();
//    SHT30_General_RESET();//��λ�豸
//    delay_ms(10);
//}

////�������ֽ�ָ�stopȷ���Ƿ���ֹͣ�ź�
//void SHT30_SendBytes(u16 cmd,u8 stop)
//{
//    i2c_Start();
//    i2c_SendByte(SHT30_ADDR<<1 | I2C_WR);//д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ
//    i2c_WaitAck();
//    i2c_SendByte(cmd>>8);
//    i2c_WaitAck();
//    i2c_SendByte(cmd&0xFF);
//    i2c_WaitAck();
//    if(stop)
//        i2c_Stop();
//}

////��λ
//void SHT30_SOFTRESET(void)
//{
//    SHT30_SendBytes(0x30A2,1);
//}

////ͨ�ø�λ
//void SHT30_General_RESET(void)
//{
//    i2c_Start();
//    i2c_SendByte(0x00);
//    i2c_WaitAck();
//    i2c_SendByte(0x06);
//    i2c_WaitAck();
//}

////��ȡ״̬�Ĵ�������
//void SHT30_Get_Status(u8 *buffer)
//{
//    SHT30_SendBytes(0xF32D,0);
//    delay_ms(3);
//    i2c_Start();
//    i2c_SendByte(SHT30_ADDR<<1 | I2C_RD);//д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ
//    if(i2c_WaitAck()==0)
//    {
//        buffer[0]=i2c_ReadByte(1);
//        buffer[1]=i2c_ReadByte(1);
//        buffer[2]=i2c_ReadByte(1);
//        i2c_Stop();
//    }
//}

////���״̬�Ĵ���
//void SHT30_Clear_Status(void)
//{
//    SHT30_SendBytes(0x3041,1);
//}

////����0����״̬�Ĵ�����ȡ�ɹ���1�����ȡ����
//u8 SHT30_Status(void)
//{
//    SHT30_Get_Status(status);
//    
//    if(CRC_Check(status,2,*(status+2)))
//        return 0;//��ȷ
//    else
//        return 1;//����
//}

////���ζ�ȡ����
//void SHT30_Single_Shot(u8 *buffer)
//{
//    u8 try_time=100;
//    
//    SHT30_SendBytes(0x2C06,1);
//    
//    //delay_ms(20);//����Ҫ����Ȼ����������
//	
//	  delay_ms(100);//2022-4-8 14:21:57
//	
//	
//    i2c_Start();
//    i2c_SendByte(SHT30_ADDR<<1 | I2C_RD);//д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ

//    while(i2c_WaitAck())
//    {
//        try_time--;
//        delay_us(50);
//        if(try_time==0)
//            return;
//    }
//    buffer[0]=i2c_ReadByte(1);
//    buffer[1]=i2c_ReadByte(1);
//    buffer[2]=i2c_ReadByte(1);
//    buffer[3]=i2c_ReadByte(1);
//    buffer[4]=i2c_ReadByte(1);
//    buffer[5]=i2c_ReadByte(0);
//    i2c_Stop();
//}

////����/�رռ�����
//void SHT30_Heater(u8 enable)
//{
//    if(enable)
//        SHT30_SendBytes(0x306D,1);
//    else
//        SHT30_SendBytes(0x3066,1);
//}

////������Ӧָ��
//void SHT30_ART(void)
//{
//    SHT30_SendBytes(0x2B32,0);
//}

////�������ڶ�ȡ�ظ��ԺͲ�������
//void SHT30_Periodic_SetRepeat(void)
//{
//    SHT30_SendBytes(0x2737,0);//���ظ��ȣ�mpsΪ10
//}

////�������ڶ�ȡ������
//void SHT30_Periodic_Config(void)
//{
//    //����
//    SHT30_Periodic_SetRepeat();
//    SHT30_ART();
//}
////���ڶ�ȡ���� ���ʹ�þ�Ҫ�ڳ�ʼ��ʱ����SHT30_Periodic_Config()����
//void SHT30_Periodic(u8 *buffer)
//{
//    u8 try_time=100;
//    
//    //��ȡ����
//    SHT30_SendBytes(0xE000,0);
//    delay_ms(3);//����Ҫ����Ȼ����������

//    i2c_Start();
//    i2c_SendByte(SHT30_ADDR<<1 | I2C_RD);//д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ
//    
//    while(i2c_WaitAck())
//    {
//        try_time--;
//        delay_us(50);
//        if(try_time==0)
//            return;
//    }
//    buffer[0]=i2c_ReadByte(1);
//    buffer[1]=i2c_ReadByte(1);
//    buffer[2]=i2c_ReadByte(1);
//    buffer[3]=i2c_ReadByte(1);
//    buffer[4]=i2c_ReadByte(1);
//    buffer[5]=i2c_ReadByte(0);
//    i2c_Stop();
//}

////�ж�ָ��/ֹͣ���ڻ�ȡ���ݹ���
//void SHT30_Stop_Break(void)
//{
//    SHT30_SendBytes(0x3093,1);
//    delay_ms(15);
//}

////��ȡSHT3x��ʪ��
//void SHT30_Read(void)
//{    
//    u8 buff[6];   //��ȡraw����
//    u16 tem,hum;  //ƴ����ʪ������
//    u8 crcT,crcH; //�¶Ⱥ�ʪ�ȵ�CRCУ��

//    float Temperature=0;//ת�������ʪ��
//    float Humidity=0;

//    //SHT30_Single_Shot(buff);
//    SHT30_Periodic(buff);
//    
//    tem = ((buff[0]<<8) | buff[1]);//�¶�ƴ��
//    hum = ((buff[3]<<8) | buff[4]);//ʪ��ƴ��

//    //�����¶Ⱥ�ʪ��CRCУ����
//    crcT = CRC_Check(buff,2,buff[2]);   //�¶�
//    crcH = CRC_Check(buff+3,2,buff[5]); //ʪ��
//    
//	

//	
//	  
//		//�����ֲ���㹫ʽ����
//			Temperature = (175.0*(float)tem/65535.0-45.0) ;  // T = -45 + 175 * tem / (2^16-1)
//			Humidity    = (100.0*(float)hum/65535.0);           // RH = hum*100 / (2^16-1)
//			if((Temperature>=-20)&&(Temperature<=125)&&(Humidity>=0)&&(Humidity<=100))//���˳���������Χ�Ĵ�������
//			{
//					temperature.fdata=Temperature;
//					humidity.fdata=Humidity;
//			}
//	
//	  printf("\r\n\r\n tem:%d\r\n",tem);
//		printf(" hum:%d\r\n",hum);
//    
//		printf(" crcT:%d\r\n",crcT);
//		printf(" crcH:%d\r\n",crcH);	
//		 	
//		printf(" tem:%lf\r\n",Temperature);
//		printf(" Hum:%lf\r\n",Humidity);		
//				
//			
//			
//			
//			
//			
//	  printf(" sht30_ceshi_front\r\n");
//			
//    if(crcT&&crcH)//�ж�CRCУ���Ƿ��
//    {
//        //�����ֲ���㹫ʽ����
//        Temperature = (175.0*(float)tem/65535.0-45.0) ;  // T = -45 + 175 * tem / (2^16-1)
//        Humidity    = (100.0*(float)hum/65535.0);           // RH = hum*100 / (2^16-1)
//        if((Temperature>=-20)&&(Temperature<=125)&&(Humidity>=0)&&(Humidity<=100))//���˳���������Χ�Ĵ�������
//        {
//            temperature.fdata=Temperature;
//            humidity.fdata=Humidity;
//        }
//					//����
//					printf("\r\n temperature:%lf\r\n",Temperature);
//					printf("\r\n Humidity:%lf\r\n",Humidity);
//     }
//		
//		printf(" sht30_ceshi_back\r\n\r\n");
//		
//		
//}


/**************************************************�ϴβ��ԣ���ʱ����*************************************************************/


				 

unsigned short int   sht30_data_buffer[6];

float SHT30_temperature;
float SHT30_humidity;




//��ʼ��SHT30
void SHT30_Init(void)
{
    delay_ms(250); 
   	HTIIC_Start();
   	HTIIC_Send_Byte(0x88);
   	HTIIC_Wait_Ack();
   	HTIIC_Send_Byte(0x21);
   	HTIIC_Wait_Ack();
   	HTIIC_Send_Byte(0x30);
   	HTIIC_Wait_Ack();
    HTIIC_Stop();
   
    delay_ms(150); 
}




//��ȡ��ʪ��
void sht30_read_temp_humi(u16 *p)
{
   HTIIC_Start();
   HTIIC_Send_Byte(0x88);
   HTIIC_Wait_Ack();
   HTIIC_Send_Byte(0xe0);
   HTIIC_Wait_Ack();
   HTIIC_Send_Byte(0x00);
   HTIIC_Wait_Ack();

	 HTIIC_Start();
   HTIIC_Send_Byte(0x89);
   HTIIC_Wait_Ack();
   
   p[0] = HTIIC_Read_Byte(1);
   p[1] = HTIIC_Read_Byte(1);
   p[2] = HTIIC_Read_Byte(1);
   p[3] = HTIIC_Read_Byte(1);
   p[4] = HTIIC_Read_Byte(1);
   p[5] = HTIIC_Read_Byte(0);
	
   HTIIC_Stop();
}







//�����ȡ������
int sht30_data_process(void)
{
  u8 temporary[3];
  u16 data;
  u8 crc_result;
	
  sht30_read_temp_humi(sht30_data_buffer);
  temporary[0]=sht30_data_buffer[0];
  temporary[1]=sht30_data_buffer[1];
  temporary[2]=sht30_data_buffer[2];
  crc_result=sht30_crc8_check(temporary,2,temporary[2]);
	
	
if(crc_result==0)
		{
		data=((u16)temporary[0] << 8) | temporary[1];
		SHT30_temperature = (int)((175.0 * ((float)data) / 65535.0 - 45.0) *10.0);
		}
else
		{
		return 1;
		}
  temporary[0]=sht30_data_buffer[3];
  temporary[1]=sht30_data_buffer[4];
  temporary[2]=sht30_data_buffer[5];
  crc_result=sht30_crc8_check(temporary,2,temporary[2]);
	
	
		
if(crc_result==0)
		{
		data=((u16)temporary[0] << 8) | temporary[1];
		SHT30_humidity = (int)((100.0 * (float)data / 65535.0) *10.0); 
		return 0;
		}
else
		{
		return 2;
		}
	
	
	//=2022-4-13 13:13:45
	printf("temperature:%6.1fC\r\nhumidity:%6.1f\r\n",SHT30_temperature/10,SHT30_humidity/10);
	
}








//������������ΪCRCУ��
 int  crc8_compute(u8 *check_data, u8 num_of_data)
{
 	uint8_t bit;        // bit mask
 uint8_t crc = 0xFF; // calculated checksum
 uint8_t byteCtr;    // byte counter

 // calculates 8-Bit checksum with given polynomial
 for(byteCtr = 0; byteCtr < num_of_data; byteCtr++) {
     crc ^= (check_data[byteCtr]);
     for(bit = 8; bit > 0; --bit) {
         if(crc & 0x80) {
             crc = (crc << 1) ^ 0x31;
         }  else {
             crc = (crc << 1);
         }
     }
 }
 return crc;
}







int sht30_crc8_check(u8 *p,u8 num_of_data,u8 CrcData)
{
  uint8_t crc;
  crc = crc8_compute(p, num_of_data);// calculates 8-Bit checksum
 if(crc != CrcData) 
 {   
     return 1;           
 }
 return 0;
}





















