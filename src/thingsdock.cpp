#include "thingsdock.h"
#include "config.h"  // Include the config file
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
static const char ca_cert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh
MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3
d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD
QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT
MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j
b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG
9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB
CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97
nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt
43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P
T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4
gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO
BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR
TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw
DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr
hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg
06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF
PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls
YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk
CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=
-----END CERTIFICATE-----
)EOF";
static const char ca_cert1[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIICnzCCAiWgAwIBAgIQf/MZd5csIkp2FV0TttaF4zAKBggqhkjOPQQDAzBHMQsw
CQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzEU
MBIGA1UEAxMLR1RTIFJvb3QgUjQwHhcNMjMxMjEzMDkwMDAwWhcNMjkwMjIwMTQw
MDAwWjA7MQswCQYDVQQGEwJVUzEeMBwGA1UEChMVR29vZ2xlIFRydXN0IFNlcnZp
Y2VzMQwwCgYDVQQDEwNXRTEwWTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAARvzTr+
Z1dHTCEDhUDCR127WEcPQMFcF4XGGTfn1XzthkubgdnXGhOlCgP4mMTG6J7/EFmP
LCaY9eYmJbsPAvpWo4H+MIH7MA4GA1UdDwEB/wQEAwIBhjAdBgNVHSUEFjAUBggr
BgEFBQcDAQYIKwYBBQUHAwIwEgYDVR0TAQH/BAgwBgEB/wIBADAdBgNVHQ4EFgQU
kHeSNWfE/6jMqeZ72YB5e8yT+TgwHwYDVR0jBBgwFoAUgEzW63T/STaj1dj8tT7F
avCUHYwwNAYIKwYBBQUHAQEEKDAmMCQGCCsGAQUFBzAChhhodHRwOi8vaS5wa2ku
Z29vZy9yNC5jcnQwKwYDVR0fBCQwIjAgoB6gHIYaaHR0cDovL2MucGtpLmdvb2cv
ci9yNC5jcmwwEwYDVR0gBAwwCjAIBgZngQwBAgEwCgYIKoZIzj0EAwMDaAAwZQIx
AOcCq1HW90OVznX+0RGU1cxAQXomvtgM8zItPZCuFQ8jSBJSjz5keROv9aYsAm5V
sQIwJonMaAFi54mrfhfoFNZEfuNMSQ6/bIBiNLiyoX46FohQvKeIoJ99cx7sUkFN
7uJW
-----END CERTIFICATE-----
)EOF";
ThingsDock::ThingsDock() : _mqttClient(_wifiClient) {}
String getMqttEndpointFromConfig(const char* authToken) {
    HTTPClient http;
    WiFiClientSecure client;
client.setTrustAnchors(new BearSSL::X509List(ca_cert1));

    http.begin(client, "https://backen-58yt.onrender.com/config"); 
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", String("Bearer ") + authToken);
    
    int httpCode = http.GET();
    String response = http.getString();
    http.end();

    if (httpCode == 200) {
        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, response);
        if (!error) {
            return doc["mqtt_credentials_url"].as<String>();
        }
    }
    return "";
}
void ThingsDock::fetchMqttCredentials(const char* authToken) {
        String endpoint = getMqttEndpointFromConfig(authToken);
    if (endpoint == "") return;
    HTTPClient http;
WiFiClientSecure client;
client.setTrustAnchors(new BearSSL::X509List(ca_cert1));
http.begin(client, MQTT_CREDENTIALS_URL);
 // Allows HTTPS connection without certificates

    http.begin(client, endpoint);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", String("Bearer ") + authToken); 

    int httpCode = http.GET();
    String response = http.getString();
    http.end();


    if (httpCode == 200) {
        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, response);
   

        _mqttServer = doc["mqttServer"].as<String>();
        _mqttPort = doc["mqttPort"].as<int>();
        _mqttUser = doc["mqttUser"].as<String>();
        _mqttPassword = doc["mqttPassword"].as<String>();
    } 
}


void ThingsDock::begin(const char* ssid, const char* password, const char* authToken) {
    Serial.print("Connecting to Wi-Fi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected to Wi-Fi");

    syncTime();
    fetchMqttCredentials(authToken); 
    BearSSL::X509List* caCertList = new BearSSL::X509List(ca_cert);
    _wifiClient.setTrustAnchors(caCertList);

    _mqttClient.setServer(_mqttServer.c_str(), _mqttPort);
}
void ThingsDock::syncTime() {
    configTime(0, 0, "pool.ntp.org");
    Serial.print("Connecting with thingsdock");
    time_t now = time(nullptr);
    while (now < 8 * 3600 * 2) {
        delay(1000);
        Serial.print(".");
        now = time(nullptr);
    }
    Serial.println(" Connected to thingsdock :) .");
}

void ThingsDock::setCallback(void (*callback)(char*, uint8_t*, unsigned int)) {
    _mqttClient.setCallback(callback);
}

void ThingsDock::send(const char* projectId, const char* labelName, const char* payload,const char* authToken) { 
    if (!_mqttClient.connected()) {
        reconnect(projectId, labelName,authToken);
    }

    String topic = "mqtt-subscription-mqttjs_" + String(projectId) + "_" + String(labelName) + "_qos1";
    
    if (_mqttClient.publish(topic.c_str(), payload)) {
      
        Serial.print("Message send  ");
        Serial.println(payload);
    } else {
        Serial.println("Publishing failed!");
    }
}

void ThingsDock::recieve(const char* projectId, const char* labelName,const char* authToken) {    
    if (!_mqttClient.connected()) {
        reconnect(projectId, labelName,authToken);
    }

    String topic = "null_" + String(projectId) + "_" + String(labelName);
    if (_mqttClient.subscribe(topic.c_str())) {
        Serial.print("All label have been connected  ");
    
    } else {
        Serial.println("Subscription failed!");
    }
}

void ThingsDock::loop(const char* projectId, const char* labelName,const char* authToken) {
    if (!_mqttClient.connected()) {
        reconnect(projectId, labelName,authToken);
    }
    _mqttClient.loop();
}
bool ThingsDock::validateTopic(const char* projectId, const char* labelName, const char* authToken) {
    HTTPClient http;
WiFiClientSecure client;
client.setTrustAnchors(new BearSSL::X509List(ca_cert1));
http.begin(client, MQTT_CREDENTIALS_URL);


    String payload = "{\"projectId\": \"" + String(projectId) + "\", \"labelName\": \"" + String(labelName) + "\"}";

    http.begin(client, VALIDATE_TOPIC_URL);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", String("Bearer ") + authToken);

    int httpCode = http.POST(payload);
    String response = http.getString();
    http.end();
    if (httpCode == 200) {
        Serial.println(" Validation Successful");
        return true; 
    } else {
        Serial.print("Validation Failed! HTTP Code: ");
        return false;
    }
}

void ThingsDock::reconnect(const char* projectId, const char* labelName, const char* authToken) {

    if (!validateTopic(projectId, labelName, authToken)) {
        Serial.println("Invalid Project ID or Label Name.");
        return;
    }

    static BearSSL::X509List caCertList(ca_cert);
    _wifiClient.setTrustAnchors(&caCertList);

    while (!_mqttClient.connected()) {
        Serial.print("Connecting to Server...");
        String clientId = "ESP8266Client-" + String(WiFi.macAddress());
        if (_mqttClient.connect(clientId.c_str(), _mqttUser.c_str(), _mqttPassword.c_str())) {
            Serial.println("Connected ");
        } else {
            Serial.print("Failed to connect, rc=");
            Serial.print(_mqttClient.state());
            Serial.println(" Retrying in 5 seconds...");
            delay(5000);
        }
    }
}
void ThingsDock::reconnect() {
    Serial.println("reconnect() called without parameters. Skipping MQTT connection.");
}
