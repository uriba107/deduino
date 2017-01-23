
// Declare screen Object
#ifdef ARDUINO_DUE
  #ifndef rotateDED
    U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI dedDisp(U8G2_R2,DED_SEL, DISP_A0); //DED screen SSD1322 based 256*64 (Buydisplay/rising star)
  #else
    U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI dedDisp(U8G2_R0,DED_SEL, DISP_A0); //DED screen SSD1322 based 256*64 (Buydisplay/rising star)
  #endif
#else
  #ifndef rotateDED
    U8G2_SSD1322_NHD_256X64_1_4W_HW_SPI dedDisp(U8G2_R2,DED_SEL, DISP_A0); //DED screen SSD1322 based 256*64 (Buydisplay/rising star)
  #else
    U8G2_SSD1322_NHD_256X64_1_4W_HW_SPI dedDisp(U8G2_R0,DED_SEL, DISP_A0); //DED screen SSD1322 based 256*64 (Buydisplay/rising star)
  #endif
#endif

// Font settings
// Font offset calc
// width: Screen is 256px wide. font is 9px wide. DED has 24 chars. 24*9=216 (Total text width). 256-216=40 diff. 40/2 = 20 offset in px to center text in screen
// Height: (64-(12*5))/2=2
  #define dedFont FalconDED_wide
  #define DED_CHAR_W 10
  #define DED_CHAR_H 12
  #define DED_H_CONST 12
  #define DED_V_CONST 1

// Global Variable required
char DED[5][25] = {{ 0 }};

////////////////////
//// Functions ////
///////////////////

    
void initDED() {
  //  pinMode(DED_SEL, OUTPUT);
  dedDisp.begin();

//  dedDisp.disableCursor(); //disable cursor, enable cursore use: enableCursor();
  dedDisp.setFont(dedFont);
  dedDisp.setFontPosTop();
  dedDisp.firstPage();
  do {
    dedDisp.drawStr(DED_H_CONST, 2 * DED_CHAR_H + DED_V_CONST, "DED - READY!");
    
// Below crosshair is for alignment purposes. Defined at config.h
    #ifdef crosshair
      dedDisp.drawFrame(0,0,256,64);
      dedDisp.drawLine(128,0,128,64);
      dedDisp.drawLine(0,32,256,32);
    #endif
  } while ( dedDisp.nextPage() );
}

void  readDED() {
  COM.print("d");
  for (short i = 0; i < 5; i++) {
    COM.print(i); 
    commsCheck(COM.readBytes(DED[i], 24));
  }
}

void drawDED() {
  /// Begin Picture loop ///
//  MICRO_DELAY
  dedDisp.firstPage();
  do {
    for (unsigned short i = 0; i < 5; i++ ) {
      dedDisp.drawStr(DED_H_CONST, i * DED_CHAR_H + DED_V_CONST, DED[i]);
    }
  } while ( dedDisp.nextPage() );
  /// End Picture loop ///
}
