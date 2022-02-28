#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>


#define wifiName "POCO F3"
#define wifiPassword "Hassan112233@"
#define serverIP "192.168.150.223:5000"

const int RSSI_MAX = -50; // define maximum strength of signal in dBm
const int RSSI_MIN = -100; // define minimum strength of signal in dBm

String saved_networks[] = {"STUDBME1", "STUDBME2", "POCO F3", "SBME_STAFF", "CMP_LAB4", "CMP_LAB2"};
String scanned_ssids[6];
int rssi_values[6];

int w_len = sizeof(saved_networks) / sizeof(saved_networks[0]);
int s_len = sizeof(scanned_ssids) / sizeof(scanned_ssids[0]);
int s_index = 0;          // index for scanned_ssids
int w_index = 0;          // index for saved_networks
int n = 0;                // number of scanned networks


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
  //  scanNetwork("STUDBME2", "CMP_LAP2", "CMP_LAP4", "soher", "dodo", "adham");

  n = WiFi.scanNetworks();
  saveValues();


  String json = " ";
  
  for (int i = 0; i < 6; i++)
  {
//    Serial.print(scanned_ssids[i]);
//    Serial.print(" : ");
    Serial.print(rssi_values[i]);
    Serial.print(";");
    
//    json = toJSON(scanned_ssids[i], rssi_values[i]);
//    postValues(json);
  }
  Serial.println("0");
  Serial.println(" ");

  
  
  //  scanNetwork("STUDBME1", "STUDBME2", "POCO F3", "SBME_STAFF", "CMP_LAB4", "CMP_LAB2");
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

      if (WiFi.SSID(i) == name1 || WiFi.SSID(i) == name2 || WiFi.SSID(i) == name3 || WiFi.SSID(i) == name4 || WiFi.SSID(i) == name5 || WiFi.SSID(i) == name6 ) {
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
  http.begin(ourClient, "http://"  serverIP  "/saveReadings"); //Specify request destination
  http.addHeader("Content-Type", "application/json"); //Specify content-type header
  int httpCode = http.POST(json); //Send the request
  String payload = http.getString(); //Get the response payload
  Serial.println(payload);
  return httpCode;
}

String toJSON(String Name, float value) {
  String strength = String(value);
  return String("{\"SSID\": ") + "\"" + Name + "\"" + ", \"Strength\": " + strength + "}";
}

int dBmtoPercentage(int dBm)
{
  int quality;
  if (dBm <= RSSI_MIN)
  {
    quality = 0;
  }
  else if (dBm >= RSSI_MAX)
  {
    quality = 100;
  }
  else
  {
    quality = 2 * (dBm + 100);
  }

  return quality;
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
