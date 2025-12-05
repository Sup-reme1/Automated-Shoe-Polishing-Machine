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
  delay(2000);
  digitalWrite(pump1RelayPin, HIGH);
  delay(2000);
}
// This function turns on the Polish spray
void turnOnPump() {
  digitalWrite(pump2RelayPin, HIGH);
  delay(2000);
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
void runStepper2(int direction, int numOfSteps=800, int pulsewidthMicros = 10000000) {
  digitalWrite(dirpin2, direction);
  for (int n = 0; n < numOfSteps; n++) {
    digitalWrite(steppin2, HIGH);
    delayMicroseconds(pulsewidthMicros);
    digitalWrite(steppin2, LOW);
    delayMicroseconds(pulsewidthMicros);  
  }
}
void driveStepper2ClockWise(int x=800){
  // Move forward
  runStepper2(HIGH, x);
  delay(1000); // 1 second pause
}
void driveStepper2AntiClockWise(int x=800){
  // Move Backward
  runStepper2(LOW, x);
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
    // Move forward
  for (int i = 0; i < preDefinedDistance; i++) {
    runStepper3(LOW, 3200);
  }
  delay(1000); // 1 second pause

    // Move backward
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

   // Drive shoe holder 
//   driveStepper2ClockWise();  
   
//   turnOnWaterPump();
   driveStepper1(); 

    // Drive shoe holder 
   driveStepper2AntiClockWise(); 

    // Clean left side of the shoe 
   driveStepper1(); 
   
   turnOnWaterPump();

   // Drive shoe holder 
   driveStepper2AntiClockWise();  

    // Clean top side of the shoe
   driveStepper1(); 
   
//   turnOnWaterPump();
   
   // Drive shoe holder
   driveStepper2AntiClockWise(805);  

   // Clean right side of the shoe
   driveStepper1();  
}
// Shoe polishing function
void polishShoe(){
  // Adjust this function to return the shoe to the start position
  driveStepper2ClockWise(1200);  // Drive shoe holder
  
  // polishing routine 
  
  // Activate pump for black polish on right side
  turnOnPump();     

  // Drive shoe holder
  driveStepper2ClockWise(650); 

  // Polish right side of shoe
  driveStepper3();  

  // Activate pump for black polish on top side 
  turnOnPump();

  
  driveStepper2ClockWise(400);  // Drive shoe holder

  driveStepper3();  // Polish top side of shoe

  // Drive shoe holder
  driveStepper2AntiClockWise(300);  

  // Activate pump for black polish
  turnOnPump();     

  // Drive shoe holder
  driveStepper2ClockWise(850);  

  // Drive polish brush and return to start
  driveStepper3();  

  // Drive shoe holder
  driveStepper2AntiClockWise();  

  // Drive shoe holder
  driveStepper2AntiClockWise();  
}
