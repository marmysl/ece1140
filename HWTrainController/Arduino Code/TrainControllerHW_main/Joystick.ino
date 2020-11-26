//Joystick Pin Assignments
const int X_pin = 0; //analog pin connected to X output
const int Y_pin = 1; //analog pin connected to Y output

//Variables to store the outputs of the display
String commandedSpeed = "";
String currentSpeed = "";
String authority = "";
String setpointSpeed = "";
String Kp = "";
String Ki = "";
String power  = "";
String platformSide = "";
String stationName = "";
String stationCode = "";
String announcement = "";

//Integer to keep track of which menu the LCD is displaying
int joystickCount;

void speedRegulatorSetup()
{
  //Set joystickCount to 0
  joystickCount = 0;
  pinMode(X_pin, INPUT);
  pinMode(Y_pin, INPUT);
}

void joystick()
{
  if(analogRead(X_pin) < 50) joystickCount--;
  else if(analogRead(X_pin) > 1000) joystickCount++;
  
  //Handles the joystick swiping (left/right joystick motions display different menus
  if(abs(joystickCount) % 5 == 0)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Current Speed: ");
    lcd.setCursor(0,1);
    lcd.print(currentSpeed + " mi/hr");
    lcd.setCursor(0,2);
    lcd.print("Setpoint Speed:");
    lcd.setCursor(0,3);
    lcd.print(setpointSpeed + " mi/hr");
  }
  else if(abs(joystickCount) % 5 == 1)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Kp: " + Kp + " W/(m/s)");
    lcd.setCursor(0,1);
    lcd.print("Ki: " + Ki + " W/m");
    lcd.setCursor(0,2);
    lcd.print("Power:" + power + " kW");
  }
  else if(abs(joystickCount) % 5 == 2)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Commanded Speed: ");
    lcd.setCursor(0,1);
    lcd.print(commandedSpeed + " mi/hr");
    lcd.setCursor(0,2);
    lcd.print("Authority: ");
    lcd.setCursor(0,3);
    lcd.print(authority + " blocks");
  }
  else if(abs(joystickCount) % 5 == 3)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Next Station: ");
    lcd.setCursor(0,1);
    lcd.print(stationName);
    lcd.setCursor(0,2);
    lcd.print("Platform Side:");
    lcd.setCursor(0,3);
    lcd.print(platformSide);
  }
  else if(abs(joystickCount) % 5 == 4)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Length: ");
    lcd.setCursor(0,1);
    lcd.print(receivedString.length());
    /*
    if(CabinAnnouncementsOut == HIGH)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Announcement: ");
      lcd.setCursor(0,1);
      lcd.print("The next station is");
      lcd.setCursor(0,2);
      lcd.print(stationName);
      lcd.setCursor(0,3); 

      if(platformSide == "RIGHT") lcd.print("Exit right.");
      else if(platformSide == "LEFT") lcd.print("Exit left.");
      else lcd.print("Exit either side.");
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Announcements Off");
    }
    */
  }
}
