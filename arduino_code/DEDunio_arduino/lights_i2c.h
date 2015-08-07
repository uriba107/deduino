#ifndef lights_h
#define lights_h

#include "Arduino.h"
#include "i2c_hardware.h"

///////////////////////////////////////////// Generic Functions ////////////////////////////////////////////
void initLights() {
#ifdef Indexers_on
  // Indexer using one PCF8574
  PCF8574_send(AoaAddr, ~(66)); // Light two green lights (invert byte)
#endif //indexers

#ifdef CautionPanel_on
  // Caution Panel via PCA9505 (Jshep CP)
  PCA9505_SetOutptMode(CpAddr);
  PCA9505_SendOutputData(CpAddr,5,{0});

// using 2 MCP23017 for the CP will look like this
//  MCP23017_SetOutptMode(Cpaddr1);
//  MCP23017_SetOutptMode(Cpaddr2);

//  MCP23017_SendOutputData(CpAddr1, 0, 0);
//  MCP23017_SendOutputData(CpAddr2, 0, 0);
#endif //caution

#ifdef Glareshield_on
// Glareshield via MCP23017
  MCP23017_SetOutptMode(GsAddr);
  MCP23017_SendOutputData(GsAddr, 0x55, 0x55);
#endif //Glareshield

}


////// Indexers ///////

#ifdef Indexers_on
byte AoaIndexer[1];

void readAOA() {
  COM.print('A');
  commsCheck(COM.readBytes(AoaIndexer, 1));

}

void lightAOA() {
  PCF8574_send(AoaAddr, ~(AoaIndexer[0])); //PCF8574 sinks current, so inverse the byte you are sending
}
#endif //indexers

////// Caution Panel ///////
#ifdef CautionPanel_on
// Caution panel is only 4 bytes. however Shep's CP is using 5 bytes data structure with random bits all over.
// if you use your own stuff, only use the first 4 bytes (the fifth will be all 0)
byte CautionPanel[5]; 

void readCautionPanel() {
  COM.print('C');
  COM.readBytes(CautionPanel, 5);
}

void lightCautionPanel() {
    // Caution Panel via PCA9505 (Jshep CP)
  PCA9505_SendOutputData(CpAddr,5,CautionPanel);
  
// using 2 MCP23017 for the CP will look like this
//  MCP23017_SendOutputData(CpAddr1, CautionPanel[0], CautionPanel[1]);
//  MCP23017_SendOutputData(CpAddr2, CautionPanel[2], CautionPanel[3]);
}
#endif //caution

#ifdef Glareshield_on

byte GlareShield[2];

void readGlareShield() {
  COM.print('G');
  COM.readBytes(GlareShield, 2);
}

void lightGlareshield() {
  MCP23017_SendOutputData(GsAddr, ~(GlareShield[1]), ~(GlareShield[0]));
}
#endif //Glareshield

#endif //ndef


