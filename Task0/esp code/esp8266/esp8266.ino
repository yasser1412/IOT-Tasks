/****************************************
 * Include Libraries
 ****************************************/
#include <OneWire.h>
#include <DallasTemperature.h>
/****************************************
 * Define Constants
 ****************************************/
#define temperatureSensorPin D3
#define lineTrackerPin D0

float temperature = 0;
int lineTrackerValue = 0;

// Create instances of libraries of temperature sensor
OneWire ourWire(temperatureSensorPin);
DallasTemperature sensors(&ourWire);


/****************************************
 * Main Functions
 ****************************************/
void setup() {
  
  Serial.begin(9600); // Begin serial communication at baudrate 9600
  Serial.println("1111");
  
  pinMode(lineTrackerPin, INPUT);
  
  sensors.begin();
  }

  
void loop() {
  
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

  delay(1000);
  
 }
