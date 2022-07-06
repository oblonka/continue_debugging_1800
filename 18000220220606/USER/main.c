#include "includes.h"	



#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
//#include "sram.h"
#include "malloc.h"
#include "ILI93xx.h"//�޸ĵ���ʾ��





#include "led.h"
#include "beep.h"
#include "timer.h"
//#include "touch.h"
#include "sdio_sdcard.h" //    
#include "GUI.h"
#include "ff.h"
#include "exfuns.h"
#include "w25qxx.h"
#include "includes.h"
#include "ButtonUse.h"
#include "WM.h"
#include "DIALOG.h" 


#include "cst148.h"//20220223  �������������괦��
#include "ctiic.h" //20220223  ��������IICͨ�ŵ�
#include "usart.h" //20220223  usart6�Ĵ�ӡ������Խӿ�     

#include "HTIIC.h"//2022-4-11 15:27:46
#include "HT.h"   //2022-4-11 15:27:46
#include "PRTC.h" //2022-4-11 15:27:49
#include "AIR.h"  //2022-4-11 15:27:52
#include "WIFI.h" //2022-4-12 15:06:47
#include "TCP.h"  //2022-4-12 15:06:50
#include "MQTT.h" //2022-4-12 15:06:54

#include "DMA.h"



#include "KEYa.h"
#include "KEYAA.h"

#include "KEYnum.h"

#include "WIFIcon.h"

#include "KeyPad.h"

const u8 gSystemDate[12] = __DATE__;//ע�⣬�������»���__
const u8 gSystemTime[16] = __TIME__;
	//printf("date:%s \r\n",gSystemDate); 
  //printf("time:%s  \r\n",gSystemTime);

  //printf("date:%s \r\n",__DATE__);
  //printf("time:%s \r\n",__TIME__);





extern u16  CO2_data;


//extern uint16_t    CO2_Measure_data;


extern u16 wifi_ap_flag;

extern U8  Key_Data[26];


extern uchar top_button_flag;       //
extern uchar wificon_to_keypad_flag;//wifi�б��л��������ļ��̵ı�־λ


extern u8 wificon_to_mainui_flag;//wifi���б�Ľ������ת��������

extern u8 wificon_to_up_flag;    //wifi���б�Ľ�����ʾ���䣬���� ���Ϸ�ҳ

extern u8  wificon_to_down_flag;  //wifi���б�Ľ������ʾ���䣬���� ���·�ҳ





/************************************************
 UCOSIII���������ȼ��û�������ʹ��
 ����Щ���ȼ��������UCOSIII��5��ϵͳ�ڲ�����
 ���ȼ�0���жϷ������������� OS_IntQTask()
 ���ȼ�1��ʱ�ӽ������� OS_TickTask()
 ���ȼ�2����ʱ���� OS_TmrTask()
 
 //TOUCH����
 //LED0����
 //EMWINUI����
 //SHT30����
 //CO2����
 //PRTC����
 //WIFI����
 
************************************************/


/******************************************************************************************************************************/
/******************************************************************************************************************************/
/******************************************************************************************************************************/


/*********************************************************��ʼ����*************************************************************/
//�������ȼ�
#define START_TASK_PRIO				3
//�����ջ��С	
#define START_STK_SIZE 				1024
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ	
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);





/*********************************************************��������*************************************************************/
//TOUCH����
//�����������ȼ�
#define TOUCH_TASK_PRIO				4
//�����ջ��С
#define TOUCH_STK_SIZE				1024//128  �޸��˴����Ķ�ջ��Сλ256     20220224 2022-2-24 15:59:39
//������ƿ�
OS_TCB TouchTaskTCB;
//�����ջ
CPU_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//touch����
void touch_task(void *p_arg);





/*********************************************************LED,ADC�����������������ţ�����IO������******************************/
//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO 				4//5
//�����ջ��С
#define LED0_STK_SIZE				256
//������ƿ�
OS_TCB Led0TaskTCB;
//�����ջ
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
//led0����
void led0_task(void *p_arg);



/*********************************************************GUI����*************************************************************/
//EMWINUI����
//�����������ȼ�
#define EMWINUI_TASK_PRIO			4//6
//�����ջ��С
#define EMWINUI_STK_SIZE			2048//2048
//������ƿ�
OS_TCB EmwinuiTaskTCB;
//�����ջ
CPU_STK EMWINUI_TASK_STK[EMWINUI_STK_SIZE];
//emwinui_task����
void emwinui_task(void *p_arg);




/*********************************************************��ʪ������*************************************************************/

//SHT30����
//�����������ȼ�
#define SHT30_TASK_PRIO 				4//5
//�����ջ��С
#define SHT30_STK_SIZE				1024
//������ƿ�
OS_TCB SHT30TaskTCB;
//�����ջ
CPU_STK SHT30_TASK_STK[SHT30_STK_SIZE];
//SHT30����
void SHT30_task(void *p_arg);

/*********************************************************CO2����*************************************************************/

//CO2����
//�����������ȼ�
#define CO2_TASK_PRIO 				4//5
//�����ջ��С
#define CO2_STK_SIZE				1024
//������ƿ�
OS_TCB CO2TaskTCB;
//�����ջ
CPU_STK CO2_TASK_STK[CO2_STK_SIZE];
//SHT30����
void CO2_task(void *p_arg);



/*********************************************************ʵʱʱ������*************************************************************/


//PRTC����
//�����������ȼ�
#define PRTC_TASK_PRIO 				4//5
//�����ջ��С
#define PRTC_STK_SIZE				1024
//������ƿ�
OS_TCB PRTCTaskTCB;
//�����ջ
CPU_STK PRTC_TASK_STK[PRTC_STK_SIZE];
//SHT30����
void PRTC_task(void *p_arg);

/*********************************************************WIFI����*************************************************************/

//WIFI����
//�����������ȼ�
#define WIFI_TASK_PRIO 				4//5
//�����ջ��С
#define WIFI_STK_SIZE				1024
//������ƿ�
OS_TCB WIFITaskTCB;
//�����ջ
CPU_STK WIFI_TASK_STK[WIFI_STK_SIZE];
//SHT30����
void WIFI_task(void *p_arg);

/******************************************************************************************************************************/
/******************************************************************************************************************************/
/******************************************************************************************************************************/


//uchar time_data[6]={0};//��ȡDS1302��ǰʱ�仺�����

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
	uchar init_time[6]={22,7,5,11,12,06};//��ʼ��ʱ�����   �ֶ�����ʱ�������
	
	
	
	delay_init(168);       	  //��ʱ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ�������
	
	
	uart_init(115200);    	  //���Դ���6����������
	uart2_init_wifi(115200);  //WIFI����
	
	uart1_init_CO2(9600);     //CO2���ڲ���������    2022.05   9600
	//USART1_Init(9600);
	
	LCD_Init();			          //��ʼ��LCD
	
	
	
	//W25QXX_Init();			    //��ʼ��W25Q128
	LED_Init();   			      //LED��ʼ��
	BEEP_Init();			        //��ʼ��������
	CO2_VCC_CTR_Init();       //������̼��ƽIO��ʼ��
	
	//FSMC_SRAM_Init(); 		  //SRAM��ʼ��	
	mem_init(SRAMIN); 		    //�ڲ�RAM��ʼ��
	//mem_init(SRAMEX); 		  //�ⲿRAM��ʼ��
	mem_init(SRAMCCM);		    //CCM��ʼ��
	
	
	exfuns_init();			      //Ϊfatfs�ļ�ϵͳ�����ڴ�
	f_mount(fs[0],"0:",1);	  //����SD��
  //f_mount(fs[1],"1:",1);	//����FLASH

  TP_Init();                //���λ�ô�����ʼ�����ŵ����λ�ã�����ִ�У���ʼʱ��Ƭ����ѯ�Ĺ�����
	cstp_dev.init();          //��������ʼ��
	
	
	HTIIC_Init();
  SHT30_Init();             //��ʪ��
	
	
	
	
	
	DS1302_init(init_time);
	DS1302_SetTime(init_time);
	//Time_Init();
	//DS1302_WriteBYTE(0x80,0x00,0);
	
	
	
	//ds1302_gpio_init();delay_ms(5);
	//ds1032_DATAOUT_init();delay_ms(5);
	//ds1032_DATAINPUT_init();delay_ms(5);
	//ds1032_init();delay_ms(5);//ʱ��
	//ds1032_read_realTime();delay_ms(5);	
		
		
		
		
		
	//delay_init();
	//uart3_Init(115200);
	ESP32S_Init(115200);	    //WiFi
		
		
		
	OSInit(&err);			        //��ʼ��UCOSIII
	OS_CRITICAL_ENTER();	    //�����ٽ���
	
	
	
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		      //������ƿ�
				 (CPU_CHAR	* )"start task", 		          //��������
                 (OS_TASK_PTR )start_task, 			  //������
                 (void		* )0,					          //���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					        //�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					          //��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					          //�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				        //��Ÿú�������ʱ�ķ���ֵ
								 
	OS_CRITICAL_EXIT();	                            //�˳��ٽ���	 
	OSStart(&err);                                  //����UCOSIII
								 
	while(1);
								 
}


/******************************************************************************************************************************/
/******************************************************************************************************************************/
/******************************************************************************************************************************/


//��ʼ������
void start_task(void *p_arg)
{
	
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
	
	
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err); //ͳ������                
#endif
	
	
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN	 //���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif

	
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);//����CRCʱ��   emwin�ڲ���Ҫ
	
	WM_SetCreateFlags(WM_CF_MEMDEV);                  //�������д��ڵĴ洢�豸   ����޸�16bitBP�ĺ���  
	GUI_Init();  			                                //STemWin��ʼ��

	
	
	OS_CRITICAL_ENTER();	                            //�����ٽ���  ���񱣻�
	
	
	
/*********************************************************************/	
/*****************Emwin TASK******************************************/
/*********************************************************************/
	OSTaskCreate((OS_TCB*     )&EmwinuiTaskTCB,		
				 (CPU_CHAR*   )"Emwinui task", 		
                 (OS_TASK_PTR )emwinui_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )EMWINUI_TASK_PRIO,     
                 (CPU_STK*    )&EMWINUI_TASK_STK[0],	
                 (CPU_STK_SIZE)EMWINUI_STK_SIZE/10,	
                 (CPU_STK_SIZE)EMWINUI_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
								 
					
								 
/*********************************************************************/								 
/*****************Touch TASK******************************************/
/*********************************************************************/								 
	OSTaskCreate((OS_TCB*     )&TouchTaskTCB,		
				 (CPU_CHAR*   )"Touch task", 		
                 (OS_TASK_PTR )touch_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )TOUCH_TASK_PRIO,     
                 (CPU_STK*    )&TOUCH_TASK_STK[0],	
                 (CPU_STK_SIZE)TOUCH_STK_SIZE/10,	
                 (CPU_STK_SIZE)TOUCH_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);		

				
								 
/********************************************************************/								 
/*****************LED TASK*******************************************/
/********************************************************************/								 
	OSTaskCreate((OS_TCB*     )&Led0TaskTCB,		
				 (CPU_CHAR*   )"Led0 task", 		
                 (OS_TASK_PTR )led0_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )LED0_TASK_PRIO,     
                 (CPU_STK*    )&LED0_TASK_STK[0],	
                 (CPU_STK_SIZE)LED0_STK_SIZE/10,	
                 (CPU_STK_SIZE)LED0_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);		

								 
								 
/*******************************************************************/								 
/*****************SHT30 TASK****************************************/
/*******************************************************************/								 
	OSTaskCreate((OS_TCB*     )&SHT30TaskTCB,		
				 (CPU_CHAR*   )"SHT30 task", 		
                 (OS_TASK_PTR )SHT30_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )SHT30_TASK_PRIO,     
                 (CPU_STK*    )&SHT30_TASK_STK[0],	
                 (CPU_STK_SIZE)SHT30_STK_SIZE/10,	
                 (CPU_STK_SIZE)SHT30_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);									 
								 
			
								 
/*******************************************************************/								 
/*****************PRTC TASK*****************************************/
/*******************************************************************/								 
	OSTaskCreate((OS_TCB*     )&PRTCTaskTCB,		
				 (CPU_CHAR*   )"PRTC task", 		
                 (OS_TASK_PTR )PRTC_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )PRTC_TASK_PRIO,     
                 (CPU_STK*    )&PRTC_TASK_STK[0],	
                 (CPU_STK_SIZE)PRTC_STK_SIZE/10,	
                 (CPU_STK_SIZE)PRTC_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);					 
								 
				
								 
/*******************************************************************/				
/*****************CO2 TASK******************************************/
/*******************************************************************/								 
	OSTaskCreate((OS_TCB*     )&CO2TaskTCB,		
				 (CPU_CHAR*   )"CO2 task", 		
                 (OS_TASK_PTR )CO2_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )CO2_TASK_PRIO,     
                 (CPU_STK*    )&CO2_TASK_STK[0],	
                 (CPU_STK_SIZE)CO2_STK_SIZE/10,	
                 (CPU_STK_SIZE)CO2_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);	
								 
		
								 
/*******************************************************************/								 
/*****************WIFI TASK*****************************************/
/*******************************************************************/								 
	OSTaskCreate((OS_TCB*     )&WIFITaskTCB,		
				 (CPU_CHAR*   )"WIFI task", 		
                 (OS_TASK_PTR )WIFI_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )WIFI_TASK_PRIO,     
                 (CPU_STK*    )&WIFI_TASK_STK[0],	
                 (CPU_STK_SIZE)WIFI_STK_SIZE/10,	
                 (CPU_STK_SIZE)WIFI_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);	
								 							 
								 
								 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//����ʼ����			 
	OS_CRITICAL_EXIT();	                            //�˳��ٽ���  ����						 
}





/************************************************************************************************************************/
/************************************************************************************************************************/
/*********************************************************|| ����ֽ� ||*************************************************/
/************************************************************************************************************************/
/************************************************************************************************************************/


/*
1.GUI TASK
2.TOUCH TASK
3.LED TASK
4.SHT30 TASK
5.PREC TASK
6.CO2 TASK
7.WIFI TASK


*/



/************************************************************************************************************************/
/********************************************************| EMWINDEMO���� |***********************************************/
/************************************************************************************************************************/
void emwinui_task(void *p_arg)
{
	
	
	
	OS_ERR err;
	
	//GUI_CURSOR_Show(); 
	
	//����Ƥ��
	/*
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX); 
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	MENU_SetDefaultSkin(MENU_SKIN_FLEX);
	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	SPINBOX_SetDefaultSkin(SPINBOX_SKIN_FLEX); 
	*/
	
	
	while(1)
	{
		
		//�����ĵ��Ը���������̡߳�
		
		
		//printf("\r\n GUI-test \r\n");	
		
		
		//�����ﵥ������ø�����Ҫ�л���ʾ�Ľ��� 
		//��������ʾ��� ����     
		
		
		
		
		
//ESP32S_JoinAP_connect_list_parse("AT+CWLAP",500);
		
		
		
/*
������  wifi_ssid���б���ʾ����   ���������Сд����   ��д����  ���ֽ��� 
emwin������һ����ⴥ����Ƶ�ʣ����Ƕ�ü��һ���Ƿ��д���ʱ�䣬��ԭ�����������Ƶ���Ǻܵͺܵ͵ģ������ĸ��˾ͺ���
		
�����������б���ʾSSID ��Ӧһ���ַ����Ľӿ�  char*  ���뵽User_ESP32S_SSID  ����AP�ĺ���   ESP32S_JoinAP(User_ESP32S_SSID, User_ESP32S_PWD); 
�����ȥ�� password  	 ��Ӧһ���ַ����Ľӿ�  char*  ���뵽User_ESP32S_PWD   ����AP�ĺ���   ESP32S_JoinAP(User_ESP32S_SSID, User_ESP32S_PWD); 
		
		
ESP32S_JoinAP(User_ESP32S_SSID, User_ESP32S_PWD); �ǵ����ĺ��� 	  MQTT  TCP ��ͬƽ̨ƽ̨�Խӵı�Ҫ�����Ӳ���	
		
		
	
ssid      �Ľ�����		���ڵĽ�����ɵĴ��ڵ�����        ESP32S_Fram_Record_Struct.Data_RX_BUF                                   
password  �Ľ�����    emwin     edit������ַ���        Edit_buff                 		
		
*/		







/*

������Ǹ�������Ĳ��Խ���

�������ĺ���ֻ��ʾ�����棬�����������������Ľ��档


*/



	  ButtonUse_Demo();  //������
		
	 //	if(top_button_flag==1)
	 //	{
	 //	
	 //	MainTask_WIFIcon();
	 //	
	 //	}
		
		//wifi�б��10����������������̽��棬��ȡwifi����Ȼ�������̵��������
		if(wificon_to_keypad_flag==1)
			{
			 MainTask_allin();//��ȡ��ssid����ָ����������wifi �ĺ����ӿ���   ssid[]   
			}
		
			
			if(wificon_to_mainui_flag==1)//wifi���б�Ľ������ת��������
				{
				ButtonUse_Demo();
				}
			
				
		/*
		if(wificon_to_up_flag==1) //wifi���б�Ľ�����ʾ���䣬���� ���Ϸ�ҳ
				{
				}
			
		if(wificon_to_down_flag==1)//wifi���б�Ľ������ʾ���䣬���� ���·�ҳ
				{
				}
		*/	
			
				
		
		
		
		
    //KEY_a();  //Сд�ļ��̵Ľ��棬��edit������Ĵ���
		//KEY_num();//���ֺ������ַ��Ľ��棬��edit������Ĵ���
		//KEYAA();    //��д�ļ��̵Ľ��棬��edit������Ĵ���
		//KEY_WIFIcon();//��ʾwifi�б�Ľ��棬��edit������Ĵ���
		
		
		
		
		
		
		//MainTask_WIFIcon();
		//MainTask_a();
		//MainTask_AA();
		//MainTask_num();
		
		//CreateWindow123();
		//MainTask_allin();
		
		//printf("\r\n Emwin_UI_test \r\n");
		//delay_ms(1000);
		
		
		
		
		
		//printf("date:%s \r\n",gSystemDate); 
    //printf("time:%s  \r\n",gSystemTime);
		
		
		
	  //GUI_SetColor(GUI_RED);
    //GUI_SetBkColor(GUI_BLUE);
    //GUI_SetFont(&GUI_Font24_ASCII);
    //GUI_Clear();
    //GUI_DispStringAt("Hello World",10,10); 	
		
		
		OSTimeDlyHMSM(0,0,0,1500,OS_OPT_TIME_PERIODIC,&err);//��ʱ5ms
		
	}
}





/************************************************************************************************************************/
/********************************************************| TOUCH���� |***************************************************/
/************************************************************************************************************************/
void touch_task(void *p_arg)
{
	/*
	u8 cst_num;
	
	u8 cst_1;
	u8 cst_2;
	u8 cst_3;
	u8 cst_4;
	u8 cst_5;
	
	u8 yy[2];
	u8 XX[2];
	
	u8 tt;
	u8 RR;
	u8 WW;
	u8 AA;
	u8 II;
	
	u8 hh;
	u8 jj;
	u8 ll;
	u8 zz;
	u8 nn;
	
	u8 cc;
	u8 ee;
	
	u8 kk = 0X00;
	u8 i;
	u8 SS;
	u8 vv[2]={0XD1,0X01};
	*/
	
	OS_ERR err;
	
	while(1)
	{
	/*	
	//��д����  ��Ȼ����0XD101,�ٶ��������Ĵ���0XD204	����ȡ��ֵ
	CST_IIC_Init();
  delay_ms(60);
	//����������������꣬��⵽����״̬�������� 
		
	CST148_WR_Reg(MODE_INFO,yy,1);	
		
	CST148_RD_Reg(BOOTLOADER,&AA,1);      //0XD1FE 
	printf(" \r\n 0XD1FE:%#X\r\n",AA);			
		
	CST148_RD_Reg(BOOTLOADER_TG,&II,1);   //0XD1FF 
	printf(" 0XD1FF:%#X\r\n",II);	
		
		
	CST148_RD_Reg(STYLE_ID,&RR,1);        //0XD204  0XA0        
	printf(" \r\n 0XD204:%#X\r\n",RR);
		            
  CST148_RD_Reg(STYLE_ID_jj,&cc,1);     //0XD205  0X31        
	printf(" 0XD205:%#X\r\n",cc);
		
	CST148_RD_Reg(STYLE_ID_IC,&tt,1);     //0XD206  0X94           
	printf(" 0XD206:%#X\r\n",tt);		
	
	CST148_RD_Reg(STYLE_ID_hh,&ee,1);     //0XD207  0
	printf(" 0XD207:%#X\r\n",ee);	
	
	CST148_RD_Reg(STYLE_ID_FF,&WW,1);     //0XD208  0X1
	printf(" 0XD208:%#X\r\n",WW);	
	
		
	CST148_RD_Reg(Guding,&kk,1);          //�������̶��Ĵ�����ȡ
	printf(" \r\n Guding:%#X\r\n",kk);	
	CST148_RD_Reg(Num,&SS,1);             //���������Դ�����ĸ���     5������
	
	printf(" Num:%#X\r\n",((SS>>8)&0x00FF));
	
	printf(" Num:%#X\r\n",SS);
	printf(" Num:%d\r\n",SS);
	
  if(SS>3)
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_14);
			delay_ms(15);
			GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		}
  
  CST148_RD_Reg(CST_TP1_REG,&hh,1);     //���������Դ�����ĸ���     5������
	printf(" TP1:%#X\r\n",hh);		        //CST_TP1_REG
	
	
	CST148_RD_Reg(CST_TP2_REG,&jj,1);     //���������Դ�����ĸ���     5������
	printf(" TP2:%#X\r\n",jj);		        //CST_TP2_REG
		
	CST148_RD_Reg(CST_TP3_REG,&ll,1);     //���������Դ�����ĸ���     5������
	printf(" TP3:%#X\r\n",ll);		        //CST_TP3_REG

	CST148_RD_Reg(CST_TP4_REG,&zz,1);     //���������Դ�����ĸ���     5������
	printf(" TP4:%#X\r\n",zz);		        //CST_TP4_REG
	
	CST148_RD_Reg(CST_TP5_REG,&nn,1);     //���������Դ�����ĸ���     5������
	printf(" TP5:%#X\r\n",nn);		        //CST_TP5_REG

	cst_num=cstp_dev.scan(); //������ɨ��  
	printf("cstp_dev.scan---num:%d\r\n",cst_num);		     //CST_TP5_REG	
		
	if(cst_num > 0)
		{
		MulTouch_Send(cstp_dev.x,\
			            cstp_dev.y,\
			            cstp_dev.tp_sta,\
			            cstp_dev.tp_id,\
			            cst_num);
			
		//printf("cstp_dev.x:%d\r\n",cstp_dev.x);	
		//printf("cstp_dev.y:%d\r\n",cstp_dev.y);	
		//printf("cstp_dev.tp_sta:%d\r\n",cstp_dev.tp_sta);	
		//printf("cstp_dev.tp_id:%d\r\n",cstp_dev.tp_id);	
		//printf("cst_num:%d\r\n\r\n\r\n\r\n",cst_num);		
			
		}
		delay_ms(10);	
	
	//ctp_test();	
	
  //lcd_draw_bline(130, 75, 124, 190,5,RED);//����
	
	delay_ms(3000);	
		*/
		
		//ctp_test();
		
		//printf("\r\n TOUCH-test \r\n");	
		
		GUI_TOUCH_Exec();	
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_PERIODIC,&err);//10�������ɾ��ok   ��ʱ5ms    1500    ��Ϊ10����Сɨ������
		
		//BEEP=~BEEP;
	}
}





/************************************************************************************************************************/
/********************************************************| LED0���� |****************************************************/
/************************************************************************************************************************/
void led0_task(void *p_arg)
{
	OS_ERR err;
	
	
	while(1)
	{
		LED1 = !LED1;
		LED3 = !LED3;

		
		//printf("\r\n LED-test \r\n");	
		
		
		OSTimeDlyHMSM(0,0,0,1500,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms
	}
}





/************************************************************************************************************************/
/********************************************************| SHT30���� |***************************************************/
/************************************************************************************************************************/
void SHT30_task(void *p_arg)
{
	
	OS_ERR err;
	
  extern float SHT30_temperature;
  extern float SHT30_humidity;
	
	while(1)
	{
		
		sht30_data_process();
		/*
		delay_ms(1000);
		
		printf("\r\n qian:ceshi \r\n");
		delay_ms(1000);
		sht30_data_process();
		delay_ms(1000);
		printf("\r\n hou:ceshi \r\n");	
		
		//=2022-4-13 13:13:45
	  printf("temperature:%6.1f 'C\r\n humidity:%6.1f \r\n",SHT30_temperature/10,SHT30_humidity/10);
		
	*/
		
		
		
		OSTimeDlyHMSM(0,0,0,1500,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms
	}
}





/************************************************************************************************************************/
/*******************************************************| PRTC���� |*****************************************************/
/************************************************************************************************************************/
void PRTC_task(void *p_arg)
{
	OS_ERR err;
	while(1)
	{
		
		//printf("\r\n  PRTC-test \r\n");	
		
    //DS1302_WriteBYTE(0x80,0x00,0);
		//DS1302Z_WriteQ();
		//DS1302Z_Read();
	
		
		
		//ds1032_init();
		//ds1302_wirte_rig(0x80,0x00);
		//ds1032_read_realTime();
		
		
		
		
		
		DS1302_Readtime();
		
		
		
		
		delay_ms(1000);
		
		OSTimeDlyHMSM(0,0,0,1500,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms
	}
}





/************************************************************************************************************************/
/*******************************************************| CO2���� |******************************************************/
/************************************************************************************************************************/
void CO2_task(void *p_arg)
{
	OS_ERR err;
	
	extern int  CO2_ppm;
	
	
	
	
  //extern float SHT30_humidity;
	
	while(1)
	{
		//���Դ���1  CO2
		//USART_SendData(USART1, 1111);                         //�򴮿�1��������
	  //while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		
		//printf("\r\n CO2_data_test_start \r\n");	
		//delay_ms(1000);
		//CO2_Send_Data(); 
		//Read_CO2_ppm();//��ȡʵʱ�Ķ�����̼������
		//printf("ʵ�ʲ��Ե�Ũ��_CO2_ppm :%d\r\n",CO2_ppm);//����6�ĵ��Դ�ӡ������ݲ���
		//delay_ms(1000);
	
		
		//CO2_Send_Data(); 
		
		printf("\r\n CO2_data_test_start \r\n");	
		
		//CO2_Send_Data();
		delay_ms(3000);
		Read_CO2_ppm();
		printf("\r\n CO2=  %d ppm \r\n",CO2_Measure_data);
		delay_ms(1000);	
		
		//CO2_Tx();
		//printf("CO2=  %d ppm \r\n",CO2_data);
		//delay_ms(1000);	
		
		
		printf("\r\n CO2_data_test_end \r\n");	
		
		//printf("date:%s \r\n",__DATE__);
    //printf("time:%s \r\n",__TIME__);
		
		
		OSTimeDlyHMSM(0,0,0,1000,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms
	}
}





/************************************************************************************************************************/
/*******************************************************| WIFI���� |*****************************************************/
/************************************************************************************************************************/
void WIFI_task(void *p_arg)
{
	OS_ERR err;
	
	u8 t;
	u8 len;	
	
	while(1)
	{
		
		
		
//���Դ���2   WiFi
//			if(USART2_RX_STA_WIFI&0x8000)
//		{					   
//			len=USART2_RX_STA_WIFI&0x3fff;//�õ��˴ν��յ������ݳ���
//			for(t=0;t<len;t++)
//			{
//				USART_SendData(USART2, USART2_RX_BUF[t]);             //�򴮿�1��������
		
		
		    //USART_SendData(USART2, 2222);                         //�򴮿�2��������
				//while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//			}
//			USART2_RX_STA_WIFI=0;
		
			
		//ESP32S_AT_Test();
			
		//printf("\r\n WIFI-test-start \r\n");	
		//delay_ms(1000);
		
		
		
		
		
		//�����ǲ��Խ���WIFI�б�ĺ�������������SSID��ӡ�����������ʾ��
		delay_ms(2000);
		ESP32S_JoinAP_connect_list_parse("AT+CWLAP",500);//����SSID������ĺ���,�����������ݽ�����
	  delay_ms(2000);
		//����WIFI�б�ĺ���
		
		
		
		//����wifi �Զ���ȡʱ�亯����  ����������ʱ��ĸ�ʽ��
		  /*
			 [16:01:55.398]�ա���AT+CIPSNTPTIME?
				+CIPSNTPTIME:Sat May 28 16:01:58 2022
				OK
			 */
		
		
		
		
		
		
		
		
		//U8  Key_Data[26] = { 0 };
		
		//ssid�ǻ�ȡ��ɨ����ַ���   password��������ַ�����ȡ
	
/*
if(wifi_ap_flag ==1)
			{
			ESP32S_STA_MQTTClient_Test_SA_test(User_ESP32S_SSID, Key_Data);
			}
		
*/	

		
		
		
		
	
/*
ͨ������������SSID��Ӧ�ӿ��ַ���      char*   
1.��ʾ������SSID�б�
2.button�����⴦��
3.ssid �� password�ĽӿڵĶԽ�        ֱ�ӶԽӵ�MQTT�Ľӿ����          
*/
		
		
		
		//�����������Ĳ���MQTT�Ĵ��룬����+++�˳�͸����ָ��2022.06.10����
		//delay_ms(1000);
		//ESP32S_STA_TCPClient_Test();//����TCPͨѶ
		//ESP32S_STA_MQTTClient_Test_SA();//����MQTTͨѶ    ����OK
		//delay_ms(1000);
		
		//����MQTT�Ĵ���
		
		OSTimeDlyHMSM(0,0,10,5000,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms
	}
}


/*
log:

*/

