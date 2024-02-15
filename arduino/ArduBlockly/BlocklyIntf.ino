
// Interface: ARDUINO <---> JS

#include "arduboard.h"
#include "ucrt.h"

#include "AndroidComm.h"

/////////////////////////////////////////////////

const int DPORTSTART  = 2;
const int DPORTEND    = 8;

const int APORTSTART  = 0;
const int APORTEND    = 5;

//////////////////////////////////////////////////

void initPorts () {
  for (char pinNumber = DPORTSTART; pinNumber <= DPORTEND; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

///////////////////////////////////////////////////
// Blockly Arduino Interface

extern char mport_digital[];
extern char mport_analog_input[];

void sendDigitalInPort() {  
  int ipin = 0;
  for (ipin = 0; ipin < SZ_DIGITAL_PORT; ipin++) {
      if (mport_analog_input[ipin] == TPORT_DIG_IN) {
          sendDigitalValue(ipin);
      }
  }
}

void sendPinValues() {
   sendDigitalValues();
   sendAnalogValues();
}

void sendDigitalValues() {  
  char pinNumber = 0;
  for (pinNumber = DPORTSTART; pinNumber <= DPORTEND; pinNumber++) {
      sendDigitalValue(pinNumber);
  }
}

void sendAnalogValues() {
  char pinNumber = 0;  
  for (pinNumber = APORTSTART; pinNumber <= APORTEND; pinNumber++) {
      sendAnalogValue(pinNumber);
  }
}

///////////////////////////////////////////////////////

void sendDigitalValue(char pinNumber) {
  if (digitalRead(pinNumber) == HIGH) {
    SerialBt.write(B10000000
                 | ((pinNumber & B1111)<<2)
                 | (B1));
  } else {
    SerialBt.write(B10000000
               | ((pinNumber & B1111)<<2));
  }
}


void sendAnalogValue(char pinNumber) {
  int value = analogRead(pinNumber);
  SerialBt.write(B11000000
               | ((pinNumber & B111)<<3)
               | ((value>>7) & B111));
  SerialBt.write(value & B1111111);
}

void setPortReadable (char port) {
  if (isPortWritable(port)) {
    pinMode(port, INPUT);
  }
}

void setPortWritable (char port) {
  if (!isPortWritable(port)) {
    pinMode(port, OUTPUT);
  }
}

boolean isPortWritable (char port) {
  if (port > 7)
    return bitRead(DDRB, port - 8);
  else
    return bitRead(DDRD, port);
}

/// End ///////////////////////////
