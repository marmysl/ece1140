/* 
 * Char 0 = Joystick left
 * Char 1 = Joystick right
 * Char 2 = Manually change Switch Position: 0 or 1
 * Char 3 = Manually activate railway crossing: 0 or 1
 * Char 4 = Update PLC Button: 0 or 1
 */

 // string to transmsit
 String outgoingData;
 
void Transmitter() {
  outgoingData = "";
  
  // Joystick
  // -x Left: previous block
  if (xPosition<=90 && yPosition>=500){
    outgoingData += "1";
  } else {
    outgoingData += "0";
  }
  
  // +x Right: next block
  if (xPosition>=900 && yPosition>=500){
    outgoingData += "1";
  } else {
    outgoingData += "0";
  }

  // Switch position state
  if (Rail_State == 1) {
    outgoingData += "1";
  } else { 
    outgoingData += "0";
  }

  // Railway crossing state
  if (Crossing_State == 1) {
    outgoingData += "1";
  } else { 
    outgoingData += "0";
  }

  // PLC Button state
  if (PB_State == 1) {
    outgoingData += "1";
  } else {
    outgoingData += "0";
  }

  Serial.println(outgoingData);
  
 }
