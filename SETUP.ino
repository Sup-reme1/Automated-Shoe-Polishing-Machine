#include <Adafruit_MCP23X08.h> 
#include <Adafruit_MCP23X17.h>
#include <Adafruit_MCP23XXX.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <AccelStepper.h>

//DEFINITION OF STEPPER MOTOR PINS
#define  nema1_DIR 8 // Pin to control the NEMA 17
#define  nema1_STEP 9 // Pin to control the NEMA 17
#define  nema2_DIR 10 // Pin to control the NEMA 17
#define  nema2_STEP 11 // Pin to control the NEMA 17
#define  nema3_DIR 12 // Pin to control the NEMA 17
#define  nema3_STEP 13 // Pin to control the NEMA 17

//DEFINITION OF PUMP PINS
#define  pumpBlack 2 // Pin to control the Pump 1
#define  pumpBrown 3 // Pin to control the Pump 2 
//#define  pump3 1; // Pin to control the Pump 1



//steepper objects
AccelStepper cleanBrush(AccelStepper::DRIVER, nema1_STEP, nema1_DIR);
AccelStepper shoeHolder(AccelStepper::DRIVER, nema2_STEP, nema2_DIR);
AccelStepper polishBrush(AccelStepper::DRIVER, nema3_STEP, nema3_DIR);


//function to drive motors 
void driveAndReturnNema17(AccelStepper& stepper, long distance, int returnMotor = 0) {
    //steppers setup
  stepper.setMaxSpeed(4000.0);       // Max speed in steps/second
  stepper.setAcceleration(2000.0);   // Acceleration in steps/second/second

  
  // Set the target position.
  stepper.moveTo(distance);

  // Run the motor until the target position is reached.
  while (stepper.currentPosition() != distance) {
    stepper.run();
  }

  if ( returnMotor == 0 ){
    // Return the motor to its starting position (0).
    stepper.moveTo(0);  
    // Run the motor until the starting position is reached.
    while (stepper.currentPosition() != 0) {
      stepper.run();
    }
  }
} 


// pump control functions
void turnOnPumpBlack() {
  digitalWrite(pumpBlack, HIGH); // Turn on the pump
  Serial.println("pump running");
  delay(2000); 
  digitalWrite(pumpBlack, LOW); // Turn off the pump
  Serial.println("pump stopped");
}


void setup() {
  Serial.begin(9600);
   //set initial position to zero
//  cleanBrush.setCurrentPosition(0);
//  shoeHolder.setCurrentPosition(0);
//  polishBrush.setCurrentPosition(0);
  
  //pump setup
  pinMode(pumpBlack, OUTPUT);
  digitalWrite(pumpBlack, HIGH);
  digitalWrite(pumpBlack, LOW);
  pinMode(pumpBrown, OUTPUT);
  digitalWrite(pumpBrown, HIGH);
  digitalWrite(pumpBrown, LOW);

  digitalWrite(pumpBlack, LOW); // Turn off pump initially
  digitalWrite(pumpBrown, LOW); // Turn off pump initially

}


void loop() {
  turnOnPumpBlack();
}
//  //clean routine
//  driveAndReturnNema17(cleanBrush, 60000); // Move clean brush motor 2000 steps and return to start
//  delay(1000); // Wait for 1 second
//
//  driveAndReturnNema17(shoeHolder, 2000); // Move clean brush motor 2000 steps and return to start
//  delay(1000); // Wait for 1 second
//
//  driveAndReturnNema17(cleanBrush, 60000); // Move clean brush motor 2000 steps and return to start
//  delay(1000); // Wait for 1 second
//
//  driveAndReturnNema17(shoeHolder, 2000); // Move clean brush motor 2000 steps and return to start
//  delay(1000); // Wait for 1 second
//
//  driveAndReturnNema17(cleanBrush, 60000); // Move clean brush motor 2000 steps and return to start
//  delay(1000); // Wait for 1 second


//  // return to original position of shoe holder
//  driveAndReturnNema17(shoeHolder, 2000, 0); // Move clean brush motor 2000 steps and return to start
//  delay(1000); // Wait for 1 second
//
//
//// polishing routine
//// first wave of polish
//  turnOnPumpBlack();// Activate pump for black polish
//  delay(1000);
//  driveAndReturnNema17(polishBrush, 60000); // Move clean brush motor 2000 steps and return to start
//  delay(1000);
//  driveAndReturnNema17(shoeHolder, 2000); // Move clean brush motor 2000 steps and return to start
//  delay(1000); // Wait for 1 second
//
//// second wave of polish
//  turnOnPumpBlack(); // Activate pump for brown polish
//  delay(1000);
//  driveAndReturnNema17(polishBrush, 60000); // Move clean brush motor 2000 steps and return to start
//  delay(1000);
//  driveAndReturnNema17(shoeHolder, 2000); // Move clean brush motor 2000 steps and return to start
//  delay(1000); // Wait for 1 second
//
//// third wave of polish
//  turnOnPumpBlack(); // Activate pump for brown polish
//  delay(1000);
//  driveAndReturnNema17(polishBrush, 60000); // Move clean brush motor 2000 steps and return to start
//  delay(1000);
//  driveAndReturnNema17(shoeHolder, 2000, 0); // Move clean brush motor 2000 steps and return to start
//  delay(1000); // Wait for 1 second
//}
