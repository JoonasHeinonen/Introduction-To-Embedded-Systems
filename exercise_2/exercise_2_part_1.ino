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
  digitalWrite(pins[0], HIGH);
  delay(animSpeed); // Wait for the set millisecond(s).
  digitalWrite(pins[0], LOW);
  delay(animSpeed); // Wait for the set millisecond(s).
  digitalWrite(pins[1], HIGH);
  delay(animSpeed); // Wait for the set millisecond(s).
  digitalWrite(pins[1], LOW);
  delay(animSpeed); // Wait for the set millisecond(s).
  digitalWrite(pins[2], HIGH);
  delay(animSpeed); // Wait for the set millisecond(s).
  digitalWrite(pins[2], LOW);
  delay(animSpeed); // Wait for the set millisecond(s).
  digitalWrite(pins[1], HIGH);
  delay(animSpeed); // Wait for the set millisecond(s).
  digitalWrite(pins[1], LOW);
  delay(animSpeed); // Wait for the set millisecond(s).
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