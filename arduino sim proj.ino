#include <Arduino.h>
//Bus 001 Device 009: ID 0403:6001 Future Technology Devices International, Ltd FT232 Serial (UART) IC
//before you upload make sure the port has the correct permissions
//chmod 777 /dev/ttyUSB0
//https://core-electronics.com.au/attachments/localcontent/SIM7000E-NB-IoT-HAT-Manual-EN_13735387456.pdf
//https://www.youtube.com/watch?v=-XPrSScamXc
//https://www.aliexpress.com/item/1005009551754213.html?af=6436a9f7d915b83661024974
//https://img.yfisher.com/m0/1692269111123-sim7000-series-model-bk-sim7000-board-user-manual-v10.pdf
//https://www.youtube.com/watch?v=j4xw8QomkXs

#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);
#define Readypin 4
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  

  mySerial.begin(115200);

  Serial.println("Initializing..."); 
  // delay(1000);
  digitalWrite(Readypin, HIGH);

  mySerial.write("AT"); 
  // updateSerial();
  
  // mySerial.println("AT+CMGF=1"); 
  // updateSerial();
  // mySerial.println("AT+CNMI=1,2,0,0,0");
  // updateSerial();
}

void loop()
{
  printpins();
  delay(500);

  // pinMode(ledPin,OUTPUT)
  // mySerial.write("AT\n");
  // delay(100); 
  // toggleled();
  // delay(2.5);

  // digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  // delay(1000);                      // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  // delay(1000);  
}
void toggleled(){
  static int state;
  state = (state == NULL) ? HIGH : (state == HIGH ? LOW : HIGH);
  Serial.println(state);
  digitalWrite(LED_BUILTIN, state);
}
void printpins(){
  for(int i=2;i<8;i++){
    Serial.write("pin ");
    Serial.write(String(i));
    Serial.write(":");
    Serial.write(digitalRead(i));
    Serial.write("\n");
  }

}
void updateSerial()
{
  delay(500);
  // while (Serial.available()) 
  // {
  //   Serial.write("listening");
    // mySerial.write(Serial.read());
  // }
  // Serial.write("hello\n");
  // Serial.write(mySerial.available()+"\n");
  

  while(mySerial.available())
  {

    Serial.write(mySerial.read()+" says\n");
  }
}