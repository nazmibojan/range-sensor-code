#include <Arduino.h>

#define TRIGGER1_PIN 33
#define ECHO1_PIN 34
#define TRIGGER2_PIN 25
#define ECHO2_PIN 26
#define BUZZER_PIN 27
#define VIBRA_PIN 35

float distance1 = 0;
float distance2 = 0;

float jsnsr04tRead(int trigPin, int echoPin);
void alertCheck(float range);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(VIBRA_PIN, OUTPUT);
  pinMode(TRIGGER1_PIN, OUTPUT);
  pinMode(ECHO1_PIN, INPUT);
  pinMode(TRIGGER2_PIN, OUTPUT);
  pinMode(ECHO2_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  distance1 = jsnsr04tRead(TRIGGER1_PIN, ECHO1_PIN);
  distance2 = jsnsr04tRead(TRIGGER2_PIN, ECHO2_PIN);

  if (distance1 != 0.00) {
    Serial.println("First Sensor Distance: " + String(distance1) + " cm");
    // Trigger buzzer dan vibration motor
    alertCheck(distance1);
  }

  if (distance2 != 0.00) {
    Serial.println("Second Sensor Distance: " + String(distance2) + " cm");
    // Trigger buzzer dan vibration motor
    alertCheck(distance2);
  }

  delay(1000);
}

float jsnsr04tRead(int trigPin, int echoPin) {
  float result;
  long duration = 0;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  result = (float)duration * 0.034 / 2;

  return result;
}

void alertCheck(float range) {
  if (range < 100.00) {
    Serial.println("Watch out. There is obstacle infront of you");
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(VIBRA_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(VIBRA_PIN, LOW);
  }
}