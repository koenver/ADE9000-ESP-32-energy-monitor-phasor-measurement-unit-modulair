
#include <TinyGPS.h>
#include <Int64String.h>
#include "driver/timer.h"
#define PPSpin 35  //later used for interrupt for counter

// with DIO and ESP wroom32D gpio 9 and 10 are not free **
//#define RXD1 8
//#define TXD1 9
// So Tx of GPS placed at RX0 , so for programming no GPS in slot 2 !!!!

TinyGPS gps;
int val;
int teller;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PPSpin, INPUT);
  Serial.println("3000 x 10ms PPSpin output:");
  for (teller=0; teller<300; teller++)
    {val = digitalRead(PPSpin);
     Serial.print(val);
     delay(10);
    }
  Serial.println();
  Serial.println("U-BLOX GPS serial test");
}

void loop() {
 byte flagbyte;
int tyear;
byte  tsecond,tminute,thour,tday,tmonth,thundredths;
unsigned long tage;
bool newData = false;
char c;
  for(;;)
  { 
    //
   // Serial.print(c);
    
    while (Serial.available())
    {c = Serial.read();
    if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
    if (newData)
    { gps.crack_datetime(&tyear, &tmonth, &tday, &thour, &tminute, &tsecond, &thundredths, &tage);
      newData = false;
      Serial.print(tday);Serial.print("/");Serial.print(tmonth);Serial.print("/"); Serial.print(tyear);Serial.print("-");
      Serial.print(thour);Serial.print(":");Serial.print(tminute);Serial.print(":"); Serial.print(tsecond);Serial.print("-");Serial.println(thundredths);
    }
  } 
  
}
