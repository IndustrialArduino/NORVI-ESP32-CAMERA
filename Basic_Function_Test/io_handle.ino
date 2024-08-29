void config_io(){
  if (io.begin() == false)
  {
    Serial.println("PCA9536 not detected. Please check wiring. Freezing...");
    while (1)
      ;
  }

  pinMode(IO_SWITCH, INPUT_PULLUP);
  pinMode(IO_BUTTON_DOWN, INPUT_PULLUP);
  io.revert(0);
  io.revert(1);
  io.revert(2);
  io.revert(3);
  io.pinMode(IO_TRIGGER, INPUT); io.pinMode(IO_LED_FLASH, OUTPUT); io.pinMode(IO_BUTTON_UP, INPUT_PULLUP); io.pinMode(IO_USER_LED, OUTPUT);
  
  attachInterrupt(IO_SWITCH, handleInterrupt, RISING);

  ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  
  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }

}

void read_io(){
  TRIGGER = io.digitalRead(IO_TRIGGER);
  SWITCH = digitalRead(IO_SWITCH);
  B_UP = io.digitalRead(IO_BUTTON_UP);
  B_DOWN = digitalRead(IO_BUTTON_DOWN);

  if(serial_enable==1){
  Serial.print(" TRIGGER: ");Serial.print(TRIGGER);Serial.print(" SWITCH: ");Serial.print(SWITCH);Serial.print(" B_UP: ");Serial.print(B_UP);Serial.print(" B_DOWN: ");Serial.println(B_DOWN);
  }

}


void param_adjust_run(){
  V_DELAY=100;
  while(digitalRead(46)==0){
    param_up(&param_aec, &param_aec_max);
    if(V_DELAY>25)V_DELAY-=25;
    delay(V_DELAY);

  }

   while(digitalRead(0)==0){
    param_down(&param_aec, &param_aec_min);
    if(V_DELAY>25)V_DELAY-=25;
    delay(V_DELAY);

  }
}

void param_up(unsigned int *var,unsigned int *max){
  if (*var < *max) {
    *var += 1;
  }
}

void param_down(unsigned int *var,unsigned int *min){
  if (*var > *min) {
    *var -= 1;
  }
}

void read_battery(){
adc0 = ads.readADC_SingleEnded(0);
volts0 = ads.computeVolts(adc0*2);
  if(serial_enable==1){
    Serial.print("AIN0: "); Serial.print(adc0); Serial.print("  "); Serial.print(volts0); Serial.println("V");
  }  
}
