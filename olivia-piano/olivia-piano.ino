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
#include <Servo.h>
#include <EEPROM.h>
//------------------------------------------------------------------
const bool DEBUG_MODE = true;
//------------------------------------------------------------------
// Control Pins
//------------------------------------------------------------------

// Buttons
const uint8_t buttonCount = 2;
const uint8_t yellowButton = 2;
const uint8_t blueButton = 4;
const uint8_t buttons[buttonCount] = {yellowButton, blueButton};
Bounce debouncer[buttonCount];
//------------------------------------------------------------------
// Pots
const uint8_t potCount = 4;
const uint8_t leftPotPin = A0;
const uint8_t rightPotPin = A1;
const uint8_t slidePotPin = A2;
const uint8_t pressurePotPin = A3;
const uint8_t pots[potCount] = {leftPotPin, rightPotPin, slidePotPin, pressurePotPin};

//------------------------------------------------------------------
// pot array position
const uint8_t leftPot     = 0;
const uint8_t rightPot    = 1;
const uint8_t slidePot    = 2;
const uint8_t pressurePot = 3;
const uint8_t rapidSolenoidPot = leftPot;
//------------------------------------------------------------------
// Output Pins
const uint8_t solenoidCount = 2;
const uint8_t solenoid[solenoidCount] = {8, 7};
const uint8_t rapidSolenoid = 6;
const uint8_t motorCount = 1;
const uint8_t dcMotor[motorCount] = {3};
//------------------------------------------------------------------
// Readings
bool buttonPressed[buttonCount] = {false};
bool buttonHeld[buttonCount] = {false};
unsigned int potValue[potCount] = {0u};
//------------------------------------------------------------------
// Timers and switches
unsigned long buttonOnTime[buttonCount] = {0};
unsigned int solenoidFireTime[solenoidCount] = {15};
unsigned int rapidSolenoidSpeed = 15;
unsigned int rapidSolenoidTimer = 0;
bool rapidSolenoidOn = false;
//------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  //------------------------------------------------------------------
  // input setup
  for (uint8_t i  = 0; i < buttonCount; ++i)
  {
    pinMode(buttons[i], INPUT_PULLUP);
    debouncer[i].attach(buttons[i]);
    debouncer[i].interval(5); // interval in ms
  }
  //------------------------------------------------------------------
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
//------------------------------------------------------------------------------
void loop()
{
  //----------------------------------------------------
  getInputValues();
  //----------------------------------------------------
  const unsigned long now = millis();
  //----------------------------------------------------
  // Solenoid Buttons
  for (uint8_t i  = 0; i < solenoidCount; ++i)
  {
    if (!buttonHeld[i] && buttonPressed[i])
    {
      digitalWrite(solenoid[i] , HIGH);
      Serial.println("fire");
      buttonHeld[i] = true;
      buttonOnTime[i] = millis();
    }
    else if (!buttonPressed[i])
    {
      buttonHeld[i] = false;
    }
    if (now - buttonOnTime[i] > solenoidFireTime[i])
    {
      digitalWrite(solenoid[i] , LOW);
    }
  }
  //----------------------------------------------------
  // Rapid Solenoid Pot Control

  rapidSolenoidSpeed = map(analogRead(pots[rapidSolenoidPot]), 0, 1024, 100, 10);
  rapidSolenoidOn = (rapidSolenoidSpeed > 80) ? false : true;
  if (rapidSolenoidOn)
  {
    if (now - rapidSolenoidTimer > rapidSolenoidSpeed)
    {
      digitalWrite(rapidSolenoid, !digitalRead(rapidSolenoid));
      rapidSolenoidTimer = now;
    }
  }
  else
  {
    digitalWrite(rapidSolenoid, LOW);
  }
  //----------------------------------------------------
  // Motor Pot Control
  uint8_t motorSpeed = map(potValue[rightPot], 0, 1024, 0, 255);
  analogWrite(dcMotor[0], motorSpeed);
  motorSpeed = map(potValue[pressurePot], 0, 1024, 0, 255);
  analogWrite(dcMotor[1], motorSpeed);
  //----------------------------------------------------
  // Servo Scraper
  // How many rotations in full movement of rack and pinion?
  // Save the position of the servo in EEPROM
  //----------------------------------------------------
  if (DEBUG_MODE)
  {
    printInputValues();
    delay(500);
  }
}
//------------------------------------------------------------------
