
TaskHandle_t xCore0_main;  //ADE9000 core
TaskHandle_t xCore1_main;   
TaskHandle_t xCore1_irqcheckMCP;


//************ SETUP *****************
void setup() {
  Wire.setClock(I2CclockFrequency);
  Wire.begin (sdapin,sclpin);
  pinMode(INT_MCP23017pin, INPUT_PULLUP); 
  pinMode(PPSpin, INPUT_PULLUP);
#ifdef DEBUG
  Serial.begin(115200);  // output to PC
  I2Cscan;
#else
  Serial.begin(9600);    // GPS serial data flow
#endif
  xTaskCreatePinnedToCore(Core0_main,"Core0_main",15000,NULL,1,&xCore0_main,0);
  xTaskCreatePinnedToCore(Core1_main,"Core1_main",10000,NULL,1,&xCore1_main,1); 
  xTaskCreatePinnedToCore(Core1_irqcheckMCP,"irqcheckMCP",10000,NULL,1,&xCore1_irqcheckMCP,1);
  //xTaskCreatePinnedToCore(Webpages,"Webpages",30000,NULL,1,&xWebpages,1);  
}
//****************** LOOP MAIN **********************************
void loop() 
{
 // do nothing here..to release core 1 from activities here
 vTaskDelay(portMAX_DELAY);  
}
