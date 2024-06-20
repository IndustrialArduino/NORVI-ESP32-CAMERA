/*********
  I2C device found at address 0x41
  I2C device found at address 0x48
  I2C device found at address 0x6A
*********/

#include "esp_camera.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include <TJpg_Decoder.h>
#include "ESP32_OV5640_AF.h"
#include <Wire.h>
#include <PCA9536D.h>
#include <Adafruit_ADS1X15.h>

#define BQ25180_ADDR 0x6A  // I2C address of the bq25180
#define CGCTRL_REG_ADDR 0x4
#define IC_CTRL  0x7
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

unsigned int menu_index=0;
unsigned int value_change_flag=0;

struct Parameter {
    const char* label;
    int value;
    int minValue;
    int maxValue;
};

// Define an array of structures to store the parameters and their min/max values
Parameter parameters[] = {
    // Each element corresponds to a parameter
    // Format: {label, value, minValue, maxValue}
    {"Brightness", 0, -2, 2},
    {"Contrast", 2, -2, 2},
    {"Saturation", 0, -2, 2},
    {"Special Effect", 0, 0, 6},
    {"White Balance", 1, 0, 1},
    {"AWB Gain", 1, 0, 1},
    {"WB Mode", 0, 0, 4},
    {"Exposure Control", 0, 0, 1},
    {"AEC2", 1, 0, 1},
    {"AE Level", 2, -2, 2},
    {"AEC Value", 800, 0, 1200},
    {"Gain Control", 1, 0, 1},
    {"AGC Gain", 0, 0, 30},
    {"Gain Ceiling", 6, 0, 6},
    {"BPC", 1, 0, 1},
    {"WPC", 1, 0, 1},
    {"RAW GMA", 1, 0, 1},
    {"LENC", 1, 0, 1},
    {"H-Mirror", 1, 0, 1},
    {"V-Flip", 0, 0, 1},
    {"DCW", 1, 0, 1},
    {"Color Bar", 0, 0, 1},
    {"Flash", 0, 0, 2},
    {"SYSTEM", 0, 0, 2}
};

int param_saturation=0,param_saturation_max=2,param_saturation_min=-2;
int param_aec=0,param_aec_max=1200,param_aec_min=0;
unsigned int TRIGGER, SWITCH, B_UP, B_DOWN, TRIGGER_S, SWITCH_S, B_UP_S, B_DOWN_S ;
unsigned int V_DELAY;
volatile int count = 0;

int16_t adc0, adc1, adc2, adc3;
float volts0, volts1, volts2, volts3;

void IRAM_ATTR handleInterrupt() {
  // Increase the count when interrupt occurs
  menu_index++;
  if(menu_index>23)menu_index=0;
}

void setup() {
  Wire.begin(1,14); delay(100);
  Serial.begin(115200);

  delay(1000);
  config_io();            // Configure Inputs and Outputs on both ESP32 and PCA9536 IO Expander
  delay(100);
  config_charger();       // Sets the charging current and input current limits

  displayInit();
  cameraInit();
  
  sensor_t* sensor = esp_camera_sensor_get();
  ov5640.start(sensor);

  if (ov5640.focusInit() == 0) {
    Serial.println("OV5640_Focus_Init Successful!");
  }

  if (ov5640.autoFocusMode() == 0) {
    Serial.println("OV5640_Auto_Focus Successful!");
  }
  delay(100);
  
 //write_register(SHIP_RST, 0x51);  Serial.println("Writing to CHARGE REGISTER Done");
}


void loop() {
  //read_status();
  //read_io();
  showingImage();
  display_menu();
  //param_adjust();
  param_adjust_run();
  update_setting();
  read_status();
  config_sys();
  read_battery();
  if(parameters[22].value==1)io.digitalWrite(IO_LED_FLASH, HIGH); 
  else io.digitalWrite(IO_LED_FLASH, LOW); 
  //delay(100); // Delay before next read
}
