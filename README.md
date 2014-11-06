# DEDUino
Arduino Based DED for Falcon BMS

## Requirements:
### Hardware:
1. an Arduino or compatible board:
  * Arduino Uno (or compatible)
  * Arduino Micro (or compatible)
  * all other arduino types (mega/leonardo/Due) will require code to be adjusted
2. For DED/PFL: One 2.8" 256*64 OLED display, SSD1322 based
  * [BuyDisplay 2.8" yello on black oled](http://www.buydisplay.com/default/spi-2-8-inch-oled-arduino-256x64-graphic-module-with-pcb-yellow-on-black)
  * other screens may be also compatible - but may require code edit
3. For FFI: one 1.3" 128*64 OLED white on black. SSD1306 or SH1106 based
  * [Adafruit 1.3" 128*64 OLED](http://www.adafruit.com/product/938)
  * Generic 1.3" OLED (off the internet), will do fine as long as it's of one of the supported chipsets.
  * Other displays might be also compatible - but may require code edit
4. For Indexers/Caution panel:
  * [74HC595 Shift Register](http://www.adafruit.com/product/450) - can be also generic from ebay
  * LEDs of your choosing (If using attached PCB design unmodified - 5mm pirahna leds are used)
  * Resistors (220-330 ohm reesistors would be a good place to start)

### Software:
1. Arduino IDE with u8glib library installed
1. Windows Vista and up with .net 4.5 installed (XP does not suppoer .net4.5 and I've not tested the supplied connector app with .net4.0)
2. Falcon BMS 4.32+

## How to use:
### Initial setup:
1. Download and install the Arduino IDE (if not already installed)
2. Download the Arduino code - uncomment the correct define for your arduino version (Uno, Micro or Due).
3. In the Arduino IDE - "Add library" choose "U8glib_DEDuino" it's standard U8glib 1.16 with 16BIT support enabled (required for the large displays)
4. Uncomment the define statements for the periferials you want to use. please note that adding both DED and PFL may have an impact on performace.
5. Advanced - If needed modify the loop function (for PFD only configuration for example).
6. Wire prereferials according the the pinout in the code. Please pay attention to the SCK and MOSI pins and the latchpins
7. Upload code to your Arduino.
8. Download the DEDuino Windows app and place it in a folder of your choosing (no installation required)

### running the project:
1. launch DEDuino App
2. Select proper COM port for the arduino to be used and hit "Start"
3. Once connected - WIndows app will indicate connected status and all displays and leds should be blanked except for FFI screen that will show "00000".
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
3. Lights have some issues with the Due - I'm still debugging, but it's electrical thing, maybe too low voltage on the latch pin for the shift registers.
4. currently there is an issue with Micro/Due in using tow shift registers, with two screens, SPI freezes, again, it's an electrical thing I'm currently debugging.

## PCB
In the PCB folder you would find Eagle files and PDFs with schematics and board drawings. These are the boards I'm working with. You can make them yourself by hand soldering the connectors (see schematics) or source them out to production. All boards were edited using the Free version of Eagle (version 7).

## Enclosures
In the "enclosure" folders you'll find some stractual stuff, like the foamboard DED box.
