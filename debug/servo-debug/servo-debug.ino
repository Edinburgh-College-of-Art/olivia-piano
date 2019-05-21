//------------------------------------------------------------------
#include <Servo.h>
//------------------------------------------------------------------
Servo myservo;
const uint8_t servoPin = 9;
unsigned int servoSpeed = 0;
const float servoRpm = 46;
const int targetAngle = 90;
int currentAngle = 0;
const float degreesPerSecond = (1000.f * 60.f) / (360.f*servoRpm);
unsigned long previousAngleTime = 0;
unsigned long rotationTime = (degreesPerSecond * (float)targetAngle)/1000.f;
unsigned int servoUpdateTime = 50;
unsigned long previousServoTime = 0;
bool state = false;
//------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  myservo.attach(servoPin);
  myservo.write(879);
}
//------------------------------------------------------------------
void loop()
{
  (currentAngle >= targetAngle) ? myservo.write(90) : myservo.write(servoSpeed);
  if (millis() - previousAngleTime > rotationTime)
  {
    currentAngle++;
    previousAngleTime = millis();
  }

  
  //  myservo.write(servoSpeed);
  //  delay(rotationTime);
  //  myservo.write(90);
  //  delay(rotationTime);

  //  myservo.writeMicroseconds();
  //  delay(rotationTime);
  //  myservo.write(90);
  //  delay(rotationTime);

  //  while (servoPos <= 180)
  //  {
  //    unsigned long now = millis();
  //    if (now - previousServoTime > servoUpdateTime)
  //    {
  //      state = !state;
  //      Serial.println(servoPos);
  //      (state)? myservo.write(servoPos) : myservo.write(0);
  //      previousServoTime = now;
  //    }
  //  }
  //  servoPos = 0;
  //  while (servoPos >= 0)
  //  {
  //    unsigned long now = millis();
  //    if (now - previousServoTime > servoUpdateTime)
  //    {
  //      myservo.write(servoPos--);
  //      previousServoTime = now;
  //    }
  //  }
}
//------------------------------------------------------------------
