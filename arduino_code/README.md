## DEDuino - Arduino code
This Is the Arduino side of the project, Licensed under MIT license.

### Usage:
The code contain define statemenst for the three supported Arduino (UNO, Micro and Due).
The code also contains define statmens to all supported featues in this version
#### Available features:
  * Displays: DED, FFI, PFD
  * Lights: Indexers, Caution Panel

#### Default settings (enabled by default):
  * Arduino Uno
  * Displays: DED, FFI
  * Lights: Indexers


#### Known issues:
  * you cannot corrently activate both indexers and caution panel - probably due to the lack of a pull up resistor somewhere. 
  * Lights do not work properly on Due - probably due to a electric design problem - will be solved in future revision.

### Note:
  * Check corresponding wiring diagram in the folder - adjust if needed.
  * Project is using Hardware SPI for best performance - please note that some pins are hardware limited
