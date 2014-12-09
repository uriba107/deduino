///////////////////////////////////////////////////////////////////////
// Select Arduino Type - Uncomment correct board type                //
///////////////////////////////////////////////////////////////////////

//// Arduino Uno is the default as it is the most common - how ever it is NOT the recommended Arduino to use due to it's low amount of SRAM
//// Arduino Micro is considered the Minimum at this stage of the project
//// Arduino Due is the recommended Arduino in the long run (able to support future expansions)

#define ARDUINO_UNO
//#define ARDUINO_MICRO
//#define ARDUINO_DUE


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
  #define Indexers_on
//  #define CautionPanel_on 
#endif

///////////////////////////////////////////////////////////////////////
// Sub-Module config                                                 //
// Uncomment The options you want to enable                          //
///////////////////////////////////////////////////////////////////////


////////// DED/PFL //////////
//// DED and PFL use the same font to save memory, you have two possible fonts.
//// "Wide" variant is more readable - Font my Alan "Cool Hand" Locatelli. (enabled by default) 
#define Widefont

////////// FFI //////////
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
//// Feature is recommended - however disabled by default 
//#define RealFFI

////////// DEBUGGING //////////
//// Enable crosshair to help align text on screens ////
//#define crosshair
