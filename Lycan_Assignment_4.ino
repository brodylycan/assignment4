#define trigPin 13
#define echoPin 12
#define redLed 11
#define blueLed 10
#define piezoPin 8

int normalDistance = 200;
boolean triggered = false;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(piezoPin, OUTPUT);

  long duration, distance;

  digitalWrite(redLed, HIGH); // to indicate that the calibration is in process
  digitalWrite(blueLed, HIGH);

  digitalWrite(piezoPin, HIGH);

  while (millis() < 5000) {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration / 2) / 29.1;
      if (distance < normalDistance) {
        normalDistance = distance;
      }
   }

   digitalWrite(redLed, LOW); // finish calibration
   digitalWrite(blueLed, LOW);
   digitalWrite(piezoPin, LOW);
}

void loop() {
  long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
    
  if (distance < normalDistance - 10) {
    digitalWrite(redLed, HIGH);
    digitalWrite(blueLed, LOW);
    tone(piezoPin, 635, 500);
    delay(500);
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, HIGH);
    tone(piezoPin, 912, 500);
    delay(500);
  } else {
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, LOW);
  }
  delay(20);
}

 