This code initializes an ESP32 connected to a TFT display, then runs a series of graphical tests and displays text. 
In the `setup` function, it initializes the display, shows "Hello World!" for 2 seconds, then clears the display. 
It sequentially fills the screen with various colors, draws rectangles of decreasing size, fills the center of the screen with nested rectangles in different colors.
Finally draws and fills circles in different colors, each followed by a short delay. 
At the end, it displays the text "NORVI" prominently on the screen. The `loop` function is empty, meaning these actions are only performed once at startup.

The code relies on two libraries for controlling the TFT display and SPI communication.

TFT_eSPI Library:
This library provides an efficient way to control TFT displays. It supports various types of displays and includes functions for drawing shapes, text, and images.
https://github.com/IndustrialArduino/NORVI-ESP32-CAMERA/blob/2cdc9e4bf35bfe05fbdf0871fa1c9219eab5530c/Libraries/TFT_eSPI.zip

SPI Library:
The SPI (Serial Peripheral Interface) library is included by default with the Arduino IDE. It provides communication with SPI devices, such as the TFT display.
You don't need to install this library separately as it is bundled with the Arduino IDE.
