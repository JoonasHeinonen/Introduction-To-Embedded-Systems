#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 9, 8, 7, 6);

const int switchPin = 10;
int switchState = 0;
int prevSwitchState = 0;
int reply;
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
  
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT);
  lcd.print("Consult the");
  lcd.setCursor(0, 1);
  lcd.print("crystal ball!");
  
  // Using the interrupt function.
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

void temperatureValue()
{
  int agc = analogRead(A0);
  float lt = ((5 * agc / 1024.0) - 0.5) * 100;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature now:");
  lcd.setCursor(0, 1);
  lcd.print(lt);
}