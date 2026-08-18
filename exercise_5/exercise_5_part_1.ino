#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int switchPin = 6;
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
  lcd.begin(16, 2);
  pinMode(switchPin, INPUT);
  lcd.print("Consult the");
  lcd.setCursor(0, 1);
  lcd.print("crystal ball!");
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