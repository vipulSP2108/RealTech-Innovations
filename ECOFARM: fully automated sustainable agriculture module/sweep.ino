#include <Servo.h>
Servo myservo;
int sensor1Pin = A0;
int sensor2Pin = A1; 
int sensor3Pin = A2;
int LDR_PIN = A3;
int pumpPin = 2;
int buzzerPin = 2;
int LED_PIN = 3;

const int lm35Pin = A2;
float temperature;

int numReadings = 1;
int sensor1Value = 0;
int sensor2Value = 0;
int sensor3Value = 0;
int soilAverage = 0;

int high_threshold = 700;
int low_threshold = 300;

void setup() {
  myservo.attach(7);
  pinMode(pumpPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);

  Serial.println("Enter soil type (claye/normal/rocky): ");
  while (!Serial.available()) {
  }
  int soilType = Serial.parseInt();

  switch (soilType) {
    case 1:
      high_threshold = 700;
      low_threshold = 200;
      break;
    case 2:
      high_threshold = 700;
      low_threshold = 300;
      break;
    case 3:
      high_threshold = 700;
      low_threshold = 400;
      break;

    default:
      Serial.println("Invalid soil type");
      while (1) {
      }
  }
}

void loop() {
  // soil mosture and pump
  sensor1Value = analogRead(sensor1Pin);
  sensor2Value = analogRead(sensor2Pin);
  sensor3Value = analogRead(sensor3Pin);
  soilAverage = (sensor1Value + sensor2Value + sensor3Value) / 3;
  Serial.print("Average soil moisture reading: ");
  Serial.println(soilAverage);

  if (soilAverage < high_threshold && soilAverage > low_threshold) {
    digitalWrite(pumpPin, HIGH);
    Serial.println("Pump started");
    myservo.write(90); // dam opened
  } 
  else {
    digitalWrite(pumpPin, LOW);
    Serial.println("Pump stopped");
    myservo.write(90); // closed opened
  }

  // buzzer code
  if (soilAverage > 700){
  digitalWrite(buzzerPin, HIGH); // continue
  delay(1000);
  }
  else if (soilAverage > 650){
    digitalWrite(buzzerPin, HIGH); // 2 beat
    delay(300);
    digitalWrite(buzzerPin, LOW);
    delay(300);
    digitalWrite(buzzerPin, HIGH);
    delay(300);
    digitalWrite(buzzerPin, LOW);
    delay(1000);
  }
  else if (soilAverage > 600){
    digitalWrite(buzzerPin, HIGH); // 1 beat
    delay(300);
    digitalWrite(buzzerPin, LOW);
    delay(1000);
  }
  else if (soilAverage > 300){
    digitalWrite(buzzerPin, HIGH); // 1 beat
    delay(300);
    digitalWrite(buzzerPin, LOW);
    delay(1000);
  }
  else if (soilAverage > 250){
    digitalWrite(buzzerPin, HIGH); // 2 beat
    delay(300);
    digitalWrite(buzzerPin, LOW);
    delay(300);
    digitalWrite(buzzerPin, HIGH);
    delay(300);
    digitalWrite(buzzerPin, LOW);
    delay(1000);
  }
  else if (soilAverage > 200){
    digitalWrite(buzzerPin, HIGH); // continue
    delay(1000);
  }
  // LDR
  int lightLevel = analogRead(LDR_PIN);
  // Serial.print("Light level: ");
  // Serial.println(lightLevel);
  if (lightLevel < 400) {
    digitalWrite(LED_PIN, HIGH);
  } 
  else if (lightLevel > 400) {
    digitalWrite(LED_PIN, LOW);
    delay(200); 
  }
  // Temp
  int sensorValue = analogRead(lm35Pin);
  float millivolts = (sensorValue / 1024.0) * 5000;
  temperature = millivolts / 10;
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
  delay(200); 
}
