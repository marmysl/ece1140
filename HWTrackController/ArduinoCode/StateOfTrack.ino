// Manual Override
int Rail_Switch = 4;
int Crossing_Switch = 2;
int Rail_LED = 22;
int Crossing_LED = 23; 
int Rail_State;
int Crossing_State;

// Update PLC
int PLC_Button = 11;
int PB_State;

// Set up Functions
void setManual() {
  // set I/Os
  pinMode(Rail_Switch, INPUT);
  pinMode(Rail_LED, OUTPUT);
  pinMode(Crossing_Switch, INPUT);
  pinMode(Crossing_LED, OUTPUT);

  // Traffic lights
  pinMode(Red_LED, OUTPUT);
  pinMode(Yellow_LED, OUTPUT);
  pinMode(Green_LED, OUTPUT);
}

// Detect Train
void detectTrain() {
  pinMode(Detect_LED, OUTPUT);             
}

// Show Failure
void detectFailure() {
  pinMode(Failure_LED, OUTPUT);             
}

void setUpload(){
  pinMode(PLC_Button, INPUT); 
}

void uploadPLC(){
  PB_State = digitalRead(PLC_Button);
}

// Updating function
void enableOverride() { 
  Rail_State = digitalRead(Rail_Switch);
  Crossing_State = digitalRead(Crossing_Switch);

  // Turn on LED for Railway Switch or Crossbarss if enabled
  if (Rail_State == 1) {
    digitalWrite(Rail_LED, HIGH);
  } else { 
    digitalWrite(Rail_LED, LOW);}

  if (Crossing_State == 1) {
    digitalWrite(Crossing_LED, HIGH);
  } else { 
    digitalWrite(Crossing_LED, LOW);}
}
