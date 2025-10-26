#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int dirpin1 = 8;
int steppin1 = 9;

int dirpin2 = 10;
int steppin2 = 11;

int dirpin3 = 12;
int steppin3 = 13;

int preDefinedDistance = 220;

// Define the pins for your components
const int stopButtonPin = 3; // Pin for the start button
const int BpolishButtonPin = 4; // Pin for the button to select polish
const int BrpolishButtonPin = 5; // Pin for the button to select polish

const int doorSensorPin ;  // Digital pin for the magnetic reed switch
const int shoeSensorPin ;  // Digital pin for the IR proximity sensor

const int buzzerRelayPin = 6; // Analog pin 1 - Pin to control the buzzer relay
const int pump1RelayPin = 7; // Pin to control the pump2 relay
const int pump2RelayPin; // Pin to control the pump2 relay

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
  digitalWrite(pump1RelayPin, LOW);
  delay(1000);
  digitalWrite(pump1RelayPin, HIGH);
}

//long getDistanceCM(int trigPin, int echoPin) {
//  // Clears the trigPin
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  // Sets the trigPin on HIGH state for 10 micro seconds
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  
//  // Reads the echoPin, returns the sound wave travel time in microseconds
//  long duration = pulseIn(echoPin, HIGH);
//  
//  // Calculating the distance in CM
//  long distance = duration * 0.034 / 2;
//  return distance;
//}

//void checkFluid() {
//  // Read distance from both sensors
//  long distance1 = getDistanceCM(TRIG_PIN_1, ECHO_PIN_1);
//  long distance2 = getDistanceCM(TRIG_PIN_2, ECHO_PIN_2);
//
//  Serial.print("Sensor 1 Distance: ");
//  Serial.print(distance1);
//  Serial.print("cm | Sensor 2 Distance: ");
//  Serial.print(distance2);
//  Serial.println("cm");
//
//  // Check if both sensors agree that the level is low
//  if (distance1 > LOW_LEVEL_THRESHOLD && distance2 > LOW_LEVEL_THRESHOLD) {
//    Serial.println("STATUS: Fluid Level is LOW ⚠️");
//    // You can also add code here to trigger a low level warning on your LCD
//    // or trigger an action like turning on a warning LED.
//  }
//  // Check if at least one sensor detects a good level
//  else if (distance1 <= LOW_LEVEL_THRESHOLD || distance2 <= LOW_LEVEL_THRESHOLD) {
//    Serial.println("STATUS: Fluid Level is GOOD ✅");
//  }
//  // A final check in case of a single sensor error or discrepancy
//  else {
//    Serial.println("STATUS: Reading Discrepancy, Check Sensors.");
//  }
//}
//

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
  for (int i = 0; i < preDefinedDistance; i++) {
    runStepper1(LOW, 200);
  }
  delay(1000); // 1 second pause 
}

void runStepper2(int direction, int numOfSteps, int pulsewidthMicros = 810) {
  digitalWrite(dirpin2, direction);
  for (int n = 0; n < numOfSteps; n++) {
    digitalWrite(steppin2, HIGH);
    delayMicroseconds(pulsewidthMicros);
    digitalWrite(steppin2, LOW);
    delayMicroseconds(pulsewidthMicros);  
  }
}
void driveStepper2(){
  // Move forward
  for (int i = 0; i < preDefinedDistance; i++) {
    runStepper2(HIGH, 200);
  }
  delay(1000); // 1 second pause

  // // Move backward
  // for (int i = 0; i < preDefinedDistance; i++) {
  //   runStepper2(LOW, 200);
  // }
  // delay(1000); // 1 second pause 
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

void setup() {
  Serial.begin(9600);

//Initializing Stepper motor 
  initializeMotor();

  pinMode(pump1RelayPin, OUTPUT);
  pinMode(pump2RelayPin, OUTPUT);

// Set up  pins as inputs or outputs
  pinMode(stopButtonPin, INPUT_PULLUP);
  pinMode(BpolishButtonPin, INPUT_PULLUP);
  pinMode(BrpolishButtonPin, INPUT_PULLUP);

  pinMode(buzzerRelayPin, OUTPUT);
  pinMode(pump1RelayPin, OUTPUT);
  pinMode(pump2RelayPin, OUTPUT);

//  Off the components by default
  digitalWrite(pump1RelayPin, HIGH);
  digitalWrite(pump2RelayPin, HIGH);  
  digitalWrite(buzzerRelayPin, LOW); 

  //pump setup
  pinMode(pumpBlack, OUTPUT);
  pinMode(pumpBrown, OUTPUT);
  
//  Test Pump
  Serial.println("testing PUMP");
  lcdDisplay("Checking Pump", 1);
  digitalWrite(pump1RelayPin, LOW);
  delay(1000);
  digitalWrite(pump1RelayPin, HIGH);
}

void loop() { 

  Serial.println("In the loop");
  if (digitalRead(stopButtonPin) == LOW){
    Serial.println("Stop Btn Pressed");
  } else if (digitalRead(BpolishButtonPin) == LOW){
    Serial.println("Black polish Btn Pressed");
  } else if (digitalRead(BrpolishButtonPin) == LOW){
    Serial.println("Brown polish Btn Pressed");
  }

  //clean routine
  // Move stepper 1 forward 
  Serial.println("Drive and return Clean brush");
  driveStepper1();  // Drive clean brush and return to start  
  driveStepper2();  // Drive shoe holder
  driveStepper1();  // Drive clean brush and return to start
  driveStepper2();  // Drive shoe holder
  driveStepper1();  // Drive clean brush and return to start

  // Adjust this function to return the shoe to the start position
  driveStepper2();  // Drive shoe holder to start position

  // polishing routine
  // first wave of polish
  driveStepper2();  // Drive shoe holder to face the side of the shoe upward
  turnOnPump();     // Activate pump for black polish
  driveStepper2();  // Drive shoe holder
  driveStepper3();  // Drive polish brush and return to 

  turnOnPump();     // Activate pump for black polish
  driveStepper2();  // Drive shoe holder
  driveStepper3();  // Drive polish brush and return to start

  turnOnPump();     // Activate pump for black polish
  driveStepper2();  // Drive shoe holder
  driveStepper3();  // Drive polish brush and return to start
  // Adjust this function to return the shoe to the start position
  driveStepper2();  // Drive shoe holder to start position

  Serial.println("Restarting the loop");

}
