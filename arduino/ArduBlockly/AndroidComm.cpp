
#include <Arduino.h>

#include "sysconfig.h"
#include "AndroidComm.h"


// Digtal
char mport_digital[SZ_DIGITAL_PORT] = { 0 };

// Analog
char mport_analog_input[SZ_ANALOG_IN] = { 0 };

char mmode_t = MPSET_NULL; // MPSET_PWM
byte mm_port;
byte mdout = 0;
int  mvalue;

//char remainData = 0;

char update_port_proc(byte c)
{
    if (c & 0x80) {
        if (c & 0x40) { // Analog 
            byte mode = c & 0x30;
            if (mode == 0x00) { // Analog Input Setting
                mmode_t = MPSET_IN_ANL;
                byte port = c & 0x0F;
                int p = (int) port;
                mport_analog_input[p] = TPORT_ANALG_IN;
                mm_port = port;
                return BKLY_AINTF_INANALOG;
            }
            else if (mode == 0x20) {  // Port PWM Setting
                mmode_t = MPSET_PWM;
                mm_port = c & 0x0F;   // 11 10 pppp
                mm_port <<= 2;
                mvalue = 0;
                return BKLY_AINTF_PWM_ST;
            }
        } else {
            byte port = (c >> 2) & 0x0F;
            mm_port = port;
            if (c & 0x02) { // MPSET_DIG_WR - Digital Output Setting
                mmode_t = MPSET_DIG_WR;
                setPortWritable(port);
                //mvalue = c & 0x01;
                mdout = c & 0x01;
                if (mdout) digitalWrite(port, HIGH);
                else  digitalWrite(port, LOW);
                mport_digital[(int)port] = TPORT_DIG_OUT;
                mm_port = port;
                return BKLY_AINTF_DIGOUT;
            }
            else {
                setPortReadable(port);
                mmode_t = MPSET_DIG_RD;
                mport_digital[(int)port] = TPORT_DIG_IN;
                mm_port = port;
                return BKLY_AINTF_DIGIN;
            }
        }
    } else {
        if (mmode_t == MPSET_PWM) {
            byte mode = c & 0xC0;
            if (mode == 0x40) { // Second
                mvalue = c & 0x0F;
                mvalue <<= 6;
                char port = (c >> 4) & 0x03;
                mm_port |= port;
                return BKLY_AINTF_PWM_ST;
            }
            else if (mode == 0x00) { // 3th
                mvalue |= (int)(c & 0x3F);
                analogWrite(mm_port, mvalue);
                return BKLY_AINTF_PWM;
            }
        }
        else return BKLY_AINTF_UNKNOWN;
    }
    return BKLY_AINTF_NULL;
}

#if 0
char get_portstate_in_analog(char port) { return mport_analog_input[port]; }
void set_portstate_in_analog(char port) { mport_analog_input[port] = 1; }

char msz_port_analog_in = 0;

char get_port_in_analog(char port)
{
   for (int c = ;c < msz_port_analog_in;c++) {
     if (mport_analog_input[c] == port)
        return c;
   }
   return -1;
}
char get_port_in_analog(char port)
{
   mport_analog_input[msz_port_analog_in++] = port;

}
#endif

#ifdef DBG_LOG

void print_blocklyread(char retc)
{
    char port  = mm_port;
    char dout  = mdout;
    int  value = mvalue;

    switch (retc) {
    case BKLY_AINTF_DIGIN:
        DPRINTS("D IN %d\n", port);
        break;

    case BKLY_AINTF_DIGOUT:
        DPRINTS("D OUT %d\n", port);
        break;

    case BKLY_AINTF_INANALOG:
        DPRINTS("A In [%d] %d\n", port);
        break;

    case BKLY_AINTF_PWM_ST:
        break;

    case BKLY_AINTF_PWM:
        DPRINTS("PWM [%d]=%d\n", port, value);
        break;

    //case BKLY_AINTF_REMNEXT:
    case BKLY_AINTF_PREAD:
        DPRINTS("A RD: %d\n", port);
        break;
        
    case BKLY_AINTF_ANSET:
        DPRINTS("A SET [%d]:%d\n", port, value);
        break;
    }
}

#endif

/////////////////////////////////////////////////

#if 0   

void set_pwm_msg(char *pdata, char port, int value)
{
   char a,b,c;

   a = (port>>2) | 0xE0;
   b = ((port<<4) & 0x30) | 0x40;
   b |= (value >> 6);
   c = value & 0x3F;

   pdata[0] = a; pdata[1] = b; pdata[2] = c;
}

char update_port_proc(char c)
{
   if (c & 0x80) {
    switch (c & B11100000){
    case B11100000 :
      port = (c >> 1) & B1111;
      setPortWritable(port);
      dout = c & 1;
      if (dout) digitalWrite(port, HIGH);
      else digitalWrite(port, LOW);
      return BKLY_AINTF_DIGOUT;
      
    case B11000000 :
      remainData = c; 
      return BKLY_AINTF_REMNEXT;

    case B10100000 :
      port = (c >> 1) & B1111;
      setPortReadable(port);
      return BKLY_AINTF_PREAD;
    }
   } else {
     port = (remainData >> 1) & B1111;
     value = ((remainData & 1) << 7) + (c & B1111111);
     setPortWritable(port);
     analogWrite(port, value);
     remainData = 0;
     return BKLY_AINTF_ANSET;
   }
   return BKLY_AINTF_NULL;
}

void updateDigitalPort (char c) {
  // first data
  if (c & 0x80) { // >>7) {
    // is output
    if (c & 0x40) { //>>6) & 1) {
      // is data end at this chunk
      if (c & 0x20) { // (c>>5) & 1) {
        port = (c >> 1) & B1111;
        setPortWritable(port);
        if (c & 1)
          digitalWrite(port, HIGH);
        else
          digitalWrite(port, LOW);
      } else {
        remainData = c;
      }
    } else {
      port = (c >> 1) & B1111;
      setPortReadable(port);
    }
  } else {
    port = (remainData >> 1) & B1111;
    value = ((remainData & 1) << 7) + (c & B1111111);
    setPortWritable(port);
    analogWrite(port, value);
    remainData = 0;
  }
}
#endif
