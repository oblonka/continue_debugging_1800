#include "WIFI.h"
#include "usart.h"
#include "delay.h"
#include <stdarg.h>
#include "includes.h"	
#include "sys.h"  

#include "WIFIcon.h"



struct STRUCT_USART_Fram ESP32S_Fram_Record_Struct = { 0 };  //������һ������֡�ṹ��


char SSID_str[10][64] = {0};//ȫ��


char Extract_ssid[256]={0};//ȫ�ֱ��� 
uint32_t  offset_list_parse=0;//2022.05




//����wifi ssid�Ľ����ı����Ķ��壬ȫ��
	      int                ecn;
				char          ssid[64];
				int               rssi;
				char           mac[64];
				int            channel; 
				char*       ssid_list_ptr = NULL;
				int         list_offset = 0;
			  
			  char* str_buffer=NULL;//����������洮�ڽ��յ������飬   ESP32S_Fram_Record_Struct.Data_RX_BUF[]
				
				
				char  text_wifi[80];//char*���� 












void ESP32S_Init(u32 bound)
		{
     //�޸�ǰ��IO�ĳ�ʼ��			     ����ӵ���ʹ�ܵ����ź͸�λ��IO �����ţ��������Ҫ���ϵ���ֱ��IO���ƣ����ڵĵ��Ե�ʱ���õ��ǰ��������ⲿ�ĸ�λ
      
			
			/*		  GPIO_InitTypeDef GPIO_InitStructure;

				RCC_APB2PeriphClockCmd(ESP32S_RST_Pin_Periph_Clock|ESP32S_CH_PD_Pin_Periph_Clock, ENABLE);

				GPIO_InitStructure.GPIO_Pin = ESP32S_RST_Pin;             
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //�����������
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
				GPIO_Init(ESP32S_RST_Pin_Port, &GPIO_InitStructure);

				GPIO_InitStructure.GPIO_Pin = ESP32S_CH_PD_Pin;               
				GPIO_Init(ESP32S_CH_PD_Pin_Port, &GPIO_InitStructure);
*/
			
	

				
		   /*	 
			 GPIO_InitTypeDef GPIO_InitStructure;
			 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);     //ʹ��GPIOB��ʱ��
			 GPIO_InitStructure.GPIO_Pin    =  ESP32S_RST_Pin;
			 GPIO_InitStructure.GPIO_Mode   =  GPIO_Mode_OUT;         //���
			 GPIO_InitStructure.GPIO_OType  =  GPIO_OType_PP;         //�������
			 GPIO_InitStructure.GPIO_PuPd   =  GPIO_PuPd_NOPULL;      //�������
			 GPIO_InitStructure.GPIO_Speed  =  GPIO_Speed_100MHz;     //����GPIO
			 GPIO_Init(ESP32S_RST_Pin_Port,&GPIO_InitStructure);
			 
			 
			 GPIO_InitStructure.GPIO_Pin = ESP32S_CH_PD_Pin;               
			 GPIO_Init(ESP32S_CH_PD_Pin_Port, &GPIO_InitStructure);
		   */	
			 
			 
			 
			
			
				uart2_init_wifi(bound);     //��ʱ����     
		    //		ESP32S_Rst();              //Ŀǰ���ֶ���λ�����ڵ��ԣ������IO�ĵ��ԡ�
		}






//��ESP32Sģ�鷢��ATָ��        2022-4-20 10:05:21  ����ķ����ַ����յ����ַ���  ��֤�ظ������               
// cmd �����͵�ָ��
// ack1,ack2;�ڴ�����Ӧ��ΪNULL������Ӧ������Ϊ���߼���ϵ
// time �ȴ���Ӧʱ��
//����1���ͳɹ��� 0ʧ��
bool ESP32S_Send_AT_Cmd(char *cmd,char *ack1,char *ack2,u32 time)
{ 
	
	  OS_ERR err;//ϵͳ��ʱ���
	
	
    ESP32S_Fram_Record_Struct .InfBit .FramLength = 0; //���½����µ����ݰ�
    ESP32S_USART("%s\r\n", cmd);//�����ͨ������2,���������� ���ݵ�ת���Ľӿ�
	  //printf("%s\r\n", cmd);//ͨ������6���Խӿڣ����е��������ӡlog	
    if(ack1==0&&ack2==0)     //����Ҫ��������
    {
    return true;
    }
		
		
    //delay_ms(time);   //��ʱ   2022-4-20 09:37:20
		//delay_ms(1000);   //   2022-4-20 09:37:33
		
	  OSTimeDlyHMSM(0,0,0,time,OS_OPT_TIME_PERIODIC,&err);//��ʱ time ms 
		OSTimeDlyHMSM(0,0,0,1000,OS_OPT_TIME_PERIODIC,&err);//��ʱ time ms 
		
		
    ESP32S_Fram_Record_Struct.Data_RX_BUF[ESP32S_Fram_Record_Struct.InfBit.FramLength ] = '\0';
		
    printf("%s",ESP32S_Fram_Record_Struct.Data_RX_BUF);
		
    if(ack1!=0&&ack2!=0)
    {
        return ( ( bool ) strstr ( ESP32S_Fram_Record_Struct.Data_RX_BUF, ack1 ) || 
                         ( bool ) strstr ( ESP32S_Fram_Record_Struct.Data_RX_BUF, ack2 ) );
    }
    else if( ack1 != 0 )  //strstr(s1,s2);���s2�Ƿ�Ϊs1��һ���֣��Ƿ��ظ�λ�ã����򷵻�false����ǿ��ת��Ϊbool������
        return ( ( bool ) strstr ( ESP32S_Fram_Record_Struct.Data_RX_BUF, ack1 ) );

    else
        return ( ( bool ) strstr ( ESP32S_Fram_Record_Struct.Data_RX_BUF, ack2 ) );

}


//��λ����     ��ʱ��Ӳ���İ���������  ���� ��ӡlog
/*
void ESP32S_Rst(void)
{
    ESP32S_RST_Pin_SetL;
    delay_ms(500); 
    ESP32S_RST_Pin_SetH;
}

*/








//���ͻָ�����Ĭ������ָ�ģ��ָ��ɳ�������
void ESP32S_AT_Test(void)
{
	
    char count=0;
	
	  OS_ERR err;
	  OSTimeDlyHMSM(0,0,0,1000,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms    2022-4-20 09:39:34
    //delay_ms(1000); //OS_ERR err;   OSTimeDlyHMSM(0,0,0,1500,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms   
    while(count < 10)
    {
        if(ESP32S_Send_AT_Cmd("AT+RESTORE","OK",NULL,500)) 
        {
            printf("OK\r\n");
            return;
        }
        ++ count;
    }
}





//ѡ��ESP32S�Ĺ���ģʽ,���ӵ�MQTT ���Ʒ���Ļ���ֱ��ʹ��MQTT��ģʽ���У�����WIFI��ģʽ
// enumMode ģʽ����
//�ɹ�����true��ʧ�ܷ���false
bool ESP32S_Net_Mode_Choose(ENUM_Net_ModeTypeDef enumMode)
{
    switch ( enumMode )
    {
        case STA:
            return ESP32S_Send_AT_Cmd ( "AT+CWMODE=1", "OK", "no change", 2500 ); 

        case AP:
            return ESP32S_Send_AT_Cmd ( "AT+CWMODE=2", "OK", "no change", 2500 ); 

        case STA_AP:
            return ESP32S_Send_AT_Cmd ( "AT+CWMODE=3", "OK", "no change", 2500 ); 

        default:
          return false;
    }       
}





//ESP32S�����ⲿ��WIFI
//pSSID WiFi�ʺ�
//pPassWord WiFi����
//���óɹ�����true ��֮false
bool ESP32S_JoinAP( char * pSSID, char * pPassWord)
{
    char cCmd [120];
	
    sprintf ( cCmd, "AT+CWJAP=\"%s\",\"%s\"", pSSID, pPassWord );
    return ESP32S_Send_AT_Cmd( cCmd, "OK", NULL, 5000 );
}


//ESP32S ͸��ʹ��
//enumEnUnvarnishTx  �Ƿ�����ӣ�bool����
//���óɹ�����true����֮false
bool ESP32S_Enable_MultipleId (FunctionalState enumEnUnvarnishTx )
{
    char cStr [20];

    sprintf ( cStr, "AT+CIPMUX=%d", ( enumEnUnvarnishTx ? 1 : 0 ) );

    return ESP32S_Send_AT_Cmd ( cStr, "OK", 0, 500 );

}


//ESP32S ���ӷ�����
//enumE  ��������
//ip ��������IP
//ComNum  �������˿�
//id�����Ӻţ�ȷ��ͨ�Ų���������
//���óɹ�����true����֮fasle
bool ESP32S_Link_Server(ENUM_NetPro_TypeDef enumE, char * ip, char * ComNum, ENUM_ID_NO_TypeDef id)
{
    char cStr [100] = { 0 }, cCmd [120];

    switch (  enumE )
    {
        case enumTCP:
          sprintf ( cStr, "\"%s\",\"%s\",%s", "TCP", ip, ComNum );
          break;

        case enumUDP:
          sprintf ( cStr, "\"%s\",\"%s\",%s", "UDP", ip, ComNum );
          break;

        default:
            break;
    }

    if ( id < 5 )
        sprintf ( cCmd, "AT+CIPSTART=%d,%s", id, cStr);

    else
        sprintf ( cCmd, "AT+CIPSTART=%s", cStr );

    return ESP32S_Send_AT_Cmd ( cCmd, "OK", "ALREAY CONNECT", 4000 );

}


//͸��ʹ��
//���óɹ�����true�� ��֮false
bool ESP32S_UnvarnishSend ( void )
{
    if (!ESP32S_Send_AT_Cmd ( "AT+CIPMODE=1", "OK", 0, 500 ))
        return false;

    return 
        ESP32S_Send_AT_Cmd( "AT+CIPSEND", "OK", ">", 500 );

}


//ESP32S�����ַ���
//enumEnUnvarnishTx�Ƿ�ʹ��͸��ģʽ
//pStr�ַ���
//ulStrLength�ַ�������
//ucId ���Ӻ�
//���óɹ�����true�� ��֮false
bool ESP32S_SendString(FunctionalState enumEnUnvarnishTx, char * pStr, u32 ulStrLength, ENUM_ID_NO_TypeDef ucId )
{
    char cStr [20];
    bool bRet = false;


    if ( enumEnUnvarnishTx )
    {
        ESP32S_USART ( "%s", pStr );

        bRet = true;

    }

    else
    {
        if ( ucId < 5 )
            sprintf ( cStr, "AT+CIPSEND=%d,%d", ucId, ulStrLength + 2 );

        else
            sprintf ( cStr, "AT+CIPSEND=%d", ulStrLength + 2 );

        ESP32S_Send_AT_Cmd ( cStr, "> ", 0, 1000 );

        bRet = ESP32S_Send_AT_Cmd ( pStr, "SEND OK", 0, 1000 );
  }

    return bRet;

}


//ESP32S�˳�͸��ģʽ
void ESP32S_ExitUnvarnishSend ( void )
{
    
	  OS_ERR err;
	  OSTimeDlyHMSM(0,0,0,1000,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms 
	
	  //delay_ms(1000);  //�ò���ϵͳ�ĺ������
    ESP32S_USART( "+++" );
    //delay_ms( 500 ); //�ò���ϵͳ�ĺ������ 
	
	  OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms 
	
}


//ESP32S �������״̬
//����0����ȡ״̬ʧ��
//����2�����ip
//����3���������� 
//����4��ʧȥ���� 
u8 ESP32S_Get_LinkStatus ( void )
{
    if (ESP32S_Send_AT_Cmd( "AT+CIPSTATUS", "OK", 0, 500 ) )
    {
        if ( strstr ( ESP32S_Fram_Record_Struct .Data_RX_BUF, "STATUS:2\r\n" ) )
            return 2;

        else if ( strstr ( ESP32S_Fram_Record_Struct .Data_RX_BUF, "STATUS:3\r\n" ) )
            return 3;

        else if ( strstr ( ESP32S_Fram_Record_Struct .Data_RX_BUF, "STATUS:4\r\n" ) )
            return 4;       

    }

    return 0;
}

static char *itoa( int value, char *string, int radix )
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;

    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */


void USART_printf ( USART_TypeDef * USARTx, char * Data, ... )
{
    const char *s;
    int d;   
    char buf[16];


    va_list ap;
    va_start(ap, Data);

    while ( * Data != 0 )     // �ж������Ƿ񵽴������
    {                                         
        if ( * Data == 0x5c )  //'\'
        {                                     
            switch ( *++Data )
            {
                case 'r':                                     //�س���
                USART_SendData(USARTx, 0x0d);
                Data ++;
                break;

                case 'n':                                     //���з�
                USART_SendData(USARTx, 0x0a);   
                Data ++;
                break;

                default:
                Data ++;
                break;
            }            
        }

        else if ( * Data == '%')
        {                                     
            switch ( *++Data )
            {               
                case 's':                                         //�ַ���
                s = va_arg(ap, const char *);
                for ( ; *s; s++) 
                {
                    USART_SendData(USARTx,*s);
                    while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
                }
                Data++;
                break;

                case 'd':           
                    //ʮ����
                d = va_arg(ap, int);
                itoa(d, buf, 10);
                for (s = buf; *s; s++) 
                {
                    USART_SendData(USARTx,*s);
                    while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
                }
                     Data++;
                     break;
                default:
                     Data++;
                     break;
            }        
        }
        else USART_SendData(USARTx, *Data++);
        while ( USART_GetFlagStatus ( USARTx, USART_FLAG_TXE ) == RESET );

    }
}















/*

bool ESP32S_Send_AT_Cmd(char *cmd,char *ack1,char *ack2,u32 time)
{ 
	
	  OS_ERR err;//ϵͳ��ʱ���
	
    ESP32S_Fram_Record_Struct .InfBit .FramLength = 0; //���½����µ����ݰ�
    ESP32S_USART("%s\r\n", cmd);//�����ͨ������2,���������� ���ݵ�ת���Ľӿ�
	
    if(ack1==0&&ack2==0)     //����Ҫ��������
    {
    return true;
    }
		
    //delay_ms(time);   //��ʱ   2022-4-20 09:37:20
		//delay_ms(1000);   //   2022-4-20 09:37:33
		
	  OSTimeDlyHMSM(0,0,0,time,OS_OPT_TIME_PERIODIC,&err);//��ʱ time ms 
		OSTimeDlyHMSM(0,0,0,1000,OS_OPT_TIME_PERIODIC,&err);//��ʱ time ms 
		
    ESP32S_Fram_Record_Struct.Data_RX_BUF[ESP32S_Fram_Record_Struct.InfBit.FramLength ] = '\0';
		
    printf("%s",ESP32S_Fram_Record_Struct .Data_RX_BUF);
    if(ack1!=0&&ack2!=0)
    {
        return ( ( bool ) strstr ( ESP32S_Fram_Record_Struct .Data_RX_BUF, ack1 ) || 
                         ( bool ) strstr ( ESP32S_Fram_Record_Struct .Data_RX_BUF, ack2 ) );
    }
    else if( ack1 != 0 )  //strstr(s1,s2);���s2�Ƿ�Ϊs1��һ���֣��Ƿ��ظ�λ�ã����򷵻�false����ǿ��ת��Ϊbool������
        return ( ( bool ) strstr ( ESP32S_Fram_Record_Struct .Data_RX_BUF, ack1 ) );

    else
        return ( ( bool ) strstr ( ESP32S_Fram_Record_Struct .Data_RX_BUF, ack2 ) );

}

*/


//��������WiFi �б�
//��������WiFi��ʱ��Ļ�ȡ
/*
[16:08:11.785]�ա���AT+CWLAP

+CWLAP:(3,"loong",-36,"7e:c8:7e:35:08:73",11,-1,-1,4,4,7,0)
+CWLAP:(4,"TP-12345678",-76,"34:96:72:b1:d8:a9",11,-1,-1,4,4,7,0)
+CWLAP:(4,"MERCURY_4F5E",-81,"bc:5f:f6:4e:4f:5e",13,-1,-1,4,4,7,0)

OK
*/


/*
[16:01:55.398]�ա���AT+CIPSNTPTIME?
+CIPSNTPTIME:Sat May 28 16:01:58 2022
OK
*/





//wifi_con   ��ȡWiFi�б�   
/*
������ʽ��ȡ�������ַ�
AT����ؽ��Ϊ��
+CWLAP:(4,"TP-LINK_PocketAP_DFBCD4",-57,"38:83:45:df:bc:d4",6)
+CWLAP:(3,"LSTM",-61,"8c:21:0a:bc:8e:70",13)
+CWLAP:(3,"LabWiFi",-62,"68:3b:78:8f:16:23",1)
+CWLAP:(0,"GuestWiFi",-64,"68:3b:78:8f:16:22",1)

OK -
AT+CWLAP

���ҵ�+CWLAP��
strstr(buffer+offset, "+CWLAP:");
ʹ��sscanf+������ʽ��ȡssid��mac��rssi��
sscanf(str+strlen("+CWLAP:"), "(%d,\"%[^\"]\",%d,\"%[^\"]\",", &ecn, ssid, &rssi, mac);
��ȡ֮�󣬽�strָ���ƶ������н�����������һ�ֵĲ��ң�

while (*str++ != '\n')
	 {
	offset++;
	}

*/



//bool ESP32S_JoinAP_connect_list_parse( char * pSSID, char * pPassWord)
//bool ESP32S_GET_RealTime_parse( char * pSSID, char * pPassWord)



//ESP32S�����ⲿ��WIFI
//pSSID WiFi�ʺ�
//pPassWord WiFi����
//���óɹ�����true ��֮false

/*
����ֻ��Ҫ��������Ӧ��SSID�Ϳ��ԡ�
��ʾ��GUI�����Ӧ��ʾ�����ӵ�wifi






*/


bool ESP32S_JoinAP_connect_list_parse( char *list_parse_cmd,  u32 time)
//bool ESP32S_JoinAP_connect_list_parse()
		{
			char i = 0;
			
			
			WM_HWIN      hItem;
			
				/*
				AT+CWLAP
				
				+CWLAP:(4,"TP-LINK_PocketAP_DFBCD4",-57,"38:83:45:df:bc:d4",6)
				+CWLAP:(3,"LSTM",-61,"8c:21:0a:bc:8e:70",13)
				+CWLAP:(3,"LabWiFi",-62,"68:3b:78:8f:16:23",1)
				+CWLAP:(0,"GuestWiFi",-64,"68:3b:78:8f:16:22",1)
					
				
				rssi <= 0 && rssi >= -50       //�ź����
				rssi < -50 && rssi >= -70      //�źŽϺ�
				rssi < -70 && rssi >= -80      //�ź�һ��
				rssi <-80  && rssi >= -100     //�źŽϲ�
				rssiû����0����-100)֮�䣬     //��ʾ���ź�
				
			
				int day, year;
				char weekday[20], month[20], dtm[100];
				strcpy( dtm,"+loong:Thuriday May 12 2022" );
				sscanf( dtm, "%s %s %d  %d", weekday, month, &day, &year );
				
				//ret = sscanf(str, "+CSQ:%d,%d", &rssi, &ber);
				
				printf("%s %d, %d = %s\n", month, day, year, weekday );  
				return(0);
				
			  const char haystack[20] = "RUNOOB";
        const char needle[10] = "NOOB";
        char *ret;
        ret = strstr(haystack+2, needle);//������Ҫ���ַ��� 
        printf("���ַ����ǣ� %s\n", ret);
        return(0);
	      
				*/				
				
				
				
				OS_ERR err;//ϵͳ��ʱ���
				 
				//uint32_t  offset_list_parse=0;//2022.05
																        //&ecn, ssid, &rssi, mac    
				//uint32_t         ecn;         //���֣�����            //2022.05
				// int32_t        rssi;         //���֣��ź�ǿ��        //2022.05
				//		char  ssid_list[32];      //�ַ���    ����        //2022.05
				//		char        mac[32];      //�ַ���  mac��ַ       //2022.05
			  //    char *str_ret=NULL;//ָ��ĳ�ʼ��һ��Ҫ��ȷָ��,��ʼ������Ϊ�ա�
				//		uint32_t scan_num;
				//char Extract_ssid[256];
			
			
			
			
		/*	//ʵ��ʹ�õĶ���   ����ȫ�ֱ���
				int                ecn;
				char          ssid[32];
				int               rssi;
				char           mac[32];
				int            channel; 
				char*       ssid_list_ptr = NULL;
				int         list_offset = 0;
			  
			  char* str_buffer=NULL;//����������洮�ڽ��յ������飬   ESP32S_Fram_Record_Struct.Data_RX_BUF[]
				
				
				char  text_wifi[80];//char*���� 
			*/	
				
				
				
				
				
				
				
				
/*				
char* str = 
"+CWLAP:(4,\"TP-LINK_PocketAP_DFBCD4\",-57,\"38:83:45:df:bc:d4\",6)\r\n\
+CWLAP:(3,\"LSTM\",-61,\"8c:21:0a:bc:8e:70\",13)\r\n\
+CWLAP:(3,\"LabWiFi\",-62,\"68:3b:78:8f:16:23\",1)\r\n\
+CWLAP:(0,\"GuestWiFi\",-64,\"68:3b:78:8f:16:22\",1)\r\n\
\r\n\
OK\r\n";

int main()
{
     while(1){
         ptr = strstr(str+offset,"+CWLAP");
         if(!ptr)break;
         sscanf(ptr,"+CWLAP:(%d,\"%[^\"]\",%d,\"%[^\"]\",%d",&ecn, ssid, &rssi, mac,&channel);
         printf(" ecn = %d\r\n ssid =%s\r\n rssi =%d\r\n mac =%s\r\n channel = %d\r\n",ecn, ssid, rssi, mac,channel);
         printf("==========================\r\n");
         while (*ptr++ != '\n') 
         {  
             offset++; 
         }
     }
     system("pause");
     return 0;
 
 }     2022.06

*/
		    delay_ms(3000);
				//**********1
				ESP32S_USART("%s","+++");//�˳�͸����ָ����û��е��ַ���    2022.06
				delay_ms(5000); 
				printf("\r\n\r\n");
				
				
				//**********2
				ESP32S_AT_Test();//�ȴ�ӡ��λ��ָ���ӡ�����OK ���ں���������    2022.06
				delay_ms(3000);  //2022-06
				delay_ms(3000);  
				
				
				ESP32S_Fram_Record_Struct.InfBit.FramLength = 0; //���½����µ����ݰ�
				
				
				//**********3     AT+CWMODE=1      AT+CWMODE=3 
				ESP32S_Net_Mode_Choose(STA);//��ִ�У�AT+CWMODE=1 �� AT+CWMODE=3                                                           
				delay_ms(3000);
				

				//**********4    ����WIFI�����ӵ����
				ESP32S_Send_AT_Cmd("AT+CWSTATE?","OK",NULL,500);//����WIFI�����ӵ����   2022.6
				printf("\r\n%s\r\n",ESP32S_Fram_Record_Struct.Data_RX_BUF);
				
				
				//**********5
				ESP32S_USART("%s\r\n", list_parse_cmd);//�����ͨ������2,���������� ���ݵ�ת���Ľӿ�  OK   2022.06
				delay_ms(5000);   //2022-4-20 09:37:33
			  printf("\r\n%s\r\n",ESP32S_Fram_Record_Struct.Data_RX_BUF); //���ԿڵĴ�ӡ���   OK
				delay_ms(5000);   //2022-4-20 09:37:33
				delay_ms(5000);   //2022-4-20 09:37:33
				
				
				ESP32S_Fram_Record_Struct.Data_RX_BUF[ESP32S_Fram_Record_Struct.InfBit.FramLength] = '\0';
				
				
			  //Extract_ssid[offset_list_parse]=*ssid_list; //ͨ��ƫ��������ȡ����ssid�浽����
				//������ȡ10��Ϊһ����λ��������ʾ���б�
				//printf("\r\n %d : %c \r\n",offset_list_parse,Extract_ssid[offset_list_parse]); //��ӡ�ַ���
				//�����������[0],ֱ�ӵ���			 
			   
				str_buffer=ESP32S_Fram_Record_Struct.Data_RX_BUF;//2022.06��wifi���صĽ��������ַ����ָ��
				//int buffer[5],*pa;   pa = buffer;  /* pa = &buffer[0]; */ 
				//������ѭ����ɨ��Ľ���SSID,����ĳɵ���һ��ɨ��һ�Σ���ʾһ�εĽ���� 
				while(1)
							 { //2022.06
								 ssid_list_ptr = strstr(str_buffer+list_offset,"+CWLAP");
								 //ptr = strstr(ESP32S_Fram_Record_Struct.Data_RX_BUF+list_offset,"+CWLAP");
								 //if(s[0]!='\0')���ַ����ǿմ�   ǰ���� �ַ������ж�
								 
								 
								 hItem = WM_GetDialogItem(WIFI_hWin, ID_BUTTON_0 + i);   
								 BUTTON_SetText(hItem,ssid);
								 i++;
								 if(i>9)
									 i = 0;
								 
								 
								 
								 
								 if(!ssid_list_ptr)break;
								 sscanf(ssid_list_ptr,"+CWLAP:(%d,\"%[^\"]\",%d,\"%[^\"]\",%d",&ecn, ssid, &rssi, mac,&channel);
								 
								 //sscanf(SSID_str[i],"%s",ssid);
								 
								 
								 printf(" ecn = %d\r\n ssid =%s\r\n rssi =%d\r\n mac =%s\r\n channel = %d\r\n",ecn, ssid, rssi, mac,channel);
								 printf("===========================\r\n");
								  while (*ssid_list_ptr++ != '\n') 
												 {  
													 list_offset++; 
												 }
									
//delay_ms(3000);

											 
								}	
			return 0;		 		 	
}
								 





								 //���� str     if(str[0]=='\0') ���ǿ�
								 //ָ��         if(*p=='\0') ���ǿ� 
								 //if( str == NULL || strlen(str) == 0 ) 
								 //if(!str || !*str)puts("str�ǿ�");
								 //if(str && *str)puts("str���ǿ�");
								 
								 //if(ssid[0]!='\0')//�ж��Ƿ�ssid�Ĵ����Ƿǿյģ�ɨ����Ե�����ʾ���ɼ���wifi,��ʾ�����ǿյ��ַ���������
								 
								 
								 //if( (*ssid != NULL) && (strlen(ssid) != 0) )//SSID�ķǿ���ʾ�ж� 
								 //if( (*ssid != NULL)�������ж�������������ָʾ
								/* 
								 if(str != NULL)
									 {
                    if(strlen(str) == 0) 
							        {
                      // it is empty string
                      }
                   }
								 */
								 
								 
								 //if(*ssid != NULL)
									// {
                  //  if(strlen(ssid) != 0) 
								     // if(strlen(ssid) != 0) 
								 	  // { 
									  //  printf(" ecn = %d\r\n ssid =%s\r\n rssi =%d\r\n mac =%s\r\n channel = %d\r\n",ecn, ssid, rssi, mac,channel);
									  //  printf("===========================\r\n");
								 	  // }
								 
								  // }
								 //sprintf(text_wifi, "%s", ssid);
								 
								 
								 
											// while (*ssid_list_ptr++ != '\n') 
											//			 {  
											//				 list_offset++; 
											//			 }
						   // }	
		//	return 0;		 		 
			
//}

		
		
		
		

bool ESP32S_GET_RealTime_parse(char *cmd,u32 time)
		 {
			 /*
			 [16:01:55.398]�ա���AT+CIPSNTPTIME?
				+CIPSNTPTIME:Sat May 28 16:01:58 2022
				OK
			 */
			 
        OS_ERR err;//ϵͳ��ʱ���
				 
				uint32_t offset_RealTime_parse=0;//2022.05
													                
			  /* &ecn, ssid, &rssi, mac */
			  char     *SNTP_week;     //SNTP_week     �ַ���  mac��ַ //2022.06
			  char    *SNTP_month;     //SNTP_month    �ַ���  ����  //2022.06
			  int32_t    SNTP_day;     //&SNTP_day                     //2022.06
			  int32_t   SNTP_time;     //&SNTP_time    ���֣�  �ź�ǿ��  //2022.05
				uint32_t  SNTP_year;     //&SNTP_year    ���֣�  ����      //2022.05
				
				char Extract_realtime[256];
				
				ESP32S_Fram_Record_Struct.InfBit .FramLength = 0; //���½����µ����ݰ�
				ESP32S_USART("\r\n%s\r\n", cmd);//�����ͨ������2,���������� ���ݵ�ת���Ľӿ�
			
				delay_ms(1000);   //   2022-4-20 09:37:33
				OSTimeDlyHMSM(0,0,0,1000,OS_OPT_TIME_PERIODIC,&err);//��ʱ time ms 
				
				ESP32S_Fram_Record_Struct.Data_RX_BUF[ESP32S_Fram_Record_Struct.InfBit.FramLength ] = '\0';
				
				printf("\r\n%s\r\n",ESP32S_Fram_Record_Struct.Data_RX_BUF);
						 
				//���ҵ�+CWLAP��
				//strstr(buffer+offset, "+CWLAP:");
				strstr(ESP32S_Fram_Record_Struct.Data_RX_BUF+offset_RealTime_parse, "+CIPSNTPTIME:");
						
				//ʹ��sscanf+������ʽ��ȡssid��mac��rssi��   +CIPSNTPTIME:Sat May 28 16:01:58 2022    "(%d,\"%[^\"]\",%d,\"%[^\"]\","    
				sscanf(ESP32S_Fram_Record_Struct.Data_RX_BUF+strlen("+CIPSNTPTIME:"), "(\"%[^\"]\" \"%[^\"]\" %d %d %d", SNTP_week, SNTP_month, &SNTP_day, &SNTP_time,&SNTP_year);
				//��ȡ֮�󣬽�strָ���ƶ������н�����������һ�ֵĲ��ң�

				while ((*ESP32S_Fram_Record_Struct.Data_RX_BUF)++ != '\n')
						 {
							
							//Extract_realtime[offset]=*ssid; //ͨ��ƫ��������ȡ����ssid�浽����
							 
							 Extract_realtime[0]=*SNTP_week;
							 Extract_realtime[1]=*SNTP_month;
							 Extract_realtime[2]=SNTP_day;
							 Extract_realtime[3]=SNTP_time;
							 Extract_realtime[4]=SNTP_year;
							 
							 printf("\r\n%c\r\n",Extract_realtime[offset_RealTime_parse]); //��ӡ�ַ���
							 
							//�����������[0],ֱ�ӵ���
							 
							offset_RealTime_parse++;//��0��ʼ������һ�Σ�Ȼ��ƫ������1��������
						 }
		 }



		 
		 
		 
		 
		 






//����ΪESP32SMQTT����ָ��

/*
*MQTT�����û�����
*LinkID ����ID,Ŀǰֻ֧��0
*scheme ���ӷ�ʽ������ѡ��MQTT over TCP,��������Ϊ1
*client_id MQTTclientID ���ڱ�־client���
*username ���ڵ�¼ MQTT ������ �� username
*password ���ڵ�¼ MQTT ������ �� password
*cert_key_ID ֤�� ID, Ŀǰ֧��һ�� cert ֤��, ����Ϊ 0
*CA_ID Ŀǰ֧��һ�� CA ֤��, ����Ϊ 0
*path ��Դ·������������Ϊ""
*���óɹ�����true ��֮false
*/
bool ESP32S_MQTTUSERCFG( char * pClient_Id, char * pUserName,char * PassWord)
{
    char cCmd [120];
    sprintf ( cCmd, "AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"", pClient_Id,pUserName,PassWord );
    return ESP32S_Send_AT_Cmd( cCmd, "OK", NULL, 500 );
}


/*
*����ָ����MQTT������
*LinkID ����ID,Ŀǰֻ֧��0
*IP��MQTT�������϶�Ӧ��IP��ַ
*ComNum MQTT�������϶�Ӧ�Ķ˿ںţ�һ��Ϊ1883
*���óɹ�����true ��֮false
*/
bool ESP32S_MQTTCONN( char * Ip, int  Num)
{
    char cCmd [120];
    sprintf ( cCmd,"AT+MQTTCONN=0,\"%s\",%d,0", Ip,Num);
    return ESP32S_Send_AT_Cmd( cCmd, "OK", NULL, 500 );
}

/*
*����ָ�����ӵ� MQTT ����, ���ظ���ζ��Ĳ�ͬ topic
*LinkID ����ID,Ŀǰֻ֧��0
*Topic ���ĵ��������֣���������ΪTopic
*Qosֵ��һ��Ϊ0����������Ϊ1
*���óɹ�����true ��֮false
*/
bool ESP32S_MQTTSUB(char * Topic)
{
    char cCmd [120];
    sprintf ( cCmd, "AT+MQTTSUB=0,\"%s\",1",Topic );
    return ESP32S_Send_AT_Cmd( cCmd, "OK", NULL, 500 );
}


/*
*��LinkID��ͨ�� topic �������� data, ���� data Ϊ�ַ�����Ϣ
*LinkID ����ID,Ŀǰֻ֧��0
*Topic ���ĵ��������֣���������ΪTopic
*data���ַ�����Ϣ
*���óɹ�����true ��֮false
*/
bool ESP32S_MQTTPUB( char * Topic,char *temp)
{
    char cCmd [120];
    sprintf (cCmd, "AT+MQTTPUB=0,\"%s\",\"%s\",1,0", Topic ,temp);
    return ESP32S_Send_AT_Cmd( cCmd, "OK", NULL, 1000 );
}

/*
*�ر� MQTT Client Ϊ LinkID ������, ���ͷ��ڲ�ռ�õ���Դ
*LinkID ����ID,Ŀǰֻ֧��0
*Topic ���ĵ��������֣���������ΪTopic
*data���ַ�����Ϣ
*���óɹ�����true ��֮false
*/
bool ESP32S_MQTTCLEAN(void)
{
    char cCmd [120];
    sprintf ( cCmd, "AT+MQTTCLEAN=0");
    return ESP32S_Send_AT_Cmd( cCmd, "OK", NULL, 500 );
}

//ESP32S�����ַ���
//enumEnUnvarnishTx�Ƿ�ʹ��͸��ģʽ
//pStr�ַ���
//ulStrLength�ַ�������
//ucId ���Ӻ�
//���óɹ�����true�� ��֮false
bool MQTT_SendString(char * pTopic,char *temp2)
{
	  OS_ERR err;
	  //OSTimeDlyHMSM(0,0,0,1000,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms 
	
    bool bRet = false;
    ESP32S_MQTTPUB(pTopic,temp2);
	  
	  //delay_ms(1000);//�����ϵͳ����ʱ�������        
	  OSTimeDlyHMSM(0,0,0,1000,OS_OPT_TIME_PERIODIC,&err);//��ʱ1000ms     2022-4-20 09:41:12
	  
	
    bRet = true;
    return bRet;

}

