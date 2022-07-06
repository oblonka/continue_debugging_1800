#ifndef __WIFI_H
#define __WIFI_H 			   

#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#include "DIALOG.h"
#include "WM.h"

#define ID_WINDOW_0        (GUI_ID_USER + 0x0B)
#define ID_BUTTON_0        (GUI_ID_USER + 0x0C)
#define ID_BUTTON_1        (GUI_ID_USER + 0x0D)
#define ID_BUTTON_2        (GUI_ID_USER + 0x0E)
#define ID_BUTTON_3        (GUI_ID_USER + 0x0F)
#define ID_BUTTON_4        (GUI_ID_USER + 0x10)
#define ID_BUTTON_5        (GUI_ID_USER + 0x11)
#define ID_BUTTON_6        (GUI_ID_USER + 0x12)
#define ID_BUTTON_7        (GUI_ID_USER + 0x13)
#define ID_BUTTON_8        (GUI_ID_USER + 0x14)
#define ID_BUTTON_9        (GUI_ID_USER + 0x15)
#define ID_BUTTON_10        (GUI_ID_USER + 0x16)
#define ID_BUTTON_11        (GUI_ID_USER + 0x17)
#define ID_BUTTON_12        (GUI_ID_USER + 0x18)
#define ID_IMAGE_0        (GUI_ID_USER + 0x19)




typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8; 


#if defined ( __CC_ARM   )
#pragma anon_unions
#endif
extern WM_HWIN WIFI_hWin;

//ESP32Sģʽѡ��
typedef enum
			{
					STA,
					AP,
					STA_AP  
			}ENUM_Net_ModeTypeDef;





//���紫���Э�飬ö������
typedef enum
			{
				 enumTCP,
				 enumUDP,
			} ENUM_NetPro_TypeDef;
			
			
			
//���Ӻţ�ָ��Ϊ�����Ӻſ��Է�ֹ�������������ͬһ�˿ڶ���������
typedef enum
			{
				Multiple_ID_0 = 0,
				Multiple_ID_1 = 1,
				Multiple_ID_2 = 2,
				Multiple_ID_3 = 3,
				Multiple_ID_4 = 4,
				Single_ID_0   = 5,
		} ENUM_ID_NO_TypeDef;




//��Щ�ӿڵ�ʱ��

//#define ESP32S_RST_Pin                       GPIO_Pin_4               //��λ�ܽ�
//#define ESP32S_RST_Pin_Port                  GPIOA                    //��λ 
//#define ESP32S_RST_Pin_Periph_Clock          RCC_AHB1Periph_GPIOB     //��λʱ��  RCC_APB2Periph_GPIOA

//#define ESP32S_CH_PD_Pin                     GPIO_Pin_5               //ʹ�ܹܽ�
//#define ESP32S_CH_PD_Pin_Port                GPIOA                    //ʹ�ܶ˿�
//#define ESP32S_CH_PD_Pin_Periph_Clock        RCC_AHB1Periph_GPIOB     //ʹ��ʱ��   RCC_APB2Periph_GPIOA





#define ESP32S_RST_Pin_SetH       GPIO_SetBits(ESP32S_RST_Pin_Port,ESP32S_RST_Pin)
#define ESP32S_RST_Pin_SetL       GPIO_ResetBits(ESP32S_RST_Pin_Port,ESP32S_RST_Pin)


#define ESP32S_CH_PD_Pin_SetH     GPIO_SetBits(ESP32S_CH_PD_Pin_Port,ESP32S_CH_PD_Pin)
#define ESP32S_CH_PD_Pin_SetL     GPIO_ResetBits(ESP32S_CH_PD_Pin_Port,ESP32S_CH_PD_Pin)





#define ESP32S_USART(fmt, ...)    USART_printf (USART2, fmt, ##__VA_ARGS__)    
#define PC_USART(fmt, ...)         printf(fmt, ##__VA_ARGS__)       //���Ǵ��ڴ�ӡ����������2��ִ��printf����Զ�ִ��fput�������ض�����printf��



#define RX_BUF_MAX_LEN   8192      //4096  ssid�б���������������ַ������ܴ�    ����ֽ���  1024  



//ʹ�õ�����֡�ṹ���   �ṹ�庯��     �ṹ��Ƕ�׹����壬Ƕ�׽ṹ��
//������ռ�õ��ڴ������ĳ�Առ�õ��ڴ档������ʹ�����ڴ渲�Ǽ�����ͬһʱ��ֻ�ܱ���һ����Ա��ֵ��������µĳ�Ա��ֵ���ͻ��ԭ����Ա��ֵ���ǵ���
extern struct STRUCT_USART_Fram   //����֡�ṹ��
						{
								char Data_RX_BUF[RX_BUF_MAX_LEN];//�������ݵ�buffer��������    ����
							
							
								union 
								{
										__IO u16 InfAll;
										struct 
										{
												__IO u16 FramLength       :15;                               // 14:0 
												__IO u16 FramFinishFlag   :1;                                // 15 
										}InfBit;
								}; 
								
								
							
						}ESP32S_Fram_Record_Struct;





//��ʼ����TCP���ܺ���
void ESP32S_Init(u32 bound);
void ESP32S_AT_Test(void);
bool ESP32S_Send_AT_Cmd(char *cmd,char *ack1,char *ack2,u32 time);
void ESP32S_Rst(void);
bool ESP32S_Net_Mode_Choose(ENUM_Net_ModeTypeDef enumMode);
						
bool ESP32S_JoinAP( char * pSSID, char * pPassWord );
						
						
						
//���ص�ack�����ǲ��������ݣ�ֱ��ͨ�����ͽ�������	  2022.05					
bool ESP32S_JoinAP_connect_list_parse( char *cmd,u32 time);//ap �����б�	
//bool ESP32S_JoinAP_connect_list_parse();					
bool ESP32S_GET_RealTime_parse( char *cmd,u32 time);//��ȡSNTP������ʱʵʱ						
						
						
						
						
bool ESP32S_Enable_MultipleId ( FunctionalState enumEnUnvarnishTx );
bool ESP32S_Link_Server(ENUM_NetPro_TypeDef enumE, char * ip, char * ComNum, ENUM_ID_NO_TypeDef id);
bool ESP32S_SendString(FunctionalState enumEnUnvarnishTx, char * pStr, u32 ulStrLength, ENUM_ID_NO_TypeDef ucId );
bool ESP32S_UnvarnishSend ( void );
void ESP32S_ExitUnvarnishSend ( void );
u8 ESP32S_Get_LinkStatus ( void );
void USART_printf( USART_TypeDef * USARTx, char * Data, ... );




//MQTT���ܺ���
bool ESP32S_MQTTUSERCFG(char * pClient_Id, char * pUserName,char * PassWord);

bool ESP32S_MQTTCONN(char * Ip, int Num_MQTTCONN);//NUM����ı������ظ�����ĵط���USMART    ,�޸�ΪNum_MQTTCONN

bool ESP32S_MQTTSUB(char * Topic);

bool ESP32S_MQTTPUB(char * Topic,char *temp);

bool ESP32S_MQTTCLEAN(void);

bool MQTT_SendString(char * pTopic,char *temp2);




#endif



/*
���ڽ���������SSID��ɨ��������пհ׵�ssid������������ص����ƣ�ȥ��
OK
AT+CWLAP
+CWLAP:(3,"",-47,"18:3c:b7:df:49:99",6,-1,-1,4,4,7,1)
+CWLAP:(3,"",-47,"18:3c:b7:df:49:95",6,-1,-1,4,4,7,1)
+CWLAP:(4,"shian",-48,"18:3c:b7:df:49:94",6,-1,-1,4,4,7,1)
+CWLAP:(4,"shian_Wi-Fi5",-48,"18:3c:b7:ff:49:99",6,-1,-1,4,4,7,1)
+CWLAP:(4,"bjzjhyjz622",-48,"00:94:ec:40:4f:cc",11,-1,-1,4,4,7,1)
+CWLAP:(3,"",-48,"00:94:ec:40:4f:cd",11,-1,-1,4,4,7,1)
+CWLAP:(3,"",-48,"00:94:ec:40:4f:d1",11,-1,-1,4,4,7,1)
+CWLAP:(3,"CU_5TMN",-51,"72:d8:3d:66:66:38",3,-1,-1,4,4,7,1)
+CWLAP:(4,"656",-52,"30:fc:68:eb:e6:03",6,-1,-1,4,4,7,0)
+CWLAP:(4,"XCYL",-59,"9c:a6:15:fa:3d:a3",1,-1,-1,4,4,7,0)
+CWLAP:(4,"GBSN",-64,"7c:b5:9b:59:e1:11",7,-1,-1,5,3,7,0)
+CWLAP:(4,"CNCEC",-65,"14:51:7e:67:65:be",11,-1,-1,4,4,7,0)
+CWLAP:(0,"",-65,"14:51:7e:67:65:c0",11,-1,-1,0,0,7,0)
+CWLAP:(0,"",-69,"14:51:7e:67:55:1c",11,-1,-1,0,0,7,0)
+CWLAP:(4,"bmkbmkbmk",-70,"54:a7:03:54:d2:8e",1,-1,-1,4,4,7,0)
+CWLAP:(4,"CNCEC",-70,"14:51:7e:67:55:1a",11,-1,-1,4,4,7,0)
+CWLAP:(3,"DIRECT-82-HP Laser 178nw",-74,"06:0e:3c:81:2c:82",1,-1,-1,4,4,6,0)
+CWLAP:(4,"",-74,"46:59:43:3c:45:78",4,-1,-1,4,4,7,0)
+CWLAP:(4,"kzl528",-75,"0c:4b:54:4a:76:62",1,-1,-1,4,4,7,0)
+CWLAP:(4,"CU-4578",-75,"44:59:43:7c:45:78",4,-1,-1,4,4,7,1)
+CWLAP:(3,"CU_LVbG",-75,"9c:69:65:1f:ca:bc",13,-1,-1,4,4,7,0)
+CWLAP:(3,"1",-76,"78:85:f4:7f:56:2c",1,-1,-1,4,4,7,1)
+CWLAP:(4,"KZL",-76,"cc:08:fb:d8:a1:26",1,-1,-1,4,4,7,0)
+CWLAP:(4,"CU_uyz4",-76,"54:46:17:03:05:c8",8,-1,-1,4,4,7,0)
+CWLAP:(3,"CU_T322",-77,"72:60:8c:03:44:a4",1,-1,-1,4,4,7,1)
+CWLAP:(4,"ahead",-81,"d8:3d:cc:03:2b:35",1,-1,-1,5,3,7,1)
+CWLAP:(3,"CU_76a4",-87,"38:3e:5b:28:c4:88",13,-1,-1,4,4,7,0)
+CWLAP:(4,"6209",-88,"d8:3d:cc:03:80:05",11,-1,-1,5,3,7,1)
+CWLAP:(4,"zh",-88,"78:53:0d:c9:81:dd",11,-1,-1,5,3,7,1)
+CWLAP:(3,"",-90,"78:2c:29:07:fc:70",6,-1,-1,4,4,7,0)
+CWLAP:(3,"",-91,"78:2c:29:07:fb:90",6,-1,-1,4,4,7,0)
+CWLAP:(4,"CU_rNDR",-91,"e0:38:3f:52:ab:31",9,-1,-1,4,4,7,0)
+CWLAP:(3,"",-92,"8c:5a:c1:99:84:b9",6,-1,-1,4,4,7,1)
+CWLAP:(3,"",-92,"78:2c:29:07:fa:30",11,-1,-1,4,4,7,0)
+CWLAP:(4,"TP-LINK_B849",-93,"60:3a:7c:51:b8:49",6,-1,-1,4,4,7,0)
+CWLAP:(3,"CU_t9jE",-93,"58:d0:61:2d:0e:34",9,-1,-1,4,4,7,1)
+CWLAP:(3,"",-94,"78:2c:29:07:fc:d0",6,-1,-1,4,4,7,0)
+CWLAP:(4,"XKJH",-94,"ec:6c:9f:b4:ff:06",11,-1,-1,5,3,7,0)
+CWLAP:(3,"",-94,"6c:b7:49:2c:fa:fd",11,-1,-1,4,4,7,0)
+CWLAP:(3,"zhang",-95,"6c:b7:49:2c:fa:fc",11,-1,-1,4,4,7,1)
+CWLAP:(3,"",-96,"78:2c:29:07:fc:10",11,-1,-1,4,4,7,0)

OK

 ecn = 151587081
 ssid =o?
 rssi =3
 mac =
 channel = 9
==========================
 ecn = 151587081
 ssid =o?
 rssi =3
 mac =
 channel = 9
==========================
 ecn = 151587081
 ssid =o?
 rssi =3
 mac =
 channel = 9
==========================
 ecn = 151587081
 ssid =o?
 rssi =3
 mac =
 channel = 9
==========================
 ecn = 151587081
 ssid =o?
 rssi =3
 mac =
 channel = 9
==========================
 ecn = 151587081
 ssid =o?
 rssi =3
 mac =
 channel = 9
==========================
 ecn = 3
 ssid =o?
 rssi =3
 mac =
 channel = 9
==========================
 ecn = 3
 ssid =o?
 rssi =3
 mac =
 channel = 9
==========================
 ecn = 4
 ssid =shian
 rssi =-48
 mac =18:3c:b7:df:49:94
 channel = 6
==========================
 ecn = 4
 ssid =shian_Wi-Fi5
 rssi =-48
 mac =18:3c:b7:ff:49:99
 channel = 6
==========================
 ecn = 4
 ssid =bjzjhyjz622
 rssi =-48
 mac =00:94:ec:40:4f:cc
 channel = 11
==========================
 ecn = 3
 ssid =bjzjhyjz622
 rssi =-48
 mac =00:94:ec:40:4f:cc
 channel = 11
==========================
 ecn = 3
 ssid =bjzjhyjz622
 rssi =-48
 mac =00:94:ec:40:4f:cc
 channel = 11
==========================
 ecn = 3
 ssid =CU_5TMN
 rssi =-51
 mac =72:d8:3d:66:66:38
 channel = 3
==========================
 ecn = 4
 ssid =656
 rssi =-52
 mac =30:fc:68:eb:e6:03
 channel = 6
==========================
 ecn = 4
 ssid =XCYL
 rssi =-59
 mac =9c:a6:15:fa:3d:a3
 channel = 1
==========================
 ecn = 4
 ssid =GBSN
 rssi =-64
 mac =7c:b5:9b:59:e1:11
 channel = 7
==========================
 ecn = 4
 ssid =CNCEC
 rssi =-65
 mac =14:51:7e:67:65:be
 channel = 11
==========================
 ecn = 0
 ssid =CNCEC
 rssi =-65
 mac =14:51:7e:67:65:be
 channel = 11
==========================
 ecn = 0
 ssid =CNCEC
 rssi =-65
 mac =14:51:7e:67:65:be
 channel = 11
==========================
 ecn = 4
 ssid =bmkbmkbmk
 rssi =-70
 mac =54:a7:03:54:d2:8e
 channel = 1
==========================
 ecn = 4
 ssid =CNCEC
 rssi =-70
 mac =14:51:7e:67:55:1a
 channel = 11
==========================
 ecn = 3
 ssid =DIRECT-82-HP Laser 178nw
 rssi =-74
 mac =06:0e:3c:81:2c:82
 channel = 1
==========================
 ecn = 4
 ssid =DIRECT-82-HP Laser 178nw
 rssi =-74
 mac =06:0e:3c:81:2c:82
 channel = 1
==========================
 ecn = 4
 ssid =kzl528
 rssi =-75
 mac =0c:4b:54:4a:76:62
 channel = 1
==========================
 ecn = 4
 ssid =CU-4578
 rssi =-75
 mac =44:59:43:7c:45:78
 channel = 4
==========================
 ecn = 3
 ssid =CU_LVbG
 rssi =-75
 mac =9c:69:65:1f:ca:bc
 channel = 13
==========================
 ecn = 3
 ssid =1
 rssi =-76
 mac =78:85:f4:7f:56:2c
 channel = 1
==========================
 ecn = 4
 ssid =KZL
 rssi =-76
 mac =cc:08:fb:d8:a1:26
 channel = 1
==========================
 ecn = 4
 ssid =CU_uyz4
 rssi =-76
 mac =54:46:17:03:05:c8
 channel = 8
==========================
 ecn = 3
 ssid =CU_T322
 rssi =-77
 mac =72:60:8c:03:44:a4
 channel = 1
==========================
 ecn = 4
 ssid =ahead
 rssi =-81
 mac =d8:3d:cc:03:2b:35
 channel = 1
==========================
 ecn = 3
 ssid =CU_76a4
 rssi =-87
 mac =38:3e:5b:28:c4:88
 channel = 13
==========================
 ecn = 4
 ssid =6209
 rssi =-88
 mac =d8:3d:cc:03:80:05
 channel = 11
==========================
 ecn = 4
 ssid =zh
 rssi =-88
 mac =78:53:0d:c9:81:dd
 channel = 11
==========================
 ecn = 3
 ssid =zh
 rssi =-88
 mac =78:53:0d:c9:81:dd
 channel = 11
==========================
 ecn = 3
 ssid =zh
 rssi =-88
 mac =78:53:0d:c9:81:dd
 channel = 11
==========================
 ecn = 4
 ssid =CU_rNDR
 rssi =-91
 mac =e0:38:3f:52:ab:31
 channel = 9
==========================
 ecn = 3
 ssid =CU_rNDR
 rssi =-91
 mac =e0:38:3f:52:ab:31
 channel = 9
==========================
 ecn = 3
 ssid =CU_rNDR
 rssi =-91
 mac =e0:38:3f:52:ab:31
 channel = 9
==========================
 ecn = 4
 ssid =TP-LINK_B849
 rssi =-93
 mac =60:3a:7c:51:b8:49
 channel = 6
==========================
 ecn = 3
 ssid =CU_t9jE
 rssi =-93
 mac =58:d0:61:2d:0e:34
 channel = 9
==========================
 ecn = 3
 ssid =CU_t9jE
 rssi =-93
 mac =58:d0:61:2d:0e:34
 channel = 9
==========================
 ecn = 4
 ssid =XKJH
 rssi =-94
 mac =ec:6c:9f:b4:ff:06
 channel = 11
==========================
 ecn = 3
 ssid =XKJH
 rssi =-94
 mac =ec:6c:9f:b4:ff:06
 channel = 11
==========================
 ecn = 3
 ssid =zhang
 rssi =-95
 mac =6c:b7:49:2c:fa:fc
 channel = 11
==========================
 ecn = 3
 ssid =zhang
 rssi =-95
 mac =6c:b7:49:2c:fa:fc
 channel = 11
==========================









*/




