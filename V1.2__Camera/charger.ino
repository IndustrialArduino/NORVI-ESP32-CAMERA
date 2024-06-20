

unsigned int read_register(byte reg_addr){
  byte registerValue;

  Wire.beginTransmission(BQ25180_ADDR);
  Wire.write(reg_addr); // Register address to read
  Wire.endTransmission(false); // Restart

  Wire.requestFrom(BQ25180_ADDR, 1); // Request 1 byte from the device

  if (Wire.available()) {
    registerValue = Wire.read(); // Read the byte
   
  } else {
    Serial.println("Error: No response from device");
  }
  return registerValue;
}

void write_register(byte reg_add, byte reg_val){

  Wire.beginTransmission(BQ25180_ADDR);
  Wire.write(reg_add);   // Address of register to write to
  Wire.write(reg_val);       // Data to write
  Wire.endTransmission(); 
}

void read_status(){
  byte status_reg0, status_reg1;
  int bits56, bits34;
  bool bit0, bit1, bit2, bit3, bit4, bit5, bit6, bit7;

  status_reg0 = read_register(0x00);
  status_reg1 = read_register(0x01);
  
  bits56 = ((status_reg0 >> 5) & 0b00000011);
  
  bit0 = (status_reg0 & 0b00000001) > 0;
  bit1 = (status_reg0 & 0b00000010) > 0;
  bit2 = (status_reg0 & 0b00000100) > 0;
  bit3 = (status_reg0 & 0b00001000) > 0;
  bit4 = (status_reg0 & 0b00010000) > 0;
  bit5 = (bits56 & 0b00000001) > 0;
  bit6 = (bits56 & 0b00000010) > 0;
  bit7 = (status_reg0 & 0b10000000) > 0;


  Serial.print(" VIN: ");Serial.print(bit0);Serial.print(" THM: ");Serial.print(bit1);Serial.print(" DPM: ");Serial.print(bit2);Serial.print(" PPM: ");Serial.print(bit3);Serial.print(" ILIM: ");Serial.print(bit4);Serial.print(" CHG: ");Serial.print(bits56);Serial.print(" TS: ");Serial.print(bit7);

  bits34 = ((status_reg1 >> 3) & 0b00000011);
  
  bit0 = (status_reg1 & 0b00000001) > 0;
  bit1 = (status_reg1 & 0b00000010) > 0;
  bit2 = (status_reg1 & 0b00000100) > 0;
  bit3 = (status_reg1 & 0b00001000) > 0;
  bit4 = (status_reg1 & 0b00010000) > 0;
  bit5 = (status_reg1 & 0b00100000) > 0;
  bit6 = (status_reg1 & 0b01000000) > 0;
  bit7 = (status_reg1 & 0b10000000) > 0;

  Serial.print(" WK2: ");Serial.print(bit0);Serial.print(" WK1: ");Serial.print(bit1);Serial.print(" SFC: ");Serial.print(bit2);Serial.print(" TS: ");Serial.print(bits34);Serial.print(" BUV: ");Serial.print(bit6);Serial.print(" IOV: ");Serial.println(bit7);
  
  
 
}


void config_charger(){
  write_register(CGCTRL_REG_ADDR, 0x50);  Serial.println("Charging Current Set to 530mA");
  delay(100);
  write_register(IC_CTRL, 0x04);  Serial.println("Disable TS Auto");
  write_register(TMR_ILIM, 0x0D);  Serial.println("Push button Long Press to 5s");
  delay(100);
  write_register(SYS_REG, 0x40);  Serial.println("Writing to SYS CONTROL");
}

void config_sys(){

  if(parameters[23].value==1)write_register(SYS_REG, 0x48); 
  else write_register(SYS_REG, 0x40);
  
  
}
