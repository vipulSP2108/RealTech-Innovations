#include <Servo.h>
Servo servo1;
Servo servo2; 
Servo servo3; 
Servo servo4; 
Servo servo5;
Servo servo6;

int fbPin = 2;
int bbPin = 3;

int testPin = 4;
int test = 0;

int servo1Angle = 0;
int servo2Angle = 0;
int servo3Angle = 0;
int servo4Angle = 0;
int servo5Angle = 0;
int servo6Angle = 0;
int i = 0;
int oldi = 0;

void setup() {
  pinMode(fbPin, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(bbPin, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(testPin, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
  
  servo1.attach(5);
  servo2.attach(6);
  servo3.attach(7);
  servo4.attach(8);
  servo5.attach(9);
  servo6.attach(10);
}

char englishalpha[][1] = {{'A'}, {'B'}, {'C'}};
int english[][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 90}, {0, 0, 0, 0, 90, 90}};

void loop() {
  oldi = i;
  
  // working of buttons 
  if (digitalRead(fbPin) == 1) {
    digitalWrite(13, HIGH);
    i++;
    delay(1000);
    /*speak next*/
  } 
  else {
    digitalWrite(13, LOW);
  }

  if (digitalRead(bbPin) == 1) {
    i--;
    digitalWrite(12, HIGH);
    delay(1000);
    /*speak next*/
  } 
  else {
    digitalWrite(12, LOW);
  }

  if (digitalRead(testPin) == 1) {
    // test mode
    if (test == 1){
      test = 0;
      digitalWrite(11, HIGH);
    }
    else{
      test = 1;
      digitalWrite(11, LOW);
    }
    delay(1000);
    /*speak next*/
  }
 // Serial.println(i);
 // Serial.println(test);

  if (test == 0){
    // working to train mode
    // speak from englishalpha[i]
    servo1Angle = english[i][0], servo2Angle = english[i][1], servo3Angle = english[i][2], servo4Angle = english[i][3], servo5Angle = english[i][4], servo6Angle = english[i][5];
  }
  else{
    // working to test mode
    int rand(void);
    int i = random(10);
    Serial.println(i);
    delay(1000);
  }
  Serial.println(servo6Angle);
  
  if (oldi != i){
    servo1.write(servo1Angle);
    servo2.write(servo2Angle);
    servo3.write(servo3Angle);
    servo4.write(servo4Angle);
    servo5.write(servo5Angle);
    servo6.write(servo6Angle);
  }
}
