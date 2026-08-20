// C++ code
//
#include <EEPROM.h>

int counter = 0;

void setup()
{
  // Opens a serial port.
  Serial.begin(9600);
  // Set the led, pin 12 to output mode.
  pinMode(12,OUTPUT);
  // Set the TMP, pin A0, to input mode.
  pinMode(A0, INPUT);
  // Set the button, pin 4, to input mode.
  pinMode(4, INPUT);
  
  // Using the interrupt function to print the value.
  attachInterrupt(
    digitalPinToInterrupt(3),
    printMemoryValue,
    CHANGE
  );

  // Using the interrupt function to empty the EEPROM memory.
  attachInterrupt(
    digitalPinToInterrupt(2),
    emptyMemory,
    CHANGE
  );
}

void loop()
{
  // The variable to read the value from pin 4.
  int switchState = digitalRead(4);

  // If the button is not pressed, the led is off.
  if (switchState == LOW)
  {
    EEPROM.write(counter, 123);

    Serial.print("Writing 123 to address ");
    Serial.println(counter);
    counter++;

    delay(200);

    while (digitalRead(4) == LOW)
    {
      // Wait until the button is released.
    }

    delay(50);
  }
}

void printMemoryValue()
{
  Serial.println("Printing memory value");
}

void emptyMemory()
{
  Serial.println("Emptying EEPROM memory");
}