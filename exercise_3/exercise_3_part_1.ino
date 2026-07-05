// C++ code
//

void setup()
{
  // Set the led, pin 12 to output mode.
  pinMode(12,OUTPUT);
  // Set the button, pin 3, to input mode.
  pinMode(3,INPUT);
}

void loop()
{
  // The variable to read the value from pin 3.
  int switchState = digitalRead(3);

  // If the button is not pressed, the led is off.
  if (switchState == LOW)
  {
    digitalWrite(12, HIGH);
  }
  else if (switchState == HIGH)
  {
    digitalWrite(12, LOW);
  }
}