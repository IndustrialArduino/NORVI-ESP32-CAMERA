void displayInit(){
  Serial.println("DISPLAY");
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);

  TJpgDec.setJpgScale(1);
  TJpgDec.setSwapBytes(true);
  TJpgDec.setCallback(tft_output);
}

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap){
  if( y>= tft.height()) return 0;
  tft.pushImage(x, y, w, h, bitmap);
  return 1;
}

void display_menu(){
  tft.fillRect(0, tft.height() - 30, tft.width(), 30, TFT_BLACK);
   
  // Draw the name "bhanuka" on the black rectangle
  tft.setCursor(10, tft.height() - 30 + 5); // Adjust the coordinates as needed
  tft.setTextColor(TFT_WHITE); // Set text color
  tft.setTextSize(2); // Set text size
  tft.print(parameters[menu_index].label); tft.print(" : "); tft.print(parameters[menu_index].value);

  tft.setCursor(10, 10); // Adjust the coordinates as needed
  tft.setTextColor(TFT_WHITE); // Set text color
  tft.setTextSize(2); // Set text size
  tft.print(volts0*2);
}
