const int w_led = 12, y_led = 11, touch_pin = 13;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int last_state = HIGH;
int curr_state;
int led_state = LOW;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello!");
  lcd.setCursor(0,1);
  lcd.print("Love you moe:3");
  delay(2500);
  lcd.clear();
  pinMode(w_led, OUTPUT);
  pinMode(y_led, OUTPUT);
  pinMode(touch_pin, INPUT);

  lcd.setCursor(0,0);
  lcd.print("LED: ");
  lcd.setCursor(5,0);
  if (led_state == LOW) lcd.print("OFF");
  else lcd.print("ON");
}

void loop() {
  // put your main code here, to run repeatedly:
  curr_state = digitalRead(touch_pin);
  if (curr_state == HIGH) {
    lcd.setCursor(0,1);
    lcd.print("Touching...    ");
    lcd.setCursor(5, 0);
    digitalWrite(y_led, HIGH);
    if (last_state == LOW) {
      led_state = !led_state;
      digitalWrite(w_led, led_state);
      if (led_state == LOW) lcd.print("OFF");
      else lcd.print("ON ");
    }
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("No touching...");
    digitalWrite(y_led, LOW);
  }
  last_state = curr_state;
  delay(50);
}
