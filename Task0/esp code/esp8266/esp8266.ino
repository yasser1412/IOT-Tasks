/****************************************
 * Include Libraries
 ****************************************/
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ArduinoJson.h>
/****************************************
 * Define Constants
 ****************************************/
#define temperatureSensorPin D3
#define lineTrackerPin D0
#define serverIP "192.168.1.3:8000"

float temperature = 0;
int lineTrackerValue = 0;
String wifiName = "Hassan";
String wifiPassword= "hassan87890"; 

// Create instances of libraries of temperature sensor
OneWire ourWire(temperatureSensorPin);
DallasTemperature sensors(&ourWire);

String jsonn ="";
/****************************************
 * Main Functions
 ****************************************/
void setup() {
  
  Serial.begin(9600); // Begin serial communication at baudrate 9600
  Serial.println("1111");
  
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

//    Serial.println("Enter the wifi name");  
//    while (Serial.available() == 0)   
//    { //Wait for user input  }  
//    wifiName = Serial.readString(); //Reading the Input string from Serial port.

//    Serial.println("Enter the wifi password");  
//    while (Serial.available() == 0)   
//    { //Wait for user input  }  
//    wifiPassword = Serial.readString(); //Reading the Input string from Serial port.


    
   // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {
    
    Serial.println("Connecteddd");
    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "http://" serverIP "/api/readings/"); //HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body

    
    jsonn = toJSON(temperature);

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

  String json = toJSON(temperature);
  int httpCode = postValues(json);

  if (httpCode == 201) {
    Serial.print("POSTED: ");
    Serial.println(json);
    delay(1000);
    } else {
    Serial.print("Fail. HTTP ");
    Serial.println(httpCode);
    Serial.println(WiFi.status());

    }

  delay(1000);
  
 }

 String toJSON(float temperature) {

    String temp = String(temperature);
    //String LT = String(lineTracker);
    return String("{\"sensor\": ") + "\"temp\" "+ ", \"value\": " + temp + "}"; 
}

int postValues(String json) {
WiFiClient ourClient;
HTTPClient http; //Declare object of class HTTPClient
//Serial.print("http://" serverIP "/api/readings/");
http.begin(ourClient, "http://" serverIP "/api/readings/"); //Specify request destination
//http.begin("0.0.0.0",3000,"/measures");
http.addHeader("Content-Type", "application/json"); //Specify content-type header
//http.addHeader("Accept", "application/json");
 Serial.print(json);
int httpCode = http.POST(json); //Send the request
String payload = http.getString(); //Get the response payload
Serial.print(payload);
return httpCode;

// Serial.print("HTTP Response: "); //Print HTTP return code
// Serial.print(httpCode);
// Serial.println(payload); //Print request response payload
}
