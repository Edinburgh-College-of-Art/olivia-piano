/*
   Olivia Piano

   Two push buttons:
      One: Solenoid fire once per push
      Two: Solenoid fire once per push

   Two Pots:
      One: Solenoid fire speed
      Two: DC Motor Speed
      
   Slider:
      Scraping

   Pressure:
      Motor Speed
*/
#include <Bounce2.h>
//------------------------------------------------------
const bool DEBUG_MODE = true;
//------------------------------------------------------
// Control Pins
//------------------------------------------------------
// Buttons
const uint8_t buttonCount = 2;
const uint8_t yellowButton = 2;
const uint8_t blueButton = 4;
const uint8_t buttons[buttonCount] = {yellowButton, blueButton};
Bounce debouncer[buttonCount];
//------------------------------------------------------
// Pots
const uint8_t potCount = 4;
const uint8_t leftPot = A0;
const uint8_t rightPot = A1;
const uint8_t slidePot = A2;
const uint8_t pressurePot = A3;
const uint8_t pots[potCount] = {leftPot, rightPot, slidePot, pressurePot};
//------------------------------------------------------
// Output Pins
const uint8_t solenoidCount = 2;
const uint8_t solenoid[solenoidCount] = {8, 7};
const uint8_t motorCount = 1;
const uint8_t dcMotor[motorCount] = {3};
//------------------------------------------------------
// Readings
bool buttonValue[buttonCount] = {false};
unsigned int potValue[potCount] = {0u};
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
  for (uint8_t i  = 0; i < solenoidCount; ++i)
  {
    pinMode(solenoid[i], OUTPUT);
  }
}
//------------------------------------------------------
bool buttonLock[buttonCount] = {false};

void loop()
{
  getInputValues();
  //----------------------------------------------------
  // what do the controls do?
  for (uint8_t i  = 0; i < solenoidCount; ++i)
  {
    if (buttonLock[buttonCount] && !buttonValue[i])
    {
      digitalWrite(solenoid[i] , HIGH);
      Serial.println("fire");
    }
    buttonLock[buttonCount] = !buttonValue[i] ? true : false;    
    delay(15);
    digitalWrite(solenoid[i] , LOW);
  }
  for (uint8_t i  = 0; i < motorCount; ++i)
  {
    uint8_t motorSpeed = map(potValue[i], 0, 1024, 0, 255);
    analogWrite(dcMotor[i], motorSpeed);
  }
  //----------------------------------------------------
  if (DEBUG_MODE)
  {
//    printInputValues();
    delay(500);
  }
}
//------------------------------------------------------
