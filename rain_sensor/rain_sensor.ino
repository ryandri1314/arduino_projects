byte sensorPin = A0;
byte relayPin = 13;

void setup() 
{
  Serial.begin(9600);
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  Serial.print(analogRead(A0));
  Serial.print("  ");
  int sensorState = analogRead(A0);
  Serial.println(sensorState);
  if (sensorState < 900 ) {
    digitalWrite(relayPin, LOW);
  }
  else {
    digitalWrite(relayPin, HIGH);
  }
}
