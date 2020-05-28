#include <Wire.h>
#define sdapin           32
#define sclpin           33
#define I2CclockFrequency 400000

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  
  Serial.println("i2c-test");
  
  byte error, address;
  int nDevices;

  Wire.setClock(I2CclockFrequency);
  Wire.begin (sdapin,sclpin);
  
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
}

void loop() {
  // put your main code here, to run repeatedly:

}
