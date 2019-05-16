void setup()
{
//  TCCR2B = TCCR2B & B11111000 | B00000001; // for PWM frequency of 31372.55 Hz
//  TCCR2B = TCCR2B & B11111000 | B00000010; // for PWM frequency of 3921.16 Hz
//  TCCR2B = TCCR2B & B11111000 | B00000011; // for PWM frequency of 980.39 Hz
//  TCCR2B = TCCR2B & B11111000 | B00000100; // for PWM frequency of 490.20 Hz (The DEFAULT)
//  TCCR2B = TCCR2B & B11111000 | B00000101; // for PWM frequency of 245.10 Hz
//  TCCR2B = TCCR2B & B11111000 | B00000110; // for PWM frequency of 122.55 Hz
//  TCCR2B = TCCR2B & B11111000 | B00000111; // for PWM frequency of 30.64 Hz
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  //  analogWrite(3, 200);
  digitalWrite(7, LOW);
//  delay(100);
//  analogWrite(3, 55);
}

void loop()
{
  //    for (uint8_t i  = 0; i < 255; ++i)
  //    {
  //      analogWrite(3, i);
  //      Serial.println(i);
  //      delay(100);
  //    }
}
