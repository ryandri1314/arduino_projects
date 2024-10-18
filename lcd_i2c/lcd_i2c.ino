#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

byte radian[8] = {
  B00000,
  B00110,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000,  
  B00000
};

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.createChar(0, radian);
}
void loop() {
  lcd.setCursor(0, 0);
  lcd.print("30");
  lcd.print(char(0));
  lcd.print("C");
}