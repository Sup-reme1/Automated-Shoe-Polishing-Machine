void initializeMotor(){
  pinMode(dirpin1, OUTPUT);
  pinMode(steppin1, OUTPUT);

  digitalWrite(dirpin1, LOW);
  digitalWrite(steppin1, LOW);

  pinMode(dirpin2, OUTPUT);
  pinMode(steppin2, OUTPUT);

  digitalWrite(dirpin2, LOW);
  digitalWrite(steppin2, LOW);

  pinMode(dirpin3, OUTPUT);
  pinMode(steppin3, OUTPUT);

  digitalWrite(dirpin3, LOW);
  digitalWrite(steppin3, LOW);
}

// ticker params is used to indicate the row for the message. It is default to 0
void screen(String scrollMessage, int ticker = 0) {
  int displayWidth = 16; 
  int scrollNum = scrollMessage.length() - displayWidth + 1;

  // Print the scrolling message to the second row
  lcd.clear();
  lcd.setCursor(0, ticker);
  lcd.print(scrollMessage);

  // Scroll the message to the left
  if (scrollNum > 0) {
    for (int i = 0; i < scrollNum; i++) {
      lcd.scrollDisplayLeft();
      delay(200); // Adjust delay for scrolling speed
    };
  }
  lcd.clear();
  lcd.setCursor(0, ticker);
  lcd.print(scrollMessage); 
  delay(1000); 
};

// This function take a string as an argument 
// lesser than 16 char and display it on the lcd screen
void fixScreen(String Message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(Message);
}

// This function turns on the water spray
void turnOnWaterPump() {
  digitalWrite(pump1RelayPin, LOW);
  delay(1000);
  digitalWrite(pump1RelayPin, HIGH);
  delay(2000);
}
// This function turns on the Polish spray
void turnOnPump() {
  digitalWrite(pump2RelayPin, HIGH);
  delay(1000);
  digitalWrite(pump2RelayPin, LOW);
  delay(2000);
}

// This function power the buzzer after polishing
void alertUser(){
   digitalWrite(buzzerRelayPin, LOW); // Turn on buzzer to indicate end of cycle
   delay(2000); // Buzzer on for 2 seconds
   digitalWrite(buzzerRelayPin, HIGH); // Turn on buzzer to indicate end of cycle
}

// Function to run steppers
void runStepper1(int direction, int numOfSteps, int pulsewidthMicros = 35) {
  digitalWrite(dirpin1, direction);
  for (int n = 0; n < numOfSteps; n++) {
    digitalWrite(steppin1, HIGH);
    delayMicroseconds(pulsewidthMicros);
    digitalWrite(steppin1, LOW);
    delayMicroseconds(pulsewidthMicros);  
  }
}
void driveStepper1(){
    // Move forward
  for (int i = 0; i < preDefinedDistance; i++) {
    runStepper1(HIGH, 3200);
  }
  delay(1000); // 1 second pause

  // Move backward
  Serial.println("Moving Stepper 1 backward");
  for (int i = 0; i < preDefinedDistance; i++) {
    runStepper1(LOW, 3200);
  }
  delay(1000); // 1 second pause 
}

//
// Setting the numOfSteps to 48 to increase the speed
void runStepper2(int direction, int pulsewidthMicros = 10000000, int numOfSteps=800) {
  digitalWrite(dirpin2, direction);
  for (int n = 0; n < numOfSteps; n++) {
    digitalWrite(steppin2, HIGH);
    delayMicroseconds(pulsewidthMicros);
    digitalWrite(steppin2, LOW);
    delayMicroseconds(pulsewidthMicros);  
  }
}
void driveStepper2ClockWise(){
  // Move forward
  runStepper2(HIGH);
  delay(1000); // 1 second pause
}
void driveStepper2AntiClockWise(){
  // Move Backward
  runStepper2(LOW);
  delay(1000); // 1 second pause
}

void runStepper3(int direction, int numOfSteps, int pulsewidthMicros = 35) {
  digitalWrite(dirpin3, direction);
  for (int n = 0; n < numOfSteps; n++) {
    digitalWrite(steppin3, HIGH);
    delayMicroseconds(pulsewidthMicros);
    digitalWrite(steppin3, LOW);
    delayMicroseconds(pulsewidthMicros);  
  }
}
void driveStepper3(){
  // Move backward
  for (int i = 0; i < preDefinedDistance; i++) {
    runStepper3(LOW, 3200);
  }
  delay(1000); // 1 second pause 


    // Move forward
  for (int i = 0; i < preDefinedDistance; i++) {
    runStepper3(HIGH, 3200);
  }
  delay(1000); // 1 second pause
}


//ROTATION SEQUENCE FUNCTION
void setStep(int a, int b, int c, int d) {
  mcp.digitalWrite(A_0, a);
  mcp.digitalWrite(A_1, b);
  mcp.digitalWrite(A_2, c);
  mcp.digitalWrite(A_3, d);
  delayMicroseconds(STEP_DELAY);
}

void changePolishBrush(int cycles){
  // Calculate the total number of steps needed
  long totalSteps = ((long)cycles * STEPS_PER_REVOLUTION)/2;

  // Loop through all the steps
  for (long i = 0; i < totalSteps; i++) {    
    // Step 1: 1000
    setStep(HIGH, HIGH, LOW, LOW);
    // Step 2: 0100
    setStep(LOW, HIGH, HIGH, LOW);
    // Step 3: 0010
    setStep(LOW, LOW, HIGH, HIGH);
    // Step 4: 0001
    setStep(HIGH, LOW, LOW, HIGH);
  }
  setStep(LOW, LOW, LOW, LOW);
}

// Shoe cleaning functions
void cleanShoe() {
  // Clean routine
  // Move stepper 1 forward 
   driveStepper2ClockWise();  // Drive shoe holder 
   turnOnWaterPump();
   driveStepper2AntiClockWise();  // Drive shoe holder 
   driveStepper1();  // Clean left side of the shoe 
   turnOnWaterPump();
   driveStepper2AntiClockWise();  // Drive shoe holder 
   driveStepper1();  // Clean top side of the shoe
   turnOnWaterPump();
   driveStepper2AntiClockWise();  // Drive shoe holder
   driveStepper1();  // Clean right side of the shoe
}
// Shoe polishing function
void polishShoe(){
   // Adjust this function to return the shoe to the start position
   driveStepper2ClockWise();  // Drive shoe holder
   // driveStepper2ClockWise();  // Drive shoe holder
   
   // polishing routine  
   turnOnPump();     // Activate pump for black polish on right side
   driveStepper2ClockWise();  // Drive shoe holder
   driveStepper3();  // Polish right side of shoe
  
   turnOnPump();     // Activate pump for black polish on top side  
   driveStepper2ClockWise();  // Drive shoe holder
   driveStepper3();  // Polish top side of shoe

  turnOnPump();     // Activate pump for black polish
  driveStepper2ClockWise();  // Drive shoe holder
  driveStepper3();  // Drive polish brush and return to start

   driveStepper2AntiClockWise();  // Drive shoe holder
   driveStepper2AntiClockWise();  // Drive shoe holder
}
