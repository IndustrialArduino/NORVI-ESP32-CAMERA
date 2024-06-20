void config_io(){
  if (io.begin() == false)
  {
    Serial.println("PCA9536 not detected. Please check wiring. Freezing...");
    while (1)
      ;
  }

  pinMode(46, INPUT_PULLUP);
  pinMode(0, INPUT_PULLUP);
  io.revert(0);
  io.revert(1);
  io.revert(2);
  io.revert(3);
  io.pinMode(0, INPUT); io.pinMode(1, OUTPUT); io.pinMode(2, INPUT_PULLUP); io.pinMode(3, OUTPUT);
  io.digitalWrite(2, HIGH);
  


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
  B_UP = digitalRead(IO_BUTTON_UP);
  B_DOWN = io.digitalRead(IO_BUTTON_DOWN); 
//  if(B_UP==1)io.digitalWrite(1, LOW);
//  if(B_UP==0)io.digitalWrite(1, HIGH);

  Serial.print(" TRIGGER: ");Serial.print(TRIGGER);Serial.print(" SWITCH: ");Serial.print(SWITCH);Serial.print(" B_UP: ");Serial.print(B_UP);Serial.print(" B_DOWN: ");Serial.println(B_DOWN);


}


void param_adjust_run(){
  V_DELAY=100;
  while(digitalRead(IO_BUTTON_UP)==0){
    param_up(&parameters[menu_index].value, &parameters[menu_index].maxValue);
    if(V_DELAY>25)V_DELAY-=25;
    delay(V_DELAY);
    display_menu();
  }

   while(io.digitalRead(IO_BUTTON_DOWN)==0){
    param_down(&parameters[menu_index].value, &parameters[menu_index].minValue);
    if(V_DELAY>25)V_DELAY-=25;
    delay(V_DELAY);
    display_menu();
  }
  
}

void param_up(int *var,int *max){
  if (*var < *max) {
    *var += 1;
    value_change_flag=1;
  }
}

void param_down(int *var,int *min){
  if (*var > *min) {
    *var -= 1;
    value_change_flag=1;
  }
}

void read_battery(){
adc0 = ads.readADC_SingleEnded(0);
volts0 = ads.computeVolts(adc0);
Serial.print("AIN0: "); Serial.print(adc0); Serial.print("  "); Serial.print(volts0); Serial.println("V");
  
}
