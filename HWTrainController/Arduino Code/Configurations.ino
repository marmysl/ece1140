//Keypad Configuration
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'.', '0', '#', 'D'}
};

byte rowPins[ROWS] = {35, 37, 39, 41}; 
byte colPins[COLS] = {43, 45, 47, 49}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//Brake Pins
const int serviceBrakeOut = 33; //verified
const int emergencyBrakeOut = 32; //verified
const int serviceBrakeIn = 36; //verified
const int emergencyBrakeIn = 28; //verified

//Headlights Pins
const int headlightsIn = 38; //verified
const int headlightsOut = 31; //verified

//Logout Pin
const int LogoutIn = 29; //verified

//Failure Resolve Pin
const int resolveFailure  = 26; //verified

void brakeSetup()
{
  pinMode(serviceBrakeIn, INPUT);
  pinMode(emergencyBrakeIn, INPUT);
  pinMode(serviceBrakeOut, OUTPUT);
  pinMode(emergencyBrakeOut, OUTPUT);
  digitalWrite(serviceBrakeIn, LOW);
  digitalWrite(emergencyBrakeIn, LOW);
  digitalWrite(emergencyBrakeOut, LOW);
  digitalWrite(serviceBrakeOut, LOW);
}

void securitySetup()
{
  //Configure Log out as an Input
  pinMode(LogoutIn,INPUT);
  digitalWrite(LogoutIn,LOW);
}

//Cabin Controls Pin Assignments
const int CabinLightsOut = 2;
const int CabinAcOut = 3;
const int CabinHeatOut = 4;
const int CabinDoorsOut = 5;
const int CabinAdvertisementsOut = 6;
const int CabinAnnouncementsOut = 7;
const int CabinLightsIn = 8;
const int CabinAcIn = 9;
const int CabinHeatIn = 10;
const int CabinDoorsIn = 11;
const int CabinAdvertisementsIn = 12;
const int CabinAnnouncementsIn = 13;

//Function to initalize each cabin control pin
void cabinControlsSetup()
{
  //Declare digital pins as input or output
  pinMode(CabinLightsIn,INPUT);
  pinMode(CabinLightsOut,OUTPUT);
  pinMode(CabinAcIn,INPUT);
  pinMode(CabinAcOut,OUTPUT);
  pinMode(CabinHeatIn,INPUT);
  pinMode(CabinHeatOut,OUTPUT);
  pinMode(CabinDoorsIn,INPUT);
  pinMode(CabinDoorsOut,OUTPUT);
  pinMode(CabinAdvertisementsIn,INPUT);
  pinMode(CabinAdvertisementsOut,OUTPUT);
  pinMode(CabinAnnouncementsIn,INPUT);
  pinMode(CabinAnnouncementsOut,OUTPUT);

  //Set pins low initially
  digitalWrite(CabinLightsIn, LOW);
  digitalWrite(CabinLightsOut, LOW);
  digitalWrite(CabinAcIn, LOW);
  digitalWrite(CabinAcOut, LOW);
  digitalWrite(CabinHeatIn,LOW);
  digitalWrite(CabinHeatOut,LOW);
  digitalWrite(CabinDoorsIn,LOW);
  digitalWrite(CabinDoorsOut,LOW);
  digitalWrite(CabinAdvertisementsIn,LOW);
  digitalWrite(CabinAdvertisementsOut,LOW);
  digitalWrite(CabinAnnouncementsIn,LOW);
  digitalWrite(CabinAnnouncementsOut,LOW);

  //Headlights Pin Setup - will be in different category in future iterations
  pinMode(headlightsIn,INPUT);
  pinMode(headlightsOut,OUTPUT);
  digitalWrite(headlightsIn, LOW);
  digitalWrite(headlightsOut, LOW);
}
