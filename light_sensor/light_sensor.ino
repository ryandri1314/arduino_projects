#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const short max_val = 10, g_led = 9, b_led = 10, y_led = 11;
short sensor_val, min_val;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello moemoe!");
  delay(5000);

  pinMode(g_led, OUTPUT);
  pinMode(b_led, OUTPUT);
  pinMode(y_led, OUTPUT);

  min_val = analogRead(A0);
}

void loop() {
  // put your main code here, to run repeatedly:
  int light_sensor = analogRead(A0);
  Serial.print(light_sensor);
  Serial.print("\n");
  lcd.setCursor(0,0);
  lcd.print("Value of sensor:");
  lcd.setCursor(0,1);
  lcd.print(light_sensor);
  lcd.print("  ");

  light_sensor = map(light_sensor, min_val, max_val, 0, 255);
  light_sensor = constrain(light_sensor, 0, 255);

  for (int i = g_led; i <= y_led; i++) {
    analogWrite(i, light_sensor);
    delay(10);
  }

  delay(50);
}
