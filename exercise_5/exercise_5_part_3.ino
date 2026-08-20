// The buzzer to arduino pin 13.
const int buzzerPin = 13;
// The switch that sets the alert on/off to arduino pin 4.
const int switchPin = 4;
// The potentiometer to arduino pin A0.
const int potentioMeterPin = A0;
// The PIR-sensor to arduino pin 3.
const int pirSensorPin = 3;

// Store the state of the alert on the variable alertOn.
boolean alertOn = false;

// The RGB pins that define the colors used.
int rgbPins[3] = { 11, 10, 9 };

void setup()
{
  Serial.begin(9600);
  // Set the buzzer as an output.
  pinMode(buzzerPin, OUTPUT);
  // Set the switch as an input pullup.
  pinMode(switchPin, INPUT_PULLUP);
  // Set the potentiometer as an input.
  pinMode(potentioMeterPin, INPUT);
  // Set the PIR-sensor as an input.
  pinMode(pirSensorPin, INPUT);

  // Set the RGB pins to be output.
  pinMode(rgbPins[0], OUTPUT);
  pinMode(rgbPins[1], OUTPUT);
  pinMode(rgbPins[2], OUTPUT);
}

void loop()
{
  int switchState = digitalRead(switchPin);
  int pirMotion = digitalRead(pirSensorPin);

  // If the PIR-sensor detects any
  // motion, trigger the alert.
  delay(500);
  if (pirMotion)
  {
    alertOn = true;
  }
  
  // Once alert is triggered.
  if (alertOn)
  {
    animColors();
    // If switch is closed (LOW), turn on piezo tone
    if (switchState == LOW) {
      // Tone value is defined by the potentiometer.
      int toneVal = analogRead(potentioMeterPin) * 4;
      setAlarm(buzzerPin, toneVal, 200);
    } else {
      // If switch is open (HIGH), turn off piezo
      noTone(buzzerPin);
      alertOn = false;
    }
  }
}

// Centralize the alarm values, delay, tone and pin
// to play sound in a specified interval.
void setAlarm(int pinVal, int toneVal, int delayVal)
{
  tone(pinVal, toneVal);
  delay(delayVal);
  noTone(pinVal);
  delay(delayVal);
}

// Animate the RGB led with 50ms of delay with each color.
void animColors()
{
  // Red color.
  setRgbColor(255, 0, 0);
  delay(50);
  // Green color.
  setRgbColor(0,  255, 0);
  delay(50);
  // Blue color.
  setRgbColor(0, 0, 255); // Blue Color
  delay(50);
}

// Sets the 3-dimensional RGB color for the RGB led.
void setRgbColor(int redVal, int greenVal, int bluVal)
{
  analogWrite(rgbPins[0], redVal);
  analogWrite(rgbPins[1], greenVal);
  analogWrite(rgbPins[2], bluVal);
}