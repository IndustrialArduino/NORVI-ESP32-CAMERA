#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Create a display object
uint16_t colors[] = {TFT_BLACK, TFT_WHITE, TFT_GREEN, TFT_BLUE, TFT_CYAN, TFT_MAGENTA, TFT_YELLOW, TFT_ORANGE};

void setup() {
  Serial.begin(115200);
  
  // Initialize the display
  tft.init();
  tft.setRotation(1);  // Set the display orientation

  // Print a message to the display
  tft.fillScreen(TFT_BLACK);  // Clear the display
  tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text color to white and background to black
  tft.setTextSize(4);  // Set text size
  tft.setCursor(15, 10);  // Set cursor position
  tft.println("Hello World!");  // Print text
  delay(2000);
  tft.fillScreen(TFT_BLACK);  // Clear the display

  // Draw some test graphics
  tft.fillRect(0, 0, 320, 240, TFT_RED);   //(x coordinate, y coordinate, width of the rectangle, height of the rectangle, color used to fill the rectangle)
  delay(1000);
  tft.fillRect(0, 0, 320, 240, TFT_GREEN);
  delay(1000);
  tft.fillRect(0, 0, 320, 240, TFT_BLUE);
  delay(1000);
  tft.fillRect(0, 0, 320, 240, TFT_ORANGE);
  delay(1000);
  tft.fillRect(0, 0, 320, 240, TFT_WHITE);
  delay(1000);
  tft.fillRect(0, 0, 320, 240, TFT_CYAN);
  delay(1000);
  tft.fillScreen(TFT_BLACK);  // Clear the display

  tft.drawRect(0, 0, 240, 240, TFT_RED);
  delay(1000);
  tft.drawRect(20, 20, 220, 220, TFT_GREEN);
  delay(1000);
  tft.drawRect(40, 40, 200, 200, TFT_YELLOW);
  delay(1000);
  tft.drawRect(60, 60, 180, 180, TFT_ORANGE);
  delay(1000);
  tft.fillScreen(TFT_BLACK);  // Clear the display

  // (320 - 220) / 2 = x coordinate.  220 = size of the rectangle. 
  // (240 - 220) / 2 = y coordinate,
  tft.fillRect((320 - 220) / 2, (240 - 220) / 2, 220, 220, TFT_WHITE); //(x coordinate, y coordinate, width of the rectangle, height of the rectangle, color used to fill the rectangle)
  delay(1000);
  tft.fillRect((320 - 195) / 2, (240 - 195) / 2, 195, 195, TFT_RED);
  delay(1000);
  tft.fillRect((320 - 170) / 2, (240 - 170) / 2, 170, 170, TFT_GREEN);
  delay(1000);
  tft.fillRect((320 - 145) / 2, (240 - 145) / 2, 145, 145, TFT_YELLOW);
  delay(1000);
  tft.fillRect((320 - 120) / 2, (240 - 120) / 2, 120, 120, TFT_ORANGE);
  delay(1000);
  tft.fillScreen(TFT_BLACK);  // Clear the display

  // Draw a circle
  tft.fillCircle(160, 120, 100, TFT_YELLOW);  //(x coordinate of the center of the circle , y coordinate of the center of the circle, Radius of the circle, color used to fill the circle)
  delay(1000);
  tft.fillCircle(160, 120, 100, TFT_RED);
  delay(1000);
  tft.fillCircle(160, 120, 100, TFT_GREEN);
  delay(1000);
  tft.fillCircle(160, 120, 100, TFT_YELLOW);
  delay(1000);
  tft.fillCircle(160, 120, 100, TFT_BLUE);
  delay(1000);
  tft.fillScreen(TFT_BLACK);  // Clear the display

  tft.drawCircle(160, 120, 100, TFT_YELLOW);
  delay(1000);
  tft.drawCircle(160, 120, 100, TFT_RED);
  delay(1000);
  tft.drawCircle(160, 120, 100, TFT_GREEN);
  delay(1000);
  tft.drawCircle(160, 120, 100, TFT_YELLOW);
  delay(1000);
  tft.drawCircle(160, 120, 100, TFT_BLUE);
  delay(1000);
  tft.fillScreen(TFT_BLACK);  // Clear the display

  // Print a message to the display
  tft.setTextColor(TFT_WHITE, TFT_BLACK);  // Set text color to white and background to black
  tft.setTextSize(12);  // Set text size
  tft.setCursor(60, 90);  // Set cursor position
  tft.println("NORVI");  // Print text
}

void loop() {
  
}
