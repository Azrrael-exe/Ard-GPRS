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
  if(Serial.available() > 0){
   StaticJsonBuffer<200> jsonBuffer;
   String inp = Serial.readStringUntil('\n');
   JsonObject& req = jsonBuffer.parseObject(inp);

   String output;
   req.printTo(output);
   Serial.println(output);
   Serial.print(output.length());

   if(req.success()){
     httpSendData(M95, "50.23.124.68", "80", req);
   }
 }
}
