///////////////////////////////////////////////////////////////////////
// Select Arduino Type - Uncomment correct board type                //
///////////////////////////////////////////////////////////////////////

//// Arduino Uno is the default as it is the most common - how ever it is NOT the recommended Arduino to use due to it's low amount of SRAM
//// Arduino Micro is considered the Minimum at this stage of the project
//// Arduino Due is the recommended Arduino in the long run (able to support future expansions)
//// There are two USB connections on the DUE, the NATIVE is the recommended, but in some cases driver issues may strike.

//#define ARDUINO_UNO
//#define ARDUINO_MICRO
#define ARDUINO_DUE_NATIVE
//#define ARDUINO_DUE_PROG



///////////////////////////////////////////////////////////////////////
// Module Defines                                                    //
// Uncomment The modules you want                                    //
// Without this settings Nothing will work                           //
// NOTE: Lights are going to be overhauled in V1.2                   //
///////////////////////////////////////////////////////////////////////

#define Screens //global enable screens
//#define Lights //global enable lights 


///////////////////////////////////////////////////////////////////////
// Sub-Module Defines                                                //
// Uncomment The modules you want                                    //
///////////////////////////////////////////////////////////////////////
#ifdef Screens
  #define DED_on
  #define FuelFlow_on
//  #define PFD_on 
#endif

#ifdef Lights
// Select transfer protocol (SPI or I2C)
// SPI is retained for legacy support I2C is preferable
  //#define USE_SPI
  #define USE_I2C
  
// Choose what to light up
// Available to both protocols
  #define Indexers_on
//  #define CautionPanel_on 

// Available only on I2C
//  #define Glareshield_on 
#endif


///////////////////////////////////////////////////////////////////////
// Sub-Module config                                                 //
// Uncomment The options you want to enable                          //
///////////////////////////////////////////////////////////////////////


////////// DED/PFL //////////
//// DED and PFL use the same font to save memory, you have two possible fonts.
//// "Wide" variant is more readable - Font my Alan "Cool Hand" Locatelli. (enabled by default) 
//#define Widefont
//// Another Variant based on Alan's Widefont. tweaked to be more lifelike
#define MoonWidefont

////////// FFI //////////
//*****************************************************************************************//
//** NOTE:                                                                               **// 
//** Due to performance issues, when using Arduino Uno,                                  **//
//** The RealFFI animation and the Bezel will be Automaticly disabled (check fuelflow.h) **//
//*****************************************************************************************//

//// Select the correct FFI display driver
//// SSD1306 dispaly drivers (such as the ones sold by Adafruit and sparkfun)
#define FFI_SSD1306

//// SH1106 display drivers (commonly found on ebay)
//#define FFI_SH1106

//** NOTE: Ebay bought displays are sometime mislabled and SH1106 displays may be SSD1306 (and vice versa) **//

/// Define bezel to draw FUEL FLOW and PPH on screen.
//// Bezel reduces FPS considerably - if you build a real Bezel, this option should be off
#define Bezel

//// Define RealFFI to draw "Real" FFI - when not defined a BMS style FFI is drawn
//// Real FFI animation requires more RAM available there for is not suitable for an Uno if DED/PFL are enabled
//// This feature will be automaticly disabled when using arduino Uno
#define RealFFI

////////// DEBUGGING //////////
//// Enable crosshair to help align text on screens ////
//#define crosshair

///*************** DO NOT EDIT BELOW THIS LINE WITHOUT INTENT! ***************//
// if any of the DUE options are enabled, enable the global DUE flag
#if defined(ARDUINO_DUE_NATIVE) || defined(ARDUINO_DUE_PROG)
  #define ARDUINO_DUE
#endif
///////////////////////////////////////////////////////////////////////
// Sub-Module Pinout configurations                                  //
// (Advanced settings - Don't change unless you mean it              //
///////////////////////////////////////////////////////////////////////

// Screen pins should be relativly static
#ifdef Screens
  #if defined(ARDUINO_UNO) || defined(ARDUINO_DUE)
    #define DISP_A0 9
    #define DED_SEL 8
    #define FF_SEL 7
    #define PFD_SEL 6
    #define CMDS_SEL 5
    #define EXT1_SEL 4
    #define EXT2_SEL 3
  #endif

  #ifdef ARDUINO_MICRO
    #define DISP_A0 12
    #define DED_SEL 11
    #define FF_SEL 10
    #define PFD_SEL 9
    #define CMDS_SEL 8
    #define EXT1_SEL 7
    #define EXT2_SEL 6
  #endif
#endif

// Adjust i2c addresses to fit your rig.
// you will probably need to adjust the lights_i2c.h and i2c_hardware.h to suit your specific board/hardware
#ifdef Lights
   #ifdef USE_I2C
       #define AoaAddr 0x20
       #define CpAddr  0x21
//       #define CpAddr2  0x22
       #define GsAddr  0x23

   #endif
// Retained for Legacy support - i2c is preferable.
   #ifdef USE_SPI
       #define AoaLatchPin 2 // AOA indexed
       #define CpLatchPin 3 // Caution Panels
   #endif
#endif

////////// INTERNAL VARS //////////
// How many seconds should go by before screens turn off after no response recived to the "I'm alive" signal
#define SLEEP_TIMER 120

// How many milliseconds go before the displays reset after initillizing (for user inspection)
#define POST_BOOT_BIT 4000
