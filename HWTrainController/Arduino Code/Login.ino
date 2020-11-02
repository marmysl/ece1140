bool driverLogin()
{
  //Character representing the input of the keypad
  char customKey;

  //String representing the employee ID that has been entered
  String employeeId = "";

  //Prompt user to enter in employee code
  String message = "Enter 5-Digit ID: ";
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(message);

  //Takes in 5 digits as the employee code
  //Note: takes all values except 00000
  //In actual implementation, would only accept valid driver ID number
  for(int i = 0; i<5; i++)
  {
    do
    {
      customKey = customKeypad.getKey();
    }
    while(!customKey);
    lcd.setCursor(i,1); 
    lcd.print(customKey);
    employeeId += customKey;
  }

  //Return a bool to the main with the success of the process
  if(employeeId != "00000")
  {
    //Return true to inform that the login process is over and successful
    lcd.clear();
    lcd.print("Login Successful");
    delay(1000);
    return true;
  }
  else
  {
    //Return false to inform that the login process was incomplete due to an incorrect 5 digit code
    lcd.clear();
    lcd.print("Login Unsuccessful. Enter a valid ID.");
    delay(1000);
    return false;
  }
}

bool engineerLogin()
{
  //Character representing the input of the keypad
  char customKey;

  //String representing the employee ID that has been entered
  String employeeId = "";

  //Prompt user to enter in employee code
  String message = "Enter 5-Digit ID: ";
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(message);

  //Takes in 5 digits as the employee code
  //Note: takes all values except 00000
  //In actual implementation, would only accept valid driver ID number
  for(int i = 0; i<5; i++)
  {
    do
    {
      customKey = customKeypad.getKey();
    }
    while(!customKey);
    lcd.setCursor(i,1); 
    lcd.print(customKey);
    employeeId += customKey;
  }

    //Return a bool to the main with the success of the process
  if(employeeId != "00000")
  {
    //Return true to inform that the login process is over and successful
    lcd.clear();
    lcd.print("Login Successful");
    delay(2000);
    return true;
  }
  else
  {
    //Return false to inform that the login process was incomplete due to an incorrect 5 digit code
    lcd.clear();
    lcd.print("Login Unsuccessful. Enter a valid ID.");
    delay(1000);
    return false;
  }
}

bool enterKpKi()
{
  //Character representing the input of the keypad
  char customKey;

  Kp_in = "";
  Ki_in = "";
  
  //Used to increment the columns of the keypad when entering in values
  int i = 0;

  //Flag that indicates if an incorrect digit is entered (a letter) for Kp and Ki
  bool errorKp = false;
  bool errorKi = false;

  //Prompt user to enter in Ki
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Enter Ki:");
  do
  {
    do
      {
        customKey = customKeypad.getKey();
      } while(!customKey);
      lcd.setCursor(i,1); 
      lcd.print(customKey);
      if(customKey != '#') Ki_in += customKey;
      if(customKey == 'A' || customKey == 'B' || customKey == 'C' || customKey == 'D') errorKi = true;
      i++;
  } while(customKey != '#');

  //Prompt user to enter in Kp
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Enter Kp:");
  i = 0;
  do
  {
    do
      {
        customKey = customKeypad.getKey();
      } while(!customKey);
      lcd.setCursor(i,1); 
      lcd.print(customKey);
      if(customKey != '#') Kp_in += customKey;
      if(customKey == 'A' || customKey == 'B' || customKey == 'C' || customKey == 'D') errorKp = true;
      i++;
  } while(customKey != '#');
  
  //Report the success of the login process
  if(errorKp || errorKi || Kp_in.length() != 5 || Ki_in.length() != 5)
  {
    //Return false to inform that the login process was incomplete due to an incorrect 5 digit code
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Error - invalid Kp");
    lcd.setCursor(1,0);
    lcd.print("and Ki values.");
    lcd.setCursor(2,0);
    lcd.print("Re-enter values.");
    delay(2000);
    return false;
  }
  else
  {
    //Return true to inform the user that the values were entered successfully
    lcd.clear();
    lcd.print("Success!");
    delay(2000);
    return true;
  }
}

void login()
{
  digitalWrite(loginSuccess, LOW);
  
  while(!engineerLogin());
  while(!enterKpKi());
  while(!driverLogin());

  digitalWrite(loginSuccess, HIGH);
}

void logout()
{
  lcd.setCursor(0,0);
  lcd.print("Logout Confirmation:");
  lcd.setCursor(1,0);
  lcd.print("(A = yes, B = no)");
  char customKey = customKeypad.getKey();
  if(customKey == 'A') login();
  else return;
}
