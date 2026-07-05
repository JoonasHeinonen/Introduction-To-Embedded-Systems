// C++ code
//

int index = 1;

void setup()
{
  // Opens a serial port.
  Serial.begin(9600);
  // Set the led, pin 12 to output mode.
  pinMode(12,OUTPUT);
  // Set the TMP, pin A0, to input mode.
  pinMode(A0, INPUT);
  
  // Using the interrupt function to increase the index.
  attachInterrupt(
    digitalPinToInterrupt(3),
    incIndex,
    CHANGE
  );

  // Using the interrupt function to increase the index.
  attachInterrupt(
    digitalPinToInterrupt(2),
    heatValue,
    CHANGE
  );
}

void loop()
{
  // The variable to read the value from pin 3.
  int switchState = digitalRead(3);

  // If the button is not pressed, the led is off.
  if (switchState == HIGH)
  {
    digitalWrite(12, LOW);
  }
}

void incIndex()
{
  Serial.print("Counter: ");
  Serial.println(index);
  index += 1;
  digitalWrite(12, HIGH);
}

/**
 * Print the heatvalue from the TMP component.
 */
void heatValue()
{
  float sum = 0.0f;

  for (int i = 0; i < 50; i++)
  {
    sum += analogRead(A0);
    delay(20);
  }

  float avgADC = sum / 50.0f;
  float lt = ((5 * avgADC / 1024.0) - 0.5) * 100;

  Serial.print("ADC: ");
  Serial.print(avgADC);

  Serial.print(" lt: ");
  Serial.println(lt);
}