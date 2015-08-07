# DEDUino
Arduino Based DED for Falcon BMS.
Project Blog: http://pits.108vfs.org

## Requirements:
### Hardware:
1. an Arduino or compatible board:
  * Arduino Uno (or compatible)
  * Arduino Micro (or compatible)
  * Arduino Due (or compatible)
  * all similar Arduino/Arduino-like variations (Mega/leonardo/pro Micro) will require code to be adjusted
2. For DED/PFL: One 2.8" or 3.2" 256*64 OLED display (yellow or green), SSD1322 based
  * [BuyDisplay 2.8" yellow on black oled](http://www.buydisplay.com/default/spi-2-8-inch-oled-arduino-256x64-graphic-module-with-pcb-yellow-on-black)
  * [BuyDisplay 3.2" green on black oled](http://www.buydisplay.com/default/spi-oled-manufacturer-256x64-display-panel-supplier-green-on-black)
  * other screens may be also compatible (as long as they are SSD1322 based) - but may require different wiring.
3. For FFI: one 1.3" 128*64 OLED white on black. SSD1306 or SH1106 based
  * [Adafruit 1.3" 128*64 OLED](http://www.adafruit.com/product/938)
  * Generic 1.3" OLED (off the internet), will do fine as long as it's of one of the supported chipsets.
  * Other displays might be also compatible - but may require code edit
4. For Indexers/Caution panel:
  * [PCF8574 8-bit I2C I/O Expander](http://www.ebay.com/sch/sis.html?_nkw=PCF8574P+PCF8574+DIP-16+NXP%2FPHI+Remote+8-bit+I%2FO+Expander+IC) - for Indexers
  * [MCP23017 16-bit I2C I/O Expander](http://www.ebay.com/sch/sis.html?_nkw=MCP23017-E%2FSP+DIP28+16-Bit+I%2FO+Expander+with+I2C+Interface+IC) - optional 16 bit extender (useful for caution panel and other things)
  * LEDs of your choosing (If using attached PCB design unmodified - 5mm pirahna leds are used)
  * Resistors (220-330 ohm reesistors would be a good place to start)
  * Legacy SPI lights are using [74HC595 Shift Register](http://www.adafruit.com/product/450) - you can find them on ebay as well.

### Software:
1. Arduino IDE
2. Windows Vista and up with .net 4.5 installed (XP does not support .net4.5 and I've not tested the supplied connector app with .net4.0)
3. Falcon BMS 4.32+

## How to use:
### Initial setup:
1. Download and install the Arduino IDE (if not already installed)
2. Download the Arduino code
3. In the Arduino IDE - "Add library" choose "U8glib_DEDuino" it's standard U8glib 1.18.1 with 16BIT support enabled (required for the large displays)
4. In "config.h" and uncomment the correct define for your arduino version (Uno, Micro or Due).
5. In "config.h" Uncomment the define statements for the periferials you want to use. please note that adding both DED and PFL may have an impact on performace.
6. Wire prereferials according the the pinout in the code. Please pay attention to the SCK and MOSI pins and the latchpins
7. Upload code to your Arduino.
8. Download the DEDuino Windows app and place it in a folder of your choosing (no installation required)

### running the project:
1. launch DEDuino App
2. Select proper COM port for the arduino to be used and hit "Start"
3. Once connected - Windows app will indicate connected status and all displays and leds should be blanked except for FFI screen that will show "00000".
4. Launch Falcon BMS - As soon as you enter the cockpit, all the instruments connected should display acording to the pit.

## Supported instruments:
1. Displays:
  * DED - Tier 1
  * FFI - Tier 1
  * PFD - Tier 1 (disabled by default due to performance considuration)
2. Lights:
  * Indexers - Tier 1
  * Caution Panel - Tier 1 (Disabled by default due to performance consideration)
3. Future supported instruments:
  * Glareshield lighs - TBD
  * Threat Warning Prime - TBD
  * CMDS - via OLED screen, TBD

## Knows issues:
1. Activating more the one large res display (DED/PFD) will cause performace degradation. Activating more then two might cause noticable lag without further optimization to Arduino code (not yet implemented).
2. "lamp test" might not work properly for Caution panel is some scenarios.
3. When using SPI for driving multiple light arrays, there are issues including freezes, wrongly timed blinks and all sort of wierd shananigans. That is way, I2C is now the primary, prefered protocol for driving lights. SPI support will not be extended, and only retained for comptability.

## PCB
In the PCB folder you would find Eagle files and PDFs with schematics and board drawings. These are the boards I'm working with. You can make them yourself by hand soldering the connectors (see schematics) or source them out to production. All boards were edited using the Free version of Eagle (version 7).

## Enclosures
In the "enclosure" folders you'll find some stractual stuff, like the foamboard DED box.

## Notes and remarks
While the project is OpenSource. Currently I'm holding back the source code for the PC connector application. That is done because The code is a mess, I need to properly document it before I release it. Hopfully sometime this year. Nothing secret about it, promise :)
