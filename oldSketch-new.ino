// Add the library with motor functions
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_MCP23XXX.h>
#include <Adafruit_MCP23X17.h>


// Set the LCD address to 0x27 for a 16 chars and 2 line display
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

int preDefinedDistance = 235;

// Define the pins for your components
const int startButtonPin = 2; // Pin for the start button
const int BpolishButtonPin = 3; // Pin for the button to select polish
const int BrpolishButtonPin = 4; // Pin for the button to select polish

const int doorSensorPin ;  // Digital pin for the magnetic reed switch
const int shoeSensorPin ;  // Digital pin for the IR proximity sensor

const int buzzerRelayPin = 5; // Analog pin 1 - Pin to control the buzzer relay
const int pump1RelayPin = 6; // Pin to control the pump1 water relay
const int pump2RelayPin = 7; // Pin to control the pump2 relay



// Define system states
enum SystemState {
  ENTER_COLOR,
  START,
  // Add other states as needed
};


SystemState currentState = ENTER_COLOR;

//  SETUP
void setup() {
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
  delayMicroseconds(STEP_DELAY);

  //Initializing Stepper motor 
  initializeMotor();

  pinMode(pump1RelayPin, OUTPUT);
  pinMode(pump2RelayPin, OUTPUT);
  digitalWrite(pump1RelayPin, HIGH);
  digitalWrite(pump2RelayPin, LOW);  

  // Set up  pins as inputs or outputs
  pinMode(startButtonPin, INPUT_PULLUP);
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

};

//  LOOP
void loop() {
  switch (currentState) {
    case ENTER_COLOR:
      // Wait for a button press to select color
      int blackButtonState = digitalRead(BpolishButtonPin);
      int brownButtonState = digitalRead(BrpolishButtonPin);
      
      if (brownButtonState == LOW){
        currentState = START;
        screen("Brown Polish Selected");
        fixScreen("Changing brush face");
        changePolishBrush(1);
        screen("Press the RED btn to start polishing");
      } 
      break;


    case START: // Always check for e-stop in polishing loop
      int start = digitalRead(startButtonPin);
      if (start == LOW) {
        lcd.print("Polishing in progress");
        delay(200);
        // Engine Starts Here
        cleanShoe(); 
        polishShoe();
        alertUser();
        currentState = CHECKING_LEVELS; // Reset to the start of the flow
      break;
  }
}
