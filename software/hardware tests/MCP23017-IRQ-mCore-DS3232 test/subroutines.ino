//********************************************************
void Presskey()
{String inputstring;
#ifdef DEBUG
  Serial.println("Press [Enter] to continue");
  while(Serial.read()>=0);     //Flush any extra characters
  while (!Serial.available());  //wait for serial data to be available
  inputstring = Serial.read();
#endif
}
//********************************************************

void MCP23017start()
{ mcp.init();
  mcp.writeRegister(MCP23017Register::IOCON, 0b01100000); //INTA+B coupled , 16 bit mode, INT Active =low  Bank:0 
  //BANK =    0  : sequential register addresses
  //MIRROR =  1  : interrupt A+B are same
  //SEQOP =   1  : sequential operation disabled, address pointer does not increment
  //DISSLW =  0  : slew rate enabled
  //HAEN =    0  : hardware address pin is always enabled on 23017
  //ODR =     0  : open drain output
  //INTPOL =  0  : interrupt active low
  mcp.portMode(MCP23017Port::A, 0b01111001,0b01111001,0b00000000);          //Port A Input=1 or output=0 ...inverted in lib from datasheet!!, second byte is pullup
  mcp.portMode(MCP23017Port::B, 0b11100000,0b11100000,0b00000000);           //Port B Input=1 or output=0  ... 3ed byte is inverted bit 0= no
  //INT DS3232 goes to MCP23017 so it's interrupt has to be defined
  mcp.writeRegister(MCP23017Register::GPINTEN_A,0b00010000); //1= enable interrupt 0= no interrupt*********only RTC interrupt test now ****!!!!!*****
  mcp.writeRegister(MCP23017Register::GPINTEN_B,0b00000000); 
  mcp.writeRegister(MCP23017Register::INTCON_A, 0b00010000);  // 1=compared with DEFVAL  0=compared with previous pin value (on change)
  mcp.writeRegister(MCP23017Register::INTCON_B, 0b00000000);
  mcp.writeRegister(MCP23017Register::DEFVAL_A, 0b00010000);  // if input is different DEFVAL -> interrupt
  mcp.writeRegister(MCP23017Register::DEFVAL_B, 0b00000000); 
  mcp.clearInterrupts();
  
 
}

//********************************************************
void I2Cscan()   // only used in DEBUG
{byte error, address;
 int nDevices;
 Serial.println("i2c-test");
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
}
//********************************************************
void RedLedOn()
{mcp.digitalWrite(LedRed_Pin,LED_On);}
//***********************
void RedledOff()
{mcp.digitalWrite(LedRed_Pin,LED_Off);}
//***********************
void WhtLedOn()
{mcp.digitalWrite(LedWht_Pin,LED_On);}
//***********************
void WhtLedOff()
{mcp.digitalWrite(LedWht_Pin,LED_Off);}
//***********************
void LedTest()
{Serial.println("Led test..");
 RedledOff();
 WhtLedOff();
 delay(500);
 RedLedOn();
 delay(500);
 WhtLedOn();
 delay(1000);
 RedledOff();
 WhtLedOff();
}
//***********************
void RTCtest()
{Serial.println("RTC DS3223 test");
 tm.Second=00;
 tm.Minute=00;
 tm.Hour=12;
 tm.Day=31;
 tm.Month=5;
 tm.Year=2020-1970;
 myRTC.write(tm);
 myRTC.read(tm);
 Serial.print("Actual DS3232 time: ");
 Serial.print(tm.Day,DEC);Serial.print('/');Serial.print(tm.Month,DEC);Serial.print('/');Serial.print(tm.Year,DEC);Serial.print(' ');
 Serial.print(tm.Hour,DEC);Serial.print(":");Serial.print(tm.Minute,DEC);Serial.print(":");Serial.println(tm.Second,DEC);
  // initialize the alarms to known values, clear the alarm flags, clear the alarm interrupt flags
 //myRTC.setAlarm(ALM1_MATCH_DATE, 0, 0, 0, 1);
 //myRTC.setAlarm(ALM2_MATCH_DATE, 0, 0, 0, 1);
 DS3232Alarmread_reset();
 myRTC.alarmInterrupt(ALARM_1,false);
 myRTC.alarmInterrupt(ALARM_2,false);
 myRTC.squareWave(SQWAVE_NONE); 
 mcp.clearInterrupts();
 Presskey();
 myRTC.setAlarm(ALM1_EVERY_SECOND, 0, 0, 0, 0);
 myRTC.setAlarm(ALM2_EVERY_MINUTE, 0, 0, 0, 0);
 // clear the alarm flags
 DS3232Alarmread_reset();
 myRTC.squareWave(SQWAVE_NONE);
 // enable interrupt output for Alarm 1
 myRTC.alarmInterrupt(ALARM_1, true);
 myRTC.alarmInterrupt(ALARM_2, true);
 DS3232Alarmread_reset();
 mcp.clearInterrupts();
}
//************** DEBUG serial print time + <LF> *****
void Printtime()
{Serial.print(tm.Day,DEC);Serial.print('/');Serial.print(tm.Month,DEC);Serial.print('/');Serial.print(tm.Year,DEC);Serial.print(' ');
 Serial.print(tm.Hour,DEC);Serial.print(":");Serial.print(tm.Minute,DEC);Serial.print(":");Serial.println(tm.Second,DEC);
}
//************* faster read alarm RTC and reset ******
uint8_t DS3232Alarmread_reset()
{uint8_t statusRegDS3232,dummystatus;
 statusRegDS3232= myRTC.readRTC(0x0F);  // 0x0f is status register of DS3232
 dummystatus=(statusRegDS3232 & 0b11111100);
 // set lower 2 bits to 0
 myRTC.writeRTC(0x0F, dummystatus);   
 return statusRegDS3232;   // statusReg:0 = alarm1 statusReg:1= alarm2 triggered
}
//************** interrupt MCP23017 selection routine *******
void IdentWhichInterruptMCP23017(uint8_t PortA_INT_capb,uint8_t PortB_INT_capb)
{uint8_t statRTCreg;
 //****check for DS3232 ALARM ****
 #ifdef RTC 
   if (( PortA_INT_capb | 0b11101111)== 0b11101111)  // is check for RTC alarm1&2 flag..the CAPflag is the pin states at moment of interrupt
    {// alarm1 or alarm2 of DS3232 went off-> find out which...or both at the same time
     statRTCreg=DS3232Alarmread_reset();
     //Serial.print("statRTCreg= ");Serial.println(statRTCreg,BIN);
     if ((statRTCreg & 0b00000001)== 0b00000001)  // is check for alarm1 triggerd
       {IntAlarm1flag=true;
        #ifdef DEBUG
          myRTC.read(tm);
          Serial.print("Alarm1 at: ");
           Printtime();  
         #endif
        }
     if ((statRTCreg & 0b00000010)== 0b00000010)  
       {IntAlarm1flag=true;
        #ifdef DEBUG
          myRTC.read(tm);
          Serial.print("Alarm2 at: ");
          Printtime();  
        #endif
       }      
    } 
 #endif 
 //********** check for the other input pins of the MCP23017 
}
