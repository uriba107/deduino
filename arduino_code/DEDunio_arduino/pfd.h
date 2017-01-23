// Declare screen Object
#ifdef ARDUINO_DUE
  #ifndef rotatePFD
    U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI pfdDisp(U8G2_R2,PFD_SEL, DISP_A0); //DED screen SSD1322 based 256*64 (Buydisplay/rising star)
  #else
    U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI pfdDisp(U8G2_R0,PFD_SEL, DISP_A0); //DED screen SSD1322 based 256*64 (Buydisplay/rising star)
  #endif
#else
  #ifndef rotatePFD
    U8G2_SSD1322_NHD_256X64_1_4W_HW_SPI pfdDisp(U8G2_R2,PFD_SEL, DISP_A0); //DED screen SSD1322 based 256*64 (Buydisplay/rising star)
  #else
    U8G2_SSD1322_NHD_256X64_1_4W_HW_SPI pfdDisp(U8G2_R0,PFD_SEL, DISP_A0); //DED screen SSD1322 based 256*64 (Buydisplay/rising star)
  #endif
#endif

// Font settings
  #define pfdFont FalconDED_wide
  #define PFD_CHAR_W 10
  #define PFD_CHAR_H 12
// Font offset calc
// width: Screen is 256px wide. font is 9px wide. DED has 24 chars. 24*10=240 (Total text width). 256-240=16 diff. 16/2 = 8 offset in px to center text in screen
// Height: (64-(12*5))/2=2
  #define PFD_H_CONST 8
  #define PFD_V_CONST 2


// Global Variable required
char PFD[5][25] =  {{ 0 }};

////////////////////
//// Functions ////
///////////////////

void initPFD() {
  pfdDisp.begin();
//#ifdef rotatePFD
//  pfdDisp.setRot180();
//#endif
//  pfdDisp.disableCursor(); //disable cursor, enable cursore use: enableCursor();
  pfdDisp.setFont(pfdFont);
  pfdDisp.setFontPosTop();
  pfdDisp.firstPage();
  do {
    pfdDisp.drawStr(PFD_H_CONST, 2 * PFD_CHAR_H + PFD_V_CONST, "PFD - READY!");
// Below crosshair is for alignment purposes. Defined at config.h   
    #ifdef crosshair
      pfdDisp.drawFrame(0,0,256,64);
      pfdDisp.drawLine(128,0,128,64);
      pfdDisp.drawLine(0,32,256,32);
    #endif
  } while ( pfdDisp.nextPage() );
}

void  readPFD() {
  COM.print("p");
  for (short i = 0; i < 5; i++) {
    COM.print(i);
    COM.readBytes(PFD[i], 24);
  }
}

void drawPFD() {
//  MICRO_DELAY
  /// Begin Picture loop ///
  pfdDisp.firstPage();
  do {
    for (unsigned short i = 0; i < 5; i++ ) {
      pfdDisp.drawStr(PFD_H_CONST, i * PFD_CHAR_H + PFD_V_CONST, PFD[i]);
    }
  } while ( pfdDisp.nextPage() );
  /// End Picture loop ///
}


