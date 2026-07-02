// C++ code
//

int animSpeed = 0;
int pins[3] = {13, 12, 11};

void setup()
{
  // CPP function for setting the animation speed.
  setAnimSpeed(300);
  pinMode(pins[0], OUTPUT);
  pinMode(pins[1], OUTPUT);
  pinMode(pins[2], OUTPUT);
}

void loop()
{
  // Hardcoded pin that begins the sequence.
  int pin = pins[0];

  // Randomly pick one of the pins for the sequence.
  // TODO: For more dynamic sequence, keep this pin, but commented.
  // int pin = pins[rand() % 3];

  blinkAnim(pin, 3);
}

/**
 * Blinking sequence for pins.
 *
 * First, blinks set times the set pin.
 * After, all the pins are going to blink.
 *
 * @param pin The pin that is set to blink for set times.
 * @param times The times the set pin is going to blink.
 */
void blinkAnim(int pin, int times)
{
  for (int index = 0; index < times; index++)
  {
    digitalWrite(pin, HIGH);
    delay(animSpeed);
    digitalWrite(pin, LOW);
    delay(animSpeed);
  }
  // All pins blink.
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  // Wait for the set millisecond(s)
  delay(animSpeed);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  // Wait for the set millisecond(s)
  delay(animSpeed);
}

/**
 * Setter function, sets the animSpeed.
 *
 * @param speed The animation delay speed.
 */
void setAnimSpeed(int speed)
{
  animSpeed = speed;
}