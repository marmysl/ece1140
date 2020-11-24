void receiver()
{
  //Check if new serial data has been written
  if (Serial.available() > 0) receivedString = Serial.readStringUntil('\n');
  //lcd.clear();
  //lcd.print(receivedString.length());

  //Create a system to encode all data to be returned to the interface in the string
    //char 0 = cabinLights
    //char 1 = cabinAc
    //char 2 = cabinHeat
    //char 3 = cabinDoorsLeftClosed
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
    //char 46 = mode
    //char 47 = cabinDoorsRightClosed
    //char 48-49 = platformSideChar
    //char 50-54 = stationCode
    //char 55 = stationUpcoming
    //char 56 = turnHeadlightsOn
    //char 57 = stationHere
    //char 58 = newline

//    lcd.clear();
//    lcd.setCursor(0,0);    
//    lcd.print(receivedString);
//    lcd.setCursor(0,3);
//    lcd.print(receivedString.length());

  if (receivedString.length() == 58)
  {
    //Adjusts cabin control outputs based on input data
    if (receivedString.substring(0,1).equals("1")) digitalWrite(CabinLightsOut, HIGH);
    else if (receivedString.substring(0,1).equals("0")) digitalWrite(CabinLightsOut, LOW);
    
    if (receivedString.substring(1,2).equals("1")) digitalWrite(CabinAcOut, HIGH);
    else if (receivedString.substring(1,2).equals("0")) digitalWrite(CabinAcOut, LOW);
    
    if (receivedString.substring(2,3).equals("1")) digitalWrite(CabinHeatOut, HIGH);
    else if (receivedString.substring(2,3).equals("0")) digitalWrite(CabinHeatOut, LOW);
    
    if (receivedString.substring(3,4).equals("1")) digitalWrite(CabinDoorsLeftOut, HIGH);
    else if (receivedString.substring(3,4).equals("0")) digitalWrite(CabinDoorsLeftOut, LOW);
    
    if (receivedString.substring(47,48).equals("1")) digitalWrite(CabinDoorsRightOut, HIGH);
    else if (receivedString.substring(47,48).equals("0")) digitalWrite(CabinDoorsRightOut, LOW);
    
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
    if(receivedString.substring(46,47).equals("1")) digitalWrite(mode, HIGH);
    else digitalWrite(mode, LOW);

    if(authority == "0    ") digitalWrite(zeroAuth, HIGH);
    else digitalWrite(zeroAuth, LOW);
    
    failureCode = receivedString.substring(44,45).toInt();
  
    int platformSideChar = receivedString.substring(48,50).toInt();
    if (platformSideChar == 66) platformSide = "BOTH";
    else if(platformSideChar == 76) platformSide = "LEFT";
    else platformSide = "RIGHT";
 
    stationCode = receivedString.substring(50,55);
    stationName = decodeStationName(stationCode);
    
    announcement = "The next station is " + stationName + ". ";
    if(platformSide == "LEFT") announcement += "Please exit on your left.";
    else if(platformSide == "RIGHT") announcement += "Please exit on your right.";
    else announcement += "Exit on either side.";

    stationUpcoming = receivedString.substring(55,56).toInt();
    if(stationUpcoming == 1) digitalWrite(stationSoon, HIGH);
    else digitalWrite(stationSoon, LOW);
    
    turnHeadlightsOn = receivedString.substring(56,57).toInt();
    if(turnHeadlightsOn == 1) digitalWrite(tunnel, HIGH);
    else digitalWrite(tunnel, LOW);

    stationHere = receivedString.substring(57,58).toInt();
    if(stationHere == 1 || authority == "0    ") digitalWrite(zeroAuth, HIGH);
    else digitalWrite(zeroAuth, LOW); 
  }
}

String decodeStationName(String code)
{
    if(stationCode == "00000") stationCode = "SHADYSIDE";
    else if(stationCode == "00001") stationCode = "HERRON AVE";
    else if(stationCode == "00010") stationCode = "SWISSVILLE";
    else if(stationCode == "00011") stationCode = "PENN STATION";
    else if(stationCode == "00100") stationCode = "STEEL PLAZA";
    else if(stationCode == "00101") stationCode = "FIRST AVE";
    else if(stationCode == "00110") stationCode = "STATION SQUARE";
    else if(stationCode == "00111") stationCode = "SOUTH HILLS JUNCTION";
    else if(stationCode == "01000") stationCode = "PIONEER";
    else if(stationCode == "01001") stationCode = "EDGEBROOK";
    else if(stationCode == "01010") stationCode = "WHITED";
    else if(stationCode == "01011") stationCode = "SOUTH BANK";
    else if(stationCode == "01100") stationCode = "CENTRAL";
    else if(stationCode == "01101") stationCode = "INGLEWOOD";
    else if(stationCode == "01110") stationCode = "OVERBROOK";
    else if(stationCode == "01111") stationCode = "GLENBURY";
    else if(stationCode == "10000") stationCode = "DORMONT";
    else if(stationCode == "10001") stationCode = "MT. LEBANON";
    else if(stationCode == "10010") stationCode = "POPLAR";
    else if(stationCode == "10011") stationCode = "CASTLE SHANNON";
    else stationCode = "YARD";
    return stationCode;
}
