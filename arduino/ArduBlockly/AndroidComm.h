#ifndef _ANDROIDCOMM_H_
#define _ANDROIDCOMM_H_


#ifdef UNO
 #define SZ_DIGITAL_PORT 19
 #define SZ_ANALOG_IN    6
 #define SZ_PWM_PORT     6
#elif defined(MEGA)
 #define SZ_DIGITAL_PORT 69
 #define SZ_ANALOG_IN    16
 #define SZ_PWM_PORT     15
#endif

////////////////////////////////////////////

#define TPORT_NULL      0
#define TPORT_DIG_IN    1
#define TPORT_DIG_OUT   2
#define TPORT_ANALG_IN  3
#define TPORT_PWM       4

/////////////////////////////////////////////

#define BKLY_AINTF_UNKNOWN  -1
#define BKLY_AINTF_NULL     0
#define BKLY_AINTF_DIGOUT   1
#define BKLY_AINTF_DIGIN    2

#define BKLY_AINTF_INANALOG 3
#define BKLY_AINTF_PWM_ST   4
#define BKLY_AINTF_PWM      5

#define BKLY_AINTF_REMNEXT  11
#define BKLY_AINTF_PREAD    12
#define BKLY_AINTF_ANSET    13

//////////////////////////////////////

#define MPSET_NULL     0
#define MPSET_DIG_RD   1
#define MPSET_DIG_WR   2
#define MPSET_IN_ANL   3
#define MPSET_PWM      5
#define MPSET_PWM_CONT 6

void initPorts();

void sendDigitalInPort();
void sendAnalogValue(char pinNumber);

void setPortReadable(char port);
void setPortWritable(char port);
boolean isPortWritable(char port);

// Command Data Processor

void print_blocklyread(char retc);
char update_port_proc(byte c);

#endif
