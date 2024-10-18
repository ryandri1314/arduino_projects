#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RT0 10000 
#define B 3977 
float a = A0;

const short btn_led_pin = 5, btn_motor_pin = 6, led_pin = 12, motor_pin = 13;
short btn_motor_last_state = HIGH, btn_led_last_state = HIGH;
short btn_motor_curr_state, btn_led_curr_state;
short motor_state = LOW, led_state = LOW;
short count = 0;

#define VCC 5
#define R 10000

float RT, VR, ln, Temp, T0, Read;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.print("Hello!");
  pinMode(a, INPUT);
  T0 = 25 + 273.15;
  delay(2000);
  lcd.clear();

  pinMode(motor_pin, OUTPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(btn_motor_pin, INPUT_PULLUP);
  pinMode(btn_led_pin, INPUT_PULLUP);

  float curr_temp = set_temp();
  print_temp(curr_temp);
}

void set_motor_by_btn() {
  btn_motor_curr_state = digitalRead(btn_motor_pin);
  if (btn_motor_curr_state == LOW && btn_motor_last_state == HIGH) {
    motor_state = !motor_state;
    digitalWrite(motor_pin, motor_state);
  }
  btn_motor_last_state = btn_motor_curr_state;
}

void set_led_by_btn() {
  btn_led_curr_state = digitalRead(btn_led_pin);
  if (btn_led_curr_state == LOW && btn_led_last_state == HIGH) {
    led_state = !led_state;
    digitalWrite(led_pin, led_state);
  }
  btn_led_last_state = btn_led_curr_state;
}

void print_temp(float Temp) {
  lcd.setCursor(0,0);
  lcd.print("Temperature: ");
  lcd.setCursor(0,1);
  lcd.print(Temp);
}

float set_temp() {
  Read = analogRead(a);
  Read = (5.00 / 1023.00) * Read;
  VR = VCC - Read;
  RT = Read / (VR / R);

  ln = log(RT / RT0);
  Temp = (1 / ((ln / B) + (1 / T0)));
  Temp = Temp - 273.15;
  return Temp;
}

void control_devices_by_temp(float Temp) {
  if (Temp >= 33.00 && motor_state == LOW) {
    motor_state = HIGH;
    digitalWrite(motor_pin, motor_state);
  }
  else if (Temp <= 20.00 && led_state == LOW) {
    led_state = HIGH;
    digitalWrite(led_pin, led_state);
  }
  else if (Temp > 22.00 && Temp < 30.00) {
    led_state = LOW;
    motor_state = LOW;
    digitalWrite(led_pin, led_state);
    digitalWrite(motor_pin, motor_state);
  }
}

void loop() {
  count++;
  if (count > 30000) {
    float curr_temp = set_temp();
    control_devices_by_temp(curr_temp);
    print_temp(curr_temp);
    count = 0;
  }

  set_motor_by_btn();
  set_led_by_btn();
}


