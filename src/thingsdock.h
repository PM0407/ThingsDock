#ifndef THINGSDOCK_H
#define THINGSDOCK_H

#if defined(ESP8266)
    #include <ESP8266WiFi.h>
    #include <WiFiClientSecure.h>
    #include <BearSSLHelpers.h>
#elif defined(ESP32)
    #include <WiFi.h>
    #include <WiFiClientSecure.h>
#else
    #include <WiFiClientSecure.h>
#endif

#include <PubSubClient.h>
#include <time.h>

class ThingsDock {
public:
    ThingsDock();
    void begin(const char* ssid, const char* password, const char* authToken);
    void setCallback(void (*callback)(char*, uint8_t*, unsigned int));
    void recieve(const char* projectId, const char* labelName,const char* authToken); 
    void send(const char* projectId, const char* labelName, const char* payload,const char* authToken);
    bool validateTopic(const char* projectId, const char* labelName, const char* authToken);

    void loop(const char* projectId, const char* labelName,const char* authToken);  
    void fetchMqttCredentials(const char* authToken);

private:
void reconnect(const char* projectId, const char* labelName,const char* authToken); 

    void reconnect(); 
    void syncTime();  

    WiFiClientSecure _wifiClient;
    PubSubClient _mqttClient;
  String _mqttServer;
  int _mqttPort;
  String _mqttUser;
  String _mqttPassword;
};

#endif
