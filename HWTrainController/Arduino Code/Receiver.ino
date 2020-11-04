//String that will hold received data
String receivedString;

void reciever()
{
  //Check if new serial data has been written
  if (Serial.available() > 0) receivedString = Serial.readStringUntil('\n');

  //Create a system to encode all data to be returned to the interface in the string
    //char 0 = cabinLights
    //char 1 = cabinAc
    //char 2 = cabinHeat
    //char 3 = cabinDoorsClosed
    //char 4 = cabinAdvertisements
    //char 5 = cabinAnnouncements
    //char6-10 = authority
    //char11-15 = Kp
    //char16-20 = Ki
    //char21-25 = commandedSpeed
    //char26-30 = setpointSpeed
    //char31-35 = currentSpeed
    //char36 = service brake
    //char37 = emergency brake
    //char 38-43 = power command
    //char 44 = failure code
    //char 45 = cabinHeadlights
    //char 46 = newline

//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print(receivedString);
//    lcd.setCursor(0,3);
//    lcd.print(receivedString.length());

  if (receivedString.length() == 46)
  {
    //Adjusts cabin control outputs based on input data
    if (receivedString.substring(0,1).equals("1")) digitalWrite(CabinLightsOut, HIGH);
    else if (receivedString.substring(0,1).equals("0")) digitalWrite(CabinLightsOut, LOW);
    if (receivedString.substring(1,2).equals("1")) digitalWrite(CabinAcOut, HIGH);
    else if (receivedString.substring(1,2).equals("0")) digitalWrite(CabinAcOut, LOW);
    if (receivedString.substring(2,3).equals("1")) digitalWrite(CabinHeatOut, HIGH);
    else if (receivedString.substring(2,3).equals("0")) digitalWrite(CabinHeatOut, LOW);
    if (receivedString.substring(3,4).equals("1")) digitalWrite(CabinDoorsOut, HIGH);
    else if (receivedString.substring(3,4).equals("0")) digitalWrite(CabinDoorsOut, LOW);
    if (receivedString.substring(4,5).equals("1")) digitalWrite(CabinAdvertisementsOut, HIGH);
    else if (receivedString.substring(4,5).equals("0")) digitalWrite(CabinAdvertisementsOut, LOW);
    if (receivedString.substring(5,6).equals("1")) digitalWrite(CabinAnnouncementsOut, HIGH);
    else if (receivedString.substring(5,6).equals("0")) digitalWrite(CabinAnnouncementsOut, LOW);

    //Sets joystick outputs
    authority = receivedString.substring(6,11);
    Kp = receivedString.substring(11,16);
    Ki = receivedString.substring(16,21);
    commandedSpeed = receivedString.substring(21,26);
    setpointSpeed = receivedString.substring(26,31);
    currentSpeed = receivedString.substring(31,36);
    power  = receivedString.substring(38,44);

    if(receivedString.substring(36,37).equals("1")) digitalWrite(serviceBrakeOut, HIGH);
    else digitalWrite(serviceBrakeOut, LOW);
    if(receivedString.substring(37,38).equals("1")) digitalWrite(emergencyBrakeOut, HIGH);
    else digitalWrite(emergencyBrakeOut, LOW);
    if(receivedString.substring(45,46).equals("1")) digitalWrite(headlightsOut, HIGH);
    else digitalWrite(headlightsOut, LOW);
    
    failureCode = receivedString.substring(44,45).toInt();
  }
  
}
