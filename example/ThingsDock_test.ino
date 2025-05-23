#include "thingsdock.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";
const char* projectId = "PROJECT_ID";
const char* displayWidgetLabel = "LABEL_NAME";  
const char* sensorWidgetLabel = "LABEL_NAME";   
const char* switchWidgetLabel = "LABEL_NAME";   
const char* authToken = "AUTH_TOKEN";

ThingsDock thingsdock;
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int sensorPin = 0;   
const int ledPin = LED_BUILTIN; 
unsigned long lastPublishTime = 0;
const unsigned long publishInterval = 5000; 
String currentMessage = "";
unsigned long lastScrollTime = 0;
const unsigned long scrollSpeed = 500;  
int scrollIndex = 0;
void callback(char* topic, uint8_t* payload, unsigned int length) {
    String message = "";
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
        message += (char)payload[i];
    }
    Serial.println();
    if (String(topic).endsWith(displayWidgetLabel)) {
        currentMessage = message; 
        scrollIndex = 0;           
        lcd.clear();
    } else if (String(topic).endsWith(switchWidgetLabel)) {
        if (message == "1") {
            digitalWrite(ledPin, HIGH);
            Serial.println("LED ON");
        } else {
            digitalWrite(ledPin, LOW);
            Serial.println("LED OFF");
        }
    }
}

void displayScrollingText() {
    if (currentMessage.length() <= 16) {

        lcd.setCursor(0, 0);
        lcd.print(currentMessage);
    } else {
     
        if (millis() - lastScrollTime >= scrollSpeed) {
            lastScrollTime = millis();
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(currentMessage.substring(scrollIndex, scrollIndex + 16)); 

            scrollIndex++;
            if (scrollIndex > currentMessage.length()) {
                scrollIndex = 0;
            }
        }
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(sensorPin, INPUT);
    pinMode(ledPin, OUTPUT); 
    delay(1000);

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Waiting for data");
thingsdock.begin(ssid,password, authToken);
    thingsdock.setCallback(callback);
    delay(2000);
    thingsdock.recieve(projectId, displayWidgetLabel,authToken);  
    thingsdock.recieve(projectId, switchWidgetLabel,authToken);   
}

void loop() {
    thingsdock.loop(projectId, switchWidgetLabel,authToken); 
    displayScrollingText();
    if (millis() - lastPublishTime >= publishInterval) {
        lastPublishTime = millis();

        int sensorValue =  random(300, 700); 
        String sensorData = String(sensorValue);

        Serial.print("Publishing sensor data: ");
        Serial.println(sensorData);

        thingsdock.send(projectId, sensorWidgetLabel, sensorData.c_str(),authToken);
    }
}