//
// Please install the HTTPClient Library before compiling the project.
// You can use the .zip in this repository or just donwload it in: https://github.com/espressif/arduino-esp32/blob/master/libraries/HTTPClient
// 
// Add all libraries in /src/libraries/*
// Open Arduino IDE:
// -------> Sketch
// -----------> Include library / Add .zip
// And select the .zip files

#include <Arduino.h>
#ifdef ESP32
  // #include "../libraries/WiFi"
  #include <WiFi.h>
  // #include "../libraries/HTTPClient"
  #include <HTTPClient.h>
#elif defined(ESP8266)
  // #include "../libraries/ESP8266WiFi"
  #include <ESP8266WiFi.h>
  // #include "../libraries/ESP8266HTTPClient"
  #include <ESP8266HTTPClient.h>
#endif
// Parse JSON
#include <ArduinoJson.h>

// Setup own Router AP connection
const char* ssid = "********";
const char* password = "********";

//Your Domain name with URL path or IP address with path
// String serverName = "http://domain.com:80/path/path/";
// You can use the example website
// ---> Go to http://led.ueuo.com to control
// ---> The ESP32 will request the information and update the led
String serverName = "http://led.ueuo.com:80/get/";

// ==== RGB LED VARIABLE ====
int RGB_LED[] = {
  // Red
  19,
  // Green
  18,
  // Blue
  4
};

/* =================
  The server return the data as: {"status":"ok", "r": 0, "g": 0, "b": 0}
=================== */

// The following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
// unsigned long timerDelay = 5000;
unsigned long timerDelay = 100; // 100ms


// === Set Color ===
void setColor(byte r, byte g, byte b) {
  ledcWrite(0, 255 - r);  //Common anode LED, low level to turn on the led. ledcWrite(chns[1], 255 - g);
  ledcWrite(1, 255 - g);
  ledcWrite(2, 255 - b);
}

void setup() {
    // Setup serial connection
  Serial.begin(115200); 

  for(int i = 0; i < 3; i++) {
    // Set LED part
    ledcSetup(i, 1000, 8);
    ledcAttachPin(RGB_LED[i], i);
  }

  // Wifi connection
  WiFi.begin(ssid, password);

  Serial.println("");
  Serial.println("-----------");
  Serial.println("Connecting...");

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");

    // Check if the ESP32 has connected to WIFI
    // if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    //   Serial.printf("WiFi Failed!\n");
    //   return;
    // }
  }

  Serial.println("");
  // Once connected release the IP
  Serial.println("------------");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("------------");
  Serial.println("Timer set to 100 ms (timerDelay variable), it will take 100ms before publishing the first reading.");
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      
      // If you need Node-RED/server authentication, insert user and password below
      //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode > 0) {
        Serial.println(serverPath);
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        Serial.println("------------");
        
        // JSON Parser
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);

        int r = doc["r"];
        int g = doc["g"];
        int b = doc["b"];

        // Set Color
        setColor(r, g, b);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}