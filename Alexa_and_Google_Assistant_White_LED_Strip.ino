//************************Written by Sid for Sid's E Classroom*****************************
//**********************https://www.youtube.com/c/SidsEClassroom***************************
//*************************https://github.com/shivasiddharth*******************************
//*************************Do not modify or remove this part*******************************
//************If you are modifying or re-using the code, credit the the author*************

#include <Arduino.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#include "fauxmoESP.h"
#include <ArduinoJson.h>



fauxmoESP fauxmo;

// On a Trinket or Gemma we suggest changing this to 1:
//Pin is set for Wemos. If using any other board, change it accordingly.
#define LED_PIN D6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 12

// Declare NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

//EEPROM address definition
#define Start_Address 0
#define Bri_Address Start_Address + sizeof(int)

//Firebase Database URL and KEY
#define FIREBASE_DATABASE_URL "ENTER YOUR DATABASE URL HERE"
#define FIREBASE_KEY "ENTER YOUR FIREBASE KEY HERE"

//Set the ID to the device id used in the index.json file
static const String STRMDEVID =  "2";

//Variables for brightness and state
bool onstate;
int bri;
bool alexachange;

//Set the light name to your desired value
#define LIGHTNAME  "Corridor Light"

void setup() {

  Serial.begin(115200);
  EEPROM.begin(256);
  EEPROM.get(Bri_Address, bri);
  strip.begin();
  strip.fill(0xFFFFFF);
  strip.setBrightness(bri);
  strip.show();
  Serial.println("Current value: " + String(bri));

  //WiFi Manager
  WiFiManager wifiManager;
  wifiManager.autoConnect();
  Serial.println("Connected..");
  // By default, fauxmoESP creates it's own webserver on the defined port
  // The TCP port must be 80 for gen3 devices (default is 1901)
  // This has to be done before the call to enable()
  fauxmo.createServer(true); // not needed, this is the default value
  fauxmo.setPort(80); // This is required for gen3 devices

  // You have to call enable(true) once you have a WiFi connection
  // You can enable or disable the library at any moment
  // Disabling it will prevent the devices from being discovered and switched
  fauxmo.enable(true);

  //Replace the following light name with a desired name of yours
  fauxmo.addDevice("Simulated Light");

  //Firebase Declaration
  Firebase.begin(FIREBASE_DATABASE_URL, FIREBASE_KEY);
  Firebase.stream(STRMDEVID);

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {

    // Callback when a command from Alexa is received.
    // You can use device_id or device_name to choose the element to perform an action onto (relay, LED,...)
    // State is a boolean (ON/OFF) and value a number from 0 to 255 (if you say "set kitchen light to 50%" you will receive a 128 here).
    // Just remember not to delay too much here, this is a callback, exit as soon as possible.
    // If you have to do something more involved here set a flag and process it in your main loop.
    // Checking for device_id is simpler if you are certain about the order they are loaded and it does not change.
    // Otherwise comparing the device_name is safer.

    if (strcmp(device_name, LIGHTNAME) == 0) {
      if (state == 0) {
        onstate = false;
        alexachange = true;
      } else if (state == 1) {
        onstate = true;
        alexachange = true;
        bri =  round((value * 100.0) / 255);
      }
      Serial.println(state);
      Serial.println(value);
      Serial.println(bri);
    }
  });
}


void loop() {

  if (alexachange == true) {
    Firebase.setInt("/" + STRMDEVID + "/Brightness/brightness", bri);
    Firebase.setBool("/" + STRMDEVID + "/OnOff/on", onstate);
    alexachange = false;
    delay(1000);
  }

  //Check Firebase connection
  if (Firebase.failed()) {
    Serial.println("Streaming Error");
    Serial.println(Firebase.error());
  }

  if (Firebase.available()) {
    FirebaseObject event = Firebase.readEvent();
    String eventType = event.getString("type");
    eventType.toLowerCase();
    Serial.println(eventType);
    String path = event.getString("path");
    Serial.println(path);

    if (eventType == "patch" || eventType == "put" || eventType == "type") {
      if (path == "/Brightness" || path == "/Brightness/brightness") {
        int bright = Firebase.getInt("/" + STRMDEVID + "/Brightness/brightness");
        strip.setBrightness(bright);
        strip.show();
        bri = bright;
        EEPROM.put(Bri_Address, bri);
        EEPROM.commit();
        EEPROM.end();
        Serial.println(bri);
      }
      else if (path == "/OnOff" || path == "/OnOff/on") {
        bool lightstatus = Firebase.getBool("/" + STRMDEVID + "/OnOff/on");
        if (lightstatus == 0) {
          strip.fill();
          strip.show();
        } else if (lightstatus == 1) {
          EEPROM.get(Bri_Address, bri);
          strip.fill(0xFFFFFF);
          strip.setBrightness(bri);
          strip.show();
        }
        Serial.println(lightstatus);
      }
    }
  }
  fauxmo.handle();
  static unsigned long last = millis();
  if (millis() - last > 5000) {
    last = millis();
    Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
  }
}


