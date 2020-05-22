# **ADE9000 ESP-32 energy-monitor / phasor-measurement-unit modulair**<br/>

*Prototype version of an Energy Measurement / Phasor Measurement unit with modulair interface modules*<br/>

**Specs:**<br/>
* ESP-32 processor (with double SPI and multicore, multi-tasking) and Wifi<br/> 
* Galvanic seperation with ADUM chips <br/>
* ADE9000 3 phase Energy Measurement IC , version for CT (5VA) or <br/>
        rogowski (0.1mV/A), 8kHz wavebuffering , harmonics analyses and <br/>
        event processing for 50Hz , 230V 3 phase Energy systems <br/>
* Module 1 slot: 485 interface / lorawan 868 Mhz/ Ethernet lan8720 (waveshare)<br/>
        
* Module 2 slot: Ublox GPS / DS3232 RTC<br/> 
* Expansion board: 485 interface, 2x 24lc512, mcp23017, ds2482, mcp4725,BME680<br/> 
        so 4 DI (opto), 4 DO (opto), 1-wire , temp, humidity, voc, air-pressure, <br/>
	AD en DA inputs and extra flash <br/>
* Optional I2C display  (SED1306 or H35B-I)<br/>
* future development:  security TLS1.3, module 2 with NB-Iot-LTE-M (Ublox)<br/> 
* Arduino IDE , in RTOS , C++ Language <br/>
<br/>

#### *Now in testing phase -> so only use parts which I confirmed status tested*<br/>

*Software will be open source and soft- and hardware which are based on this*<br/> 
*project and used by others have the obligation of open source and publishing*<br/> 
*at Github*<br/>
