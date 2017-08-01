#include "Arduino.h"

void config(SoftwareSerial& gprs){
  gprs.println("ATE0");
  Serial.print("Echo-off:");
  delay(100);
  gprs.read();
  while(gprs.available()){
    Serial.print(char(gprs.read()));
  }
  Serial.println("---");

  gprs.print("AT+QISRVC=1\r");
  Serial.print("Connection Type 1:");
  delay(100);
  gprs.read();
  while(gprs.available()){
    Serial.print(char(gprs.read()));
  }
  Serial.println("---");

  // gprs.print("AT+QIMUX?\r");
  // Serial.print("Mux:");
  // delay(100);
  // gprs.read();
  // while(gprs.available()){
  //   Serial.print(char(gprs.read()));
  // }
  // Serial.println("---");
}

void setAPM(SoftwareSerial& gprs, String apm){
  gprs.println("AT+QICSGP=1," +  apm);
  Serial.print("APM:");
  delay(100);
  gprs.read();
  while (gprs.available()) {
    Serial.print(char(gprs.read()));
  }
  Serial.println("---");
}

void httpSendData(SoftwareSerial& gprs, String ip, String port, JsonObject& req){

  Serial.println("--- Open TCP/IP ---");
  gprs.print("AT+QIOPEN=\"TCP\",\""+ ip + "\"," + port +"\r");
  delay(5000);
  while (gprs.available()) {
    Serial.print(char(gprs.read()));
  }
  Serial.println("--- --- ---");

  Serial.println("--- Send Data ---");
  gprs.print("AT+QISEND\r");//
  delay(1000);
  while (gprs.available()) {
    Serial.print(char(gprs.read()));
  }
  Serial.println("--- --- ---");

  String output;
  req.printTo(output);

  Serial.println("--- Write Data ---");
  gprs.println("POST /api/v1.6/devices/vmi/capas/values?token=zjLwMAMo3TzwgFqZ6vL2rCHmvPMhjl HTTP/1.1");
  gprs.println("Host: things.ubidots.com");
  gprs.println("Content-Type: application/json");
  gprs.print("Content-Length: ");gprs.println(output.length());
  gprs.println("");
  gprs.println(output);
  gprs.write(0x1A);
  delay(1000);
  while (gprs.available()) {
    Serial.print(char(gprs.read()));
  }
  Serial.println("--- --- ---");
  Serial.println("--- Waiting ---");
  delay(5000);
  while (gprs.available()) {
    Serial.print(char(gprs.read()));
  }

  Serial.println("--- Close TCP/IP ---");
  gprs.print("AT+QCLOSE\r");
  delay(100);
  while (gprs.available()) {
    Serial.print(char(gprs.read()));
  }
  Serial.println("--- --- ---");
}
