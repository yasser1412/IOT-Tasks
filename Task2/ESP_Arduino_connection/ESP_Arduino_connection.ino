#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>

String username = "POCO F3";
String password = "Hassan112233@";
String json = " ";
String response = "asl ha2olk";

void setup() {
  Serial.begin(9600); /* begin serial for debug */
  Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */

  WiFi.begin(username, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");

  json = toJSON();
}
void loop() {
  //  postValues(json);
  response = getValues();
  Serial.print(response);
  if (response == "1") {
    Serial.print("feha l a5feha");

  } else {
    Wire.beginTransmission(8); /* begin with device address 8 */
    Wire.write(response.c_str());  /* sends hello string */
    Wire.endTransmission();    /* stop transmitting */

    Wire.requestFrom(8, 50000); /* request & read data of size 20 from slave */
    while (Wire.available()) {
      char c = Wire.read();
      Serial.print(c);
    }
    Serial.println();
    delay(1000);
  }
}

int postValues(String json) {
  WiFiClient ourClient;
  HTTPClient http; //Declare object of class HTTPClient
  http.begin(ourClient, "http://192.168.164.126:5000/alo"); //Specify request destination
  http.addHeader("Content-Type", "application/json"); //Specify content-type header
  int httpCode = http.POST(json);//Send the request
  Serial.println(json);
  String payload = http.getString(); //Get the response payload
  Serial.println(payload);
  Serial.println(httpCode);
  return httpCode;
}

String getValues() {
  WiFiClient ourClient;
  HTTPClient http; //Declare object of class HTTPClient
  http.begin(ourClient, "http://192.168.164.126:5000/alo"); //Specify request destination
  http.addHeader("Content-Type", "application/json"); //Specify content-type header
  //Serial.print(json);
  int httpCode = http.GET(); //Send the request
  String payload = http.getString(); //Get the response payload
  Serial.println(payload);
  return payload;
}

String toJSON() {
  return String("{\"input\": ") + "[" + "1" + "]}";
}
