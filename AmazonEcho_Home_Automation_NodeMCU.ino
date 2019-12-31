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

#define WIFI_SSID "**********"//change your Wifi name
#define WIFI_PASS "*********"//Change your Wifi Password
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

    // By default, fauxmoESP creates it's own webserver on the defined port
    // The TCP port must be 80 for gen3 devices (default is 1901)
    // This has to be done before the call to enable()
    fauxmo.createServer(true); // not needed, this is the default value
    fauxmo.setPort(80); // This is required for gen3 devices

    // You have to call enable(true) once you have a WiFi connection
    // You can enable or disable the library at any moment
    // Disabling it will prevent the devices from being discovered and switched
    fauxmo.enable(true);

    // Device Names for Simulated Wemo switches
    fauxmo.addDevice("Living Room Lights");
    fauxmo.addDevice("Kitchen Lights");
    fauxmo.addDevice("Bedroom Lights");


    // -----------------------------------------------------------------------------
    // Device Callback
    // -----------------------------------------------------------------------------

    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {

        // Callback when a command from Alexa is received.
        // You can use device_id or device_name to choose the element to perform an action onto (relay, LED,...)
        // State is a boolean (ON/OFF) and value a number from 0 to 255 (if you say "set kitchen light to 50%" you will receive a 128 here).
        // Just remember not to delay too much here, this is a callback, exit as soon as possible.
        // If you have to do something more involved here set a flag and process it in your main loop.

        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

        // Checking for device_id is simpler if you are certain about the order they are loaded and it does not change.
        // Otherwise comparing the device_name is safer.

        if (strcmp(device_name, "Living Room Lights")==0) {
            digitalWrite(Living, state ? HIGH : LOW);
        } else if (strcmp(device_name, "Kitchen Lights")==0) {
            digitalWrite(Kitchen, state ? HIGH : LOW);
        } else if (strcmp(device_name, "Bedroom Lights")==0) {
            digitalWrite(Bedroom, state ? HIGH : LOW);
        }
    });
}

void loop() {
  fauxmo.handle();
  static unsigned long last = millis();
  if (millis() - last > 5000) {
        last = millis();
        Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
  }
}
