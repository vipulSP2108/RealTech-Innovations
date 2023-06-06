#include <Servo.h>

Servo servo1;
Servo servo2; 
Servo servo3; 
Servo servo4; 
Servo servo5;
Servo servo6;

int servo1Angle = 0;
int servo2Angle = 0;
int servo3Angle = 0;
int servo4Angle = 0;
int servo5Angle = 0;
int servo6Angle = 0;

int on = 90;
int off = 0;
int i = 0;

void setup() {
  servo1.attach(1);
  servo2.attach(2);
  servo3.attach(3);
  servo4.attach(4);
  servo5.attach(5);
  servo6.attach(6);
}

char englishalpha[][1] = {{'A'}, {'B'}, {'C'}};
int english[][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 1, 1}};

//   {"00000000": " ",
//    "00000001": "A",
//    "00000011": "B",
//    "00001001": "C",
//    "00011001": "D",
//    "00010001": "E",
//    "00001011": "F",
//    "00011011": "G",
//    "00010011": "H",
//    "00001010": "I",
//    "00011010": "J",
//    "00000101": "K",
//    "00000111": "L",
//    "00001101": "M",
//    "00011101": "N",
//    "00010101": "O",
//    "00001111": "P",
//    "00011111": "Q",
//    "00010111": "R",
//    "00001110": "S",
//    "00011110": "T",
//    "00100101": "U",
//    "00100111": "V",
//    "00111010": "W",
//    "00111101": "Y",
//    "00101101": "X",
//    "00110101": "Z", }

void loop() {
  Serial.println("Enter Alphabet");

  // M1
  while (!Serial.available()) {
  }
  int soilType = Serial.parseInt();

  // M2
  if (Serial.available()) {
    char input = Serial.read();

    if (input == "A") {
      i = 1;
    }
    else if (input == "B"){
      i = 2;
    }
    else if (input == "C"){
      i = 3;
    }
  }

  servo1Angle = english[i][0], servo2Angle = english[i][1], servo3Angle = english[i][2], servo4Angle = english[i][3], servo5Angle = english[i][4], servo6Angle = english[i][5];

  servo1.write(servo1Angle);
  servo2.write(servo2Angle);
  servo3.write(servo3Angle);
  servo4.write(servo4Angle);
  servo5.write(servo5Angle);
  servo6.write(servo6Angle);
}
