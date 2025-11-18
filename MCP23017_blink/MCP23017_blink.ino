#include <Adafruit_BusIO_Register.h>
#include <Adafruit_MCP23XXX.h>
#include <Adafruit_MCP23X17.h>
#include <Adafruit_MCP23X08.h>

// pulse pins on the ULN driver.
#define A_0 0
#define A_1 1
#define A_2 2
#define A_3 3

//create an instance
Adafruit_MCP23X17 mcp;

void setup() {
  Serial.begin(9600);
  Serial.println("MCP23xxx Drive Test!");

  //starts mcp in I2C mode
  mcp.begin_I2C();

  // configure pin for output
  mcp.pinMode(A_0, OUTPUT);
  mcp.pinMode(A_1, OUTPUT);
  mcp.pinMode(A_2, OUTPUT);
  mcp.pinMode(A_3, OUTPUT);
}

void loop() {
// pass
  mcp.digitalWrite(A_0, HIGH);
  delay(500);
  mcp.digitalWrite(A_0, LOW);
  mcp.digitalWrite(A_1, HIGH);  
  delay(500);
  mcp.digitalWrite(A_1, LOW);
  mcp.digitalWrite(A_2, HIGH);
  delay(500);
}
