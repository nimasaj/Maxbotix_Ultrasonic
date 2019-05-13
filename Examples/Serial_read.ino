/*
This code is written by Nima Sajedi on 13May2019. It is available at https://github.com/nimasaj/Maxbotix_Ultrasonic
*/
#include <SoftwareSerial.h>

#define En_US 4
#define US_txPin 2      //Ultrasonic | Data pin
#define US_rxPin 22      //Ultrtasonic |

SoftwareSerial serial(US_txPin, US_rxPin, true);   //((Module.Tx>>>MCU.Rx), (Module.Rx>>>MCU.Tx))

void setup() {
  Serial.begin(9600);
  serial.begin(9600);
  delay(500);  
  Serial.println("Hello");
}

void loop() {
  uint8_t sn=4;//sample number
  uint16_t AA[sn];

  for (uint8_t n=0; n<sn;n++){
    AA[n]=USgetData(); //Measured distance
    Serial.print("AA[");
    Serial.print(n);
    Serial.print("]= ");
    Serial.println(AA[n]);
    delay(150);
  }
  Serial.println("");  
  delay(1000);
}

uint16_t USgetData(){
  uint16_t dis; //measured distance
  char output;
  uint8_t no=3; // no. of characters | set to 3 for cm | set to 4 for mm |
  char arr[no];
  uint8_t n=0;

  while (!serial.available()){
     //blink();
  }

  while(serial.available()){
    output = serial.read();
    if (output==0x52){ //0x52= "R"
      while (n<no){
        arr[n]=serial.read();
        n++;
      }
    }
  }
  dis=atoi(arr);
  return dis;
}
