/*
   Olivia Piano

  | Input          | Output                 |
  | :------------- | :--------------------- |
  | Yellow Button  | Solenoid 1 Fire        |
  | Blue Button    | Solenoid 2 Fire        |
  | Left Pot       | Rapid Solenoid Speed   |
  | Right Pot      | Motor 1 Speed          |
  | Slide Pot      | Servo Scraper Position |
  | Force Resistor | Motor 2 Speed          |

*/
#include <Bounce2.h>
#include <Servo.h>
//------------------------------------------------------------------
const bool DEBUG_MODE = false;
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
const uint8_t solenoid[solenoidCount] = {7, 8};
const uint8_t rapidSolenoid = 6;
const uint8_t motorCount = 1;
const uint8_t dcMotor[motorCount] = {3};
//------------------------------------------------------------------
// Servo
Servo rackPinion;
const uint8_t servoPin = 9;
int rackPinionPos = 0;
unsigned int rackPinionUpdateTime = 15;
unsigned long previousRackPinionTime = 0;
bool rackPinionDir = false;
const unsigned int maxRackPinionPos = 360;
//------------------------------------------------------------------
// Readings
bool buttonPressed[buttonCount] = {false};
bool buttonHeld[buttonCount] = {false};
unsigned int potValue[potCount] = {0u};
//------------------------------------------------------------------
// Timers and switches
unsigned long buttonOnTime[buttonCount] = {0};
unsigned int solenoidFireTime[solenoidCount] = {15, 15};
unsigned int rapidSolenoidSpeed = 15;
unsigned int rapidSolenoidTimer = 0;
bool rapidSolenoidOn = true;
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
  pinMode(rapidSolenoid, OUTPUT);

  rackPinionPos = map(analogRead(pots[slidePot]), 0 , 1024, 0, maxRackPinionPos);
  rackPinion.write(rackPinionPos);
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
      //      Serial.println("fire");
      //      Serial.println(solenoid[i]);
      //      Serial.println(buttonHeld[i]);
      //      Serial.println(solenoidFireTime[i]);
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
  // Move to position based on slider
  rackPinionPos = map(analogRead(pots[slidePot]), 0 , 1024, 0, maxRackPinionPos);
  if (now - previousRackPinionTime > rackPinionUpdateTime)
  {
    rackPinion.write(rackPinionPos);
  }
  //----------------------------------------------------
  if (DEBUG_MODE)
  {
    printInputValues();
    delay(500);
  }
}
//------------------------------------------------------------------
