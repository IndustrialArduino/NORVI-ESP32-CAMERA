void config_io(){
  if (io.begin() == false)
  {
    Serial.println("PCA9536 not detected. Please check wiring. Freezing...");
    while (1)
      ;
  }

  pinMode(46, INPUT_PULLUP);
  pinMode(0, INPUT);
  io.pinMode(0, INPUT); io.pinMode(1, OUTPUT); io.pinMode(2, INPUT); io.pinMode(3, OUTPUT);
  io.digitalWrite(1, 0);


  attachInterrupt(IO_SWITCH, handleInterrupt, RISING);

}

void read_io(){
  TRIGGER = io.digitalRead(IO_TRIGGER);
  SWITCH = digitalRead(IO_SWITCH);
  B_UP = io.digitalRead(IO_BUTTON_UP);
  B_DOWN = digitalRead(IO_BUTTON_DOWN);
//  if(B_UP==1)io.digitalWrite(1, LOW);
//  if(B_UP==0)io.digitalWrite(1, HIGH);

  Serial.print(" TRIGGER: ");Serial.print(TRIGGER);Serial.print(" SWITCH: ");Serial.print(SWITCH);Serial.print(" B_UP: ");Serial.print(B_UP);Serial.print(" B_DOWN: ");Serial.println(B_DOWN);


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
