This is a library to use printf in arduino sketches, so that it writes to Serial.

Installation
--------------------------------------------------------------------------------

To install this library, just place this entire folder as a subfolder in your
~/Arduino/libraries folder.

Note : Support for %f is enabled by this library, and may make your sketch bigger.

Note : %llu support is missing in Arduino core libraries, so this package provides 
a helper function to convert long long unsigned int to C-strings : ulltoa.


Use
--------------------------------------------------------------------------------
Just add "#include <printfToSerial.h> to your sketch, and let's get printing !
See example for some examples of use.
