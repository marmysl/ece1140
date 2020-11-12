//String that will hold outgoing data
String outgoingData;

void transmitter()
{
  //Check if new serial data has been written
  //Create a system to encode all data to be returned to the interface in the string
  //char 0 = cabinLights
  //char 1 = cabinAc
  //char 2 = cabinHeat
  //char 3 = cabinDoorsLeft
  //char 4 = cabinAdvertisements
  //char 5 = cabinAnnouncements
  //char6-10 = Kp
  //char11-15 = Ki
  //char16 = joystick up
  //char17 = joystick down
  //char18 = serviceBrake
  //char19 = emergencyBrake
  //char20 = resolve failure button
  //char 21 = headlights
  //char 22 = release brake
  //char 22 = cabinDoorsRight
  
  outgoingData = "";
  
  if(digitalRead(CabinLightsIn) == HIGH) outgoingData += "1";
  else outgoingData += "0";
  
  if(digitalRead(CabinAcIn) == HIGH) outgoingData += "1";
  else outgoingData += "0";
  
  //Cabin Heat
  if(digitalRead(CabinHeatIn) == HIGH) outgoingData += "1";
  else outgoingData += "0";

  //Cabin Doors
  if(digitalRead(CabinDoorsLeftIn) == HIGH) outgoingData += "1";
  else outgoingData += "0";
  
  //Cabin Advertisements
  if(digitalRead(CabinAdvertisementsIn) == HIGH) outgoingData += "1";
  else outgoingData += "0";
  
  //Cabin Announcements
  if(digitalRead(CabinAnnouncementsIn) == HIGH) outgoingData += "1";
  else outgoingData += "0";

  //Note KP AND KI VALUES MUST BE IN FORM 00.00
  outgoingData += Kp_in;
  outgoingData += Ki_in;
    
  if(analogRead(Y_pin) < 50) outgoingData += "1";
  else outgoingData += "0";

  if(analogRead(Y_pin) > 1000) outgoingData += "1";
  else outgoingData += "0";

  if(digitalRead(serviceBrakeIn) == HIGH) outgoingData += "1";
  else outgoingData += "0";
  
  if(digitalRead(emergencyBrakeIn) == HIGH) outgoingData += "1";
  else outgoingData += "0";

  if(digitalRead(resolveFailure) == HIGH) outgoingData += "1";
  else outgoingData += "0";

  if(digitalRead(headlightsIn) == HIGH) outgoingData += "1";
  else outgoingData += "0";

  if(digitalRead(releaseBrake) == HIGH) outgoingData += "1";
  else outgoingData += "0";

  if(digitalRead(CabinDoorsRightIn) == HIGH) outgoingData += "1";
  else outgoingData+= "0";

  Serial.println(outgoingData);
  
}
