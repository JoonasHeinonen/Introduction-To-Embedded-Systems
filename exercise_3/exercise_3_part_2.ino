// C++ code
//

int index = 1;
volatile byte state = LOW;

void setup()
{
  // Opens a serial port.
  Serial.begin(9600);
  // Set the led, pin 12 to output mode.
  pinMode(12,OUTPUT);
  // Set the button, pin 3, to input mode.
  pinMode(3,INPUT);
  
  // Using the interrupt function to increase the index.
  attachInterrupt(
    digitalPinToInterrupt(3),
    incIndex,
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

/**
 * Increment the index and toggle the LED state.
 */
void incIndex() {
  state = !state;
  Serial.print("Counter: ");
  Serial.println(index);
  index += 1;
  digitalWrite(12, HIGH);
}