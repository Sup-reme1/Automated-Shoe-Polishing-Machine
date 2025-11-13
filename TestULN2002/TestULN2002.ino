int IN1=11;
int IN2= 10;
int IN3= 9;
int IN4= 8;

const int STEPS_PER_REVOLUTION = 512;

const int STEP_DELAY = 2000;

// The full-step sequence
void setStep(int a, int b, int c, int d) {
  digitalWrite(IN1, a);
  digitalWrite(IN2, b);
  digitalWrite(IN3, c);
  digitalWrite(IN4, d);
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

void moveAntiClockwise(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


void setup() {
  // put your setup code here, to run once:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  setStep(LOW, LOW, LOW, LOW);
  moveClockwise(1);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  delay(2000);
//  moveAntiClockwise();

}
