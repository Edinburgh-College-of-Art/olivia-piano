/*
   Olivia Piano
*/
#include <Bounce2.h>
//------------------------------------------------------
// Control Pins
//------------------------------------------------------
// Buttons
const uint8_t buttonCount = 2;
const uint8_t yellowButton = 2;
const uint8_t blueButton = 4;
const uint8_t buttons[buttonCount] = {yellowButton, blueButton};
//------------------------------------------------------
// Pots
const uint8_t potCount = 4;
const uint8_t leftPot = A0;
const uint8_t rightPot = A1;
const uint8_t slidePot = A2;
const uint8_t pressurePot = A3;
const uint8_t pots[potCount] = {leftPot, rightPot, slidePot, pressurePot};
//------------------------------------------------------
Bounce debouncer[buttonCount];
//------------------------------------------------------
// Output Pins
const uint8_t solenoidCount = 1;
const uint8_t solenoid[] = {3, 5, 6, 7, 8};
const uint8_t motorCount = 1;
const uint8_t dcMotor[] = {3, 5, 6, 9, 10, 11};
const uint8_t rackPinion  = 9;
//------------------------------------------------------
// Readings
bool buttonValue[buttonCount] = {false};
unsigned int potValue[buttonCount] = {0};
//------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  // input setup
  for (uint8_t i  = 0; i < buttonCount; ++i)
  {
    pinMode(buttons[i], INPUT_PULLUP);
    debouncer[i].attach(buttons[i]);
    debouncer[i].interval(5); // interval in ms
  }

  // output setup
  for (uint8_t i  = 0; i < motorCount; ++i)
  {
    pinMode(dcMotor[i], OUTPUT);
  }
}
//------------------------------------------------------
void loop()
{
  getInputValues();
  printInputValues();
  //----------------------------------------------------
  // what do the controls do?

  for (uint8_t i  = 0; i < motorCount; ++i)
  {
    uint8_t motorSpeed = map(potValue[0], 0, 1024, 0, 255);
    analogWrite(dcMotor[i], motorSpeed);
  }
  //----------------------------------------------------

}
//------------------------------------------------------
