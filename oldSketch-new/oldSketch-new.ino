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

int dirpin2 = 10;
int steppin2 = 11;

int dirpin3 = 12;
int steppin3 = 13;

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
  DEFAULT_MODE,
  ENTER_COLOR,
  START,
  // Add other states as needed
};

// Define shoe types
enum ShoeType {
  RIGHT_SHOE,
  LEFT_SHOE,
  // Add other states as needed
};

bool shoeColor = 0; // 0 represent Black and 1 represent Brown
  
SystemState currentState = DEFAULT_MODE;
ShoeType shoeType = RIGHT_SHOE;

void screen(String scrollMessage, int ticker = 0);

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

  Serial.begin(9600);
};

//  LOOP
void loop() {
//  driveStepper2ClockWise();
//  driveStepper3();
  
  Serial.println(shoeType);
  switch (currentState) {
    case DEFAULT_MODE:
      screen("Enter Polish Color");
      currentState = ENTER_COLOR;
    break;
    case ENTER_COLOR:
      // Wait for a button press to select color
      int blackButtonState = digitalRead(BpolishButtonPin);
      int brownButtonState = digitalRead(BrpolishButtonPin);
      
      if (brownButtonState == LOW){
        currentState = START;
        shoeColor = 1;
        screen("Brown Polish Selected");
        screen("Changing brush face");
        changePolishBrush(1);
        screen("Press the RED btn to start polishing");
      } 
      break;

    case START:
              
        switch(shoeType){
          case RIGHT_SHOE:
            int start = digitalRead(startButtonPin);
            Serial.println(start);
            if (start == LOW) {
              Serial.println("Right shoe block");
              shoeType = LEFT_SHOE; 
              screen("Polishing in progress");
              delay(200);

              cleanShoe(); 
              polishShoe();
              alertUser();
              // Inform user to enter second foot and hit the START btn
              screen("Insert Second Shoe and Press the RED button");
            }
          break; 
          case LEFT_SHOE:
            start = digitalRead(startButtonPin);
            Serial.println(start);
            if (start == HIGH) {
              shoeType = RIGHT_SHOE; 
              screen("Polishing in progress");
              delay(200);

              cleanShoe(); 
              polishShoe();
              alertUser();
            }
            // Inform user to enter second foot and hit the START btn
            fixScreen("Remove Shoe");
            delay(5000);

            currentState = DEFAULT_MODE; // Reset to the start of the flow
            if (shoeColor == 1){    // Reset brush to black if shoe color is brown
              changePolishBrush(1);
            }
          break; 
        }
      break;
 
  }
//  screen("down the loop");
}
