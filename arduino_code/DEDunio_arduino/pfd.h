// Declare screen Object
U8GLIB_NHD31OLED_2X_BW pfdDisp(PFD_SEL, DISP_A0); //PFD screen SSD1322 based 240*64 (Buydisplay/rising star)

// Define crosshair for debugging
//#define crosshair

// Font settings
#define Widefont
#ifdef Widefont
  #define pfdFont FalconDED_wide
  #define PFD_CHAR_W 10
  #define PFD_CHAR_H 12
// Font offset calc
// width: Screen is 256px wide. font is 9px wide. DED has 24 chars. 24*10=240 (Total text width). 256-240=16 diff. 16/2 = 8 offset in px to center text in screen
// Height: (64-(12*5))/2=2
  #define PFD_H_CONST 8
  #define PFD_V_CONST 2
#else
  #define pfdFont FalconDED_full
  #define PFD_CHAR_W 9
  #define PFD_CHAR_H 12
// Font offset calc
// width: Screen is 256px wide. font is 9px wide. DED has 24 chars. 24*9=216 (Total text width). 256-216=40 diff. 40/2 = 20 offset in px to center text in screen
// Height: (64-(12*5))/2=2
  #define PFD_H_CONST 20
  #define PFD_V_CONST 2
#endif




// Global Variable required
char PFD[5][26] =  {{ 0 }};

////////////////////
//// Functions ////
///////////////////

void initPFD() {
  pfdDisp.begin();
  pfdDisp.disableCursor(); //disable cursor, enable cursore use: enableCursor();
  pfdDisp.setFont(pfdFont);
  pfdDisp.setFontPosTop();
    pfdDisp.firstPage();
  do {
    pfdDisp.drawStr(PFD_H_CONST, 2 * PFD_CHAR_H + PFD_V_CONST, "PFD - READY!");
    #ifdef crosshair
      pfdDisp.drawFrame(0,0,256,64);
      pfdDisp.drawLine(128,0,128,64);
      pfdDisp.drawLine(0,32,256,32);
    #endif
  } while ( pfdDisp.nextPage() );
}

void  readPFD() {
  for (short i = 0; i < 5; i++) {
    COM.print("P");
    COM.print(i);
    COM.readBytes(PFD[i], 25);
  }
}

void drawPFD() {
  /// Begin Picture loop ///
  pfdDisp.firstPage();
  do {
    for (unsigned short i = 0; i < 5; i++ ) {
      pfdDisp.drawStr(PFD_H_CONST, i * PFD_CHAR_H + PFD_V_CONST, PFD[i]);
    }
  } while ( pfdDisp.nextPage() );
  /// End Picture loop ///
}

