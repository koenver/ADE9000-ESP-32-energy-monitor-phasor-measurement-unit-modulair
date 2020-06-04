//***********************  IRQ MCP23017 at Gpio 5**************************************************
void IRAM_ATTR InterruptMCP() 
{portENTER_CRITICAL_ISR(&mux);
 interruptMCPoccur=1;
 portEXIT_CRITICAL_ISR(&mux);
}
//**************************************************************************************************

//****************** Core 1 main task (I2C Display, Communication) ********************************
void Core1_main( void * parameter )
{//***** setup part  ***
#ifdef RTC
  myRTC.begin();
#endif
  MCP23017start();
#ifdef DEBUG  
  Serial.println("core1-main task:alive");
  LedTest();
  Presskey();
  #ifdef RTC
    RTCtest();
  #endif
#endif  
 interruptMCPoccur=0;
 mcp.clearInterrupts();
 attachInterrupt(digitalPinToInterrupt(INT_MCP23017pin),InterruptMCP, FALLING);  // Active low so falling INT 
 #ifdef RTC
   DS3232Alarmread_reset(); 
   #ifdef DEBUG
     Serial.println("interrupt routine activated");
   #endif
 #endif
 //***** loop part   ***
 for(;;)
 {

  
  vTaskDelay(1);
 }
 vTaskDelete( NULL );
}
//*************************************************************************************************
//****************** Core 1 second task IRQ MCP23017 handling (RTC, Display, I/O etc) *************
//****************** This task looks if the interrupt from the MCP23017 is triggered  *************
//****************** in the main task (setup part) in the subroutine mcp23017start    *************
//****************** the MCP triggers and flags are defined                           *************
//****************** This task finds out which input line of the MCP23017 caused this *************
//****************** See in decleration part of theis soft ware and the EAGLE         *************
//****************** schematics for details                                           *************
void Core1_irqcheckMCP( void * parameter )
{//***** setup part  ***
 uint8_t PortA_INT_cap,PortB_INT_cap,PortA_INT_cap_old,PortB_INT_cap_old;    // for the flag capture register of the MCP23017 ..(latched registers and cleared when read
 uint8_t statRTCreg;
 bool INTCAPChangedDuringExicution;
 #ifdef DEBUG
   Serial.println("core1-irq MCP handling task:alive");
 #endif
 //***** loop part   ***
 for(;;)
 {if (interruptMCPoccur==1)
   {// ****************** make sub for checking INT CAP changes during procedure !!!!!@
    // read flag capture latch registers
    mcp.readRegister(MCP23017Register::INTCAP_A,PortA_INT_cap,PortB_INT_cap); 
    PortA_INT_cap_old=PortA_INT_cap;
    PortB_INT_cap_old=PortB_INT_cap;
    INTCAPChangedDuringExicution= true;
    while (INTCAPChangedDuringExicution==true)
     {// now find out which bit flag in portA and the value (was it falling than bit =0)
      IdentWhichInterruptMCP23017(PortA_INT_cap,PortB_INT_cap);
      // flags for interrupt identification are set
      // check for changes in INTCAP register ..may be an extra interrupt during execution of 'IdentWhichInterruptMCP23017' routine
      mcp.readRegister(MCP23017Register::INTCAP_A,PortA_INT_cap,PortB_INT_cap); 
      if ((PortA_INT_cap != PortA_INT_cap_old)||(PortB_INT_cap != PortB_INT_cap_old))
        {INTCAPChangedDuringExicution==true; 
         PortA_INT_cap_old=PortA_INT_cap;
         PortB_INT_cap_old=PortB_INT_cap;  
        }
      else
        {INTCAPChangedDuringExicution= false;
        }
     }
    //after all the interrupt are checked and flagged...clear the MCP23017
    mcp.clearInterrupts();
    interruptMCPoccur=0;  
   }
   vTaskDelay(1);
 }
 vTaskDelete( NULL ); 
}
//*************************************************************************************************










/*

//*******************main loop************************
void loop() {
  // put your main code here, to run repeatedly:
  uint16_t PortAB;
  if (interruptoccur==1)
    { interruptdetect=1;
      Serial.println("interrupt found"); 
     myRTC.alarm(ALARM_1);
     myRTC.alarm(ALARM_2);
     mcp.clearInterrupts();
     interruptoccur=0;
     interruptdetect=0;
    }
  myRTC.read(tm);
  PortAB=mcp.read();
  Serial.print("Actual DS3232 time: ");
  Serial.print(tm.Day,DEC);Serial.print('/');Serial.print(tm.Month,DEC);Serial.print('/');Serial.print(tm.Year,DEC);Serial.print(' ');
  Serial.print(tm.Hour,DEC);Serial.print(":");Serial.print(tm.Minute,DEC);Serial.print(":");Serial.print(tm.Second,DEC);Serial.print(' ');
  Serial.println(PortAB,BIN);
  delay(100);  //so every 1/10th of a second
}

//****************** IRQ MCP23017 *************************
void INT_Handling_MCP23017()
{// select which interrupt occured
 uint8_t PortA_INT_flag,PortB_INT_flag;

 uint8_t PortA_INT_cap,PortB_INT_cap;
 //portENTER_CRITICAL_ISR(&mux);
 //
 if (interruptdetect==0)
   {interruptMCPoccur=1;
    interruptdetect=1;}
 //portEXIT_CRITICAL_ISR(&mux);
 
 mcp.interruptedBy(PortA_INT_flag,PortB_INT_flag);
 Serial.println("Interrupt at mcp2307");
 if (PortA_INT_flag != 0)
   {PortA_INT_cap=mcp.readRegister(MCP23017Register::INTCAP_A);  
    // now find out which bit flag in portA and the value (was it falling than bit =0)
    //****check for DS3232 ALARM ****      ******needs rework for Alarm1 and Alarm2 
    if ((PortA_INT_flag & 0b00010000)&&(!(PortA_INT_cap | 0b11101111))) 
      {//interrupt caused by DS3232 Alarm
       //find out alarm1 or alarm2
       if (myRTC.alarm(1))
         {//alarm1 interrupt routine
          myRTC.read(tm);
          Serial.print("Alarm1 at: ");
          Serial.print(tm.Day,DEC);Serial.print('/');Serial.print(tm.Month,DEC);Serial.print('/');Serial.print(tm.Year,DEC);Serial.print(' ');
          Serial.print(tm.Hour,DEC);Serial.print(":");Serial.print(tm.Minute,DEC);Serial.print(":");Serial.println(tm.Second,DEC);
         
         }
       if (myRTC.alarm(2))
         {//alarm2 interrupt routine
          myRTC.read(tm);
          Serial.print("Alarm2 at: ");
          Serial.print(tm.Day,DEC);Serial.print('/');Serial.print(tm.Month,DEC);Serial.print('/');Serial.print(tm.Year,DEC);Serial.print(' ');
          Serial.print(tm.Hour,DEC);Serial.print(":");Serial.print(tm.Minute,DEC);Serial.print(":");Serial.println(tm.Second,DEC);
         
         }
      }
    // here the routines for the other interrupts
   }
 if (PortB_INT_flag != 0)  
   {PortB_INT_cap=mcp.readRegister(MCP23017Register::INTCAP_B);
    
   }
  
}

*/
