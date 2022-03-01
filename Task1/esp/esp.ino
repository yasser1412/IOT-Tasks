#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>

#define serverIP "192.168.150.223:5000"


String saved_networks[] = {"STUDBME1", "STUDBME2", "POCO F3", "Ammar's samsung", "CMP_LAB4", "CMP_LAB2"};
String scanned_ssids[6];
int rssi_values[6];

int w_len = sizeof(saved_networks) / sizeof(saved_networks[0]);
int s_len = sizeof(scanned_ssids) / sizeof(scanned_ssids[0]);
int s_index = 0;          // index for scanned_ssids
int w_index = 0;          // index for saved_networks
int n = 0;                // number of scanned networks

int arrayToPost[6];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  n = WiFi.scanNetworks();
  
  saveValues();

  String json = " ";
  
//  for (int i = 0; i < 6; i++)
//  {
////    Serial.print(scanned_ssids[i]);
////    Serial.print(" : ");
//    Serial.print(rssi_values[i]);
//    Serial.print(";");
//  }
//  Serial.println("2");
//  Serial.println(" ");

  json = toJSON(rssi_values);
//  postValues(json);
  Serial.println(json);
  
  delay(5000);
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
  http.begin(ourClient, "http://"  serverIP  "/saveReadings"); //Specify request destination
  http.addHeader("Content-Type", "application/json"); //Specify content-type header
  int httpCode = http.POST(json); //Send the request
  String payload = http.getString(); //Get the response payload
  Serial.println(payload);
  return httpCode;
}

String toJSON(int arr[]) { 
  return String("{\"value\": ") + "[" + arr[0] + "," + arr[1] + "," + arr[2] + "," + arr[3] + "," + arr[4] + "," + arr[5] + "]}";
}


void saveValues()
{
  // Save SSIDs and RSSIs to array
  for (int i = 0; i < n; ++i)
  {
    // Check if the ssid exists in the saved networks
    s_index = findElement(saved_networks, w_len, WiFi.SSID(i));
    if (s_index != -1)
    {
      scanned_ssids[s_index] = WiFi.SSID(i);
      rssi_values[s_index] = WiFi.RSSI(i);
      rssi_values[s_index] = rssi_values[s_index] + 101;

    }
  }

  // Check if there's a network in saved and not scanned (Error while scanning)
  // So put it's RSSI = 0 (Take average later)
  for (int i = 0; i < w_len; i++)
  {
    w_index = findElement(scanned_ssids, w_len, saved_networks[i]);
    // If it is saved network and not scanned -> put rssi = 0
    if (w_index == -1)
    {
      scanned_ssids[i] = saved_networks[i];
      rssi_values[i] = 0;
    }
  }


}

int findElement(String arr[], int n, String val)
{
  int indx = -1;

  for (int i = 0; i < n; i++)
  {
    // if found -> 0 -> !0 = 1 = True
    if (val == String(arr[i]))
    {
      indx = i;
      break;
    }
  }
  return indx;
}
