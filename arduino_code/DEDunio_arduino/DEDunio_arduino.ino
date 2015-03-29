//*******************************************************************//
//  Name    : DEDuino, Arduino displays for FalconBMS                //
//  Author  : Uri Ben-Avraham                                        //
//  Date    : 30 Mar, 2015                                           //
//  Version : 1.2.0-alpha2                                           //
//  License : MIT                                                    //
//  Notes   : Uncomment the DEFINE for the Arduino board in use      //
//          : Boards supported by this version:                      //
//          : Arduino Uno, Arduino Micro & Arduino Due               //
//          :                                                        //
//          : Uncomment the DEFINE for the features you wish to use  //
//          : Features included in this version:                     //
//          : Displays: DED, FFI, PFD                                //
//          : Lights: Indexers, Caution Panel                        //
//*******************************************************************//

#include <Arduino.h>
#include "config.h"
//*******************************************************************//
//  All configuration options are set via the "config.h" file        //
//  Please DO NOT edit code below this segment                       //
//  (Unless you know what you are doing - in which case.. have fun!) //
//*******************************************************************//


///*************** DO NOT EDIT BELOW THIS LINE WITHOUT INTENT! ***************//
///********** ALL COMMON CONFIG OPTIONS ARE FOUND THE config.h FILE **********//
#define MICRO_DELAY delayMicroseconds(100);
#ifdef ARDUINO_UNO
///////////////////////////////////////////////////////////////////////
//  Arduino Uno                                                      //
//  SCK - Pin 13                                                     //
//  MISO - Pin 12 (not used in this project)                         //
//  MOSI - Pin 11                                                    //
//  SS - Pin10 (set to output and pulled high on setup)              //
///////////////////////////////////////////////////////////////////////
// Define SPI Pins
#define SCK 13
#define MISO 12
#define MOSI 11
#define SS 10
#endif

#ifdef ARDUINO_MICRO
///////////////////////////////////////////////////////////////////////
//  Arduino Micro                                                    //
//  SCK, MISO, MOSI - all on dedicated pins no defines needed        //
//  Just plug the Arduino Micro into the Main PCB                    //
///////////////////////////////////////////////////////////////////////
#endif

#ifdef ARDUINO_DUE
///////////////////////////////////////////////////////////////////////
//  Arduino Due                                                      //
//  SCK, MISO, MOSI - all located on the ICSP header                 //
//  Only MOSI and SCK needs to be connected via the ICSP             //
//                                                                   //
//     1 - MISO | 0 0 | 2 - VCC                                      //
//     3 - SCK  | 0 0 | 4 - MOSI                                     //
//     5 - Reset| 0 0 | 6 - GND                                      //
//                                                                   //
///////////////////////////////////////////////////////////////////////
#endif

///////////////////
//// Includes ////
//////////////////

// Serial Comm
#include "comms.h"

// displays
#ifdef Screens
#if defined(ARDUINO_UNO) || defined(ARDUINO_DUE)
#define DISP_A0 9
#define DED_SEL 8
#define FF_SEL 7
#define PFD_SEL 6
#endif

#ifdef ARDUINO_MICRO
#define DISP_A0 12
#define DED_SEL 11
#define FF_SEL 10
#define PFD_SEL 9
#endif

#include "U8glib.h"

#ifdef FuelFlow_on
#include "fuelflow_u8g.h"
#include "fuelflow.h"
#endif

#if defined DED_on || defined PFD_on
#ifdef Widefont
#include "falconded_wide_u8g.h"
#elif defined  MoonWidefont
#include "falconded_moon_u8g.h"
#else
#include "falconded_full_u8g.h"
#endif
#endif

#ifdef DED_on
#include "ded.h"
#endif

#ifdef PFD_on
#include "pfd.h"
#endif
#endif

// LightPanels general config
// Light General
#ifdef Lights
#ifdef USE_SPI
#include <SPI.h>
#define AoaLatchPin 2 // AOA indexed
#define CpLatchPin 3 // Caution Panels
#include "lights_spi.h"
#endif
#ifdef USE_I2C
#include <Wire.h>
#define AoaAddr 0x20
#define CpAddr1 0x24
#define CpAddr2 0x25
#include "lights_i2c.h"
#endif
#endif

#include "internal.h"
///////////////////////////
//// Global Variables  ////
///////////////////////////

short Run = 0;

////////////////////
//// Functions ////
///////////////////

/////// Main Program /////////////
void setup() {
  // Init SPI
#ifdef Lights
#ifdef USE_SPI
#ifdef ARDUINO_UNO
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);
#endif
  SPI.begin();
#ifdef ARDUINO_DUE
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(10);
#else
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
#endif
#endif

#ifdef USE_I2C
  Wire.begin();
#endif
#endif

  delay(1000); // to allow screen to boot on power on

  initSerial();

#ifdef FuelFlow_on
  initFF();
#endif
#ifdef DED_on
  initDED();
#endif
#ifdef PFD_on
  initPFD();
#endif

#ifdef Lights
  initLights();
#endif
}

void loop() {
  if (!SerialRDY()) {
    goDark();
  }
  // Fuel Flow
#ifdef FuelFlow_on
  updateSharedMem();
  readFF();
  drawFF();
#endif

  //DED
#ifdef DED_on
  updateSharedMem();
  readDED();
  drawDED();
#endif

  // Fuel Flow (again) - for refresh rate
#ifdef FuelFlow_on
  updateSharedMem();
  readFF();
  drawFF();
#endif
  // Indexers
#ifdef Indexers_on
  updateSharedMem();
  readAOA();
  lightAOA();
#endif

  // Non refresh critical function, run those alternating every loop.
  switch (Run) {
    case 0:
#ifdef PFD_on
      updateSharedMem();
      readPFD();
      drawPFD();
#endif
      Run = 1;
      break;
    case 1:
#ifdef CautionPanel_on
      // Caution panel
      updateSharedMem();
      readCautionPanel();
      lightCautionPanel();
#endif
      Run = 0;
      break;
  }
}
