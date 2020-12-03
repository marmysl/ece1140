// Include library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Initialize the Liquid Crystal library with the numbers of the interface pins
// set the LCD address to 0x27 for a 16 chars and 4 line display
LiquidCrystal_I2C lcd1(0x27,16,4);

// Train Detection LED
int Detect_LED = 25;

// Failure Monitor LED
int Failure_LED = 24;

// Traffic Lights
int Red_LED = 8;
int Yellow_LED = 7;
int Green_LED = 6;

void setup() {  
    // LCD and Serial Port
    lcd1.init();
    lcd1.backlight();
    Serial.begin(9600);

    // Initializer functions
    detectTrain();
    detectFailure();
    setUpload();
    setManual();
    setJoystick();
}

void loop() {
    // updating functions
    enableOverride();
    uploadPLC();
    joystick();  
    Transmitter();
    Receiver();
    delay(500);
}
