
// Declare screen Object
U8GLIB_SSD1306_128X64_2X ffDisp(FF_SEL, DISP_A0); // SSD1306 based FFI screen (adafruit)
//U8GLIB_SH1106_128X64_2X ffDisp(FF_SEL, DISP_A0); // SH1106 based FFI screen (ebay) - thanks "MrWell"!


// Font settings
#define Bezel
// Original Settings
#ifdef Bezel
  #define ffFont fuelflow_u8g
  #define FF_CHAR_W 15
  #define FF_CHAR_H 24
  // Font offset - based on trial and error, not math
#define FF_H_CONST 12
#define FF_V_CONST 8
#else
  #define ffFont u8g_font_fub25n
  #define FF_CHAR_W 19
  #define FF_CHAR_H 27
  // Font offset - based on trial and error, not math
#define FF_H_CONST 1
#define FF_V_CONST 5
#endif




// Global Variable required
char FuelFlow[5];

////////////////////
//// Functions ////
///////////////////

void initFF() {
  ffDisp.begin();
  ffDisp.disableCursor(); //disable cursor, enable cursore use: enableCursor();
  ffDisp.setFont(ffFont);
  ffDisp.setFontPosCenter();
  /// Begin Picture loop ///
  ffDisp.firstPage();
  do {
    #ifdef Bezel
      ffDisp.drawStr(short((FF_CHAR_W * 0.5)) + FF_H_CONST, short(FF_CHAR_H * 0) + FF_V_CONST,"FUEL");
      ffDisp.drawStr((FF_CHAR_W * 4) + FF_H_CONST, short(FF_CHAR_H * 0) + FF_V_CONST,"FLOW");
      ffDisp.drawStr(short((FF_CHAR_W * 2.85)) + FF_H_CONST, short(FF_CHAR_H * 2)+ FF_V_CONST,"PPH");
    #else
      ffDisp.drawStr((FF_CHAR_W * 1) + FF_H_CONST, short(FF_CHAR_H * 1) + FF_V_CONST, "99999");
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
  // the thoulsends are static entries. insert them to their own char array
  char FFT[2];
  FFT[0] =  FuelFlow[0];
  FFT[1] =  FuelFlow[1];

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
  if (FuelFlow[2] == 57) { //a
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
  
  // use tens digit to calculate the off set for animation (tens and singles are alway 0 on the guage)
  short offset = short((FuelFlow[3] - 48) * FF_CHAR_H / 10); //it's a char - Ascii value of '0'
  /// Begin Picture loop ///
  ffDisp.firstPage();
  do {
    // thousend and tens of tousend
    ffDisp.drawStr((FF_CHAR_W * 1) + FF_H_CONST, short(FF_CHAR_H * 1) + FF_V_CONST, FFT);

    // print the animation
    ffDisp.setPrintPos((FF_CHAR_W * 3) + FF_H_CONST, short((FF_CHAR_H * -1)) + offset + FF_V_CONST);
    ffDisp.print(FFhTwoOver);
    ffDisp.setPrintPos((FF_CHAR_W * 3) + FF_H_CONST, short((FF_CHAR_H * 0)) + offset + FF_V_CONST);
    ffDisp.print(FFhNext);
    ffDisp.setPrintPos((FF_CHAR_W * 3) + FF_H_CONST, short((FF_CHAR_H * 1)) + offset + FF_V_CONST);
    ffDisp.print(FFh);
    ffDisp.setPrintPos((FF_CHAR_W * 3) + FF_H_CONST, short((FF_CHAR_H * 2)) + offset + FF_V_CONST);
    ffDisp.print(FFhPriv);

    ffDisp.drawStr((FF_CHAR_W * 4) + FF_H_CONST, short(FF_CHAR_H * 1) + FF_V_CONST, "00");
    
    #ifdef Bezel
      ffDisp.drawStr(short((FF_CHAR_W * 0.5)) + FF_H_CONST, short(FF_CHAR_H * 0) + FF_V_CONST,"FUEL");
      ffDisp.drawStr((FF_CHAR_W * 4) + FF_H_CONST, short(FF_CHAR_H * 0) + FF_V_CONST,"FLOW");
      ffDisp.setColorIndex(0);
      ffDisp.drawBox((FF_CHAR_W * 3) + FF_H_CONST, 0, (FF_CHAR_W), short(FF_CHAR_H*0.3));
      ffDisp.drawBox((FF_CHAR_W * 2) + FF_H_CONST, short(FF_CHAR_H * 1.75)+ FF_V_CONST, (FF_CHAR_W * 3), short(FF_CHAR_H*2));
      ffDisp.setColorIndex(1);
      ffDisp.drawStr(short((FF_CHAR_W * 2.85)) + FF_H_CONST, short(FF_CHAR_H * 2)+ FF_V_CONST,"PPH");
    #endif
  } while ( ffDisp.nextPage() );
  /// End Picture loop ///
}


