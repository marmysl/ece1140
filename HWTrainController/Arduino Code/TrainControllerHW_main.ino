#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//LCD Object
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//String variables to hold Kp and Ki
String Kp_in, Ki_in;

//Successful Login
const int loginSuccess = 34; //verified

////Function prototypes
//void cabinControlsSetup();
//void speedRegulatorSetup();
//void securitySetup();
//void failureDetectorSetup();
//void engineerLogin();
//void enterKpKi();
//void driverLogin();
void reciever();
void transmitter();
//void failureDetector();
//void joystick();


void setup() {
  //Open Serial Port for Serial Communication
  Serial.begin(9600);
  
  //Initialize the LCD
  lcd.begin(16,4);
  lcd.clear();
  lcd.backlight();

  //Call setup functions for digital/analog pin initialization
  cabinControlsSetup();
  speedRegulatorSetup();
  securitySetup();
  failureDetectorSetup();
  brakeSetup();

  //Configure login success pin
  pinMode(loginSuccess, OUTPUT);
  digitalWrite(loginSuccess, LOW);
  login();
  //Kp_in = "44.44";
  //Ki_in = "55.55";

 }

void loop() 
{
  joystick();
  transmitter();
  reciever();
  failureDetector();
  logout();
  delay(900);
}
