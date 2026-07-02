// C++ code
//

int animSpeed = 0;
int pins[3] = {13, 12, 11};

void setup()
{
  // Open a serial port.
  Serial.begin(9600);
  // CPP function for setting the animation speed.
  setAnimSpeed(2000);
  pinMode(pins[0], OUTPUT);
  pinMode(pins[1], OUTPUT);
  pinMode(pins[2], OUTPUT);
}

void loop()
{
  sequence();
}

/**
 * Blinking sequence for pins.
 */
void sequence()
{
  // Wait for the set millisecond(s).
  // Log that the leds are off.
  delay(animSpeed);
  Serial.println("LED OFF");
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  // Wait for the set millisecond(s).
  // Log that the leds are on.
  delay(animSpeed);
  Serial.println("LED ON");
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
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