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
const uint8_t blueButton = 3;
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
const uint8_t solenoids[] = {4, 5, 6, 7, 8};
const uint8_t rackPinion  = 9;
//------------------------------------------------------
// Data
bool buttonValue[buttonCount] = {false};
unsigned int potValue[buttonCount] = {0};
//------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  for (uint8_t i  = 0; i < buttonCount; ++i)
  {
    pinMode(buttons[i], INPUT_PULLUP);
    debouncer[i].attach(buttons[i]);
    debouncer[i].interval(5); // interval in ms
  }
}
//------------------------------------------------------
void loop()
{
  getInputValues();
  printInputValues
  
  // what do the buttons do
}
//------------------------------------------------------
