#ifndef __CST148_H
#define __CST148_H

#include <stdint.h>
#include <string.h>
#include "delay.h"
#include "stdlib.h"
#include "math.h"
#include "stdio.h"
#include "ctiic.h"
//#include "lcd.h"
#include "ILI93XX.h"

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t   u8;

//I2C��д����	
#define CST148_CMD_WR 		0X34   //д����
#define CST148_CMD_RD 		0X35	 //������

//����ģʽ�ļĴ���	
#define MODE_INFO 	    0XD101   //

//����ģʽ�Ĵ����Ĳ�ѯ�Ĵ���
#define STYLE_ID 	      0XD204   //
#define STYLE_ID_jj 	  0XD205   //
#define STYLE_ID_IC 	  0XD206   //
#define STYLE_ID_hh 	  0XD207   //
#define STYLE_ID_FF     0XD208   //

//boot �Ĵ���
#define BOOTLOADER 	    0XD1FE   //
#define BOOTLOADER_TG   0XD1FF   //


//�Ĵ�����ַ
#define CST_GSTID_REG 	0X0000   //��ǰ��⵽�Ĵ������     ������



//���������ļĴ������ж�
#define CST_TP1_REG 	  0XD000  	//��һ�����������ݵ�ַ     ������ǵ�ָ�ģ���ǰ��⵽�Ĵ����������ֻ��Ҫ��ָ�Ĳ����ļĴ�����
#define CST_TP2_REG 	  0XD007		//�ڶ������������ݵ�ַ
#define CST_TP3_REG 	  0XD00C		//���������������ݵ�ַ
#define CST_TP4_REG 	  0XD011		//���ĸ����������ݵ�ַ
#define CST_TP5_REG 	  0XD016		//��������������ݵ�ַ  


//�ֱ������üĴ�����ַ
#define CST_SET_REG   	0XD1F8   	//�ֱ������üĴ�����ַ


//���Թ̶�����Ĵ���
#define Num             0XD005
#define Guding          0XD006    //�̶�ֵ�������




#define CSTP_PRES_DOWN  0x80   //����������	  
#define CSTP_CATH_PRES  0x40   //�а��������� 




#define CST_MAX_TOUCH    5     //10    ������֧�ֵĵ���,�̶�Ϊ5��
#define MAX_TOUCH_POINT 0x0a   //���Ĵ���������10�����̼�����5����������



 //__IO uint8_t cst_PrevXfer_Complete=1;//
 
 
 
//������������
typedef struct
{
	         void (*init)(void);//��ʼ��������������
	           u8 (*scan)(void);//ɨ�败����.0,��Ļɨ��;1,��������;	  u8 mode
	           //u8 (*scan)(u8 mode);
	
	       u16 x[CST_MAX_TOUCH];//��ǰ����
	       u16 y[CST_MAX_TOUCH];//�����������5������,����������x[0],y[0]����:�˴�ɨ��ʱ,����������,��
								              //x[4],y[4]�洢��һ�ΰ���ʱ������. 
	
	    u8 tp_id[CST_MAX_TOUCH];//������ָid�����ֶ���ָ          
	   u8 tp_sta[CST_MAX_TOUCH];//����״̬
	                    u8  sta;//�ʵ�״̬     0000 0000
								              //b7:����1/�ɿ�0; 
	                            //b6:0,û�а�������;1,�а�������. 
								              //b5:����
								              //b4~b0:���ݴ��������µĵ���(0,��ʾδ����,1��ʾ����)
	
	
                 u8 touchtype;//���ص����ͣ�����
	
  u16   last_x[CST_MAX_TOUCH];
  u16   last_y[CST_MAX_TOUCH];
  u8   last_id[CST_MAX_TOUCH];
  u8  last_sta[CST_MAX_TOUCH];
	
}_cst_tp_dev;



extern _cst_tp_dev cstp_dev;	//������������touch.c���涨��



void Load_Drow_Dialog(void);
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color);
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color);
u16 my_abs(u16 x1,u16 x2);
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color);
void ctp_test(void);



static int  cst3xx_i2c_read( unsigned char *buf, int len);
static int  cst3xx_i2c_write( unsigned char *buf, int len);
static int  cst3xx_i2c_read_register( unsigned char *buf, int len);
static void cst3xx_reset_ic(unsigned int ms);




u8 TP_Init(void);
u8 HYN_CST148_Scan(void);
void MulTouch_Send(u16 *x,u16 *y,u8 *s,u8 *id,u8 n);




u8 HYN_CST148_Scan_Scan(u8 mode);



#endif

