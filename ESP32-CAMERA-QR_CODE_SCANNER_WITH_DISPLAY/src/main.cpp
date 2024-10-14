#include <Arduino.h>
#include <ESP32QRCodeReader.h>

#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>
#include <Adafruit_ADS1X15.h>
#include "ESP32_OV5640_AF.h"

TFT_eSPI tft = TFT_eSPI();
OV5640 ov5640 = OV5640();

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
  String lastPayload = ""; // Variable to store the last seen payload
  String currentPayload = ""; // Variable to store the last seen payload
  unsigned long lastProcessedTime = millis(); // Timestamp of the last QR code processed
  const unsigned long resetDelay = 10000; // 10 seconds delay to reset lastPayload

  while (true)
  {
    if (reader.receiveQrCode(&qrCodeData, 100))
    {
      Serial.println("Found QRCode");
      if (qrCodeData.valid)
      {
        Serial.print("Payload: ");
        Serial.println((const char *)qrCodeData.payload);
       
        if(currentPayload!= lastPayload){
            tft.fillRect(0, (tft.height() /2) - 25, tft.width(), 50, TFT_BLACK);
    
     
            tft.setCursor(10, (tft.height() /2) - 25 + 15); // Adjust the coordinates as needed
            tft.setTextColor(TFT_WHITE); // Set text color
            tft.setTextSize(2); // Set text size
            tft.print("QR: ");
            tft.print((const char *)qrCodeData.payload);
            delay(2000);
            tft.fillScreen(TFT_WHITE);
            lastPayload = currentPayload;
            lastProcessedTime = millis();
         } 
      }
      else
      {
        Serial.print("Invalid: ");
        Serial.println((const char *)qrCodeData.payload);
        currentPayload = (const char *)qrCodeData.payload;
       
        if(currentPayload!= lastPayload){

             tft.fillRect(0, (tft.height() /2) - 25, tft.width(), 50, TFT_BLACK);
  
             tft.setCursor(10, (tft.height() /2) - 25 + 15); // Adjust the coordinates as needed
             tft.setTextColor(TFT_WHITE); // Set text color
             tft.setTextSize(2); // Set text size
             tft.print("Invalid: ");
             tft.print((const char *)qrCodeData.payload);
             delay(2000);
             tft.fillScreen(TFT_WHITE);
             lastPayload = currentPayload;
             lastProcessedTime = millis();
         } 
      }
    }
     if (currentPayload == lastPayload)
        {
          if (millis() - lastProcessedTime > resetDelay)
           {
         // Reset lastPayload after 10 seconds
            lastPayload = "";
            Serial.println("Last payload reset due to inactivity");
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

  sensor_t* sensor = esp_camera_sensor_get();
  ov5640.start(sensor);                 // Initialize Autofocus

  if (ov5640.focusInit() == 0) {
    Serial.println("OV5640_Focus_Init Successful!");
  }

  if (ov5640.autoFocusMode() == 0) {
    Serial.println("OV5640_Auto_Focus Successful!");
  }
}

void loop()
{
  delay(1000);
 
    
}
