// Data that needs to be received for the GUI
/*
 * Char 0 = Block Occupancy
 * Char 1 = Current Section
 * Char 2-3 = Current Block
 * Char 4-7 = Suggested Speed
 * Char 8-11 = Commanded Speed
 * Char 12-15 = Authority
 * Char 16 = Lights
 * Char 17 = Failure Alert
 * Last character is a newline, length 18
 */

String incomingData;

void Receiver() {
  if (Serial.available() > 0){
    incomingData = Serial.readStringUntil('\n');
  }
  
  if (incomingData.length() == 18) {
      if (incomingData.substring(0,1).equals("1")) digitalWrite(Detect_LED, HIGH);
      else if (incomingData.substring(0,1).equals("0")) digitalWrite(Detect_LED, LOW);
    
      section = incomingData.substring(1,2);
      block = incomingData.substring(2,4);
      suggested = incomingData.substring(4,8);
      commanded = incomingData.substring(8,12);
      authority = incomingData.substring(12,16); 
      
      if (incomingData.substring(16,17).equals("0")) { 
        digitalWrite(Red_LED, HIGH);
        digitalWrite(Red_LED, LOW);
        digitalWrite(Green_LED, LOW);
      } 
      else if (incomingData.substring(16,17).equals("1")) { 
        digitalWrite(Red_LED, LOW);
        digitalWrite(Yellow_LED, HIGH);
        digitalWrite(Green_LED, LOW);
      } 
      else if (incomingData.substring(16,17).equals("2")) { 
        digitalWrite(Red_LED, LOW);
        digitalWrite(Yellow_LED, LOW);
        digitalWrite(Green_LED, HIGH);
      }
    
      if (incomingData.substring(17,18).equals("1")) { 
        digitalWrite(Failure_LED, HIGH);
      } else if (incomingData.substring(17,18).equals("0")) { 
        digitalWrite(Failure_LED, LOW); }
      
  }
}
