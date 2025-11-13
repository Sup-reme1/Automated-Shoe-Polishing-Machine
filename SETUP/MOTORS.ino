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

// pump control functions
void turnOnPump() {
  digitalWrite(pump1RelayPin, HIGH);
  delay(1000);
  digitalWrite(pump1RelayPin, LOW);
  delay(2000);
}

void turnOnWaterPump() {
  digitalWrite(pump2RelayPin, HIGH);
  delay(1000);
  digitalWrite(pump2RelayPin, LOW);
  delay(2000);
}


// Function to run steppers
void runStepper1(int direction, int numOfSteps, int pulsewidthMicros = 810) {
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
    runStepper1(HIGH, 200);
  }
  delay(1000); // 1 second pause

  // Move backward
  Serial.println("Moving Stepper 1 backward");
  for (int i = 0; i < preDefinedDistance; i++) {
    runStepper1(LOW, 200);
  }
  delay(1000); // 1 second pause 
}

//
// Setting the numOfSteps to 465 to increase the speed
void runStepper2(int direction, int pulsewidthMicros = 1500, int numOfSteps=48) {
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

void runStepper3(int direction, int numOfSteps, int pulsewidthMicros = 810) {
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
    runStepper3(HIGH, 200);
  }
  delay(1000); // 1 second pause

  // Move backward
  for (int i = 0; i < preDefinedDistance; i++) {
    runStepper3(LOW, 200);
  }
  delay(1000); // 1 second pause 
}


//ROTATION SEQUENCE FUNCTION

void setStep(int a, int b, int c, int d) {
  digitalWrite(A_0, a);
  digitalWrite(A_1, b);
  digitalWrite(A_2, c);
  digitalWrite(A_3, d);
  delayMicroseconds(STEP_DELAY);
}

void moveClockwise(int cycles){
  // Calculate the total number of steps needed
  long totalSteps = (long)cycles * STEPS_PER_REVOLUTION;

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