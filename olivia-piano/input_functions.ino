//------------------------------------------------------
void getInputValues()
{
  for (uint8_t i  = 0; i < buttonCount; ++i)
  {
    debouncer[i].update();
    buttonPressed[i] = bool(debouncer[i].read()) ? false : true;
  }

  for (uint8_t i  = 0; i < potCount; ++i)
  {
    potValue[i] = analogRead(pots[i]);
  }
}

//------------------------------------------------------

void printInputValues()
{
  Serial.println("Buttons: ");
  for (uint8_t i  = 0; i < buttonCount; ++i)
  {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(buttonPressed[i]);
  }
  Serial.println("Pots: ");
  for (uint8_t i  = 0; i < potCount; ++i)
  {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(potValue[i]);
  }
}
//------------------------------------------------------
