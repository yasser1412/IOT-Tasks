#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>


#define wifiName "Hassan"
#define wifiPassword "hassan87890"
#define serverIP "..."
const int RSSI_MAX =-50;// define maximum strength of signal in dBm
const int RSSI_MIN =-100;// define minimum strength of signal in dBm


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(wifiName, wifiPassword);
  
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  scanNetwork("Adel", "Hassan", "Ali", "soher", "dodo", "adham");

  delay(5000);
}


void scanNetwork(String name1, String name2, String name3, String name4, String name5, String name6) {
//  WiFi.disconnect();
  WiFi.scanNetworks();
  Serial.print("Scan start ... ");
  int n = WiFi.scanNetworks();
  if ( n > 0 )
  {
    Serial.print(n);
    Serial.println(" network(s) found");
    for (int i = 0; i < n; i++)
    {
//      Serial.print("SSID: ");
//      Serial.println(WiFi.SSID(i));

      if (WiFi.SSID(i) == name1 || WiFi.SSID(i) == name2 || WiFi.SSID(i) == name3 || WiFi.SSID(i) == name4 || WiFi.SSID(i) == name5 || WiFi.SSID(i) == name6 ){
        Serial.print("SSID: ");
        Serial.println(WiFi.SSID(i));

        Serial.print("Signal Strength: ");
        Serial.println(dBmtoPercentage(WiFi.RSSI(i)));
      }
      
    }
    Serial.println();
  }
}

String getValue() {
  WiFiClient ourClient;
  HTTPClient http; //Declare object of class HTTPClient
  http.begin(ourClient, "http://"  serverIP  "/api/toggle/"); //Specify request destination
  http.addHeader("Content-Type", "application/json"); //Specify content-type header
  int httpCode = http.GET(); //Send the request
  String payload = http.getString(); //Get the response payload
  Serial.println(payload);
  return payload;
}

int postValues(String json) {
  WiFiClient ourClient;
  HTTPClient http; //Declare object of class HTTPClient
  http.begin(ourClient, "http://"  serverIP  "/api/readings/"); //Specify request destination
  http.addHeader("Content-Type", "application/json"); //Specify content-type header
  int httpCode = http.POST(json); //Send the request
  String payload = http.getString(); //Get the response payload
  Serial.println(payload);
  return httpCode;
}

String toJSON(String Name, float value) {
  String sensorValue = String(value);
    return String("{\"sensor\": ") + "\"" + Name + "\"" + ", \"value\": " + sensorValue + "}";
}

int dBmtoPercentage(int dBm)
{
  int quality;
    if(dBm <= RSSI_MIN)
    {
        quality = 0;
    }
    else if(dBm >= RSSI_MAX)
    {  
        quality = 100;
    }
    else
    {
        quality = 2 * (dBm + 100);
   }

     return quality;
}
