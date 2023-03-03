#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "secret.h"

char * endpoint = "https://ecse-three-led-api-v2.onrender.com/api/state";

const int ledPinNum1 = 12;
const int ledPinNum2 = 14;
const int ledPinNum3 = 27;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPinNum1, OUTPUT);
  pinMode(ledPinNum2, OUTPUT);
  pinMode(ledPinNum3, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASS); //these should be stored in secret.h and .getignore to hide from public
  
  Serial.println("Connecting");
  while (WiFi.status()!= WL_CONNECTED){
    delay (500);
    Serial.print(".");
  }
  Serial.print("");
  Serial.print("connected to WiFi network with IP Address: ");
  Serial.println (WiFi.localIP());
}



void loop() {
  //this check for the internet conectivity status
  if (WiFi.status()== WL_CONNECTED){
    HTTPClient http;

    String http_response;
    http.begin(endpoint);   //starts the connection to the server
    StaticJsonDocument<1024> doc; //create so we can put thing in this


    int httpResponseCode = http.GET(); //This is to do a get request
                                      //this code return an integer (status code)
    
    if (httpResponseCode > 0){
      Serial.print("HTTP Response Code:  ");
      Serial.println(httpResponseCode);

      Serial.print("Response from server: ");
      http_response = http.getString(); //this is getting a response from the server
      Serial.println(http_response);
    }
    else {
      Serial.print("Error code:  ");
      Serial.print(httpResponseCode);
    }
    //free resourses
    http.end();
  }
  else{
    return;
  }
}