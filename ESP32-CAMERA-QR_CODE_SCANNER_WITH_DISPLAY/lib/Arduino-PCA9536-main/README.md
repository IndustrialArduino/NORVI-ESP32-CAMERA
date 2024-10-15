SparkX PCA9536 Arduino Library
==============================

[![SparkFun RGB Sensor - BH1749NUC (SPX-14733)](https://cdn.sparkfun.com//assets/parts/1/2/9/6/0/14733-RGB_Sensor__Qwiic__-_BH1749NUC-01.jpg)](https://www.sparkfun.com/products/14733) 

[*SparkFun RGB Sensor - BH1749NUC (SPX-14733)*](https://www.sparkfun.com/products/14733)

The PCA9536 is a 4-bit I/O digital expander, which communicates via an I2C bus. The expander can read or write four separate I/O. This IC is used on the SparkX RGB breakout to turn on/off the various RGBW LEDs to illuminate the object under test.

This library handles the initialization of the PCA9536 and supports standard `pinMode`, `digitalRead`, and `digitalWrite` functions.

Thanks to:

* openelectron for adding [readReg() method](https://github.com/sparkfun/SparkFun_PCA9536_Arduino_Library/pull/2)
* tadas-s for [miscellaneous cleanup](https://github.com/sparkfun/SparkFun_PCA9536_Arduino_Library/pull/1)

Repository Contents
-------------------

* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE. 
* **/src** - Source files for the library (.cpp, .h).
* **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE. 
* **library.properties** - General library properties for the Arduino package manager. 

License Information
-------------------

This product is _**open source**_! 

Various bits of the code have different licenses applied. Anything SparkFun wrote is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!

Please use, reuse, and modify these files as you see fit. Please maintain attribution to SparkFun Electronics and release anything derivative under the same license.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.
