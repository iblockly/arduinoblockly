
#ifndef _SYSCONFIG_H_
#define _SYSCONFIG_H_

#include "arduboard.h"

void init_debug(void);

///////////////////////////////////////////////////////
// Debug

//#define DBG_LOG

#ifdef DBG_LOG

 #define DBG_CHANNEL_SWSERIAL
 //#define DBG_CHANNEL_SERIAL

 char* uprintf(char* fmt, ...);
 void  DPRINTS(char *fmt, ...);

 #define DPRINTF  uprintf 

 #ifdef DBG_CHANNEL_SWSERIAL
  // Define: Sw Serial Pin 
  #define SWSERIAL_RX  2
  #define SWSERIAL_TX  3
 #endif

#endif
#endif
