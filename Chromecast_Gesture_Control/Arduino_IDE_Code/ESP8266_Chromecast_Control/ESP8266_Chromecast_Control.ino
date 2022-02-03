//**********************Putogether by Sid for Sid's E Classroom****************************
//**********************https://www.youtube.com/c/SidsEClassroom***************************
//*************************https://github.com/shivasiddharth*******************************
//*************************Do not modify or remove this part*******************************
//************If you are modifying or re-using the code, credit the the author*************

//*****************************************************************************************
// *********************************Libraries Used*****************************************
// ArduinoJson                : version=6.18.5
// Arduino_JSON               : version=0.1.0
// Modified Sparkfun APDS9960 : Zip file in Git
// Modified ArduCastControl   : Zip file in Git
// SnappyProto                : version=0.1.2
//*****************************************************************************************

#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include <ArduinoOTA.h>
#include "ArduCastControl.h"

// Pins on wemos D1 mini
#define APDS9960_SDA    4      //GPIO4 (D2)
#define APDS9960_SCL    5      //GPIO5 (D1)
// Constants
const byte APDS9960_INT  = 12; //GPIO12 (D6)
#define STATUS_LED 13          //GPIO13 (D7)

// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
volatile bool isr_flag = 0;

//Interrupt callback function in IRAM
void ICACHE_RAM_ATTR interruptRoutine ();

#define CHROMECASTIP "ENTER YOUR CHROMECAST's IP HERE"

const char* ssid = "WiFI SSID";
const char* password = "WIFi Password";

ArduCastControl cc = ArduCastControl();

void setup() {

  //Start I2C with pins defined above
  Wire.begin(APDS9960_SDA, APDS9960_SCL);

  // Set interrupt pin as input
  pinMode(digitalPinToInterrupt(APDS9960_INT), INPUT);
  pinMode(STATUS_LED, OUTPUT);

  // Initialize Serial port
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  delay(1000);
  Serial.print("\nConnected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  ArduinoOTA.setHostname ("chromecastremote");
  ArduinoOTA.begin();
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("Chromecast----Gesture Controller"));
  Serial.println(F("--------------------------------"));

  // Initialize interrupt service routine
  attachInterrupt(digitalPinToInterrupt(APDS9960_INT), interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
}

uint32_t lastUpdated = 0;
uint32_t updatePeriod = 5000;

uint32_t bLastUpdated = 0;
uint32_t bUpdatePeriod = 25;

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(F("WiFI disconnected....."));
    digitalWrite(STATUS_LED,  !digitalRead(STATUS_LED));
    delay(1000);
    
  }
  else if (WiFi.status() == WL_CONNECTED) {
    ArduinoOTA.handle();
    //wait for 5s to boot - this is useful in case of a bootloop to keep OTA running
    if ( millis() < 10000 )
      return;

    if ( millis() - lastUpdated > updatePeriod ) {
      if ( cc.getConnection() != WAIT_FOR_RESPONSE ) {
        cc.dumpStatus();
      }
      int st;

      if ( cc.getConnection() == DISCONNECTED ) {
        Serial.print("Connecting...");
        st = cc.connect(CHROMECASTIP);
        Serial.println(st);
      } else {
        //at this point, cc.volume and cc.isMuted should be valid
        connection_t c = cc.loop();
        if ( c == WAIT_FOR_RESPONSE || c == CONNECT_TO_APPLICATION ) {
          updatePeriod = 50;
        } else if ( c == APPLICATION_RUNNING ) {
          updatePeriod = 500;
          //at this point, all public fields describing the casting
          //(e.g. cc.artist, cc.title) should be valid
        } else {
          updatePeriod = 5000;
        }
      }
      lastUpdated = millis();
      digitalWrite(STATUS_LED,  !digitalRead(STATUS_LED));
    }
    if ( millis() - bLastUpdated > bUpdatePeriod && cc.getConnection() == APPLICATION_RUNNING ) {
      if ( isr_flag == 1 ) {
        detachInterrupt(digitalPinToInterrupt(APDS9960_INT));
        handleGesture();
        isr_flag = 0;
        attachInterrupt(digitalPinToInterrupt(APDS9960_INT), interruptRoutine, FALLING);
      }
      digitalWrite(STATUS_LED,  !digitalRead(STATUS_LED));
      bLastUpdated = millis();
    }
  }
}

void interruptRoutine() {
  isr_flag = 1;
}

void handleGesture() {
  if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        cc.setVolume(true, 0.1);
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        cc.setVolume(true, -0.1);        
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        cc.seek(true, -10);
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        cc.seek(true, 10);
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        cc.setMute(true, true);
        break;
      case DIR_FAR:
        Serial.println("FAR");
        cc.pause(true);
        break;
      default:
        Serial.println("NONE");
    }
  }
}
