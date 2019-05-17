//------------------------------------------------------------------
#include <Servo.h>
//------------------------------------------------------------------
Servo myservo;
const uint8_t servoPin = 9;
int servoPos = 0;
unsigned int servoUpdateTime = 15;
unsigned long previousServoTime = 0;
//------------------------------------------------------------------
void setup()
{
  myservo.attach(servoPin);
}
//------------------------------------------------------------------
void loop()
{
  while (pos <= 360)
  {
    unsigned long now = millis();
    if (now - previousTime > servoUpdateTime)
    {
      myservo.write(pos++);
      previousTime = now;
    }
  }
  while (pos >= 0)
  {
    unsigned long now = millis();
    if (now - previousTime > servoUpdateTime)
    {
      myservo.write(pos--);
      previousTime = now;
    }
  }
}
//------------------------------------------------------------------
