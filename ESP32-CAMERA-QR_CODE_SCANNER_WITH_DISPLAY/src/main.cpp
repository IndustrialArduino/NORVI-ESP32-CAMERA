#include <Arduino.h>
#include <ESP32QRCodeReader.h>

#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>
#include <Adafruit_ADS1X15.h>
#include "ESP32_OV5640_AF.h"
#include <Wire.h>
#include <PCA9536D.h>

#define BQ25180_ADDR 0x6A // I2C address of the bq25180
#define CGCTRL_REG_ADDR 0x4
#define IC_CTRL 0x7
#define SHIP_RST 0x9
#define SYS_REG 0xA
#define TMR_ILIM 0x8

#define IO_TRIGGER 0
#define IO_LED_FLASH 1
#define IO_BUTTON_DOWN 2
#define IO_BUTTON_UP 0
#define IO_SWITCH 46

Adafruit_ADS1115 ads;
PCA9536 io;

TFT_eSPI tft = TFT_eSPI();
OV5640 ov5640 = OV5640();

unsigned int menu_index = 0;

unsigned int TRIGGER, SWITCH, B_UP, B_DOWN, TRIGGER_S, SWITCH_S, B_UP_S, B_DOWN_S;
unsigned int V_DELAY;
volatile int count = 0;

int16_t adc0, adc1, adc2, adc3;
float volts0, volts1, volts2, volts3;

void IRAM_ATTR handleInterrupt()
{
  // Increase the count when interrupt occurs
  menu_index++;
  if (menu_index > 23)
    menu_index = 0;
}

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
  if (y >= tft.height())
    return 0;
  tft.pushImage(x, y, w, h, bitmap);
  return 1;
}

void displayInit()
{
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);

  TJpgDec.setJpgScale(1);
  TJpgDec.setSwapBytes(true);
  TJpgDec.setCallback(tft_output);
}

unsigned int read_register(byte reg_addr)
{
  byte registerValue;

  Wire.beginTransmission(BQ25180_ADDR);
  Wire.write(reg_addr);        // Register address to read
  Wire.endTransmission(false); // Restart

  Wire.requestFrom(BQ25180_ADDR, 1); // Request 1 byte from the device

  if (Wire.available())
  {
    registerValue = Wire.read(); // Read the byte
  }
  else
  {
    Serial.println("Error: No response from device");
  }
  return registerValue;
}

void write_register(byte reg_add, byte reg_val)
{

  Wire.beginTransmission(BQ25180_ADDR);
  Wire.write(reg_add); // Address of register to write to
  Wire.write(reg_val); // Data to write
  Wire.endTransmission();
}

void config_charger()
{
  write_register(CGCTRL_REG_ADDR, 0x38);
  Serial.println("Charging Current Set to 280mA");
  delay(100);
  write_register(IC_CTRL, 0x04);
  Serial.println("Disable TS Auto");
  write_register(TMR_ILIM, 0x0D);
  Serial.println("Push button Long Press to 5s");
  delay(100);
  write_register(SYS_REG, 0x40);
  Serial.println("Writing to SYS CONTROL");
}

void config_sys()
{
  write_register(SYS_REG, 0x40);
}

ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);

void onQrCodeTask(void *pvParameters)
{
  struct QRCodeData qrCodeData;
  String lastPayload = "";                    // Variable to store the last seen payload
  String currentPayload = "";                 // Variable to store the last seen payload
  unsigned long lastProcessedTime = millis(); // Timestamp of the last QR code processed
  const unsigned long resetDelay = 10000;     // 10 seconds delay to reset lastPayload

  while (true)
  {
    if (reader.receiveQrCode(&qrCodeData, 100))
    {
      Serial.println("Found QRCode");
      if (qrCodeData.valid)
      {
        Serial.print("Payload: ");
        Serial.println((const char *)qrCodeData.payload);

        if (currentPayload != lastPayload)
        {
          tft.fillRect(0, (tft.height() / 2) - 25, tft.width(), 50, TFT_BLACK);

          tft.setCursor(10, (tft.height() / 2) - 25 + 15); // Adjust the coordinates as needed
          tft.setTextColor(TFT_WHITE);                     // Set text color
          tft.setTextSize(2);                              // Set text size
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

        if (currentPayload != lastPayload)
        {

          tft.fillRect(0, (tft.height() / 2) - 25, tft.width(), 50, TFT_BLACK);

          tft.setCursor(10, (tft.height() / 2) - 25 + 15); // Adjust the coordinates as needed
          tft.setTextColor(TFT_WHITE);                     // Set text color
          tft.setTextSize(2);                              // Set text size
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
  Wire.begin(1, 14);
  delay(100);
  Serial.begin(115200);
  delay(1000);

  config_charger(); // Sets the charging current and input current limits
  Serial.println();
  displayInit();
  reader.setup();

  Serial.println("Setup QRCode Reader");

  reader.beginOnCore(1);

  Serial.println("Begin on Core 1");

  xTaskCreate(onQrCodeTask, "onQrCode", 8192, NULL, 4, NULL);

  sensor_t *sensor = esp_camera_sensor_get();
  ov5640.start(sensor); // Initialize Autofocus

  if (ov5640.focusInit() == 0)
  {
    Serial.println("OV5640_Focus_Init Successful!");
  }

  if (ov5640.autoFocusMode() == 0)
  {
    Serial.println("OV5640_Auto_Focus Successful!");
  }
}

void loop()
{
  delay(1000);
  config_sys();
}
