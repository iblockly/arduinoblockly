
//  ARDUINO + Android Blockly App.
//

#include "sysconfig.h"
#include "ucrt.h"

/// RTC /////////////////////

#include "AndroidComm.h"

#define DBG_PRINT

const int TM_DATA_PROC = 100;

#ifdef UNO
 #define SerialBt Serial
#elif defined(MEGA)
 #define SerialBt Serial1
#endif


/////////////////////////////////////////

//char remainData;

unsigned long tm_curr, tm_prev;
int cntloop;

//char stTxdata;

//////////////////////////////////////////////////

void setup()
{
    SerialBt.begin(115200);  // Bluetooth
    
	init_debug();

   #if 0
    pinMode(pinLED13, OUTPUT); // LED
    Led_Off();
   #endif
 
    initPorts();
    tm_prev = millis();
    //stTxdata = 1;
}

/////////////////////////////////////////////////////

void loop()
{
   tm_curr = millis();
   if ((tm_curr - tm_prev) > TM_DATA_PROC) {
      tm_prev = tm_curr;
      
      //if (stTxdata) 
      {
         sendDigitalInPort();
         sendAnalogValues();
      }
   }
   //delay(20);
}

void bl_rx_proc(byte c)
{
	 char retc = 0;

	 retc = update_port_proc(c);
	 
  #ifdef DBG_LOG
	 if (retc) {
		  print_blocklyread(retc);
	 }
  #endif
}


#ifdef UNO
void serialEvent()
{
	byte c;
	while (SerialBt.available()) {
	   c = SerialBt.read();
	   //uprintf("%02X ", c);
	   bl_rx_proc(c);
	}
}

#elif defined (MEGA)

void serialEvent1()
{
	char retc = 0;
	byte c;

	while (SerialBt.available()) {
	   c = SerialBt.read();
	   //uprintf("%02X ", c);
	   bl_rx_proc(c);
	}

}
#endif

/// End ///////////////////////////
