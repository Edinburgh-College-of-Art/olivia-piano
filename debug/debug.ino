
void setup()
{
  Serial.begin(9600);
  pinMode(4, INPUT);
  //  analogWrite(3, 200);
  digitalWrite(4, LOW);
}

void loop()
{
  //  for (uint8_t i  = 0; i < 255; ++i)
  //  {
  //    analogWrite(3, i);
  //    Serial.println(i);
  //    delay(100);
  //  }
}
