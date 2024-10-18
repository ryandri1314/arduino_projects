const byte trig = 12;
const byte echo = 11;
const byte relayPin = 9;

byte stateOfRelay = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, stateOfRelay);
}

float getDistance() {
  unsigned long duration;
  float res;

  /* Phát xung từ chân trig */
  digitalWrite(trig,0);   // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig,1);   // phát xung từ chân trig
  delayMicroseconds(5);   // xung có độ dài 5 microSeconds
  digitalWrite(trig,0);   // tắt chân trig

  /* Tính toán thời gian */
  // Đo độ rộng xung HIGH ở chân echo. 
  duration = pulseIn(echo,HIGH);  
  // Tính khoảng cách đến vật.
  res = float(duration/(2*29.412));
  return res;
}

void printDistance(float distance) {
  Serial.print(distance);
  Serial.println("cm");
  delay(200);
}

void controlMotor(float distance, byte &stateOfRelay) {
  if (distance <= 10.00 && stateOfRelay == HIGH) {
    stateOfRelay = LOW;
    digitalWrite(relayPin, LOW);
  }
  else if (distance > 10.00 && stateOfRelay == LOW) {
    delay(5000);
    stateOfRelay = HIGH;
    digitalWrite(relayPin, HIGH);
  }
}

void loop() {
  float distance = getDistance();
  printDistance(distance);

  controlMotor(distance, stateOfRelay);
}
