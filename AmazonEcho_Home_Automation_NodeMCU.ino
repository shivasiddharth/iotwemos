 /**********************************************************************************
  * Code for controlling multiple devices connected to one NodeMCU using Amazon Echo
  * 
  * Written by Sid for Sid's E Classroom
  * 
  * https://www.youtube.com/c/SidsEClassroom
  *********************************************************************************/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"

#define WIFI_SSID "Siddhy"//change your Wifi name
#define WIFI_PASS "Siddhy1990"//Change your Wifi Password
#define SERIAL_BAUDRATE                 115200

fauxmoESP fauxmo;
//declare switching pins
//Change pins according to your NodeMCU pinouts
#define Kitchen D1
#define Bedroom D2
#define Living D3
// -----------------------------------------------------------------------------
// Wifi Setup
// -----------------------------------------------------------------------------

void wifiSetup() {

    // Set WIFI module to STA mode
    WiFi.mode(WIFI_STA);

    // Connect
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Wait
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();

    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}
// -----------------------------------------------------------------------------
// Device Callback
// -----------------------------------------------------------------------------
void callback(uint8_t device_id, const char * device_name, bool state) {
  Serial.print("Device "); Serial.print(device_name); 
  Serial.print(" state: ");
  if (state) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }
  //Switching action on detection of device name
  if ( (strcmp(device_name, "Kitchen Lights") == 0) ) {
    // adjust the relay immediately!
    if (state) {
      digitalWrite(Kitchen, HIGH);
    } else {
      digitalWrite(Kitchen, LOW);
    }
  }
  if ( (strcmp(device_name, "Bedroom Lights") == 0) ) {
    // adjust the relay immediately!
    if (state) {
      digitalWrite(Bedroom, HIGH);
    } else {
      digitalWrite(Bedroom, LOW);
    }
  }
  if ( (strcmp(device_name, "Living Room Lights") == 0) ) {
    // adjust the relay immediately!
    if (state) {
      digitalWrite(Living, HIGH);
    } else {
      digitalWrite(Living, LOW);
    }
  }
}

void setup() {
    //Initialize pins to Low on device start
    pinMode(Kitchen, OUTPUT);
    digitalWrite(Kitchen, LOW);
    pinMode(Bedroom, OUTPUT);
    digitalWrite(Bedroom, LOW);
    pinMode(Living, OUTPUT);
    digitalWrite(Living, LOW);
    
    // Init serial port and clean garbage
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println("FauxMo demo sketch");
    Serial.println("After connection, ask Alexa/Echo to 'turn <devicename> on' or 'off'");

    // Wifi
    wifiSetup();

    // Device Names for Simulated Wemo switches
    fauxmo.addDevice("Living Room Lights");
    fauxmo.addDevice("Kitchen Lights");
    fauxmo.addDevice("Bedroom Lights");
    fauxmo.onMessage(callback);
}

void loop() {
  fauxmo.handle();
}
