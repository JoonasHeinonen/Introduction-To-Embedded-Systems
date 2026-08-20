#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 9, 8, 7, 6);

const int switchPin = 10;
int switchState = 0;
int prevSwitchState = 0;
int reply; // Variable to store the random reply.
// The replies are stored in an array of strings.
char *replies[] = {
  "Yes",
  "Probably",
  "Certainly",
  "Outlook good",
  "Unsure",
  "Ask again",
  "Doubtful",
  "No"
};

void setup() {
  // Set the TMP, pin A0, to input mode.
  pinMode(A0, INPUT);

  // Initialize the LCD and set the switch pin to input mode.
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT);
  lcd.print("Consult the");
  lcd.setCursor(0, 1);
  lcd.print("crystal ball!");

  // An interrupt function to call temperatureValue.
  attachInterrupt(
    digitalPinToInterrupt(2),
    temperatureValue,
    FALLING
  );
}

void loop() {
  switchState = digitalRead(switchPin);
  if (switchState != prevSwitchState) {
    if (switchState == LOW) {
      reply = random(sizeof(replies));
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("The ball says:");
      lcd.setCursor(0, 1);
      lcd.print(replies[reply]);
    }
  }
  prevSwitchState = switchState;
}

// Prints the temperature value on the LCD screen.
void temperatureValue()
{
  // AGC takes the analog value from the TMP sensor.
  // LT is the conversion of the analog value to a 
  // temperature value in Celsius.
  int agc = analogRead(A0);
  float lt = ((5 * agc / 1024.0) - 0.5) * 100;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature now:");
  lcd.setCursor(0, 1);
  lcd.print(lt);
}