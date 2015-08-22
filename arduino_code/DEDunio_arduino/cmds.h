// Declare screen Object
U8GLIB_NHD31OLED_2X_BW cmdsDisp(CMDS_SEL, DISP_A0); //CMDS screen SSD1322 based 240*64 (Buydisplay/rising star)

// Font settings
//#define cmdsFont u8g_font_unifontr
////#define cmdsFont u8g_font_ncenR18
//#define CMDS_CHAR_W 14
//#define CMDS_CHAR_H 35
//#define CMDS_H_CONST 0
//#define CMDS_V_CONST 0

  #define cmdsFont FalconDED_full
  #define CMDS_CHAR_W 9
  #define CMDS_CHAR_H 35
// Font offset calc
// width: Screen is 256px wide. font is 9px wide. DED has 24 chars. 24*9=216 (Total text width). 256-216=40 diff. 40/2 = 20 offset in px to center text in screen
// Height: (64-(12*5))/2=2
  #define CMDS_H_CONST 0
  #define CMDS_V_CONST 2
//#endif
// Global Variable required
char CMDS[2][25] =  {{ 0 }};

////////////////////
//// Functions ////
///////////////////

void initCMDS() {
//  pinMode(CMDS_SEL, OUTPUT);

  cmdsDisp.begin();
  cmdsDisp.disableCursor(); //disable cursor, enable cursore use: enableCursor();
  cmdsDisp.setFont(cmdsFont);
  cmdsDisp.setFontPosTop();
  cmdsDisp.firstPage();
    do {
      cmdsDisp.drawStr(0, 0, "RDY");
    } while ( cmdsDisp.nextPage() );
}

void  readCMDS() {
  COM.print("M");
  for (short i = 0; i < 2; i++) {
    COM.print(i);
    COM.readBytes(CMDS[i], 24);
  }
}

void drawCMDS() {
  /// Begin Picture loop ///
  cmdsDisp.firstPage();
  do {
    for (unsigned short i = 0; i < 2; i++ ) {
      cmdsDisp.drawStr(CMDS_H_CONST, i * CMDS_CHAR_H + CMDS_V_CONST, CMDS[i]);
    }
  } while ( cmdsDisp.nextPage() );
  /// End Picture loop ///
}
