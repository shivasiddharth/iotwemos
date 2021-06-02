
//***************************************************************************************
//              Code for Controlling Dotstar LEDs using Blynk App
//                    Written by Sid for Sid's E Classroom
//                    https://www.youtube.com/c/SidsEClassroom
//             All text above must be included in any redistribution.
//  If you find this useful and want to make a donation -> https://paypal.me/sidsclass
// ***************************************************************************************
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_DotStar.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "ENETR YOUR BLYNK KEY HERE";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ENTER YOUR WIFI SSID HERE";
char pass[] = "ENTER YOUR WIFI PASSWORD HERE";

//Pin and Strip declaration
#define NUMPIXELS 30
#define DATAPIN    D7
#define CLOCKPIN   D5
Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_GRB);

//Initialize all the colours to 0
int color_r = 0, color_g = 0, color_b = 0;
uint32_t color = 0xFF0000;

//Create three sliders or use the Horse RGB Widget and connect to Virtual Pin 1, 2 and 3 for Red, Blue and Green respectively
BLYNK_WRITE(1) {
  color_r = param.asInt();
}
BLYNK_WRITE(2) {
  color_g = param.asInt();
}
BLYNK_WRITE(3) {
  color_b = param.asInt();
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  strip.begin();
  strip.show();
}

void loop() {
  Blynk.run(); //Start Blynk
  //Set pixels to a colour
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
  //Get value from the color wheel
  color <<= 8;
  color |= color_r;
  color <<= 8;
  color |= color_g;
  color <<= 8;
  color |= color_b;
}
