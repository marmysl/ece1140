// Joystick initializations
int VRx = A0;
int VRy = A1;
int SW = 13;
int xPosition = 0; 
int yPosition = 0;
int SW_state = 0;

String section;
String block;
String suggested;
String commanded;
String authority;

void setJoystick() {
    // I/Os
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
}

void joystick() {
  // Read from Joystick
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW); 
  
  // +x direction: switch to next block
  if (xPosition>=900 && yPosition>=500){
    lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.print("Section ");
    lcd1.print(section);
    lcd1.print(", Block ");
    lcd1.print(block);} 
    
  // -x : switch to previous block
  if (xPosition<=90 && yPosition>=500){
    lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.print("Section ");
    lcd1.print(section);
    lcd1.print(", Block ");
    lcd1.print(block);}
  
  // show block information
  if (SW_state == 0) {
    lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.print("Section ");
    lcd1.print(section);
    lcd1.print(", Block ");
    lcd1.print(block);
    lcd1.setCursor(0,1);
    lcd1.print("Suggested:");
    lcd1.print(suggested);
    lcd1.print(" kph");
    lcd1.setCursor(0,2);
    lcd1.print("Commanded:");
    lcd1.print(commanded);
    lcd1.print(" kph");
    lcd1.setCursor(0,3);
    lcd1.print("Authority:");
    lcd1.print(authority);
    lcd1.print(" blcks");}
}
