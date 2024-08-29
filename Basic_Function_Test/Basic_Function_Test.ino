/*********
  Program Procedure
  1 - Do the I2C Scan to Find the connected periperials
      I2C device found at address 0x41
      I2C device found at address 0x48
      I2C device found at address 0x6A
  2 - Configure the charging IC
  3 - Read the I/O and print I/O Status

  
*********/

  #include <Wire.h>
  #include <PCA9536D.h>


  #define BQ25180_ADDR 0x6A  // I2C address of the bq25180
  #define CGCTRL_REG_ADDR 0x4
  #define IC_CTRL  0x7
  #define SHIP_RST 0x9
  #define SYS_REG 0xA
  #define TMR_ILIM 0x8

  #define IO_TRIGGER 0        // On PCA9536 Port Expander
  #define IO_LED_FLASH 1      // On PCA9536 Port Expander
  #define IO_BUTTON_UP 2      // On PCA9536 Port Expander
  #define IO_USER_LED 3       // On PCA9536 Port Expander
  #define IO_BUTTON_DOWN 0    // On ESP32 S3
  #define IO_SWITCH 46        // On ESP32 S3


  unsigned char serial_enable =0;


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
  Serial.begin(115200);

  delay(5000);
  serial_enable=0;
  
 
  Wire.begin(1,14); delay(100);
  if(serial_enable==1) I2C_Scan();

  delay(1000);
  config_io();            // Configure Inputs and Outputs on both ESP32 and PCA9536 IO Expander
  config_charger();       // Sets the charging current and input current limits

 io.digitalWrite(IO_LED_FLASH, HIGH);
 delay(1000);
 io.digitalWrite(IO_LED_FLASH, LOW);
  
 delay(100);
  
 //write_register(SHIP_RST, 0x51);  Serial.println("Writing to CHARGE REGISTER Done");
  
}

void loop() {

  if (Serial.available() > 0) {
        // Read the incoming byte
        char incomingByte = Serial.read();
        if (incomingByte == '1') {
           serial_enable=1;
        }
  }


  read_status();
  read_io();

  if(serial_enable==1)Serial.println(count);

  io.digitalWrite(IO_USER_LED, HIGH);
  delay(200);
  io.digitalWrite(IO_USER_LED, LOW);

  delay(100); // Delay before next read
}
