// add the library with motor functions
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int dirpin1 = 8;
int steppin1 = 9;

int dirpin2 = 10;
int steppin2 = 11;

int dirpin3 = 12;
int steppin3 = 13;

int preDefinedDistance = 225;

// Define the pins for your components
const int stopButtonPin = 3; // Pin for the start button
const int BpolishButtonPin = 4; // Pin for the button to select polish
const int BrpolishButtonPin = 5; // Pin for the button to select polish

const int doorSensorPin ;  // Digital pin for the magnetic reed switch
const int shoeSensorPin ;  // Digital pin for the IR proximity sensor

const int buzzerRelayPin = 5; // Analog pin 1 - Pin to control the buzzer relay
const int pump1RelayPin = 7; // Pin to control the pump1 polish relay
const int pump2RelayPin = 6; // Pin to control the pump2 relay


// pump control functions
void turnOnPump() {
  digitalWrite(pump1RelayPin, HIGH);
  delay(1000);
  digitalWrite(pump1RelayPin, LOW);
  delay(2000);
}

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
  lcd.backlight();
  lcd.print("Shoe Polishing Machine");

//Initializing Stepper motor 
  initializeMotor();

  pinMode(pump1RelayPin, OUTPUT);
  pinMode(pump2RelayPin, OUTPUT);
  digitalWrite(pump1RelayPin, LOW);
  digitalWrite(pump2RelayPin, HIGH);  

// Set up  pins as inputs or outputs
  pinMode(stopButtonPin, INPUT_PULLUP);
  pinMode(BpolishButtonPin, INPUT_PULLUP);
  pinMode(BrpolishButtonPin, INPUT_PULLUP);

  pinMode(buzzerRelayPin, OUTPUT);
  pinMode(pump1RelayPin, OUTPUT);
  pinMode(pump2RelayPin, OUTPUT);

//  Off the components by default
  digitalWrite(buzzerRelayPin, HIGH); 
  digitalWrite(dirpin1, LOW); 
  digitalWrite(steppin1, LOW); 
  digitalWrite(dirpin2, LOW); 
  digitalWrite(steppin2, LOW); 
  digitalWrite(dirpin3, LOW); 
  digitalWrite(steppin3, LOW); 

}

void loop() { 

  driveStepper2ClockWise();  // Drive shoe holder
  driveStepper2ClockWise();  // Drive shoe holder
  driveStepper2ClockWise();  // Drive shoe holder
  driveStepper2ClockWise();  // Drive shoe holder

  delay(2000);
  
  driveStepper2AntiClockWise();  // Drive shoe holder
  driveStepper2AntiClockWise();  // Drive shoe holder
  driveStepper2AntiClockWise();  // Drive shoe holder
  driveStepper2AntiClockWise();  // Drive shoe holder

  driveStepper2AntiClockWise();  // Drive shoe holder


//  Serial.println("In the loop");
//  if (digitalRead(BpolishButtonPin) == LOW){
//    Serial.println("Black polish Btn Pressed");
//  } 
//  else if (digitalRead(BrpolishButtonPin) == LOW){
//    Serial.println("Brown polish Btn Pressed");
//  }
//  else if (digitalRead(stopButtonPin) == LOW){
//    Serial.println("Stop Btn Pressed");
//    delay(5000);
//  } 
//
////  //clean routine
////  // Move stepper 1 forward 
////  Serial.println("Drive and return Clean brush");
////  driveStepper1();  // Drive clean brush and return to start  
////  // driveStepper2();  // Drive shoe holder
////  driveStepper2AntiClockWise();  // Drive shoe holder
////  driveStepper1();  // Drive clean brush and return to start
////  // driveStepper2();  // Drive shoe holder
////  driveStepper2AntiClockWise();  // Drive shoe holder
////  driveStepper1();  // Drive clean brush and return to start
//
//  // Adjust this function to return the shoe to the start position
//  // driveStepper2();  // Drive shoe holder to start position
//  driveStepper2ClockWise();  // Drive shoe holder
//
//  // polishing routine
//  // first wave of polish
//  // driveStepper2();  // Drive shoe holder to face the side of the shoe upward
//  turnOnPump();     // Activate pump for black polish
//  // driveStepper2();  // Drive shoe holder
//  Serial.println("Drive and return Clean brush");
//  driveStepper2ClockWise();  // Drive shoe holder
//  driveStepper3();  // Drive polish brush and return to 
//
//  turnOnPump();     // Activate pump for black polish
//  // driveStepper2();  // Drive shoe holder
//  driveStepper2ClockWise();  // Drive shoe holder
//  driveStepper3();  // Drive polish brush and return to start
//
//  turnOnPump();     // Activate pump for black polish
//  // driveStepper2();  // Drive shoe holder
//  driveStepper2ClockWise();  // Drive shoe holder
//  driveStepper3();  // Drive polish brush and return to start
//  // Adjust this function to return the shoe to the start position
//  // driveStepper2();  // Drive shoe holder to start position
//  driveStepper2AntiClockWise();  // Drive shoe holder
//  driveStepper2AntiClockWise();  // Drive shoe holder
//
//  digitalWrite(buzzerRelayPin, HIGH); // Turn on buzzer to indicate end of cycle
//  delay(2000); // Buzzer on for 2 seconds
//  digitalWrite(buzzerRelayPin, LOW); // Turn on buzzer to indicate end of cycle
//  Serial.println("Restarting the loop");

}
