//Failure Detector Constants
const int resolveFailure = 26;
const int BCD_A = 22;
const int BCD_B = 23;
const int BCD_C = 24;
const int BCD_D = 25;

//Variable to store failure code
int failureCode;

void failureDetectorSetup()
{
  //Failure detector
  pinMode(BCD_A, OUTPUT);
  pinMode(BCD_B, OUTPUT);
  pinMode(BCD_C, OUTPUT);
  pinMode(BCD_D, OUTPUT);
  digitalWrite(BCD_A, LOW);
  digitalWrite(BCD_B, LOW);
  digitalWrite(BCD_C, LOW);
  digitalWrite(BCD_D, LOW);
  pinMode(resolveFailure, INPUT);
  digitalWrite(resolveFailure,LOW);
  failureCode = 0;
}

void failureDetector()
{
  if(failureCode == 0)
  {
    digitalWrite( BCD_A, (0 >> 0) & 0x1);
    digitalWrite( BCD_B, (0 >> 1) & 0x1);
    digitalWrite( BCD_C, (0 >> 2) & 0x1);
    digitalWrite( BCD_D, (0 >> 3) & 0x1);
  }
  if(failureCode == 1)
  {
    digitalWrite( BCD_A, (1 >> 0) & 0x1);
    digitalWrite( BCD_B, (1 >> 1) & 0x1);
    digitalWrite( BCD_C, (1 >> 2) & 0x1);
    digitalWrite( BCD_D, (1 >> 3) & 0x1);
  }
  if(failureCode == 2)
  {
    digitalWrite( BCD_A, (2 >> 0) & 0x1);
    digitalWrite( BCD_B, (2 >> 1) & 0x1);
    digitalWrite( BCD_C, (2 >> 2) & 0x1);
    digitalWrite( BCD_D, (2 >> 3) & 0x1);
  }
  if(failureCode == 3)
  {
    digitalWrite( BCD_A, (3 >> 0) & 0x1);
    digitalWrite( BCD_B, (3 >> 1) & 0x1);
    digitalWrite( BCD_C, (3 >> 2) & 0x1);
    digitalWrite( BCD_D, (3 >> 3) & 0x1);
  }
  if(failureCode != 0 && digitalRead(resolveFailure) == HIGH)
  {
    digitalWrite( BCD_A, (0 >> 0) & 0x1);
    digitalWrite( BCD_B, (0 >> 1) & 0x1);
    digitalWrite( BCD_C, (0 >> 2) & 0x1);
    digitalWrite( BCD_D, (0 >> 3) & 0x1);
  }
}
