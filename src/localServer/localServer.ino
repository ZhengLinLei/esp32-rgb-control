//
// Please install the ESPAsyncWebServer Library before compiling the project.
// You can use the .zip in this repository or just donwload it in: https://github.com/me-no-dev/ESPAsyncWebServer/tree/master
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
  // #include "../libraries/AsyncTCP"
  #include <AsyncTCP.h>
#elif defined(ESP8266)
  // #include "../libraries/ESP8266WiFi"
  #include <ESP8266WiFi.h>
  // #include "../libraries/ESPAsyncTCP"
  #include <ESPAsyncTCP.h>
#endif
// #include "../libraries/ESPAsyncWebServer"
#include <ESPAsyncWebServer.h>
#include "index.h"

// Initializate the server
AsyncWebServer server(80);

// Setup own Router AP connection
const char* ssid = "********";
const char* password = "********";

const char* PARAM_NAME = "range";
const char* PATH[] = {
  "/r",
  "/g",
  "/b"
};


// ==== RGB LED VARIABLE ====
int RGB_LED[] = {
  // Red
  19,
  // Green
  18,
  // Blue
  4
};

int RGB_COLOR[] = {
  0,  // Red
  0,  // Green
  0   // Blue
};



// === Set Color ===
void setColor(byte r, byte g, byte b) {
  ledcWrite(0, 255 - r);  //Common anode LED, low level to turn on the led. ledcWrite(chns[1], 255 - g);
  ledcWrite(1, 255 - g);
  ledcWrite(2, 255 - b);
}

void setup() {
    // Setup serial connection
    Serial.begin(115200);

    // Wifi connection
    WiFi.mode(WIFI_STA);
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
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());


    // === Set the Server ===

    // Serve the main page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", getIndex(WiFi.localIP().toString(), RGB_COLOR[0], RGB_COLOR[1], RGB_COLOR[2]));
    });

    // Get route /{r,g,b}/?range=<INT>
    for(int i = 0; i < 3; i++) {
      // Set LED part
      ledcSetup(i, 1000, 8);
      ledcAttachPin(RGB_LED[i], i);

      // Set LED path
      server.on(PATH[i], HTTP_GET, [&, i](AsyncWebServerRequest *request) {

          String range;
          if (request->hasParam(PARAM_NAME)) {
              range = request->getParam(PARAM_NAME)->value();
          } else {
              range = "255";
          }

          // Get num
          RGB_COLOR[i] = atoi(range.c_str());

          // Set color
          setColor(RGB_COLOR[0], RGB_COLOR[1], RGB_COLOR[2]);

          // Print
          Serial.print("Request: ");
          Serial.print(RGB_COLOR[0]);
          Serial.print(" ");
          Serial.print(RGB_COLOR[1]);
          Serial.print(" ");
          Serial.print(RGB_COLOR[2]);
          Serial.println("\n----");

          // Return request
          request->send(200, "text/plain", range);
      });
    }

    // Not Found
    server.onNotFound(notFound);

    server.begin();

    // Set color
    setColor(RGB_COLOR[0], RGB_COLOR[1], RGB_COLOR[2]);
}

void loop() {
  // Nothing to loop
  // int r = random(0, 256);
  // int g = random(0, 256);
  // int b = random(0, 256);

  // setColor(r, g, b);
  // delay(2000);
}