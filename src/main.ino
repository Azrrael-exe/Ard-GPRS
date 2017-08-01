#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "http.h"

SoftwareSerial M95(2, 3);

void setup(){
  Serial.begin(9600);
  M95.begin(9600);
  config(M95);
}

void loop(){

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& req = jsonBuffer.createObject();
  req["value"] = analogRead(0);

  httpSendData(M95, "190.29.76.174", "8080", req);

  while (1) {
    /* code */
  }
}
