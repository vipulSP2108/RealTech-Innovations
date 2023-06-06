#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int analogPin = A0;

const int sensorPin = A0;
const int ledPin = 13;
const int buzzer=7;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer,OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Sensor Value:");
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  lcd.setCursor(0, 0);
  lcd.print("Sensor Value:");
  lcd.setCursor(0, 1);
  lcd.print(sensorValue);

  if (sensorValue > 600) { 
    delay(300);
    lcd.setCursor(0, 0);
    lcd.print("  ALERT! ALERT!");
    lcd.setCursor(0, 1);
    lcd.print("  ALERT! ALERT!");
    digitalWrite(ledPin, HIGH); 
    digitalWrite(buzzer,HIGH);
    delay(5000);
    digitalWrite(ledPin, LOW);  
    digitalWrite(buzzer,LOW);
    delay(150);
    lcd.setCursor(0, 1);
    lcd.setCursor(0, 0);
    lcd.print("Sensor Value:");
  }
  else if (sensorValue > 900) { 
    digitalWrite(ledPin, HIGH); 
    digitalWrite(buzzer,HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);  
    digitalWrite(buzzer,LOW);
    delay(150);
    digitalWrite(ledPin, HIGH); 
    digitalWrite(buzzer,HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);  
    digitalWrite(buzzer,LOW);
    delay(150);
    digitalWrite(ledPin, HIGH); 
    digitalWrite(buzzer,HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);  
    digitalWrite(buzzer,LOW);
    delay(150);
  }
  else if (sensorValue > 8+00) { 
    digitalWrite(ledPin, HIGH); 
    digitalWrite(buzzer,HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);  
    digitalWrite(buzzer,LOW);
    delay(150);
    digitalWrite(ledPin, HIGH); 
    digitalWrite(buzzer,HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);  
    digitalWrite(buzzer,LOW);
    delay(150);
  }
  
  else {
    digitalWrite(ledPin, LOW);  
    digitalWrite(buzzer,LOW);
  }
    lcd.setCursor(0,1);
}
