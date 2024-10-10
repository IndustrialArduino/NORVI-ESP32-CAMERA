#include <Arduino.h>
#include <ESP32QRCodeReader.h>

#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>
#include <Adafruit_ADS1X15.h>

TFT_eSPI tft = TFT_eSPI();

unsigned int menu_index=0;

void IRAM_ATTR handleInterrupt() {
  // Increase the count when interrupt occurs
  menu_index++;
  if(menu_index>23)menu_index=0;
  
}

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap){
  if( y>= tft.height()) return 0;
  tft.pushImage(x, y, w, h, bitmap);
  return 1;
}

void displayInit(){
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);

  TJpgDec.setJpgScale(1);
  TJpgDec.setSwapBytes(true);
  TJpgDec.setCallback(tft_output);
}

ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);

void onQrCodeTask(void *pvParameters)
{
  struct QRCodeData qrCodeData;

  while (true)
  {
    if (reader.receiveQrCode(&qrCodeData, 100))
    {
      Serial.println("Found QRCode");
      if (qrCodeData.valid)
      {
        Serial.print("Payload: ");
        Serial.println((const char *)qrCodeData.payload);
       

       tft.fillRect(0, tft.height() - 30, tft.width(), 30, TFT_BLACK);
    
     
      tft.setCursor(10, tft.height() - 30 + 5); // Adjust the coordinates as needed
      tft.setTextColor(TFT_WHITE); // Set text color
      tft.setTextSize(2); // Set text size
      tft.print("QR: ");
      tft.print((const char *)qrCodeData.payload);

      }
      else
      {
        Serial.print("Invalid: ");
        Serial.println((const char *)qrCodeData.payload);
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}


void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  displayInit();
  reader.setup();

  Serial.println("Setup QRCode Reader");

  reader.beginOnCore(1);

  Serial.println("Begin on Core 1");

  xTaskCreate(onQrCodeTask, "onQrCode", 8192, NULL, 4, NULL);
}

void loop()
{
  delay(1000);
 
    
}