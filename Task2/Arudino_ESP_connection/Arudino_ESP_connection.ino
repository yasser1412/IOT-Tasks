//#include <Wire.h>
//
//char response[50];
//void setup() {
// Wire.begin(8);                /* join i2c bus with address 8 */
// Wire.onReceive(receiveEvent); /* register receive event */
// Wire.onRequest(requestEvent); /* register request event */
// Serial.begin(9600);           /* start serial for debug */
//
// pinMode(LED_BUILTIN, OUTPUT);
//}
//
//void loop() {
// delay(100);
//
// 
//}
//
//// function that executes whenever data is received from master
//void receiveEvent(int howMany) {
// while (0 <Wire.available()) {
//    for(int i = 0; i < 50; i++){
//      response[i] = Wire.read();
//    }
//    Serial.print(response);
////    char c = Wire.read();      /* receive byte as a character */
////    Serial.print(c);           /* print the character */
//  }
// Serial.println();             /* to newline */
//// digitalWrite(LED_BUILTIN, HIGH);
//// delay(5000);
//// digitalWrite(LED_BUILTIN, LOW);
//// delay(5000);
//}
//
//// function that executes whenever data is requested from master
//void requestEvent() {
// Wire.write("7abibi wala yhemmak");  /*send string on request */
// 
//}

//==================================================================

int data;

void setup(){
  Serial.begin(9600);
}

void loop(){
  data = Serial.read();
  delay(500);
  Serial.println(data);
}
