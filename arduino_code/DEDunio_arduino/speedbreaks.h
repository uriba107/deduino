// Declare screen Object
#ifdef SB_SSD1306
U8GLIB_SSD1306_128X64_2X sbDisp(EXT1_SEL, DISP_A0); // SSD1306 based FFI screen (adafruit/Ebay)
#endif
#ifdef SB_SH1106
U8GLIB_SH1106_128X64_2X sbDisp(EXT1_SEL, DISP_A0); // SH1106 based FFI screen (ebay) - thanks "MrWell"!
#endif

// Change these display sizes if needed
#define SB_SCREEN_W 128
#define SB_SCREEN_H 64



#define SB_IMG speedbreaks_indicator_bits
#define SB_IMG_W 192
#define SB_IMG_H 64

#define SB_OFFSET_H 32

#define OFFSET (-1*SB_IMG_H*SpeedBreaks[0])+SB_OFFSET_H
char SpeedBreaks[3] = {0};

void initSB() {
  sbDisp.begin();
//  sbDisp.disableCursor(); //disable cursor, enable cursore use: enableCursor();
  /// Begin Picture loop ///
  sbDisp.firstPage();
  do {
    sbDisp.drawXBMP(-32, 0, SB_IMG_W, SB_IMG_H, SB_IMG);
#ifdef crosshair
    sbDisp.drawFrame(0, 0, 128, 64);
    sbDisp.drawLine(64, 0, 64, 64);
    sbDisp.drawLine(0, 32, 128, 32);
#endif
  } while ( sbDisp.nextPage() );
  /// End Picture loop ///
}

void readSB() {
  SpeedBreaks[2] = SpeedBreaks[0];
  COM.print('S');
  commsCheck(COM.readBytes(SpeedBreaks, 1));
}

void drawSB() {
  if (SpeedBreaks[0] == 3) { // Check if FF is zeroed out (i.e middle digit is null (not the number 0)
    sbDisp.firstPage();
    do {  } while ( sbDisp.nextPage() );
  } else if (SpeedBreaks[2] != SpeedBreaks[0]) {
    sbDisp.firstPage();
    do {
      sbDisp.drawXBMP(OFFSET, 0, SB_IMG_W, SB_IMG_H, SB_IMG);
    } while ( sbDisp.nextPage() );

  }
}


