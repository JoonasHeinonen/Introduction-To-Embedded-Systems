// C++ code
//
#include <EEPROM.h>

unsigned long previousTime;
int previousADC;
int memoryAddress;
bool firstMeasurement = true;

void setup()
{
  // Opens a serial port.
  Serial.begin(9600);

  pinMode(12, OUTPUT);
  pinMode(A0, INPUT);

  previousTime = 0;
  previousADC = analogRead(A0);
  memoryAddress = 0;

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
  // Check temperature every 5 seconds
  if (millis() - previousTime >= 5000)
  {
    previousTime = millis();
    checkTemperature();
  }
}

void checkTemperature()
{
  // Store the time before measuring.
  unsigned int seconds = millis() / 1000;

  // Measure the ADC.
  int currentADC = heatValue();

  // Record the first measurement always,
  // then if the ADC changed.
  if (firstMeasurement || currentADC != previousADC)
  {
    // If EEPROM gets full, start from begin.
    if (memoryAddress + 4 > EEPROM.length())
    {
      memoryAddress = 0;
    }

    // Record the time.
    EEPROM.put(memoryAddress, seconds);

    // Record the ADC.
    EEPROM.put(memoryAddress + 2, currentADC);

    // Next measurement begins starting by memory address 4.
    memoryAddress += 4;

    firstMeasurement = false;
  }

  previousADC = currentADC;
}

void printMemoryValue()
{
  Serial.println("EEPROM-memory content:");

  for (int i = 0; i < memoryAddress; i += 4)
  {
    unsigned int time;
    int adc;

    // Read the time from EEPROM.
    EEPROM.get(i, time);

    // Read the ADC from EEPROM.
    EEPROM.get(i + 2, adc);

    // Calculate the temperature.
    float lt = ((5 * adc / 1024.0) - 0.5) * 100;
    printVals(time, adc, lt);
  }
}

void emptyMemory()
{
  Serial.println("Emptying EEPROM...");

  // Write zero to every EEPROM address
  for (int i = 0; i < EEPROM.length(); i++)
  {
    EEPROM.update(i, 0);
  }

  // Start writing from the beginning again
  memoryAddress = 0;

  Serial.println("EEPROM is empty.");
}

int heatValue()
{
  float sum = 0.0f;

  // Take 50 measurements
  for (int i = 0; i < 50; i++)
  {
    sum += analogRead(A0);
    delay(20);
  }

  int avgADC = sum / 50.0f;

  return avgADC;
}

// Print saved values
void printVals(unsigned int time, int adc, float lt)
{
      // Print saved values
    Serial.print("Time: ");
    Serial.print(time);

    Serial.print("    ADC: ");
    Serial.print(adc);

    Serial.print("    LT: ");
    Serial.println(lt);
}