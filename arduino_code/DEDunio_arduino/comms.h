#ifndef comms_h
#define comms_h

#define SERIAL_TIMEOUT 250 // too low of a value will cause displays to jump as connection is not fast enogth
#define BAUDRATE 9600 // base baud rate

#ifdef ARDUINO_UNO
  #define BAUDRATE_MULTIPLIER 3 // Serial speed multiplier - 3 is a safe number for Ardiuno Uno on a USB hub, YMMV depending on your board and configuration
#endif

#if defined(ARDUINO_MICRO) || defined(ARDUINO_DUE)
  #define BAUDRATE_MULTIPLIER 12 // native USB serial - speed is irrlevent it's hardware controled but setting a common cap limit seems like a good idea
#endif

#if defined(ARDUINO_UNO) || defined(ARDUINO_MICRO)
  #define COM Serial
#endif
#ifdef ARDUINO_DUE
  #define COM SerialUSB
#endif



void initSerial() {
  COM.begin(BAUDRATE * BAUDRATE_MULTIPLIER);
  COM.setTimeout(SERIAL_TIMEOUT);
}

void SerialRDY() // Main serial init, allow PC know you are ready to recive data. wait for PC to respond before sending data request message
{
  while (COM.available() <= 0)
  {
    COM.print('R');
    delay(5);
  }
  char buff[1];
  COM.readBytesUntil('G', buff, 1);
}

////////// Serial Operation Functions //////////////
void updateSharedMem() {
  COM.print('U');
  char buff[1];
  COM.readBytesUntil('k', buff, 1);
}

#endif

