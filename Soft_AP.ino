// Load Wi-Fi library
#include <WiFi.h>
  //need to install this library
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>


// Replace with your network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;




void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
            
         
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

AsyncWebServer server2(87);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <img src="resume">
</body>  
</html>)rawliteral";


void setup() {
  Serial.begin(115200);
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
    // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}
  server2.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  //please note your image must alread be present in the local esp32 flash please use SPIFFS to upload the image
  server2.on("/resume", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/resume.jpg", "image/jpg");
  });
  // Start server
  server2.begin();
