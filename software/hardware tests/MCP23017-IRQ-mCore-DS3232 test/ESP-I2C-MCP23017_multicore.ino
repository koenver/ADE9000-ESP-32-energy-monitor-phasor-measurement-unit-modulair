
#include <Wire.h>
#include <MCP23017.h>
#include <DS3232RTC.h>

#define DEBUG     //output is send to TX0  (not compatible with GPS module !!!) 

#define RTC       // there is an DS3232
//#define GPS       // ther is an GPS for time and PPS (NOT compatible with #DEBUG..same Serial)

//#define ADE9000   // there is ADE90000 circuit at PCB

#define H35BI     //there is an HB35I display
//#define SSD1306   // there is SED1306 display

//#define ETHERNET  // there is an lan8720 ethernet
//#define WIFI      // there is an Wifi 
//#define LORA      // there is a lora module (RFM95)


//*************** cores and tasks ***********
//*   Core 0 task:ADE9000 services (collect data, RTC (start/stop), GPS(PPS)
//*          IRQ :PPS, ,ADE9000
//*          HSPI (ADE9000)
//*   Core 1 task: 485,Lora, Ethernet services,Wifi
//*          IRQ MCP23017 (RTC etc)
//*          VSPI (lora)
//*******************************************

//********** ESP-32 Wroom32D pins *********

#define INT_MCP23017pin  5
#define sdapin           32
#define sclpin           33
#define PPSpin           35
#define I2CclockFrequency 400000
// *********  MCP23017 *********
#define MCP23017_ADDR 0x20
#define MCP23017INT_pin 5   ///(gpio5)
//  gpa0=i=switch     gpa4=i=INT-RTC         gpb0=o=digout0   gpb4=o=opto-rst
//  gpa1=o=ledblue    gpa5=i=Hall-switch     gpb1=o=digout1   gpb5=i=opto-in
//  gpa2=o=ledred     gpa6=i=ADS1015         gpb2=o=digout2   gpb6=i-digin1
//  gpa3=i=INT-H35BI  gpa7=0=DustsensorOn    gpb3=o=digout3   gpb7=i=digin2
//
//  switch=pressed=low, INT-H35BI=Active Low, INT-RTC=Active Low
//
//  MCP23017 is used in 16 bit mode and Inetrrupt gpio5 ESSP32 Active=low
//  Pin 0-7 for port A, 8-15 for port B.
#define  LedRed_Pin  1
#define  LedWht_Pin  2
#define  LED_On      1
#define  LED_Off     0


MCP23017 mcp = MCP23017(MCP23017_ADDR);
DS3232RTC myRTC(false);   //I2C is already initialized



portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
volatile uint8_t interruptMCPoccur=0;
volatile bool IntAlarm1flag=false;
volatile bool IntAlarm2flag=false;
//byte interruptdetect=0;
//time_t myTime;
tmElements_t tm;
