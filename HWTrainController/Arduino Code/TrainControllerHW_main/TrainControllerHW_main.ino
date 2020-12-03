#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//LCD Object
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//String variables to hold Kp and Ki
String Kp_in, Ki_in;

//String that will hold received data
String receivedString;


void setup() {
  //Open Serial Port for Serial Communication
  Serial.begin(9600);
  
  //Initialize the LCD
  lcd.begin(20,4);
  lcd.clear();
  lcd.backlight();

  //Call setup functions for digital/analog pin initialization
  cabinControlsSetup();
  speedRegulatorSetup();
  securitySetup();
  failureDetectorSetup();
  brakeSetup();

  //Initiate the login process
  //Recommended values are  Kp = 50.00 and Ki = 0.000
  while(!enterKpKi());
  //Kp_in = "50.00";
  //Ki_in = "0.000";
 }

void loop() 
{
  joystick();
  transmitter();
  receiver();
  failureDetector();
  logout();
  delay(500);
}
