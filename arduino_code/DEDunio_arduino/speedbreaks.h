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
#define NUM_FRAMES 6


#define SB_IMG speedbreaks_indicator_bits
#define SB_IMG_W 192
#define SB_IMG_H 64

#define SB_OFFSET_H SB_IMG_H/2

#define SRC_OFFSET (-1*SB_IMG_H*SpeedBreaks[1])+SB_OFFSET_H
#define DST_OFFSET (-1*SB_IMG_H*SpeedBreaks[0])+SB_OFFSET_H


char SpeedBreaks[2] = {3};

void initSB() {
  sbDisp.begin();
  sbDisp.disableCursor(); //disable cursor, enable cursore use: enableCursor();
  /// Begin Picture loop ///
  sbDisp.firstPage();
  do {
    sbDisp.drawXBMP(-32, 0, SB_IMG_W, SB_IMG_H, SB_IMG); // Start with INOP
#ifdef crosshair
    sbDisp.drawFrame(0, 0, 128, 64);
    sbDisp.drawLine(64, 0, 64, 64);
    sbDisp.drawLine(0, 32, 128, 32);
#endif
  } while ( sbDisp.nextPage() );
  /// End Picture loop ///
}

void readSB() {
  SpeedBreaks[1] = SpeedBreaks[0];
  COM.print('S');
  commsCheck(COM.readBytes(SpeedBreaks, 1));
}

void drawSB() {
  if (SpeedBreaks[0] == 5) { // Check if SB is zeroed out (i.e value of 5, which is not something you'll get)
    sbDisp.firstPage();
    do {  } while ( sbDisp.nextPage() );
  } else if (SpeedBreaks[0] != SpeedBreaks[1]) { // if speedbreak value has changed (no need to re-render frame if it hadn't
    float offsetDelta = ((SRC_OFFSET) - (DST_OFFSET)) / NUM_FRAMES;
    for (short i = 0; i < NUM_FRAMES; i++) {
      if (i == 3 || i ==4 ) {
        break;
      }
      short frameOffset = (SRC_OFFSET) + (i * offsetDelta);
      sbDisp.firstPage();
      do {
        sbDisp.drawXBMP(frameOffset, 0, SB_IMG_W, SB_IMG_H, SB_IMG);
      }  while ( sbDisp.nextPage() );

    }
    sbDisp.firstPage();
    do {
      sbDisp.drawXBMP(DST_OFFSET, 0, SB_IMG_W, SB_IMG_H, SB_IMG);
    } while ( sbDisp.nextPage() );


  }
}


