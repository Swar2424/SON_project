void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  int newval = map(sensorValue, 0, 1023, 1, 10);
  Serial.println(newval);
  delay(100);
}
