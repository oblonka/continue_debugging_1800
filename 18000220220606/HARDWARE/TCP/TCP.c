#include "TCP.h"
#include "usart.h"
#include "WIFI.h"//
#include "delay.h"
#include "stdio.h"
#include "string.h"

#include "stm32f4xx.h"//

volatile u8 TcpClosedFlag = 0;

void ESP32S_STA_TCPClient_Test(void)
{
    u8 res;
	
    char str[100]={0};
    ESP32S_AT_Test();
		printf("��������ESP32S\r\n");
    ESP32S_Net_Mode_Choose(STA);
    while(!ESP32S_JoinAP(User_ESP32S_SSID, User_ESP32S_PWD));
    ESP32S_Enable_MultipleId ( DISABLE );
    while(!ESP32S_Link_Server(enumTCP, User_ESP32S_TCPServer_IP, User_ESP32S_TCPServer_PORT, Single_ID_0));
    while(!ESP32S_UnvarnishSend());
		printf("\r\n�������");
    while ( 1 )
    {       
			  sprintf (str,"�����а��ſɿƼ����޹�˾" );//��ʽ�������ַ�����TCP������
        ESP32S_SendString ( ENABLE, str, 0, Single_ID_0 );
        delay_ms(1000);
        if(TcpClosedFlag) //�ж��Ƿ�ʧȥ����
        {
            ESP32S_ExitUnvarnishSend(); //�˳�͸��ģʽ
            do
            {
                res = ESP32S_Get_LinkStatus();     //��ȡ����״̬
            }   
            while(!res);

            if(res == 4)                     //ȷ��ʧȥ���ӣ�����
            {
                
                
                while (!ESP32S_JoinAP(User_ESP32S_SSID, User_ESP32S_PWD ) );
                while (!ESP32S_Link_Server(enumTCP, User_ESP32S_TCPServer_IP, User_ESP32S_TCPServer_PORT, Single_ID_0 ) );        
            } 
            while(!ESP32S_UnvarnishSend());                    
        }
    }   
}
