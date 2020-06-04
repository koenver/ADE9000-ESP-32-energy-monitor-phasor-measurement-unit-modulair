//****************** Core 0 main task (ADE9000) *********************************
void Core0_main( void * parameter )
{//***** setup part  ***
#ifdef DEBUG
  Serial.println("core0-main task:alive");
#endif

 //***** loop part   ***
 for(;;)
  {
   vTaskDelay(1);
  }
 vTaskDelete( NULL ); 
}
