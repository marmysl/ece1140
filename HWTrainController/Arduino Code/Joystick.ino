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
String  power  = "";

//Integer to keep track of which menu the LCD is displaying
int joystickCount;
void speedRegulatorSetup()
{
  //Set joystickCount to 0
  joystickCount = 0;
}

void joystick()
{
  if(analogRead(X_pin) < 100) joystickCount--;
  else if(analogRead(X_pin) > 900) joystickCount++;
  
  //Handles the joystick swiping (left/right joystick motions display different menus
  if(abs(joystickCount) % 6 == 0)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Current Speed: ");
    lcd.setCursor(0,1);
    lcd.print(currentSpeed);
  }
  else if(abs(joystickCount) % 6 == 1)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Commanded Speed: ");
    lcd.setCursor(0,1);
    lcd.print(commandedSpeed);
  }
  else if(abs(joystickCount) % 6 == 2)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Authority: ");
    lcd.setCursor(0,1);
    lcd.print(authority);
  }
  else if(abs(joystickCount) % 6 == 3)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Distance to Station: ");
    lcd.setCursor(0,1);
    lcd.print("Not developed");
  }
  else if(abs(joystickCount) % 6 == 4)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Setpoint Speed: ");
    lcd.setCursor(0,1);
    lcd.print(setpointSpeed);
  }
  else if(abs(joystickCount) % 6 == 5)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Kp: " + Kp);
    lcd.setCursor(0,1);
    lcd.print("Ki: " + Ki);
  }
  delay(200);
}
