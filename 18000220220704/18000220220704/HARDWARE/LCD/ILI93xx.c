#include "ILI93XX.h"
#include "stdlib.h"
#include "font.h" 
#include "usart.h"	 
#include "delay.h"	
//#include "image.h"

#include "sys.h"

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8; 

//LCD�Ļ�����ɫ�ͱ���ɫ	   
u16 POINT_COLOR =0x0000;	//������ɫ
u16 BACK_COLOR  =0xFFFF;  //����ɫ 
  
//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;
	 
//д�Ĵ�������
//regval:�Ĵ���ֵ
void LCD_WR_REG(u16 regval)
{   
	LCD->LCD_REG=regval;//д��Ҫд�ļĴ������	 
}
//дLCD����
//data:Ҫд���ֵ
void LCD_WR_DATA(u16 data)
{	 
	LCD->LCD_RAM=data;		 
}
//��LCD����
//����ֵ:������ֵ
u16 LCD_RD_DATA(void)
{
	vu16 ram;			//��ֹ���Ż�
	ram=LCD->LCD_RAM;	
	return ram;	 
}					   
//д�Ĵ���
//LCD_Reg:�Ĵ�����ַ
//LCD_RegValue:Ҫд�������
void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{	
	LCD->LCD_REG = LCD_Reg;		//д��Ҫд�ļĴ������	 
	LCD->LCD_RAM = LCD_RegValue;//д������	    		 
}	   
//���Ĵ���
//LCD_Reg:�Ĵ�����ַ
//����ֵ:����������
u16 LCD_ReadReg(u16 LCD_Reg)
{										   
	LCD_WR_REG(LCD_Reg);		//д��Ҫ���ļĴ������
	delay_us(15);		  
	return LCD_RD_DATA();		//���ض�����ֵ
}   
//��ʼдGRAM
void LCD_WriteRAM_Prepare(void)
{
 	LCD->LCD_REG=lcddev.wramcmd;	  
}	 
//LCDдGRAM
//RGB_Code:��ɫֵ
void LCD_WriteRAM(u16 RGB_Code)
{							    
	LCD->LCD_RAM = RGB_Code;//дʮ��λGRAM
}
//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ
u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
} 
//��mdk -O1ʱ���Ż�ʱ��Ҫ����
//��ʱi
void opt_delay(u8 i)
{
	while(i--);
}
//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
u16 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r=0,g=0,b=0;
	u16 color;
	if(x>=lcddev.width||y>=lcddev.height)return 0;	//�����˷�Χ,ֱ�ӷ���		   
	LCD_SetCursor(x,y);	  
  if(lcddev.id==0X9341)
	{
		LCD_WR_REG(0X2E);//9341 ���Ͷ�GRAMָ��
		r=LCD_RD_DATA();								//dummy Read	   
		opt_delay(2);	  
		r=LCD_RD_DATA();  		  						//ʵ��������ɫ
		//9341Ҫ��2�ζ���
		opt_delay(2);	  
		b=LCD_RD_DATA(); 
		g=r&0XFF;		//����9341/5310/5510,��һ�ζ�ȡ����RG��ֵ,R��ǰ,G�ں�,��ռ8λ
		g<<=8;
		return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));//ILI9341��Ҫ��ʽת��һ��
	}		
	else if(lcddev.id==0X9486||lcddev.id==0X7796)
	{
		LCD_WR_REG(0X2E);//9486 ���Ͷ�GRAMָ��
		color=LCD_RD_DATA();								//������ɫֵ	 
		opt_delay(2);	  
		color=LCD_RD_DATA();  		  						//ʵ��������ɫ
		opt_delay(2);	   
		return 	color;	
	}
	else
	{
		return 0;
	}
	
}		 
//LCD������ʾ
void LCD_DisplayOn(void)
{					   
	if(lcddev.id==0X9486||lcddev.id==0X7796||lcddev.id==0X9341||lcddev.id==0X7796)LCD_WR_REG(0X29);	//������ʾ
}	 
//LCD�ر���ʾ
void LCD_DisplayOff(void)
{	   
	if(lcddev.id==0X9486||lcddev.id==0X7796||lcddev.id==0X9341)LCD_WR_REG(0X28);	//�ر���ʾ
}   
//���ù��λ��
//Xpos:������
//Ypos:������
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	 
	if(lcddev.id==0X9486||lcddev.id==0X7796)
	{
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(Xpos>>8);LCD_WR_DATA(Xpos&0XFF); 		
		LCD_WR_DATA(Xpos>>8);LCD_WR_DATA(Xpos&0XFF); 				 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(Ypos>>8);LCD_WR_DATA(Ypos&0XFF);
		LCD_WR_DATA(Ypos>>8);LCD_WR_DATA(Ypos&0XFF);
	}
	else if(lcddev.id==0X9341||lcddev.id==0X5310)
	{		    
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(Xpos>>8);LCD_WR_DATA(Xpos&0XFF); 			 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(Ypos>>8);LCD_WR_DATA(Ypos&0XFF); 

	}
} 		 
//����LCD���Զ�ɨ�跽��
//ע��:�����������ܻ��ܵ��˺������õ�Ӱ��(������9341/6804����������),
//����,һ������ΪL2R_U2D����,�������Ϊ����ɨ�跽ʽ,���ܵ�����ʾ������.
//dir:0~7,����8������(���嶨���lcd.h)
//9320/9325/9328/4531/4535/1505/b505/5408/9341/5310/5510/1963��IC�Ѿ�ʵ�ʲ���	   	   
void LCD_Scan_Dir(u8 dir)
{
	u16 regval=0;
	u16 dirreg=0;
	if(lcddev.dir==1)//����ʱ����6804��1963���ı�ɨ�跽������ʱ1963�ı䷽��
	{			   
		switch(dir)//����ת��
		{
			case 0:dir=6;break;
			case 1:dir=7;break;
			case 2:dir=4;break;
			case 3:dir=5;break;
			case 4:dir=1;break;
			case 5:dir=0;break;
			case 6:dir=3;break;
			case 7:dir=2;break;	     
		}
	} 
	if(lcddev.id==0X9486||lcddev.id==0X7796||lcddev.id==0x9341)//9341/6804/5310/5510/1963,���⴦��
	{
		switch(dir)
		{
			case L2R_U2D://������,���ϵ���
				regval|=(0<<7)|(0<<6)|(0<<5); 
				break;
			case L2R_D2U://������,���µ���
				regval|=(1<<7)|(0<<6)|(0<<5); 
				break;
			case R2L_U2D://���ҵ���,���ϵ���
				regval|=(0<<7)|(1<<6)|(0<<5); 
				break;
			case R2L_D2U://���ҵ���,���µ���
				regval|=(1<<7)|(1<<6)|(0<<5); 
				break;	 
			case U2D_L2R://���ϵ���,������
				regval|=(0<<7)|(0<<6)|(1<<5); 
				break;
			case U2D_R2L://���ϵ���,���ҵ���
				regval|=(0<<7)|(1<<6)|(1<<5); 
				break;
			case D2U_L2R://���µ���,������
				regval|=(1<<7)|(0<<6)|(1<<5); 
				break;
			case D2U_R2L://���µ���,���ҵ���
				regval|=(1<<7)|(1<<6)|(1<<5); 
				break;	 
		}
		dirreg=0X36;
 		regval|=0X08; 
		if(lcddev.id==0X6804)regval|=0x02;//6804��BIT6��9341�ķ���	   
		LCD_WriteReg(dirreg,regval);
		
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(0);LCD_WR_DATA(0);
		LCD_WR_DATA((lcddev.width-1)>>8);LCD_WR_DATA((lcddev.width-1)&0XFF);
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(0);LCD_WR_DATA(0);
		LCD_WR_DATA((lcddev.height-1)>>8);LCD_WR_DATA((lcddev.height-1)&0XFF);  
		
  	}

}     
//����
//x,y:����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);		//���ù��λ�� 
	LCD_WriteRAM_Prepare();	//��ʼд��GRAM
	LCD->LCD_RAM=POINT_COLOR; 
}
//���ٻ���
//x,y:����
//color:��ɫ
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
{
	if(lcddev.id==0X9486||lcddev.id==0X7796)
	{
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(x>>8);LCD_WR_DATA(x&0XFF);
		LCD_WR_DATA(x>>8);LCD_WR_DATA(x&0XFF); 			 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(y>>8);LCD_WR_DATA(y&0XFF);
		LCD_WR_DATA(y>>8);LCD_WR_DATA(y&0XFF);
		
	}
	if(lcddev.id==0X9341||lcddev.id==0X5310)
	{
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(x>>8);LCD_WR_DATA(x&0XFF);  			 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(y>>8);LCD_WR_DATA(y&0XFF); 
	}			 
	LCD->LCD_REG=lcddev.wramcmd; 
	LCD->LCD_RAM=color; 
}	 


//����LCD��ʾ����
//dir:0,������1,����
void LCD_Display_Dir(u8 dir)
{
	if(dir==0)			//����
	{
		lcddev.dir=0;	//����
		lcddev.width=240;//
		lcddev.height=320;
		if(lcddev.id==0X9486||lcddev.id==0X7796||lcddev.id==0X9341)
		{
			lcddev.wramcmd=0X2C;
	 		lcddev.setxcmd=0X2A;
			lcddev.setycmd=0X2B;  	 
			if(lcddev.id==0X9486||lcddev.id==0X7796)
			{
				lcddev.width=320;
				lcddev.height=480;
			}
		}
	}
	else 				//����
	{	  				
		lcddev.dir=1;	//����
		lcddev.width=320;
		lcddev.height=240;
		if(lcddev.id==0X9486||lcddev.id==0X7796||lcddev.id==0X9341)
		{
			lcddev.wramcmd=0X2C;
	 		lcddev.setxcmd=0X2A;
			lcddev.setycmd=0X2B;  	 
		}
		if(lcddev.id==0X9486||lcddev.id==0X7796)
		{ 	 
			lcddev.width=480;
			lcddev.height=320; 			
		}
	} 
	LCD_Scan_Dir(DFT_SCAN_DIR);	//Ĭ��ɨ�跽��
}	 
//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//width,height:���ڿ�Ⱥ͸߶�,�������0!!
//�����С:width*height. 
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height)
{    
	u16 twidth,theight;
	twidth=sx+width-1;
	theight=sy+height-1;
	if(lcddev.id==0X9486||lcddev.id==0X7796||lcddev.id==0X9341)
	{
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(sx>>8); 
		LCD_WR_DATA(sx&0XFF);	 
		LCD_WR_DATA(twidth>>8); 
		LCD_WR_DATA(twidth&0XFF);  
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(sy>>8); 
		LCD_WR_DATA(sy&0XFF); 
		LCD_WR_DATA(theight>>8); 
		LCD_WR_DATA(theight&0XFF); 
	}
}
//��ʼ��lcd 

/*
����TFTLCD��(16λ��洢��)��RS�Žӵ�FMC_A18���棬ʹ��FMC_NE1(����ʹ��BANK1����bank1),  ����Ϊ0  ����Ϊ1

�ⲿ�洢����ַ��Ѱַ��A18Ϊ0ʱҲ����FMC_A[24��0]=0x3FFFF��
����һλ�����ڲ�����HADDR[25:1]=00 0000 0111 1111 1111 1111 1110=0x7fffe��
�����ڲ����߶�д�ⲿ�洢������(REG)�ĵ�ַ(Ѱַ)�ͱ�Ϊ0x60000000+0X7FFFE(FMC_A18��RSΪ0ʱ);

���洢����ַ��Ѱַ��A18Ϊ1ʱҲ����FMC_A[24��0]=0x40000��
����һλ�����ڲ�����HADDR[25:1]=00 0000 1000 0000 0000 0000 0000 =0x8000��
�ڲ����߶�д�ⲿ�洢������(RAM)�ĵ�ַ��Ϊ0x60000000+0X80000(FMC_A18��RSΪ1ʱ)��
*/






void LCD_Init(void)
{ 					
	vu32 i=0;
	
  GPIO_InitTypeDef  GPIO_InitStructure;                //GPIO���üĴ���
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;  //Ƭѡ���ƼĴ���
  FSMC_NORSRAMTimingInitTypeDef  readWriteTiming;      //Ƭѡʱ��Ĵ���
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;          //д��ʱ��Ĵ���
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��PD,PEʱ��  
  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);                       //ʹ��FSMCʱ��  
	
 
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;        //PE6 �������,���Ʊ���
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;     //��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //100MHz
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;      //����
  GPIO_Init(GPIOE, &GPIO_InitStructure);             //��ʼ�� //PE6 �������,���Ʊ���
	
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;//PD8 9 10 14 15 0 1 4 5 7 
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;      //�������
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //100MHz
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;      //����
  GPIO_Init(GPIOD, &GPIO_InitStructure);             //��ʼ��  
	
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//PE2 7 8 9 10 11 12 13 14 15
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;      //�������
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //100MHz
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;      //����
  GPIO_Init(GPIOE, &GPIO_InitStructure);             //��ʼ��  


  GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC);  //PD8
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);  //PD9
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC); //PD10
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC); //PD14
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC); //PD15
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);  //PD0
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);  //PD1
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);  //PD4
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC);  //PD5
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource7,GPIO_AF_FSMC);  //PD7
	
 
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource2,GPIO_AF_FSMC);  //PE2
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);  //PE7
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);  //PE8 
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);  //PE9
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC); //PE10
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC); //PE11
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC); //PE12
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC); //PE13
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC); //PE14
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC); //PE15
 

  readWriteTiming.FSMC_AddressSetupTime      = 2;	               //0XF ��ַ����ʱ�䣨ADDSET��Ϊ16��HCLK 1/168M=6ns*16=96ns	
  readWriteTiming.FSMC_AddressHoldTime       = 10;	             //10 0x00 ��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�	
  readWriteTiming.FSMC_DataSetupTime         = 2;			           //60 ���ݱ���ʱ��Ϊ60��HCLK	=6*60=360ns
  readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;             //0x00
  readWriteTiming.FSMC_CLKDivision           = 0;                //16  0x00
  readWriteTiming.FSMC_DataLatency           = 0;                //17  0x00
  readWriteTiming.FSMC_AccessMode            = FSMC_AccessMode_A;//ģʽA 
    

	writeTiming.FSMC_AddressSetupTime          = 2;	               //9 ��ַ����ʱ�䣨ADDSET��Ϊ9��HCLK =54ns 
  writeTiming.FSMC_AddressHoldTime           = 10;	             //10 0x00 ��ַ����ʱ�䣨A		
  writeTiming.FSMC_DataSetupTime             = 2;		             //8 ���ݱ���ʱ��Ϊ6ns*9��HCLK=54ns
  writeTiming.FSMC_BusTurnAroundDuration     = 0x00;             //0x00
  writeTiming.FSMC_CLKDivision               = 0;                //16  0x00
  writeTiming.FSMC_DataLatency               = 0;                //17  0x00
  writeTiming.FSMC_AccessMode                = FSMC_AccessMode_A;//ģʽA 

 
  FSMC_NORSRAMInitStructure.FSMC_Bank                  = FSMC_Bank1_NORSRAM1;                  // ������NE1 6000 0000  - 63FF FFFF  .��������ʹ��NE4 ��Ҳ�Ͷ�ӦBTCR[6],[7]��
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux        = FSMC_DataAddressMux_Disable;          // ���������ݵ�ַ
  FSMC_NORSRAMInitStructure.FSMC_MemoryType            = FSMC_MemoryType_SRAM;                 // FSMC_MemoryType_SRAM;  //SRAM   
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth       = FSMC_MemoryDataWidth_16b;             //�洢�����ݿ��Ϊ16bit   
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode       = FSMC_BurstAccessMode_Disable;         // FSMC_BurstAccessMode_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity    = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait      = FSMC_AsynchronousWait_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WrapMode              = FSMC_WrapMode_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive      = FSMC_WaitSignalActive_BeforeWaitState;  
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation        = FSMC_WriteOperation_Enable;	         //  �洢��дʹ��
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal            = FSMC_WaitSignal_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode          = FSMC_ExtendedMode_Enable;             // ��дʹ�ò�ͬ��ʱ��
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst            = FSMC_WriteBurst_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;                     //��дʱ��
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct     = &writeTiming;                         //дʱ��

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);                                                //��ʼ��FSMC����

  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);                                                //������NE1  ʹ��BANK1 
	
		
 
//	delay_ms(50); 					// delay 50 ms 
//  	lcddev.id=LCD_ReadReg(0x0000);	//��ID��9320/9325/9328/4531/4535��IC�� 
//    printf(" LCD ID:%x\r\n",lcddev.id); //��ӡLCD ID 
//  	if(lcddev.id<0XFF||lcddev.id==0XFFFF||lcddev.id==0X9300)//����ID����ȷ,����lcddev.id==0X9300�жϣ���Ϊ9341��δ����λ������»ᱻ����9300
//	{	
// 		//����9341 ID�Ķ�ȡ		
//		LCD_WR_REG(0XD3);				   
//		lcddev.id=LCD_RD_DATA();	//dummy read 	
// 		lcddev.id=LCD_RD_DATA();	//����0X00
//  		lcddev.id=LCD_RD_DATA();   	//��ȡ93	����94							   
// 		lcddev.id<<=8;
//		lcddev.id|=LCD_RD_DATA();  	//��ȡ41 	 	����86����88
//	} 
	
// 	printf(" LCD ID:%x\r\n",lcddev.id); //��ӡLCD ID 

	lcddev.id = 0X7796;
	if(lcddev.id==0X7796)
	{
		delay_ms(500);//120
		LCD_WR_REG(0X11);
		delay_ms(500);//120

		LCD_WR_REG(0Xf0);
		LCD_WR_DATA(0xc3);

		LCD_WR_REG(0Xf0);
		LCD_WR_REG(0x96);

		LCD_WR_REG(0X36);  
		LCD_WR_DATA(0x00);     //������ʾ����

		LCD_WR_REG(0x3A);
		LCD_WR_DATA(0x05);

		LCD_WR_REG(0Xe8);
		LCD_WR_DATA(0x40);
		LCD_WR_DATA(0x82);
		LCD_WR_DATA(0x07);
		LCD_WR_DATA(0x18);
		LCD_WR_DATA(0x27);
		LCD_WR_DATA(0x0a);
		LCD_WR_DATA(0xb6);
		LCD_WR_DATA(0x33);

		LCD_WR_REG(0Xc5);
		LCD_WR_DATA(0x27);

		LCD_WR_REG(0Xc2);
		LCD_WR_DATA(0xa7);

		LCD_WR_REG(0Xe0);
		LCD_WR_DATA(0xf0);
		LCD_WR_DATA(0x01);
		LCD_WR_DATA(0x06);
		LCD_WR_DATA(0x0f);
		LCD_WR_DATA(0x12);
		LCD_WR_DATA(0x1d);
		LCD_WR_DATA(0x36);
		LCD_WR_DATA(0x54);
		LCD_WR_DATA(0x44);
		LCD_WR_DATA(0x0c);
		LCD_WR_DATA(0x18);
		LCD_WR_DATA(0x16);
		LCD_WR_DATA(0x13);
		LCD_WR_DATA(0x15);

		LCD_WR_REG(0Xe1);
		LCD_WR_DATA(0xf0);
		LCD_WR_DATA(0x01);
		LCD_WR_DATA(0x05);
		LCD_WR_DATA(0x0a);
		LCD_WR_DATA(0x0b);
		LCD_WR_DATA(0x07);
		LCD_WR_DATA(0x32);
		LCD_WR_DATA(0x44);
		LCD_WR_DATA(0x44);
		LCD_WR_DATA(0x0c);
		LCD_WR_DATA(0x18);
		LCD_WR_DATA(0x17);
		LCD_WR_DATA(0x13);
		LCD_WR_DATA(0x16);

		LCD_WR_REG(0Xf0);
		LCD_WR_DATA(0x3c);

		LCD_WR_REG(0Xf0);
		LCD_WR_DATA(0x69);
		delay_ms(1000);//120

		LCD_WR_REG(0X29);
	}
 
	
	LCD_Display_Dir(0);		//Ĭ��Ϊ����     ��ʼ����Ļ����ʾ����
	//LCD_LED=1;				//��������
	LCD_Clear(GREEN);
}  
//��������
//color:Ҫ���������ɫ
void LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 			//�õ��ܵ���
//	printf(" width:%x\r\n",lcddev.width); //��ӡLCD ID 
	printf(" width:%x\r\n",lcddev.width); //��ӡLCD ID 
	printf(" height:%x\r\n",lcddev.height); //��ӡLCD ID 
	printf(" totalpoint:%d\r\n",totalpoint); //��ӡLCD ID 
	if((lcddev.id==0X9486)||(lcddev.id==0X7796))
	{			
		LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA(0>>8);LCD_WR_DATA(0&0XFF); 		
		LCD_WR_DATA(lcddev.width>>8);LCD_WR_DATA(lcddev.width&0XFF); 			 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA(0>>8);LCD_WR_DATA(0&0XFF);
		LCD_WR_DATA(lcddev.height>>8);LCD_WR_DATA(lcddev.height&0XFF);  
	}
	else LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
	LCD_WriteRAM_Prepare();     		//��ʼд��GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		LCD->LCD_RAM=color;	
//		printf(" color:%x\r\n",index); //��ӡLCD ID 
	}
	
}  
//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
//	u16 temp;
	if(lcddev.id==0X9486||lcddev.id==0X7796)
	{
			 for(j=sy;j<ey;j++)
			 {				 
					for(i=sx;i<ex;i++)
				 {					 
							LCD_Fast_DrawPoint(i,j,color);
				 }

			 }
	}
	else
	{
		xlen=ex-sx+1;	 
		for(i=sy;i<=ey;i++)
		{
		 	LCD_SetCursor(sx,i);      				//���ù��λ�� 
			LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	  
			for(j=0;j<xlen;j++)LCD->LCD_RAM=color;	//��ʾ��ɫ 	    
		}
	}	 
}  
//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 			//�õ����Ŀ��
	height=ey-sy+1;			//�߶�
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM
		for(j=0;j<width;j++)LCD->LCD_RAM=color[i*width+j];//д������ 
	}		  
}  
  
//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    
//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);             //5
 		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-a,y0+b);             //1       
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);             //2             
  		LCD_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									  
//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16/24
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���	
 	num=num-' ';//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 	//����1206����
		else if(size==16)temp=asc2_1608[num][t];	//����1608����
		else if(size==24)temp=asc2_2412[num][t];	//����2412����
		else return;								//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=lcddev.height)return;		//��������
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=lcddev.width)return;	//��������
				break;
			}
		}  	 
	}  	    	   	 	  
}   
//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 
//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}





































