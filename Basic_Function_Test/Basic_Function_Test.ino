/*********


  I2C device found at address 0x41
  I2C device found at address 0x48
  I2C device found at address 0x6A

*********/

#include <Wire.h>
#include <PCA9536D.h>


#define BQ25180_ADDR 0x6A  // I2C address of the bq25180
#define CGCTRL_REG_ADDR 0x4
#define IC_CTRL  0x7
#define SHIP_RST 0x9
#define SYS_REG 0xA
#define TMR_ILIM 0x8

  #define IO_TRIGGER 0
  #define IO_LED_FLASH 1
  #define IO_BUTTON_UP 2
  #define IO_BUTTON_DOWN 0
  #define IO_SWITCH 46



unsigned int param_aec=0,param_aec_max=1200,param_aec_min=0;
unsigned int TRIGGER, SWITCH, B_UP, B_DOWN, TRIGGER_S, SWITCH_S, B_UP_S, B_DOWN_S ;
unsigned int V_DELAY;
volatile int count = 0;


PCA9536 io;

void IRAM_ATTR handleInterrupt() {
  // Increase the count when interrupt occurs
  count++;
}

void setup() {
  Wire.begin(1,14); delay(100);
  Serial.begin(115200);
  delay(100);
  I2C_Scan();

  delay(1000);
  config_io();            // Configure Inputs and Outputs on both ESP32 and PCA9536 IO Expander
  config_charger();       // Sets the charging current and input current limits

  

  
  delay(100);
  
 //write_register(SHIP_RST, 0x51);  Serial.println("Writing to CHARGE REGISTER Done");
  
}

void loop() {

  read_status();
  read_io();
  //param_adjust();
  param_adjust_run();
  Serial.println(param_aec);
  Serial.println(count);


  delay(100); // Delay before next read
}
