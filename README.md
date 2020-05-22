# **ADE9000-ESP-32-energy-monitor-phasor-measurement-unit-modulair**

*Prototype version of an Energy Measurement / Phasor Measurement unit with modulair interface modules*

**Specs:**
•	ESP-32 processor (with double SPI and multicore multi tasking) and Wifi 
•	galvanic seperation with ADUM chips 
•	ADE9000 3 phase Energy Measurement IC , version for CT (5VA) or 
        rogowski (0.1mV/A), 8kHz wavebuffering , harmonics analyses and 
        event processing for 50Hz , 230V 3 phase Energy systems 
•	module 1 slot: 485 interface / lorawan 868 Mhz/ Ethernet lan8720 (wave share)
                         / NB-Iot-LTE-M (Ublox) 
•	modele 2 slot: Ublox GPS / DS3232 RTC 
•	uppper expansion board: 485 interface, 2x 24lc512, mcp23017, ds2482, mcp4725,BME680; 
        so 4 DI (opto), 4 DO (opto), 1-wire , temp, humidity, voc, air ppressure, 
	AD en DA inputs and extra flash 
•	optional I2C display  (SED1306 or H35B-I)
•	Arduino IDE , in RTOS , C++ Language 

** *Now in testing phase -> so only use parts which I confirmed status tested* ** 

*Software will be open source and soft- and hardware which are based on this 
project by others have the obligation of open source and publishing at Github*
