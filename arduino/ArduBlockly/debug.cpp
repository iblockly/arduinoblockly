
#include <Arduino.h>
#include <stdio.h>

#include "sysconfig.h"
#include "ucrt.h"

#ifdef DBG_CHANNEL_SWSERIAL

 #include <SoftwareSerial.h>
 SoftwareSerial DbgSerial(SWSERIAL_RX,SWSERIAL_TX);

 void dbg_print(char *pstr) { DbgSerial.print(pstr); }

#elif defined (DBG_CHANNEL_SERIAL)

static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,
                         _FDEV_SETUP_WRITE);

#endif

///////////////////////////////////////////////////////
// Debug

void init_debug(void)
{
  #ifdef DBG_CHANNEL_SWSERIAL
   DbgSerial.begin(9600);	// Debug
   DbgSerial.print("Arduino Blockly...\r\n");

  #elif defined (DBG_CHANNEL_SERIAL)
   stdout = &mystdout;
   printf("Arduino Blockly..\n");
  #endif
}

#ifdef DBG_CHANNEL_SWSERIAL

char gstrbuff[128];

char* uprintf(char* fmt, ...)
{
    va_list vlist;

    va_start(vlist, fmt);
    vsprintf(gstrbuff, fmt, vlist);
    va_end(vlist);

    dbg_print(gstrbuff);
    return gstrbuff;
}

unsigned char mseqprt = 0;

extern unsigned long tm_curr;


void DPRINTS(char *fmt, ...)
{
    va_list vlist;

    sprintf(gstrbuff, "%02d:%u ", mseqprt%100, (unsigned long) tm_curr);
	  mseqprt++;

  	char *pstr = string_end(gstrbuff);
		
    va_start(vlist, fmt);
    vsprintf(pstr, fmt, vlist);
    va_end(vlist);

    dbg_print(gstrbuff);
}
#endif

#ifdef DBG_CHANNEL_SERIAL

static int uart_putchar(char c, FILE *stream);

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,
                         _FDEV_SETUP_WRITE);


static int uart_putchar(char c, FILE *stream)
{
  if (c == '\n')
    uart_putchar('\r', stream);
  loop_until_bit_is_set(UCSRA, UDRE);
  UDR = c;
  return 0;
}

unsigned char mseqprt = 0;
extern unsigned long tm_curr;

void DPRINTS(char *fmt, ...)
{
    va_list vlist;

    printf("%02d:%u ", mseqprt%100, (unsigned long) tm_curr);
    mseqprt++;

    va_start(vlist, fmt);
    vprintf(fmt, vlist);
    va_end(vlist);
}
#endif


///////////////////////////////////////////
// LED  

#ifdef DBG_LED

const int pinLED13  = LED_BUILTIN;

char gstLed;  // LED 전원 상태

char getStateLED() { return gstLed; }
void setStateLED(char st) { gstLed = st; }

void Led_On();
void Led_Off();


////////////////////////////////////////////
/// LED Control 

void Led_On()
{
    gstLed = 1;
    digitalWrite(pinLED13, HIGH);
}


void Led_Off()
{
    gstLed = 0;
    digitalWrite(pinLED13, LOW);
}
#endif

/// End ///////////////////////////////////////
