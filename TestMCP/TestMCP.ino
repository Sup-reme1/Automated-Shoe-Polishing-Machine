#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the pins for your components
const int stopButtonPin = 3; // Pin for the start button
const int BpolishButtonPin = 4; // Pin for the button to select polish
const int BrpolishButtonPin = 5; // Pin for the button to select polish

const int doorSensorPin ;  // Digital pin for the magnetic reed switch
const int shoeSensorPin ;  // Digital pin for the IR proximity sensor

const int buzzerRelayPin = 6; // Analog pin 1 - Pin to control the buzzer relay
const int pump1RelayPin = 7; // Pin to control the pump2 relay
const int pump2RelayPin; // Pin to control the pump2 relay

//  4 - 7 pins is connected to Ultrasonic sensor
//  8 - 13 pins is connected to Ultrasonic sensor




/////////////////////////////////////////////////////////////////////
// Function ///////////// Function ////////////// Function //////////
/////////////////////////////////////////////////////////////////////
void sprayFluid(int pumpPin, int sprayTime = 2000){
  Serial.print("Turning on pump");
  Serial.println(pumpPin);
  digitalWrite(pumpPin, LOW);
  delay(sprayTime);
  digitalWrite(pumpPin, HIGH);
  Serial.print("Turning off pump");
  Serial.println(pumpPin);
  delay(sprayTime);
}

// Function to Dynamicaly display string if int is 1, the display has 2 rows
void lcdDisplay (String text, int row=0){
  lcd.clear();
  
  if (text.length() <= 16){ // if text lesser than 16
    lcd.setCursor(0, row);
    lcd.print(text);
  } else{ // if text greater than 16
    String line1 = text.substring(0,16);  // Display first 16 char
    lcd.setCursor(0, row);
    lcd.print(line1);

    String line2 = text.substring(16);
    lcd.setCursor(0, row + 1);
    lcd.print(line2);
  }
  delay(1000);
}



void setup() {
  Serial.begin(9600);
  Serial.println("Hello Supreme");
//  mcp.begin_I2C();

  lcdDisplay("Hello Supreme");
//  lcd.print("text");
  
  pinMode(pump1RelayPin, OUTPUT);
  pinMode(pump2RelayPin, OUTPUT);

// Set up  pins as inputs or outputs
  pinMode(stopButtonPin, INPUT_PULLUP);
  pinMode(BpolishButtonPin, INPUT_PULLUP);
  pinMode(BrpolishButtonPin, INPUT_PULLUP);
//  
  pinMode(doorSensorPin, INPUT);
//  mcp.pinMode(shoeSensorPinIR, INPUT);
  
  pinMode(buzzerRelayPin, OUTPUT);
  
  pinMode(pump1RelayPin, OUTPUT);
  pinMode(pump2RelayPin, OUTPUT);



//  Off the pumps
  digitalWrite(pump1RelayPin, HIGH);
  digitalWrite(pump2RelayPin, HIGH);  
  digitalWrite(buzzerRelayPin, LOW);  


//  Test buzzer
  Serial.println("testing buzzer");
  lcdDisplay("Checking Buzzer", 1);
  digitalWrite(buzzerRelayPin, HIGH);
  delay(1000);
  digitalWrite(buzzerRelayPin, LOW);

//  Test Pump
  Serial.println("testing PUMP");
  lcdDisplay("Checking Pump", 1);
  digitalWrite(pump1RelayPin, LOW);
  delay(1000);
  digitalWrite(pump1RelayPin, HIGH);

  Serial.println("Leaving setup and entering the loop");
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

 Serial.println("Restarting the loop");
}
