#ifndef lights_h
#define lights_h

#include "Arduino.h"

void initLights() {
#ifdef Indexers_on
  // Indexer using one PCF8574
//  MICRO_DELAY
  Wire.beginTransmission(AoaAddr); // transmit to device #4
  Wire.write(189);              // sends one byte  
  Wire.endTransmission(); 
#endif //indexers

#ifdef CautionPanel_on
  // Caution Panel via 2 MCP23017
//  MICRO_DELAY
  Wire.beginTransmission(CpAddr1); // transmit to device #4
  Wire.write(0x00); // Set IODIR0
  Wire.write(0); // Set IODIR0 to output
  Wire.write(0);  // Set IODIR1 to output
  Wire.endTransmission(); 
  
  Wire.beginTransmission(CpAddr2); // transmit to device #4
  Wire.write(0x00); // Set IODIR0
  Wire.write(0); // Set IODIR0 to output
  Wire.write(0);  // Set IODIR1 to output
  Wire.endTransmission(); 


  Wire.beginTransmission(CpAddr1); // transmit to device #4
  Wire.write(0x12); //Address GPIO0 with rollover to 1
  for (short i = 0; i < 2; i++) { //send 4 byte to clear Caution lights
    Wire.write(0);              // sends one byte  
  }
  Wire.endTransmission(); 
  
  Wire.beginTransmission(CpAddr2); // transmit to device #4
  Wire.write(0x12); //Address GPIO0 with rollover to 1
  for (short i = 2; i < 4; i++) { //send 4 byte to clear Caution lights
    Wire.write(0);              // sends one byte  
  }
  Wire.endTransmission(); 

  #endif //caution
}

#ifdef Indexers_on
byte AoaIndexer[1];

void readAOA() {
  COM.print('A');
  COM.readBytes(AoaIndexer, 1);
}

void lightAOA() {
//  MICRO_DELAY
  Wire.beginTransmission(AoaAddr); // transmit to device #4
  Wire.write(~(AoaIndexer[0]));              // sends one byte  
  Wire.endTransmission();  
}
#endif //indexers

#ifdef CautionPanel_on

byte CautionPanel[4];

void readCautionPanel() {
  COM.print('C');
  COM.readBytes(CautionPanel, 4);
}

void lightCautionPanel() {
//  MICRO_DELAY
  Wire.beginTransmission(CpAddr1); // transmit to device #4
  Wire.write(0x12); //Address GPIO0 with rollover to 1

  for (short i = 0; i < 2; i++) { //send 4 byte to clear Caution lights
    Wire.write(CautionPanel[i]);              // sends one byte  
  }
  Wire.endTransmission(); 

//  MICRO_DELAY
  Wire.beginTransmission(CpAddr2); // transmit to device #4
  Wire.write(0x12); //Address GPIO0 with rollover to 1  
  for (short i = 2; i < 4; i++) { //send 4 byte to clear Caution lights
    Wire.write(CautionPanel[i]);              // sends one byte  
  }
  
  Wire.endTransmission(); 
}
#endif //caution

#endif //ndef

