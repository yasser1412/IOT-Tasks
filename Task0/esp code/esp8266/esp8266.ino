/****************************************
   Include Libraries
 ****************************************/
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ArduinoJson.h>
/****************************************
   Define Constants
 ****************************************/
#define temperatureSensorPin D3
#define lineTrackerPin D0
#define serverIP "192.168.167.223:8000"

float temperature = 0;
int lineTrackerValue = 0;
String wifiName = "POCO F3";
String wifiPassword = "Hassan112233@";

// Create instances of libraries of temperature sensor
OneWire ourWire(temperatureSensorPin);
DallasTemperature sensors(&ourWire);

String jsonn = "";
/****************************************
   Main Functions
 ****************************************/
void setup() {

  Serial.begin(9600); // Begin serial communication at baudrate 9600

  pinMode(lineTrackerPin, INPUT);

  WiFi.begin(wifiName, wifiPassword);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");

  sensors.begin();
}


void loop() {

  if ((WiFi.status() == WL_CONNECTED)) {

    Serial.println("Connecteddd");
    WiFiClient client;
    HTTPClient http;

    Serial.println("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "http://" serverIP "/api/readings/"); //HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.println("[HTTP] POST...\n");
    // start connection and send HTTP header and body


    jsonn = toJSON("temp", temperature);

    Serial.println("This is json \n" + jsonn);
    int httpCode = http.POST(jsonn);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }




  // Send the command to get temperatures
  sensors.requestTemperatures();

  //print the temperature in Celsius
  Serial.print("Temperature: ");
  temperature = sensors.getTempCByIndex(0);
  Serial.println(temperature);

  //print line tracker value
  lineTrackerValue = digitalRead(lineTrackerPin);
  Serial.print("Line tracker: ");
  Serial.println(lineTrackerValue);

  Serial.print(" ");

  String tempName = "temp";
  String LTName = "LT";
  
  String tempJson = toJSON(tempName, temperature);
  
  delay(1000);
  
  String LTJson = toJSON(LTName, lineTrackerValue);
  
  int httpCode = postValues(tempJson);
  
  delay(1000);
  
  int httpCodee = postValues(LTJson);

  if (httpCode == 201) {
    Serial.println("POSTED: ");
    //Serial.println(json);
    delay(1000);
  } else {
    Serial.println("Fail. HTTP ");
    Serial.println(httpCode);
    Serial.println(WiFi.status());

  }

  delay(3000);

}

String toJSON(String Name, float value) {

  String sensorValue = String(value);
    return String("{\"sensor\": ") + "\"" + Name + "\"" + ", \"value\": " + sensorValue + "}";
}

int postValues(String json) {
  WiFiClient ourClient;
  HTTPClient http; //Declare object of class HTTPClient
  //Serial.print("http://" serverIP "/api/readings/");
  http.begin(ourClient, "http://" serverIP "/api/readings/"); //Specify request destination
  http.addHeader("Content-Type", "application/json"); //Specify content-type header
  //Serial.print(json);
  int httpCode = http.POST(json); //Send the request
  String payload = http.getString(); //Get the response payload
  Serial.println(payload);
  return httpCode;

  // Serial.print("HTTP Response: "); //Print HTTP return code
  // Serial.print(httpCode);
  // Serial.println(payload); //Print request response payload
}