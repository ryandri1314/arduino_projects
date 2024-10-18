const byte relayPin = 9;
const byte flamePinDigital = 10;

void setup() {
  Serial.begin(9600);
  Serial.println("This's flame sensor application!");
  
  pinMode(relayPin, OUTPUT);
  // pinMode(flamePinAnalog, INPUT);
  pinMode(flamePinDigital, INPUT);
}

void loop() {
  byte state = digitalRead(flamePinDigital);
  if (state == HIGH) {
    digitalWrite(relayPin, HIGH);
  }
  else {
    digitalWrite(relayPin, LOW);
  }
  Serial.println(state);

  delay(100);
}
