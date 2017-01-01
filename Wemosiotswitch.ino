//https://www.youtube.com/c/SidsEClassroom

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

const char* ssid = "******";             //Set your wifi network name(ssid)
const char* password = "*******";                //Set your router password
 
int RelayPin = D1;          //Relay Shield is controlled by pin 1 (D1)
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
 
  pinMode(RelayPin, OUTPUT);
  digitalWrite(RelayPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

 
void loop() {
  
   
  // Check for an active client
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until client responds
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read client request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/Relay=ON") != -1) {
    digitalWrite(RelayPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/Relay=OFF") != -1){
    digitalWrite(RelayPin, LOW);
    value = LOW;
  }
 
 
 
  // Return the client response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Relay pin is now: ");
 
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/Relay=ON\">here</a> to turn the Relay ON<br>");
  client.println("Click <a href=\"/Relay=OFF\">here</a> to turn the Relay OFF<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
