// Add the library with motor functions
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_MCP23XXX.h>
#include <Adafruit_MCP23X17.h>
//#include <Adafruit_MCP23X08.h>

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

void screen(String scrollMessage, int ticker = 0);
///////////////
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

  changePolishBrush(1);
}

void loop() { 
  screen("Polish default to Color Black");
  screen("Press the BLACK btn for Color Brown or Press the RED btn to start polishing");

  int blackButtonState = digitalRead(BpolishButtonPin);
  int brownButtonState = digitalRead(BrpolishButtonPin);
  int start = digitalRead(startButtonPin);
  delay(500);
  
  if (brownButtonState == LOW){
    screen("Brown Polish Selected");
    fixScreen("Changing brush face");
    changePolishBrush(1);
    screen("Press the RED btn to start polishing");
  } 
  else if (start == LOW){ // Btn to engage polish sequence
    fixScreen("Polishing");
    delay(500);
    // Engine Starts Here

  //  cleanShoe();
    polishShoe();
    alertUser();
  } 
  

}
