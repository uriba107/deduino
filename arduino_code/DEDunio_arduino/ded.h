
// Declare screen Object
U8GLIB_NHD31OLED_2X_BW dedDisp(DED_SEL, DISP_A0); //DED screen SSD1322 based 240*64 (Buydisplay/rising star)

// Font settings
#define dedFont FalconDED_full
#define DED_CHAR_W 9
#define DED_CHAR_H 12
// Font offset calc
// width: Screen is 256px wide. font is 9px wide. DED has 24 chars. 24*9=216 (Total text width). 256-216=40 diff. 40/2 = 20 offset in px to center text in screen
// Height: (64-(12*5))/2=2
#define DED_H_CONST 20
#define DED_V_CONST 2


// Global Variable required
char DED[5][26] = {{ 0 }};

////////////////////
//// Functions ////
///////////////////

void initDED() {
  //  pinMode(DED_SEL, OUTPUT);
  dedDisp.begin();
  dedDisp.disableCursor(); //disable cursor, enable cursore use: enableCursor();
  dedDisp.setFont(dedFont);
  dedDisp.setFontPosTop();
  dedDisp.firstPage();
  do {
    dedDisp.drawStr(DED_H_CONST, 2 * DED_CHAR_H + DED_V_CONST, "DED - READY!");
  } while ( dedDisp.nextPage() );
}

void  readDED() {
  for (short i = 0; i < 5; i++) {
    COM.print("D");
    COM.print(i);
//    Serial.flush();
    COM.readBytes(DED[i], 25);
  }
}

void drawDED() {
  /// Begin Picture loop ///
  dedDisp.firstPage();
  do {
    for (unsigned short i = 0; i < 5; i++ ) {
      dedDisp.drawStr(DED_H_CONST, i * DED_CHAR_H + DED_V_CONST, DED[i]);
    }
  } while ( dedDisp.nextPage() );
  /// End Picture loop ///
}


