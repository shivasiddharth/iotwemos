/**
   The MIT License (MIT)

   Copyright (c) 2018 by ThingPulse, Daniel Eichhorn
   Copyright (c) 2018 by Fabrice Weinberg

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.

   ThingPulse invests considerable time and money to develop these open source libraries.
   Please support us by buying our products (and not the clones) from
   https://thingpulse.com

*/

// Include the correct display library
// For a connection via I2C using Wire include
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
// #include "SH1106Wire.h"
#include "SSD1306.h"

// For a connection via SPI include
// #include <SPI.h> // Only needed for Arduino 1.6.5 and earlier
// #include "SSD1306Spi.h"
// #include "SH1106SPi.h"

// Include the UI lib
#include "OLEDDisplayUi.h"

// Include custom images

#include "images.h"

#define ARDUINOJSON_USE_DOUBLE 1
#define ARDUINOJSON_USE_LONG_LONG 1
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


// Use the corresponding display class:

// Initialize the OLED display using SPI
// D5 -> CLK
// D7 -> MOSI (DOUT)
// D0 -> RES
// D2 -> DC
// D8 -> CS
// SSD1306Spi        display(D0, D2, D8);
// or
// SH1106Spi         display(D0, D2);

// Initialize the OLED display using i2c
// D2 -> SDA
// D1 -> SCL
// Initialize the OLED display using Wire library
SSD1306  display(0x3c, D2, D1);

OLEDDisplayUi ui     ( &display );

const char *host = "production.api.coindesk.com";
const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80
String Link = "/v2/tb/price/ticker?assets=BTC";

//SHA1 finger print of certificate use web browser to view and copy
const char fingerprint[] PROGMEM = "94 19 A7 32 1E 0A E6 2E 0A 2B 8D 74 0D 94 99 4B 43 B9 89 6A";

unsigned long lastTime = 0;
unsigned long timerDelay = 120000;
StaticJsonDocument<512> cryptoReadings;
//char sample_json[] = "{\"statusCode\": 200,\"message\": \"OK\",\"data\": {\"BTC\": {\"iso\": \"BTC\",\"name\":\"Bitcoin\",\"slug\": \"bitcoin\",\"change\":{\"percent\": 0.8120221253967227,\"value\": 378.210186},\"ohlc\":{\"o\": 46576.34,\"h\": 47535.7,\"l\": 45599.775339,\"c\": 46954.550186},\"circulatingSupply\": 18905243.7915621,\"marketCap\": 887687218389.4675,\"ts\": 1640052959000,\"src\": \"tb\"}}";

// Enter the WiFi credentials
char wifissid[] = "ENTER YOUR WIFI SSID HERE";
char wifipass[] = "ENTER YOUR WIFI PASSWORD HERE";

String crypto_currency_growth_rate = "";
String crypto_currency_value = "";
String crypto_currency_iso = "";
String crypto_currency_rate_direction = "";

void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  // draw an xbm image.
  // Please note that everything that should be transitioned
  // needs to be drawn relative to x and y

  display->drawXbm(x + (SCREEN_WIDTH - Currency_Logo_width) / 2, y + (SCREEN_HEIGHT - Currency_Logo_height) / 2, Currency_Logo_width, Currency_Logo_height, Currency_Logo_bits);
}

void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_24);
  display->drawString(x + (SCREEN_WIDTH) / 2, y + 5, crypto_currency_iso);
  if (crypto_currency_value != "") {
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->setFont(ArialMT_Plain_16);
    display->drawString(x + SCREEN_WIDTH / 2, y + 8 + SCREEN_HEIGHT / 2, crypto_currency_value);
  }
  else if (crypto_currency_value == "") {
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->setFont(ArialMT_Plain_10);
    display->drawString(x + SCREEN_WIDTH / 2, y + 8 + SCREEN_HEIGHT / 2, "Waiting for Values");
  }
}

void drawFrame3(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {

  if (crypto_currency_rate_direction == "UP") {
    // Upward Trend
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->setFont(ArialMT_Plain_24);
    display->drawString(x + SCREEN_WIDTH / 2, y + 5 + Arrow_Logo_width, crypto_currency_growth_rate);
    display->drawXbm(x + (SCREEN_WIDTH / 2) - (Arrow_Logo_width / 2) - Arrow_Logo_width, y + 5, Arrow_Logo_width, Arrow_Logo_height, Up_Arrow_bits);
    display->drawXbm(x + (SCREEN_WIDTH / 2) - (Arrow_Logo_width / 2), y + 5, Arrow_Logo_width, Arrow_Logo_height, Up_Arrow_bits);
    display->drawXbm(x + (SCREEN_WIDTH / 2) - (Arrow_Logo_width / 2) + Arrow_Logo_width, y + 5, Arrow_Logo_width, Arrow_Logo_height, Up_Arrow_bits);
  }
  else if (crypto_currency_rate_direction == "DOWN") {
    // Downward Trend
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->setFont(ArialMT_Plain_24);
    display->drawString(x + SCREEN_WIDTH / 2, y + 5, crypto_currency_growth_rate);
    display->drawXbm(x + (SCREEN_WIDTH / 2) - (Arrow_Logo_width / 2) - Arrow_Logo_width, y + 5 + Arrow_Logo_width, Arrow_Logo_width, Arrow_Logo_height, Down_Arrow_bits);
    display->drawXbm(x + (SCREEN_WIDTH / 2) - (Arrow_Logo_width / 2), y + 5 + Arrow_Logo_width, Arrow_Logo_width, Arrow_Logo_height, Down_Arrow_bits);
    display->drawXbm(x + (SCREEN_WIDTH / 2) - (Arrow_Logo_width / 2) + Arrow_Logo_width, y + 5 + Arrow_Logo_width, Arrow_Logo_width, Arrow_Logo_height, Down_Arrow_bits);
  }
  else if (crypto_currency_rate_direction == "") {
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->setFont(ArialMT_Plain_10);
    display->drawString(x + SCREEN_WIDTH / 2, y + 8 + SCREEN_HEIGHT / 2, "Waiting for Values");
  }

}

// This array keeps function pointers to all frames
// frames are the single views that slide in
FrameCallback frames[] = { drawFrame1, drawFrame2, drawFrame3 };

// Number of frames
int frameCount = 3;

void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // The ESP is capable of rendering 60fps in 80Mhz mode
  // but that won't give you much time for anything else
  // run it in 160Mhz mode or just set it to 30 fps
  ui.setTargetFPS(60);

  // Customize the active and inactive symbol
  ui.setActiveSymbol(activeSymbol);
  ui.setInactiveSymbol(inactiveSymbol);

  // You can change this to
  // TOP, LEFT, BOTTOM, RIGHT
  ui.setIndicatorPosition(LEFT);

  // Defines where the first frame is located in the bar.
  ui.setIndicatorDirection(LEFT_RIGHT);

  // You can change the transition that is used
  // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_UP, SLIDE_DOWN
  ui.setFrameAnimation(SLIDE_DOWN);

  // Add frames
  ui.setFrames(frames, frameCount);

  // Initialising the UI will init the display too.
  ui.init();

  //display.flipScreenVertically();

  // Set WiFi to Station Mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(10);

  // Connect to WiFi
  WiFi.begin(wifissid, wifipass);
  Serial.print("Connecting to WiFi...");
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_10);
  display.drawString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "Connecting to WiFi...");
  display.display();
  // Check if connected to WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print connection information
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_10);
  display.drawString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "Connected to " + String(wifissid));
  display.display();
  delay(3000);
  Serial.print("\nConnected to: ");
  Serial.println(wifissid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
}


void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_10);
    display.drawString(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "Connection lost");
    display.display();
    delay(1000);
  }
  else if (WiFi.status() == WL_CONNECTED) {
    int remainingTimeBudget = ui.update();
    if (remainingTimeBudget > 0) {
      // You can do some work here
      // Don't do stuff if you are below your
      // time budget.
      delay(remainingTimeBudget);
    }
    if ((millis() - lastTime) > timerDelay) {
      WiFiClientSecure httpsClient;
      httpsClient.setFingerprint(fingerprint);
      httpsClient.setTimeout(15000);
      delay(1000);
      int r = 0; //retry counter
      while ((!httpsClient.connect(host, httpsPort)) && (r < 30)) {
        delay(100);
        Serial.print(".");
        r++;
      }
      if (r == 30) {
        Serial.println("Connection failed");
      }
      else {
        Serial.println("Connected to CoinDesk");
      }
      httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +
                        "Host: " + host + "\r\n" +
                        "Connection: close\r\n\r\n");
      Serial.println("Requesting Crypto Values...........");
      while (httpsClient.connected()) {
        String line = httpsClient.readStringUntil('\n');
        if (line == "\r") {
          Serial.println("Crypto Values Received:");
          break;
        }
      }

      DeserializationError error = deserializeJson(cryptoReadings, httpsClient);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }

      JsonObject data_BTC = cryptoReadings["data"]["BTC"];

      const char* data_BTC_iso = data_BTC["iso"]; // "BTC"
      const char* data_BTC_name = data_BTC["name"]; // "Bitcoin"
      const char* data_BTC_slug = data_BTC["slug"]; // "bitcoin"

      double data_BTC_change_percent = data_BTC["change"]["percent"]; // 0.8120221253967227
      double data_BTC_change_value = data_BTC["change"]["value"]; // 378.210186

      JsonObject data_BTC_ohlc = data_BTC["ohlc"];
      float data_BTC_ohlc_o = data_BTC_ohlc["o"]; // 46576.34
      float data_BTC_ohlc_h = data_BTC_ohlc["h"]; // 47535.7
      double data_BTC_ohlc_l = data_BTC_ohlc["l"]; // 45599.775339
      double data_BTC_ohlc_c = data_BTC_ohlc["c"]; // 46954.550186

      double data_BTC_circulatingSupply = data_BTC["circulatingSupply"]; // 18905243.7915621
      double data_BTC_marketCap = data_BTC["marketCap"]; // 887687218389.4675
      long long data_BTC_ts = data_BTC["ts"]; // 1640052959000
      const char* data_BTC_src = data_BTC["src"]; // "tb"


      Serial.print("\n");
      Serial.print(data_BTC_iso);
      crypto_currency_iso = String(data_BTC_iso);
      Serial.print("\n");
      Serial.print(data_BTC_change_percent);
      crypto_currency_growth_rate = String(data_BTC_change_percent) + "%";
      if (String(data_BTC_change_percent).indexOf("-") != -1) {
        crypto_currency_rate_direction = "DOWN";
      }
      else if (String(data_BTC_change_percent).indexOf("-") == -1) {
        crypto_currency_rate_direction = "UP";
      }
      Serial.print("\n");
      Serial.print(data_BTC_ohlc_c);
      crypto_currency_value = "$" + String(data_BTC_ohlc_c);
      Serial.print("\n");
      lastTime = millis();
    }
  }
}
