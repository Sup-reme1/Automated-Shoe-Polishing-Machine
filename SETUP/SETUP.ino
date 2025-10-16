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

void initializeMotor(AccelStepper& stepper){
  stepper.setMaxSpeed(500.0);       // Max speed in steps/second
  stepper.setAcceleration(2000.0);   // Acceleration in steps/second/second

  // Set the initial position to 0
  stepper.setCurrentPosition(0);

  driveAndReturnNema17(stepper, 2000);
}

// pump control functions
void turnOnPump() {
  digitalWrite(pumpBlack, HIGH); // Turn on the pump
  Serial.println("pump running");
  delay(1000); 
  digitalWrite(pumpBlack, LOW); // Turn off the pump
  Serial.println("pump stopped");
}


void setup() {
  Serial.begin(9600);

//Initializing motor speed and position to zero
  initializeMotor(cleanBrush);
  initializeMotor(shoeHolder);
  initializeMotor(polishBrush);

  //pump setup
  pinMode(pumpBlack, OUTPUT);
  pinMode(pumpBrown, OUTPUT);

  turnOnPump();

}


void loop() {
// //clean routine
// driveAndReturnNema17(cleanBrush, 40000, 1); // Move clean brush motor 40000 steps and return to start
// delay(1000); // Wait for 1 second
//
// driveAndReturnNema17(shoeHolder, 75, 1); // Move shoe motor 75 steps and return to start
// delay(1000); // Wait for 1 second
//
// driveAndReturnNema17(cleanBrush, 40000); // Move clean brush motor 40000 steps and return to start
// delay(1000); // Wait for 1 second
//
// driveAndReturnNema17(shoeHolder, 75, 1); // Move shoe motor 75 steps and return to start
// delay(1000); // Wait for 1 second
//
// driveAndReturnNema17(cleanBrush, 40000); // Move clean brush motor 40000 steps and return to start
// delay(1000); // Wait for 1 second
//
//
// // return to original position of shoe holder
// driveAndReturnNema17(shoeHolder, 0, 1); // Move shoe motor back to the start positon
//
//
//// polishing routine
//// first wave of polish
// turnOnPump();// Activate pump for black polish
// delay(1000);
// driveAndReturnNema17(shoeHolder, 75, 1); // Move shoe motor 75 steps and return to start
// driveAndReturnNema17(polishBrush, 40000); // Move clean brush motor 2000 steps and return to start
// delay(1000);
//
//// second wave of polish
// turnOnPump(); // Activate pump for brown polish
// delay(1000);
// driveAndReturnNema17(shoeHolder, 75, 1); // Move shoe motor 75 steps and return to start
// driveAndReturnNema17(polishBrush, 40000); // Move clean brush motor 2000 steps and return to start
// delay(1000);
//
//// third wave of polish
// driveAndReturnNema17(shoeHolder, 75, 1);  //  Move shoe motor 75 steps and return to start
// turnOnPump(); // Activate pump for polish
// delay(1000);
// driveAndReturnNema17(shoeHolder, 75, 1); // Move shoe motor 75 steps and return to start
// driveAndReturnNema17(polishBrush, 40000); // Move clean brush motor 2000 steps and return to start
}
