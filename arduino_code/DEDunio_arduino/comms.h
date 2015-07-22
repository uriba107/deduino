#ifndef comms_h
#define comms_h

#define SERIAL_TIMEOUT 50 // too low of a value will cause displays to jump as connection is not fast enogth
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


#define TIMER millis()-start_time
bool wentDark = false;


////////// Serial Operation Functions //////////////
void initSerial() {
  COM.begin(BAUDRATE * BAUDRATE_MULTIPLIER);
  COM.setTimeout(SERIAL_TIMEOUT);
}

bool SerialRDY() // Main serial init, allow PC know you are ready to recive data. wait for PC to respond before sending data request message
{
  unsigned short count = 0;
  bool addDelay = false; // begine with no delay
  unsigned long start_time = millis();
  char buff[5] = {0};
  while (COM.available() <= 0) // Wait for comm response
  {
    COM.print('R');
    if ( addDelay ) {
      if ((TIMER > SLEEP_TIMER * 1000) && (!wentDark)) { //if you have still not went dark, and timeout is over, set dark and getout to blackout everything (only once)
        wentDark = true;
        return false;
      }
      delay(40);
    }
    if ( (count > 10) && (!addDelay) ) { // If this is the 10th round, and delay was not set, add delay
      addDelay = true;
    } else {
      count++;
      MICRO_DELAY
    }
  }
  COM.readBytesUntil('G', buff, 2);
  wentDark = false;
  return true;
}


void updateSharedMem() {
  COM.print('U');
  char buff[3] = {0};
  COM.readBytesUntil('k', buff, 2);
}

#endif


