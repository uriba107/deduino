#ifndef lights_h
#define lights_h

#include "Arduino.h"

void initLights() {
#ifdef Indexers_on
  // Indexer
  pinMode(AoaLatchPin, OUTPUT);
  // Reset to off
  digitalWrite(AoaLatchPin, LOW); // pull Indexers CS low
  SPI.transfer(66); //light the two middle green lights (b01000010)
  digitalWrite(AoaLatchPin, HIGH); // light 'em up
#endif //indexers

#ifdef CautionPanel_on
  // Caution Panel
  pinMode(CpLatchPin, OUTPUT);
  digitalWrite(CpLatchPin, LOW); // pull caution panel CS low

  for (short i = 0; i < 4; i++) { //send 4 byte to clear Caution lights
    SPI.transfer(0);
  }
  digitalWrite(CpLatchPin, HIGH); // light 'em up

  #endif //caution
}

#ifdef Indexers_on
byte AoaIndexer[1];

void readAOA() {
  COM.print('A');
  COM.readBytes(AoaIndexer, 1);
}

void lightAOA() {
  digitalWrite(AoaLatchPin, LOW); // pull Indexers CS low
//  MICRO_DELAY
  SPI.transfer(AoaIndexer[0]);
  digitalWrite(AoaLatchPin, HIGH); // light 'em up
}
#endif //indexers

#ifdef CautionPanel_on

byte CautionPanel[4];

void readCautionPanel() {
  COM.print('C');
  COM.readBytes(CautionPanel, 4);
}

void lightCautionPanel() {
  digitalWrite(CpLatchPin, LOW); // pull caution panel CS low
//  MICRO_DELAY
  for (short i = 0; i < 4; i++) {
    SPI.transfer(CautionPanel[i]);
  }
  digitalWrite(CpLatchPin, HIGH); // light 'em up
}
#endif //caution

#endif //ndef

