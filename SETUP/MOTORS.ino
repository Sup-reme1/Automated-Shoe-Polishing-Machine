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

void runStepper2(int direction, int pulsewidthMicros = 810, int numOfSteps=100) {
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
