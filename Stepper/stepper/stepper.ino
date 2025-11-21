int dirpin1 = 8;
int steppin1 = 9;

int dirpin2 = 10;
int steppin2 = 11;

int dirpin3 = 12;
int steppin3 = 13;

int preDefinedDistance = 225;

void runStepper1(int direction, int numOfSteps, int pulsewidthMicros = 25 ) {
  digitalWrite(dirpin1, direction);
  for (int n = 0; n < numOfSteps; n++) {
    digitalWrite(steppin1, HIGH);
    delayMicroseconds(pulsewidthMicros);
    digitalWrite(steppin1, LOW);
    delayMicroseconds(pulsewidthMicros);  
  }
}

void runStepper2(int direction, int numOfSteps, int pulsewidthMicros = 850) {
  digitalWrite(dirpin2, direction);
  for (int n = 0; n < numOfSteps; n++) {
    digitalWrite(steppin2, HIGH);
    delayMicroseconds(pulsewidthMicros);
    digitalWrite(steppin2, LOW);
    delayMicroseconds(pulsewidthMicros);  
  }
}

void runStepper3(int direction, int numOfSteps, int pulsewidthMicros = 850) {
  digitalWrite(dirpin3, direction);
  for (int n = 0; n < numOfSteps; n++) {
    digitalWrite(steppin3, HIGH);
    delayMicroseconds(pulsewidthMicros);
    digitalWrite(steppin3, LOW);
    delayMicroseconds(pulsewidthMicros);  
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Testing stepper");
  
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

void loop() {
  //stepper1
 // Move forward 
// for (int i = 0; i < preDefinedDistance; i++) {
//   runStepper1(HIGH, 3200);
// }
//
// delay(1000); // 1 second pause

 // Move backward
 for (int i = 0; i < preDefinedDistance; i++) {
   runStepper1(LOW, 3200);
 }

 delay(1000); // 1 second pause 
}
