// Add the library with motor functions
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_MCP23XXX.h>
#include <Adafruit_MCP23X17.h>
#include <Adafruit_MCP23X08.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//create an instance
Adafruit_MCP23X17 mcp;

//small stepper variables
const int STEPS_PER_REVOLUTION = 512;
const int STEP_DELAY = 2000;

//mcp uln pins
#define A_0 0 //IN1
#define A_1 1 //IN2
#define A_2 2 //IN3
#define A_3 3 //IN4

int dirpin1 = 8;
int steppin1 = 9;

//int dirpin2 = 10;
//int steppin2 = 11;

int dirpin2 = 12;
int steppin2 = 13;

int dirpin3;
int steppin3;

int preDefinedDistance = 225;

// Define the pins for your components
const int stopButtonPin = 3; // Pin for the start button
const int BpolishButtonPin = 4; // Pin for the button to select polish
const int BrpolishButtonPin = 5; // Pin for the button to select polish

const int doorSensorPin ;  // Digital pin for the magnetic reed switch
const int shoeSensorPin ;  // Digital pin for the IR proximity sensor

const int buzzerRelayPin = 5; // Analog pin 1 - Pin to control the buzzer relay
const int pump1RelayPin = 6; // Pin to control the pump1 water relay
const int pump2RelayPin = 7; // Pin to control the pump2 relay

///////////////
//  SETUP
void setup() {
  Serial.begin(9600);

  //starts mcp in I2C mode
  mcp.begin_I2C();

  lcd.begin();
  lcd.backlight();  
  lcd.clear();
  screen("Shoe Polishing Machine");

  // configure pin of mcp for output
  mcp.pinMode(A_0, OUTPUT);
  mcp.pinMode(A_1, OUTPUT);
  mcp.pinMode(A_2, OUTPUT);
  mcp.pinMode(A_3, OUTPUT);

  // drive pins low
  setStep(LOW, LOW, LOW, LOW);

  //Initializing Stepper motor 
  initializeMotor();

  pinMode(pump1RelayPin, OUTPUT);
  pinMode(pump2RelayPin, OUTPUT);
  digitalWrite(pump1RelayPin, HIGH);
  digitalWrite(pump2RelayPin, LOW);  

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
//  screen("Enter Polish Color");
  
  if (digitalRead(BpolishButtonPin) == LOW){
    screen("Black Polish");
  } 
  else if (digitalRead(BrpolishButtonPin) == LOW){
    screen("Brown Polish");
  }
  else if (digitalRead(stopButtonPin) == LOW){
    screen("Polishing");
    delay(2000);
    // Engine is inserted here
  } 

//  screen("water pump");
//  turnOnWaterPump();
//  delay(500);
//  screen("Polish pump");
//  turnOnPump();
//  delay(500);

  driveStepper2ClockWise();
  delay(500);
  driveStepper2ClockWise();
  delay(500);
  driveStepper2ClockWise();
  delay(500);
  driveStepper2ClockWise();
  delay(500);

//  driveStepper1();
  
  // Engine Starts Here
  // Clean routine
  // Move stepper 1 forward 
//   driveStepper2AntiClockWise();
//   turnOnWaterPump();
//   driveStepper2AntiClockWise();    
//   driveStepper1();  // Clean left side of the shoe 
//   turnOnWaterPump();
//   driveStepper2AntiClockWise();  // Drive shoe holder 
//   driveStepper1();  // Clean top side of the shoe
//   turnOnWaterPump();
//   driveStepper2AntiClockWise();  // Drive shoe holder
//   driveStepper1();  // Clean right side of the shoe

   // Adjust this function to return the shoe to the start position
//   driveStepper2ClockWise();  // Drive shoe holder
   // polishing routine  
//   turnOnPump();     // Activate pump for black polish on right side
//   driveStepper2ClockWise();  // Drive shoe holder
//   driveStepper3();  // Polish right side of shoe
//  
//   turnOnPump();     // Activate pump for black polish on top side  
//   driveStepper2ClockWise();  // Drive shoe holder
//   driveStepper3();  // Polish top side of shoe
//
//   turnOnPump();     // Activate pump for black polish
//   driveStepper2ClockWise();  // Drive shoe holder
//   driveStepper3();  // Drive polish brush and return to start
//  
//   driveStepper2AntiClockWise();  // Drive shoe holder
//   driveStepper2AntiClockWise();  // Drive shoe holder

//   digitalWrite(buzzerRelayPin, HIGH); // Turn on buzzer to indicate end of cycle
//   delay(2000); // Buzzer on for 2 seconds
//   digitalWrite(buzzerRelayPin, LOW); // Turn on buzzer to indicate end of cycle
//   delay(2000);
}
