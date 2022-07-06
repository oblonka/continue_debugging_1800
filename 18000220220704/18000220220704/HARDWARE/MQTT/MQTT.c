#include "MQTT.h"
#include "WIFI.h"
#include "includes.h"	

#include "delay.h"


/*
1.��������ӵ�delay ��ʱ��   delay_ms(3000);
2.ESP32S_JoinAP�ĺ�����ִֻ��һ�εĻ�������delay 3000
3.��ESP32S_JoinAP��ִ�е�ѭ�����ж�


1.���



*/




/*
void ESP32S_STA_MQTTClient_Test_SA(void)//����wifi    STA     
		{
				OS_ERR err;//ͨ��ϵͳ����ʱ  
				
				char str[1024];
				printf("��������ESP32S����\r\n");
				
			
			  //��������ò��ɹ���ԭ�򣬿�����ǰ����Ե�ʱ���Ѿ����úõ����MQTT����͸����ģʽ��ÿ�����ӵ�ʱ�����˳�͸����ģʽ��
			  ESP32S_USART("%s","+++");//�˳�͸����ָ����û��е��ַ���    ���ָ���Ǻ����ӵģ���ʱ���Ρ���
			                           //2022��6��10��   ���Լ����˳�͸����ָ����з��� ��
				printf("\r\n%s\r\n",ESP32S_Fram_Record_Struct.Data_RX_BUF);
			  delay_ms(3000);
			
			
				//1     AT+RESTORE 
				ESP32S_AT_Test();//�ָ�����Ĭ��ģʽ                                                    
				//OSTimeDlyHMSM(0,0,6,5000,OS_OPT_TIME_PERIODIC,&err);//��ʱ1000ms
				delay_ms(5000);
			
				//2     AT+CWMODE=1
				ESP32S_Net_Mode_Choose(STA);                                                           
				//OSTimeDlyHMSM(0,0,6,5000,OS_OPT_TIME_PERIODIC,&err);//��ʱ1000ms
				delay_ms(5000);
			
				//3     AT+CWJAP="shian","shian623625"
				//������delay����ʱ�����û������
				ESP32S_JoinAP(User_ESP32S_SSID, User_ESP32S_PWD); 
				//�����ж��Ƿ������ϵķ���1
				//while(!ESP32S_JoinAP(User_ESP32S_SSID, User_ESP32S_PWD)); //while(0)ִ��һ�ξ��˳�
				//��ʱ1000ms
				//OSTimeDlyHMSM(0,0,6,5000,OS_OPT_TIME_PERIODIC,&err);
				delay_ms(5000);
			
				//4     AT+MQTTUSERCFG=0,1,"aithinker","admin","public",0,0,""
				ESP32S_MQTTUSERCFG(User_ESP32S_client_id,User_ESP32S_username,User_ESP32S_password);   
				//OSTimeDlyHMSM(0,0,6,5000,OS_OPT_TIME_PERIODIC,&err);//��ʱ1000ms
				delay_ms(3000);
				delay_ms(3000);
				
				
				//5     AT+MQTTCONN=0,"192.168.1.4",1883,0
				ESP32S_MQTTCONN( User_ESP32S_MQTTServer_IP, User_ESP32S_MQTTServer_PORT);              
				//OSTimeDlyHMSM(0,0,6,5000,OS_OPT_TIME_PERIODIC,&err);//��ʱ1000ms
				delay_ms(3000);
				delay_ms(3000);
				
				
				//6     AT+MQTTPUB=0,"ESP32S/online","shian13564",0,0
				//AT+MQTTSUB=0,"ESP32S/EMQX",0
				ESP32S_MQTTSUB( User_ESP32S_MQTTServer_Topic);//MQTT���ĵ�����                         
				//OSTimeDlyHMSM(0,0,6,5000,OS_OPT_TIME_PERIODIC,&err);//��ʱ1000ms
				delay_ms(5000);//ESP32S/online
				//delay_ms(3000);																																			
																								
																																																
				printf("\r\n MQTT������� ");   
				
while(1)
				{
				//���Ե� ���ݵĸ�ʽ    SA_wifi_1800	
				//��ʽ�������ַ�����MQTT������	
				sprintf(str,"SA_wifi_1800");  
				//�������ݵ�MQTT������  
				//���͵���������������ݣ��ַ���aithinker	
				MQTT_SendString(User_ESP32S_MQTTServer_Topic,str);             
				//�豸�˸�emqx��MQTT�������������ݣ�������Ƕ��ĵ���sub���Ǹ����⣬���Կ�֪
				//emqx���豸�˵ķ������ݵĻ��ǣ���message���Ǹ����⡣   
				//������Ļ������ڿ��Խ��յ��������
				//ͨ�������MQTT   �ƶ˷�������
					
				//����Ĳ��Ե��Ե��ַ���������
				//�����---��ʪ�����ݵļ���		 �����MQTT,AZURE�������� ESP32S��500msˢ��һ��
				//�����---ʱ�ӵ��������	     �����MQTT,AZURE�������ˣ����ӵ�wifi����ʵʱ��ʱ�䣬500msˢ��һ��
				//�����---������̼���������  �����MQTT�������ˣ�500msˢ��һ�� 	 
					
					
				}
		}
			
	*/	
			
			
			
			
			
			
void ESP32S_STA_MQTTClient_Test_SA_test(char * test_pSSID, char * test_pPassWord)//����wifi    STA     
		{
				OS_ERR err;//ͨ��ϵͳ����ʱ  
				
				char str[1024];
				printf("��������ESP32S����\r\n");
				
			
			  //��������ò��ɹ���ԭ�򣬿�����ǰ����Ե�ʱ���Ѿ����úõ����MQTT����͸����ģʽ��ÿ�����ӵ�ʱ�����˳�͸����ģʽ��
			  ESP32S_USART("%s","+++");//�˳�͸����ָ����û��е��ַ���    ���ָ���Ǻ����ӵģ���ʱ���Ρ���
			                           //2022��6��10��   ���Լ����˳�͸����ָ����з��� ��
				printf("\r\n%s\r\n",ESP32S_Fram_Record_Struct.Data_RX_BUF);
			  delay_ms(3000);
			
			
				//1     AT+RESTORE 
				ESP32S_AT_Test();//�ָ�����Ĭ��ģʽ                                                    
				//OSTimeDlyHMSM(0,0,6,5000,OS_OPT_TIME_PERIODIC,&err);//��ʱ1000ms
				delay_ms(5000);
			
				//2     AT+CWMODE=1
				ESP32S_Net_Mode_Choose(STA);                                                           
				//OSTimeDlyHMSM(0,0,6,5000,OS_OPT_TIME_PERIODIC,&err);//��ʱ1000ms
				delay_ms(5000);
			
				//3     AT+CWJAP="shian","shian623625"
				//������delay����ʱ�����û������
				ESP32S_JoinAP(test_pSSID, test_pPassWord); 
				//�����ж��Ƿ������ϵķ���1
				//while(!ESP32S_JoinAP(User_ESP32S_SSID, User_ESP32S_PWD)); //while(0)ִ��һ�ξ��˳�
				//��ʱ1000ms
				//OSTimeDlyHMSM(0,0,6,5000,OS_OPT_TIME_PERIODIC,&err);
				delay_ms(5000);
			
				//4     AT+MQTTUSERCFG=0,1,"aithinker","admin","public",0,0,""
				ESP32S_MQTTUSERCFG(User_ESP32S_client_id,User_ESP32S_username,User_ESP32S_password);   
				//OSTimeDlyHMSM(0,0,6,5000,OS_OPT_TIME_PERIODIC,&err);//��ʱ1000ms
				delay_ms(3000);
				delay_ms(3000);
				
				
				//5     AT+MQTTCONN=0,"192.168.1.4",1883,0
				ESP32S_MQTTCONN( User_ESP32S_MQTTServer_IP, User_ESP32S_MQTTServer_PORT);              
				//OSTimeDlyHMSM(0,0,6,5000,OS_OPT_TIME_PERIODIC,&err);//��ʱ1000ms
				delay_ms(3000);
				delay_ms(3000);
				
				
				//6     AT+MQTTPUB=0,"ESP32S/online","shian13564",0,0
				//AT+MQTTSUB=0,"ESP32S/EMQX",0
				ESP32S_MQTTSUB( User_ESP32S_MQTTServer_Topic);//MQTT���ĵ�����                         
				//OSTimeDlyHMSM(0,0,6,5000,OS_OPT_TIME_PERIODIC,&err);//��ʱ1000ms
				delay_ms(5000);//ESP32S/online
				//delay_ms(3000);																																			
																								
																																																
				printf("\r\n MQTT������� ");   
				
while(1)
				{
				//���Ե� ���ݵĸ�ʽ    SA_wifi_1800	
				//��ʽ�������ַ�����MQTT������	
				sprintf(str,"SA_wifi_1800");  
				//�������ݵ�MQTT������  
				//���͵���������������ݣ��ַ���aithinker	
				MQTT_SendString(User_ESP32S_MQTTServer_Topic,str);             
				//�豸�˸�emqx��MQTT�������������ݣ�������Ƕ��ĵ���sub���Ǹ����⣬���Կ�֪
				//emqx���豸�˵ķ������ݵĻ��ǣ���message���Ǹ����⡣   
				//������Ļ������ڿ��Խ��յ��������
				//ͨ�������MQTT   �ƶ˷�������
					
				//����Ĳ��Ե��Ե��ַ���������
				//�����---��ʪ�����ݵļ���		 �����MQTT,AZURE�������� ESP32S��500msˢ��һ��
				//�����---ʱ�ӵ��������	     �����MQTT,AZURE�������ˣ����ӵ�wifi����ʵʱ��ʱ�䣬500msˢ��һ��
				//�����---������̼���������  �����MQTT�������ˣ�500msˢ��һ�� 	 
					
					
				}
		}
			
			
			
			
			
			
			
			
			
			
			