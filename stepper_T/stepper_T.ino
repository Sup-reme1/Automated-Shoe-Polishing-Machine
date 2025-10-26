int dirpin = 10;
int steppin = 11;

int numOfSteps = 200;

int pulsewidthMicros = 1000;

// int distance = 0;

// int preDefinedDistance = 5000;


void forward50(){
  digitalWrite(dirpin, HIGH);
  for(numOfSteps = 0; numOfSteps < 50; numOfSteps++){
    digitalWrite(steppin, HIGH);
    delayMicroseconds(pulsewidthMicros);
    digitalWrite(steppin, LOW);
  }
}

void backward50(){
  digitalWrite(dirpin, LOW);
  for(numOfSteps = 0; numOfSteps < 50; numOfSteps++){
    digitalWrite(steppin, HIGH);
    delayMicroseconds(pulsewidthMicros);
    digitalWrite(steppin, LOW);
  }
}

void setup(){
  Serial.begin(9600);
  Serial.println("Testing stepper");
  
  pinMode(dirpin, OUTPUT);
  pinMode(steppin, OUTPUT);

  forward50();
  backward50();

//  digitalWrite(dirpin, HIGH);
//  for(int i = 0; i < numOfSteps; i++ ){
//    digitalWrite(steppin, HIGH);
//    delayMicroseconds(pulsewidthMicros);
//    digitalWrite(steppin, LOW);
//  }
//
//   delay(1000);
//
// digitalWrite(dirpin, LOW);
// for(int i = 0; i < numOfSteps; i++ ) {
//   digitalWrite(steppin, HIGH);
//   delayMicroseconds(pulsewidthMicros);
//   digitalWrite(steppin, LOW);
//  }
}


void loop()
{
 digitalWrite(dirpin, HIGH);
  for(int i = 0; i < numOfSteps; i++ ){
    digitalWrite(steppin, HIGH);
    delayMicroseconds(pulsewidthMicros);
    digitalWrite(steppin, LOW);
  }

 delay(1000);

 digitalWrite(dirpin, LOW);
 for(int i = 0; i < numOfSteps; i++ ) {
   digitalWrite(steppin, HIGH);
   delayMicroseconds(pulsewidthMicros);
   digitalWrite(steppin, LOW);
  }
  delay(1000);
  }
