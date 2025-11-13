// Add the library with motor functions
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

void screen() {
      String scrollMessage = "Shoe Polishing Machine";
      int displayWidth = 16; 

      // Print the scrolling message to the second row
      lcd.setCursor(0, 0);
      lcd.print(scrollMessage);

      // Scroll the message to the left
      for (int i = 0; i < scrollMessage.length() - displayWidth + 1; i++) {
        lcd.scrollDisplayLeft();
        delay(250); // Adjust delay for scrolling speed
      }

     // scroll the message back to the right
      for (int i = 0; i < scrollMessage.length() - displayWidth + 1; i++) {
        lcd.scrollDisplayRight();
        delay(250); // Adjust delay for scrolling speed
      }

      // Clear the second row to prepare for the next scroll
      lcd.setCursor(0, 0);
      for (int i = 0; i < displayWidth; i++) {
        lcd.print(" ");
      }
      delay(1000); // Pause before repeating the scroll
};


void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();  
  lcd.clear();
  screen();

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
  screen();
  
  if (digitalRead(BpolishButtonPin) == LOW){
    Serial.println("Black polish Btn Pressed");
  } 
  else if (digitalRead(BrpolishButtonPin) == LOW){
    Serial.println("Brown polish Btn Pressed");
  }
  else if (digitalRead(stopButtonPin) == LOW){
    Serial.println("Stop Btn Pressed");
    delay(5000);
  } 


//  driveStepper2ClockWise();
//  delay(2000);
//  driveStepper2ClockWise();
//  delay(2000);
//  driveStepper2ClockWise();
//  delay(2000);
//  driveStepper2ClockWise();
//  delay(2000);
//  driveStepper2AntiClockWise();
//  delay(2000);
//  driveStepper2AntiClockWise();
//  delay(2000);
//  driveStepper2AntiClockWise();
//  delay(2000);
//  driveStepper2AntiClockWise();
//  delay(2000);
  

//  Engine Starts Here
  //clean routine
  // Move stepper 1 forward 
  driveStepper1();  // Clean left side of the shoe 
  turnOnWaterPump();
  driveStepper2AntiClockWise();  // Drive shoe holder 
  turnOnWaterPump();
  driveStepper1();  // Clean top side of the shoe
  turnOnWaterPump();
  driveStepper2AntiClockWise();  // Drive shoe holder
  driveStepper1();  // Clean right side of the shoe

  // Adjust this function to return the shoe to the start position
  driveStepper2ClockWise();  // Drive shoe holder
  // polishing routine  
  turnOnPump();     // Activate pump for black polish on right side
  driveStepper2ClockWise();  // Drive shoe holder
  driveStepper3();  // Polish right side of shoe
  
  turnOnPump();     // Activate pump for black polish on top side  
  driveStepper2ClockWise();  // Drive shoe holder
  driveStepper3();  // Polish top side of shoe

  turnOnPump();     // Activate pump for black polish
  driveStepper2ClockWise();  // Drive shoe holder
  driveStepper3();  // Drive polish brush and return to start
  
  driveStepper2AntiClockWise();  // Drive shoe holder
  driveStepper2AntiClockWise();  // Drive shoe holder

  digitalWrite(buzzerRelayPin, HIGH); // Turn on buzzer to indicate end of cycle
  delay(2000); // Buzzer on for 2 seconds
  digitalWrite(buzzerRelayPin, LOW); // Turn on buzzer to indicate end of cycle
  delay(2000);
}
