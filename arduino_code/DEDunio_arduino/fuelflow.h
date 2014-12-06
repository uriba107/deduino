// Declare screen Object
U8GLIB_SSD1306_128X64_2X ffDisp(FF_SEL, DISP_A0); // SSD1306 based FFI screen (adafruit)
//U8GLIB_SH1106_128X64_2X ffDisp(FF_SEL, DISP_A0); // SH1106 based FFI screen (ebay) - thanks "MrWell"!

// Change these display sizes if needed
#define SCREEN_W 128
#define SCREEN_H 64

// Define bezel to draw FUEL FLOW and PPH on screen. (Bezel reduces FPS considerably) - if you build a real Bezel, this option should be off
#define Bezel
// Define RealFFI to draw "Real" FFI - when not defined a BMS style FFI is drawn (Real FFI has lover FPS
#define RealFFI

// For aligning purposes and debugging, enable
//#define crosshair

// FONT DEFINITIONS - Main fuel flow indicator digits
// - Define font
#define ffFont fuelflow_u8g // Main font used for actual digits indicating current fuel flow
// - Define Character width and height
#define FF_CHAR_W 20
#define FF_CHAR_H 30
// - Define Character horizontal and vertical offset. By design this text is perfectly centered on the display. Offset only when needed.
#define FF_H_CONST 0
#define FF_V_CONST 0
  
#ifdef Bezel
  // FONT DEFINITIONS - "FUEL FLOW"-text in bezel
  // - Define Character width and height, pertains to this particular font, best not change.
  #define BEZEL_FF_CHAR_W 10
  #define BEZEL_FF_CHAR_H 9
  // - Define Character horizontal and vertical offset, based on trial and error, not math
  #define BEZEL_FF_H_CONST 12 // in this case this is not used as an offset, but as a left and right indent for both "FUEL" and "FLOW"!
  #define BEZEL_FF_V_CONST 1

  // FONT DEFINITIONS - "PPH"-text in bezel
   // - Define Character width and height
  #define BEZEL_PPH_CHAR_W 6
  #define BEZEL_PPH_CHAR_H 11
  // - Define Character horizontal and vertical offset. Since PPH is perfectly centered, no need to adjust here.
  #define BEZEL_PPH_H_CONST 0 
  #define BEZEL_PPH_V_CONST 0
#endif

// NO NEED TO CHANGE ANYTHING BELOW THIS LINE !!


// Global Variable required
char FuelFlow[5];

// Some x,y positions are fixed throughout the running of the main loop. They never change.
// So, why not just calculate them once, store them into variables, and re-use these?
// It saves that tiny Arduino processor a whole lot of processing power, so instead of calculating
// coordinates over and over again, it can focus on just drawing.
// Things we need from here on: 
// - middle of screen, horizontal and vertical
// - "FUEL"-position
// - "FLOW"-position
// - "PPH"-position
// - "PPH"-wiping-box-position and size
// - the 3 positions for the FF-digits
// 

// Center of the used screen, based on screen size constants defined earlier
const unsigned short SCREEN_W_MID = SCREEN_W / 2;
const unsigned short SCREEN_H_MID = SCREEN_H / 2;

// Fuel flow number, X position for first two digits
const unsigned short FF_POS_X_1 = int(SCREEN_W_MID - ((FF_CHAR_W * 7) / 2)) + ((FF_CHAR_W + 1) * 1) + FF_H_CONST;
// Fuel flow number, X position for first two digits
const unsigned short FF_POS_X_2 = int(SCREEN_W_MID - ((FF_CHAR_W * 7) / 2)) + ((FF_CHAR_W + 1) * 2) + FF_H_CONST;
// Fuel flow number, X postion for third digit
const unsigned short FF_POS_X_3 = int(SCREEN_W_MID - ((FF_CHAR_W * 7) / 2)) + ((FF_CHAR_W + 1) * 3) + FF_H_CONST;
// Fuel flow number, X position for fourth and fifth digit
const unsigned short FF_POS_X_4 = int(SCREEN_W_MID - ((FF_CHAR_W * 7) / 2)) + ((FF_CHAR_W + 1) * 4) + FF_H_CONST;
// Fuel flow number, X position for fourth and fifth digit
const unsigned short FF_POS_X_5 = int(SCREEN_W_MID - ((FF_CHAR_W * 7) / 2)) + ((FF_CHAR_W + 1) * 5) + FF_H_CONST;
// Fuel flow number, Y position (base)
const unsigned short FF_POS_Y = SCREEN_H_MID + FF_V_CONST;

#ifdef Bezel
  // FUEL-position X and Y not needed, these are constants already. No need to spend more memory on putting them in new variables

  // FLOW-position X. Y-position already is a constant, so no need to re-calculate 
  const unsigned short FLOW_POS_X = SCREEN_W - BEZEL_FF_H_CONST - uint8_t(BEZEL_FF_CHAR_W * 4);

  // PPH-position X and Y
  const unsigned short PPH_POS_X = uint8_t(SCREEN_W_MID - ((BEZEL_PPH_CHAR_W * 3) / 2)) + BEZEL_PPH_H_CONST +1;
  const unsigned short PPH_POS_Y = SCREEN_H - BEZEL_PPH_V_CONST - 11;
  
    // X,Y, Width and height of the PPH wiper box
  const unsigned short WIPE_BOX_X = SCREEN_W_MID - uint8_t((BEZEL_PPH_CHAR_W * 3) / 2);
  const unsigned short WIPE_BOX_Y = PPH_POS_Y - 1;
  const unsigned short WIPE_BOX_W = uint8_t((BEZEL_PPH_CHAR_W + 1) * 3);
  const unsigned short WIPE_BOX_H = BEZEL_PPH_CHAR_H + 2;
  
  #ifdef RealFFI
  #define FF_WIPE_X 0
  #define FF_WIPE_TOP_Y 0
  const unsigned short FF_WIPE_BOTTOM_Y =  FF_POS_Y + (FF_CHAR_H/2);
  const unsigned short FF_WIPE_BOX_W = (FF_POS_X_3 - 2);
  const unsigned short FF_WIPE_BOX_H = (FF_POS_Y - (FF_CHAR_H /2));
  #endif 
#endif



////////////////////
//// Functions ////
///////////////////
#ifdef Bezel

#ifdef RealFFI
  
//void ExtendBezel() {
//  ffDisp.setColorIndex(0);
//  ffDisp.drawBox(0,FF_POS_Y - (FF_CHAR_H/2),((FF_CHAR_W * 2) + 2),FF_CHAR_H); //top box
//  ffDisp.drawBox(0,FF_POS_Y + (FF_CHAR_H/2),((FF_CHAR_W * 2) + 2 ),FF_CHAR_H); //Bottom box
//  ffDisp.setColorIndex(1);
//}
#endif
// Function drawBezel
// My intention is to create re-usable code. Why code something twice (having to change it twice if in error), when one can fix it with a function?
void drawBezel() {
// Wipe the PPH block
  ffDisp.setColorIndex(0);
  ffDisp.drawBox(WIPE_BOX_X, WIPE_BOX_Y, WIPE_BOX_W, WIPE_BOX_H ); // Clear the area below the "PPH" so the hundreds digits dont show there
 #ifdef RealFFI
  ffDisp.drawBox(FF_WIPE_X,FF_WIPE_TOP_Y,FF_WIPE_BOX_W ,FF_WIPE_BOX_H); //top box
  ffDisp.drawBox(FF_WIPE_X,FF_WIPE_BOTTOM_Y,FF_WIPE_BOX_W ,FF_WIPE_BOX_H); //Bottom box
  #endif
  ffDisp.setColorIndex(1);
// Draw the lettering
  ffDisp.drawStr(BEZEL_FF_H_CONST, BEZEL_FF_V_CONST, "FUEL");
  ffDisp.drawStr(FLOW_POS_X,  BEZEL_FF_V_CONST, "FLOW");
  ffDisp.drawStr(PPH_POS_X, PPH_POS_Y , "PPH");

}
#endif

void initFF() {
  ffDisp.begin();
  ffDisp.disableCursor(); //disable cursor, enable cursore use: enableCursor();
    ffDisp.setFont(ffFont);
    ffDisp.setFontPosCenter();
  /// Begin Picture loop ///
  ffDisp.firstPage();
  do {
    #ifdef Bezel
      drawBezel(); // Moved all this bezel stuff into a function to prevent us from needing to change everything twice
    #endif  

    // I've centered this in the same fashion as the "PPH"
    ffDisp.drawStr(FF_POS_X_1, FF_POS_Y, "99999");
    
    // Below crosshair is for alignment purposes. Defined at the top
    #ifdef crosshair
      ffDisp.drawFrame(0,0,128,64);
      ffDisp.drawLine(64,0,64,64);
      ffDisp.drawLine(0,32,128,32);
    #endif
    
  } while ( ffDisp.nextPage() );
  /// End Picture loop ///
}

void readFF() {
  COM.print('F');
  COM.readBytes(FuelFlow, 5) ;
}

void drawFF() {
  // break FuelFlow to segments for scroll animation
  // get hundred digit
  char FFh = FuelFlow[2];
  // Now for the animation  find the previuos next two digits.
  char FFhPriv;
  if (FuelFlow[2] == 48) {
    FFhPriv = 57;
  } else {
    FFhPriv = FuelFlow[2] - 1;
  }

  char FFhNext;
  if (FuelFlow[2] == 57) { //if it's a 9 then next is 0
    FFhNext = 48;
  } else {
    FFhNext = FuelFlow[2] + 1;
  }
  
  char FFhTwoOver;
  if (FFhNext == 57) {
    FFhTwoOver = 48;
  } else {
    FFhTwoOver = FFhNext + 1;
  }
// Now do the two upper digits logic - which is nothing if you are not using RealFFI  
  char FFtt = FuelFlow[0];
  char FFt = FuelFlow[1];

#ifdef RealFFI
byte RollOver; // to save memory, we will be using a single byte with bit flags
  #define FFtRollOver (RollOver & 0x01) // FFt is about to roll over
  #define FFttRollOver (RollOver & 0x02) // FFtt is about to roll over

    // FFt  
  char FFtNext;  
  char FFtPriv;

    if (FFt == 48) {
      FFtPriv = 57;
    } else {
      FFtPriv = FFt - 1;
    }  

    if (FFt == 57) { //a
      FFtNext = 48;  
    }  else {
      FFtNext = FFt + 1;
    }

    //FFtt  
  char FFttNext;
  char FFttPriv;
    if (FFtt == 48) {
      FFttPriv = 57;
    } else {
      FFttPriv = FFtt - 1;
    }
    if (FFtt == 57) { //
      FFttNext = 48;  
    } else {
      FFttNext = FFtt + 1;
    }    

  if (FFh == 57) { //If FFh is ASCII 9 we are at roll over (up or down doesn't matter)
      RollOver |= 0x01; //if FFh is 9 I'm going up
    // find above and below values 
    if (FFt == 57) { // if FFt is 9 and rolling over the FFt is rolling over
      RollOver |= 0x02;
    }
    
  }

#endif
// use tens digit to calculate the vertical offset for animation (tens and singles are alway 0 on the guage)
  short offset = short((FuelFlow[3] - 48) * FF_CHAR_H / 10); //it's a char - Ascii value of '0' is 48 so this translates the value from ascii to int
  /// Begin Picture loop ///
  ffDisp.firstPage();
  do {
    #ifdef RealFFI
    // Draw FFtt
    if (FFttRollOver) { // if rolling over - Animate
      ffDisp.setPrintPos(FF_POS_X_1, SCREEN_H_MID + short(((FF_CHAR_H + 1) * -1)) + offset + FF_V_CONST);
      ffDisp.print(FFttNext);
      ffDisp.setPrintPos(FF_POS_X_1, SCREEN_H_MID + short(((FF_CHAR_H + 1) * 0)) + offset + FF_V_CONST);
      ffDisp.print(FFtt);
      ffDisp.setPrintPos(FF_POS_X_1, SCREEN_H_MID + short(((FF_CHAR_H + 1) * 1)) + offset + FF_V_CONST);
      ffDisp.print(FFttPriv);
    } else { // just print
      ffDisp.setPrintPos(FF_POS_X_1, SCREEN_H_MID + short(((FF_CHAR_H + 1) * -1)) + FF_V_CONST);
      ffDisp.print(FFttNext);
      ffDisp.setPrintPos(FF_POS_X_1, SCREEN_H_MID + short(((FF_CHAR_H + 1) * 0)) + FF_V_CONST);
      ffDisp.print(FFtt);
      ffDisp.setPrintPos(FF_POS_X_1, SCREEN_H_MID + short(((FF_CHAR_H + 1) * 1)) + FF_V_CONST);
      ffDisp.print(FFttPriv);
    }
    // Draw FFt
    if (FFtRollOver) { //FFtRollOver rollOver is true then something is about to change - draw both up and down
      ffDisp.setPrintPos(FF_POS_X_2, SCREEN_H_MID + short(((FF_CHAR_H + 1) * -1)) + offset + FF_V_CONST);
      ffDisp.print(FFtNext);
      ffDisp.setPrintPos(FF_POS_X_2, SCREEN_H_MID + short(((FF_CHAR_H + 1) * 0)) + offset + FF_V_CONST);
      ffDisp.print(FFt);
      ffDisp.setPrintPos(FF_POS_X_2, SCREEN_H_MID + short(((FF_CHAR_H + 1) * 1)) + offset + FF_V_CONST);
      ffDisp.print(FFtPriv); 
    } else { //FFtRollOver is false - draw normal digits
      ffDisp.setPrintPos(FF_POS_X_2, SCREEN_H_MID + short(((FF_CHAR_H + 1) * -1)) + FF_V_CONST);
      ffDisp.print(FFtNext);
      ffDisp.setPrintPos(FF_POS_X_2, SCREEN_H_MID + short(((FF_CHAR_H + 1) * 0)) + FF_V_CONST);
      ffDisp.print(FFt);
      ffDisp.setPrintPos(FF_POS_X_2, SCREEN_H_MID + short(((FF_CHAR_H + 1) * 1)) + FF_V_CONST);
      ffDisp.print(FFtPriv); 
    }
    #else
    // Draw normal FFtt and FFt
      ffDisp.setPrintPos(FF_POS_X_1, SCREEN_H_MID + FF_V_CONST);
      ffDisp.print(FFtt); // First two digits
      ffDisp.setPrintPos(FF_POS_X_2, SCREEN_H_MID + FF_V_CONST);
      ffDisp.print(FFt); // First two digits
    #endif
    
    // print the FFh animation
    ffDisp.setPrintPos(FF_POS_X_3, SCREEN_H_MID + short(((FF_CHAR_H + 1) * -2)) + offset + FF_V_CONST);
    ffDisp.print(FFhTwoOver);
    ffDisp.setPrintPos(FF_POS_X_3, SCREEN_H_MID + short(((FF_CHAR_H + 1) * -1)) + offset + FF_V_CONST);
    ffDisp.print(FFhNext);
    ffDisp.setPrintPos(FF_POS_X_3, SCREEN_H_MID + short(((FF_CHAR_H + 1) * 0)) + offset + FF_V_CONST);
    ffDisp.print(FFh);
    ffDisp.setPrintPos(FF_POS_X_3, SCREEN_H_MID + short(((FF_CHAR_H + 1) * 1)) + offset + FF_V_CONST);
    ffDisp.print(FFhPriv);

    // Print the statics
    // thousand and tens of thousands
    // and two 0 for the end - two commants are for even spacing (at a cost of performance
    ffDisp.drawStr(FF_POS_X_4, SCREEN_H_MID + FF_V_CONST, "0"); // Last two digits
    ffDisp.drawStr(FF_POS_X_5, SCREEN_H_MID + FF_V_CONST, "0"); // Last two digits
    
    #ifdef Bezel
      drawBezel();
    #endif
  } while ( ffDisp.nextPage() );
  /// End Picture loop ///
}
