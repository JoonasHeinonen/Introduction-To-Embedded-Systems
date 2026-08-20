// C++ code
//
#include <EEPROM.h>

int counter = 0;

void setup()
{
  // Opens a serial port.
  Serial.begin(9600);

  pinMode(12, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(4, INPUT);

  // Attach interrupt 2.
  attachInterrupt(
    digitalPinToInterrupt(2),
    emptyMemory,
    FALLING
  );
  
  // Attach interrupt 3.
  attachInterrupt(
    digitalPinToInterrupt(3),
    printMemoryValue,
    FALLING
  );
}

void loop()
{
  // The variable to read the value from pin 4.
  int switchStateFour = digitalRead(4);

  // If the button is not pressed, the led is off.
  if (switchStateFour == LOW)
  {
    EEPROM.write(counter - 1, counter);

    Serial.print("Writing ");
    Serial.print(counter + 1);
    Serial.print(" to address ");
    Serial.println(counter);

    counter++;

    delayButtonPress(4);
  }
}

void delayButtonPress(int pin)
{
  delay(200);

  while (digitalRead(pin) == LOW)
  {
    // Wait until the button is released.
  }

  delay(50);
}

void emptyMemory()
{
  Serial.println("Emptying the memory...");

  for (int i = 0; i < EEPROM.length(); i++)
  {
    EEPROM.update(i, 0);
  }

  counter = 0;
}

void printMemoryValue()
{
  for (int i = 0; i < EEPROM.length(); i++)
  {
    int value = EEPROM.read(i);

    if (value != 0)
    {
      Serial.println(value);
    }
  }
}