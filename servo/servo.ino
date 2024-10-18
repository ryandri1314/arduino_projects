#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int r;

void setup() {
  Serial.begin(9600);
  myservo.attach(10, 1000, 2000); 
}

void loop() {
  myservo.write(0);
  delay(1000);

  myservo.write(90);
  delay(1000);

  myservo.write(180);
  delay(1000);

  myservo.write(90);
  delay(1000);
}