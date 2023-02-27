#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "env.h"

char * endpoint = "https://ecse-three-led-api.onrender.com/api/state";
const char * WIFI_SSID = "Wokwi-GUEST";
const char * WIFI_PASS = "";

void setup() {
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(25, OUTPUT);

  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    
    String http_response;

    
    http.begin(endpoint);
    http.addHeader("X-API-KEY","Posey#3055");
    int httpResponseCode = http.GET();

    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        Serial.print("Response from server: ");
        http_response = http.getString();
        Serial.println(http_response);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();

      StaticJsonDocument<1024> doc;

      DeserializationError error = deserializeJson(doc, http_response);

      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }

    const char* user = doc["user"];
    const char* id = doc["_id"];
    bool light1 = doc["light1"];
    bool light2 = doc["light2"];
    bool light3 = doc["light3"];

    Serial.println("");

    Serial.print("LED 1: ");
    Serial.println(light1);

    Serial.print("LED 2: ");
    Serial.println(light2);

    Serial.print("LED 3: ");
    Serial.println(light3);
    Serial.println("");

    if (light1==1)
    {
      digitalWrite(27,HIGH);
    }
    else
    {
      digitalWrite(27,LOW);
    }

    if (light2==1)
    {
      digitalWrite(26,HIGH);
    }
    else
    {
      digitalWrite(26,LOW);
    }

    if (light3==1)
    {
      digitalWrite(25,HIGH);
    }
    else
    {
      digitalWrite(25,LOW);
    }

  }
  else {
    return;
  }
}