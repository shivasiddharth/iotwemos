//https://www.youtube.com/c/SidsEClassroom

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

const char* ssid = "Siddhy";             //Set your wifi network name(ssid)
const char* password = "Siddhy1990";                //Set your router password

int Device1 = D1;
int Device2 = D2;
int Device3 = D3;
WiFiServer server(80);

void setup() {
  Serial.begin(115200); //change according to your com port baud rate
  delay(10);

  //Declare device pins
  pinMode(Device1, OUTPUT);
  digitalWrite(Device1, LOW);
  pinMode(Device2, OUTPUT);
  digitalWrite(Device2, LOW);
  pinMode(Device3, OUTPUT);
  digitalWrite(Device3, LOW);


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
  while (!client.available()) {
    delay(1);
  }

  // Read client request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Check device request
  if (request.indexOf("/Device1=ON") != -1) {
    digitalWrite(Device1, HIGH);
  }
  if (request.indexOf("/Device1=OFF") != -1) {
    digitalWrite(Device1, LOW);
  }
  if (request.indexOf("/Device2=ON") != -1) {
    digitalWrite(Device2, HIGH);
  }
  if (request.indexOf("/Device2=OFF") != -1) {
    digitalWrite(Device2, LOW);
  }
  if (request.indexOf("/Device3=ON") != -1) {
    digitalWrite(Device3, HIGH);
  }
  if (request.indexOf("/Device3=OFF") != -1) {
    digitalWrite(Device3, LOW);
  }

  // Return the client response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  //HTML code for controling devices from browser
  client.println("<br><br>");
  client.println("Device 1: <a href=\"/Device1=ON\">ON</a> and <a href=\"/Device1=OFF\">OFF</a><br>");
  client.println("<br>");
  client.println("Device 2: <a href=\"/Device2=ON\">ON</a> and <a href=\"/Device2=OFF\">OFF</a><br>");
  client.println("<br>");
  client.println("Device 3: <a href=\"/Device3=ON\">ON</a> and <a href=\"/Device3=OFF\">OFF</a><br>");
  client.println("<br>");
  client.println("");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");

}
