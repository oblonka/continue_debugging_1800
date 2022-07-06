#ifndef __MQTT_H
#define __MQTT_H 			   



#include "stm32f4xx.h"



/*
*�������µĲ�������  2.4G��WiFi

���ز��Ե�MQTT�������Ĳ���

"shian" 
"shian623625"

"admin"
"public" 
"192.168.1.4"
1883
"ESP32S/online"




*/






#define User_ESP32S_SSID              "shian"             //shian           TP-12345678    wifi��    "miot_default"    2.4G
#define User_ESP32S_PWD               "shian623625"       //shian623625     12345678       wifi����  "123456789x"



#define User_ESP32S_client_id         "aithinker"         //MQTTclientID ���ڱ�־client���  �256�ֽ�
#define User_ESP32S_username          "admin"						  //���ڵ�¼ MQTT ������ �� username, � 64 �ֽ�	
#define User_ESP32S_password			    "public"            //���ڵ�¼ MQTT ������ �� password, � 64 �ֽ�

#define User_ESP32S_MQTTServer_IP     "192.168.1.3"       //MQTT���ط�����IP     ������IP    ������  
#define User_ESP32S_MQTTServer_PORT   1883                //�������˿ں�
#define User_ESP32S_MQTTServer_Topic  "ESP32S/online"     //����MQTT����   ESP32S/EMQX   "topic"  ESP32S/online
                                                          //ESP32S/online    ������豸�˷���MQTT������������      ���е�����
                                                          //ESP32S/EMQX      �������MQTTT�����������豸�˵�����   ���е�����


void ESP32S_STA_MQTTClient_Test_SA(void);//����MQTT�������Ĳ���

void ESP32S_STA_MQTTClient_Test_SA_test(char * test_pSSID, char * test_pPassWord);//����wifi    STA 


#endif


