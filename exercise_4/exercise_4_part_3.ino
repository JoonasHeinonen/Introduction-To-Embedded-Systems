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

  // Button 2: empty EEPROM
  attachInterrupt(
    digitalPinToInterrupt(2),
    emptyMemory,
    FALLING
  );

  // Button 1: print EEPROM contents
  attachInterrupt(
    digitalPinToInterrupt(3),
    printMemoryValue,
    FALLING
  );
}

void loop()
{
  /**
   * 1. Osa:
   * Käytännössä siis ohjelma pyörii loopissa niin kauan, että on kulunut 5s edellisestä mittauksesta, jonka
   * jälkeen siirrytään aliohjelmaan tallentamaan lämpötilaa. Tarvitset siis timerin, joka mittaa loopissa
   * aikaa ohjelman käynnistyksen alusta ja sen avulla osataan sitten siirtyä 5 sekunnin välein mittaavaan
   * aliohjelmaan.
   */
  // Check temperature every 5 seconds
  if (millis() - previousTime >= 5000)
  {
    previousTime = millis();
    checkTemperature();
  }
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

/**
 * 2. Osa:
 * Aliohjelmassa kirjoitat EEPROM-muistiin peräkkäisiin muistipaikkoihin ajankohdan ja ADC-arvon, mutta
 * vain jos ADC on eri kuin edellisessä mittauksessa (säilytä siis edellinen mitattu ADC-arvo muuttujassa ja
 * vertaa sitä uuteen arvoon).
 */
void checkTemperature()
{
  // Otetaan aika talteen ENNEN mittausta
  unsigned int seconds = millis() / 1000;

  // Mitataan ADC
  int currentADC = heatValue();

  // Tallennetaan ensimmäinen mittaus aina,
  // sen jälkeen vain jos ADC muuttui
  if (firstMeasurement || currentADC != previousADC)
  {
    // Jos EEPROM tulee täyteen, aloitetaan alusta
    if (memoryAddress + 4 > EEPROM.length())
    {
      memoryAddress = 0;
    }

    // Tallennetaan aika
    EEPROM.put(memoryAddress, seconds);

    // Tallennetaan ADC
    EEPROM.put(memoryAddress + 2, currentADC);

    // Seuraava mittaus alkaa seuraavasta 4 tavun kohdasta
    memoryAddress += 4;

    firstMeasurement = false;
  }

  // Nykyisestä arvosta tulee seuraavan mittauksen vertailuarvo
  previousADC = currentADC;
}

void printMemoryValue()
{
  Serial.println("EEPROM-muistin sisältö:");

  for (int i = 0; i < memoryAddress; i += 4)
  {
    unsigned int time;
    int adc;

    // Luetaan EEPROMista aika
    EEPROM.get(i, time);

    // Luetaan EEPROMista ADC
    EEPROM.get(i + 2, adc);

    // Lasketaan lämpötila
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