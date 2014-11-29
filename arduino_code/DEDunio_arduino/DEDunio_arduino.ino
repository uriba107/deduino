//*******************************************************************//
//  Name    : DEDuino, Arduino displays for FalconBMS                //
//  Author  : Uri Ben-Avraham                                        //
//  Date    : 1 Nov, 2014                                            //
//  Version : 1.0                                                    //
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
#include <SPI.h>

///////////////////////////////////////////////////////////////////////
// Select Arduino Type - Uncomment correct board type                //
///////////////////////////////////////////////////////////////////////

//#define ARDUINO_UNO
#define ARDUINO_MICRO
//#define ARDUINO_DUE


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


///////////////////////////////////////////////////////////////////////
// Module Defines                                                    //
// Uncomment The modules you want                                    //
///////////////////////////////////////////////////////////////////////
// Screens
#define Screens //global enable screens
#ifdef Screens
  #define DED_on
  #define FuelFlow_on
//  #define PFD_on // require "EXTRA" to be enabled
#endif

// Lightes
#define Lights //global enable lights
#ifdef Lights
  #define Indexers_on
//  #define CautionPanel_on // require "EXTRA" to be enabled
#endif

// Uncomment for extra features (Caution panel and PFD)
// Please note that too many featuers will casue a reduced FPS due to the increased traffic required.
//#define EXTRAS



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
  #include "falconded_full_u8g.h"
  #include "falconded_wide_u8g.h"
  #include "fuelflow_u8g.h"


  #ifdef DED_on
    #include "ded.h"
  #endif

  #ifdef FuelFlow_on
    #include "fuelflow.h"
  #endif

  #ifdef PFD_on
    #include "pfd.h"
  #endif
#endif

// LightPanels general config
// Light General
#ifdef Lights
    #define AoaLatchPin 2 // AOA indexed
    #define CpLatchPin 3 // Caution Panels
  
  #include "lights.h"
#endif

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
#ifdef ARDUINO_UNO
  pinMode(SS,OUTPUT);
  digitalWrite(SS,HIGH);
#endif
    SPI.begin();
    SPI.setBitOrder(LSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV2);

  delay(1000); // to allow screen to boot on power on

  initSerial();
  //  initSPI();
  #ifdef DED_on
    initDED();
  #endif
  #ifdef PFD_on
    initPFD();
  #endif
  #ifdef FuelFlow_on
    initFF();
  #endif
  #ifdef Lights
    initLights();
  #endif
}

void loop() {
  SerialRDY();

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
  
  // Non refresh critical function, run those every three loops.

#ifdef EXTRAS
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
#endif
}
