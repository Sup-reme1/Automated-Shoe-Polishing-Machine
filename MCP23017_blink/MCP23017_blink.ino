//#include <Adafruit_SPIDevice.h>
//#include <Adafruit_I2CRegister.h>
//#include <Adafruit_I2CDevice.h>
//#include <Adafruit_GenericDevice.h>
#include <Adafruit_BusIO_Register.h>

#include <Adafruit_MCP23XXX.h>
#include <Adafruit_MCP23X17.h>
#include <Adafruit_MCP23X08.h>

// Blinks an LED attached to a MCP23XXX pin.


#define A_0 0
#define B_0 8
#define A_3 4
#define B_3 11
// MCP23XXX pin LED is attached to

// only used for SPI
//#define CS_PIN 6

// uncomment appropriate line
//Adafruit_MCP23X08 mcp;
Adafruit_MCP23X17 mcp;

void setup() {
  Serial.begin(9600);
  //while (!Serial);
  Serial.println("MCP23xxx Blink Test!");

  // uncomment appropriate mcp.begin
//  if (!mcp.begin_I2C()) {
//  //if (!mcp.begin_SPI(CS_PIN)) {
//    Serial.println("Error.");
//    while (1);
//  }

  mcp.begin_I2C();

  // configure pin for output
  mcp.pinMode(A_0, OUTPUT);
  mcp.pinMode(B_0, OUTPUT);
  mcp.pinMode(A_3, OUTPUT);
  mcp.pinMode(B_3, OUTPUT);


  Serial.println("Looping...");
}

void loop() {
  mcp.digitalWrite(A_0, HIGH);
  delay(1000);
  mcp.digitalWrite(B_0, HIGH);
  delay(1000);
  mcp.digitalWrite(A_3, HIGH);
  delay(1000);
  mcp.digitalWrite(B_3, HIGH);
  delay(1000);
  mcp.digitalWrite(A_0, LOW);
  delay(1000);
  mcp.digitalWrite(B_0, LOW);
  delay(1000);
  mcp.digitalWrite(A_3, LOW);
  mcp.digitalWrite(B_3, LOW);
}
