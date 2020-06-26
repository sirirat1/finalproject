int LedRED = 12;
int LEDgreen = 11;
int smokeA0 = 0;

int sensorThres = 400;  

void setup() {
  Serial.begin(9600);
  pinMode(LedRED, OUTPUT);
  pinMode(LEDgreen, OUTPUT);
  pinMode(smokeA0, INPUT);
}

void loop() {
  int analogSensor = analogRead(smokeA0);
  Serial.print("Pin A0: ");
  Serial.println(analogSensor); 

  if (analogSensor > sensorThres)  {
    digitalWrite(LedRED, HIGH);
    digitalWrite(LEDgreen, LOW);
  }

  else  {
    digitalWrite(LedRED, LOW);
    digitalWrite(LEDgreen, HIGH);
  }
  delay(100);
}