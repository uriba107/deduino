#ifndef i2c_hardware_h
#define i2c_hardware_h

#include "Arduino.h"

//////// Hardware functions ///////////

///////////////////////////////////////////////////
///// PCF8574 - I2C 8bit output expander      /////
///// Can only sinks LEDs - no init needed    /////
///////////////////////////////////////////////////
void PCF8574_send (byte addr, byte data) {
  Wire.beginTransmission(addr); // transmit to device
  Wire.write(data);              // sends one byte
  Wire.endTransmission();
}

///////////////////////////////////////////////////
///// MCP23017 - i2c 16bit I/O expander       /////
///// source or sink LEDs - output by default /////
///////////////////////////////////////////////////
void MCP23017_SetOutptMode (byte addr) {
  Wire.beginTransmission(addr); // transmit to device
  Wire.write(0x00); // Set IODIR0
  Wire.write(0); // Set IODIR0 to output
  Wire.write(0);  // Set IODIR1 to output
  Wire.endTransmission();
}
void MCP23017_SendOutputData (byte addr, byte data0, byte data1) {
  Wire.beginTransmission(addr); // transmit to device 
  Wire.write(0x12); // Set IODIR0
  Wire.write(data0); // Set IODIR0 to output
  Wire.write(data1);  // Set IODIR1 to output
  Wire.endTransmission();
}
///////////////////////////////////////////////////
///// PCA9505 - i2c 40bit I/O expander        /////
///// source or sink LEDs - output by default /////
///////////////////////////////////////////////////
void PCA9505_SetOutptMode (byte addr) {
  Wire.beginTransmission(addr); // transmit to device
  Wire.write(0x98); // Set IO Direction from Bank0 with Auto increment
  for (uint8_t i=0; i < 5; i++){
    Wire.write(0x00); // Set Bank to output  
  }
  Wire.endTransmission();
}

void PCA9505_SendOutputData (byte addr, uint8_t datalength, byte *data) {
  Wire.beginTransmission(addr); // transmit to device 
  Wire.write(0x88); // Output mode, AutoIncrement, start from Bank0
  for (uint8_t i=0; i < datalength; i++){
    Wire.write(data[i]); // Set Bank output value
  }
  Wire.endTransmission();
}

#endif
