#include <AFMotor.h>
#include "SD.h"
#define SD_ChipSelectPin 4

/* SET */
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
AF_DCMotor motor5(5);
AF_DCMotor motor6(6);

int fbPin = 22;
int bbPin = 40;
int onoffPin = 5;

int buttonslide1_1 = 9;             //1 is for alfa
int buttonslide1_2 = 10;
int buttonslide2_1 = 7;            //2 is for train
int buttonslide2_2 = 6;

/* VARIABLES */
int onvoice = 1;
int alfa = 1;
int train = 1;
int state1 = 0;
int state2 = 0;
int i = 0;
int oldi = 0;
int ivoice = 0;
int trained = 0;
int teston = 0;

int olddelaymotor1 = 0;
int olddelaymotor2 = 0;
int olddelaymotor3 = 0;
int olddelaymotor4 = 0;
int olddelaymotor5 = 0;
int olddelaymotor6 = 0;
int delaymotor1 = 0;
int delaymotor2 = 0;
int delaymotor3 = 0;
int delaymotor4 = 0;
int delaymotor5 = 0;
int delaymotor6 = 0;

const char* fileName = "last_words.txt";

void setup(){
  // slider
  pinMode(buttonslide1_1, INPUT_PULLUP);
  pinMode(buttonslide1_2, INPUT_PULLUP);
  pinMode(buttonslide2_1, INPUT_PULLUP);
  pinMode(buttonslide2_2, INPUT_PULLUP);

  // forword, backword and on-off pin
  pinMode(fbPin, OUTPUT);
  pinMode(bbPin, OUTPUT);
  pinMode(onoffPin, OUTPUT);

  // motor
  motor1.setSpeed(255); // Set the speed of motor 1 to maximum
  motor1.run(RELEASE); // Release motor 1 (stop)

  motor2.setSpeed(255); // Set the speed of motor 1 to maximum
  motor2.run(RELEASE); // Release motor 1 (stop)

  motor3.setSpeed(255); // Set the speed of motor 1 to maximum
  motor3.run(RELEASE); // Release motor 1 (stop)

  motor4.setSpeed(255); // Set the speed of motor 1 to maximum
  motor4.run(RELEASE); // Release motor 1 (stop)

  motor5.setSpeed(255); // Set the speed of motor 1 to maximum
  motor5.run(RELEASE); // Release motor 1 (stop)

  motor6.setSpeed(255); // Set the speed of motor 1 to maximum
  motor6.run(RELEASE); // Release motor 1 (stop)

  // file
  File file = SD.open(fileName);
  if (file) {
    i = file.parseInt();
    file.close();
  }
  Serial.begin(9600);
}

int english[][6] = {{200,0,0,0,0,0},{200,200,0,0,0,0},{200,0,0,200,0,0},{200,0,0,200,200,0},{200,0,0,0,200,0},{200,200,0,200,0,0},{200,200,0,200,200,0},{200,200,0,0,200,0},{0,200,0,200,0,0},{0,200,0,200,200,0},{200,0,200,0,0,0},{200,200,200,0,0,0},{200,0,200,200,0,0},{200,0,200,200,200,0},{200,0,200,0,200,0},{200,200,200,200,0,0},{200,200,200,200,200,0},{200,200,200,0,200,0},{0,200,200,200,0,0},{0,200,200,200,200,0},{200,0,200,0,0,200},{200,200,200,0,0,200},{0,200,0,200,200,200},{200,0,200,200,0,200},{200,0,200,200,200,200},{200,0,200,0,200,200}};
String alpha[] ={"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "", "", "", "",};

void loop(){
  // divice on
  if(digitalRead(onoffPin)==1){
    if(onvoice == 1){
      onvoice = 0;
    }

    oldi = i;

    state1 = digitalRead(buttonslide1_1);                           //train-test & alfa-word
    state2 = digitalRead(buttonslide1_2);
    if(state1 == 0){
      train = 0; //train mode off
    }
    else{
      train = 1; //train mode on
    }
    state1 = digitalRead(buttonslide2_1);           
    state2 = digitalRead(buttonslide2_2);
    if(state1 == 0){
      alfa = 0; //alfa mode off
    }
    else{
      alfa = 1; //alfa mode on
    }
    // Serial.print("train");
    // Serial.print(train);
    // Serial.print("alfa");
    // Serial.println(alfa);
    
    if (alfa == 1 && train == 1){                                 // working to alfa train mode
      
      // one time print only 
      if (trained == 0) { 
        Serial.print("train");
        Serial.print('\n');
        trained = 1;
      }

      // working
      if (i<26 && digitalRead(fbPin) == 1) {
        i++;
        Serial.print("forword");
        Serial.print('\n');
        // Serial.println("fb");
        // Serial.println(oldi);
        // Serial.println(i);
        delay(1000);
      }
      if (i>0 && digitalRead(bbPin) == 1) {
        i--;
        Serial.print("backword");
        Serial.print('\n');
        // Serial.println("bb");
        // Serial.println(oldi);
        // Serial.println(i);
        delay(1000);
      }
      olddelaymotor1 = english[oldi][0], olddelaymotor2 = english[oldi][1], olddelaymotor3 = english[oldi][2], olddelaymotor4 = english[oldi][3], olddelaymotor5 = english[oldi][4], olddelaymotor6 = english[oldi][5];
      delaymotor1 = english[i][0], delaymotor2 = english[i][1], delaymotor3 = english[i][2], delaymotor4 = english[i][3], delaymotor5 = english[i][4], delaymotor6 = english[i][5];
      
      // alfabet voice
      if (oldi != i){
        Serial.print(alpha[i]);
        Serial.print('\n');
      }
    }

    if (alfa == 1 && train == 0){                                 // working to alfa test mode
      
      // one time print only 
      if (trained == 1) { 
        Serial.print("test");
        Serial.print('\n');
        trained = 0;
      }
      
      // working
      if (teston == 0){
        int rand(void);
        i = random(26);       //26
        int subs = random(11);
        int alfavoices[] = {i, i-subs, i-(2*subs)};

        // alfabet voice
        int var = random(3);
        ivoice = alfavoices[var];
        Serial.print(alpha[ivoice]);
        Serial.print('\n');

        // Serial.println(i);
        // Serial.println(oldi);
        // Serial.println(ivoice);
        teston = 1;
      }

      if (digitalRead(fbPin) == 1){
        if (i == ivoice){
          Serial.print("correct_greetings");
          Serial.print('\n');
        }
        else {
          Serial.print("wrong_greetings");
          Serial.print('\n');
        }
        delay(1000);                // hatana pad sakta hai
        teston = 0;
      }

      if (digitalRead(bbPin) == 1){
        if(i != ivoice){
          Serial.print("correct_greetings");
          Serial.print('\n');
        }
        else{
          Serial.print("wrong_greetings");
          Serial.print('\n');
        }
        delay(1000);                // hatana pad sakta hai
        teston = 0;
      }
    olddelaymotor1 = english[oldi][0], olddelaymotor2 = english[oldi][1], olddelaymotor3 = english[oldi][2], olddelaymotor4 = english[oldi][3], olddelaymotor5 = english[oldi][4], olddelaymotor6 = english[oldi][5];
    delaymotor1 = english[i][0], delaymotor2 = english[i][1], delaymotor3 = english[i][2], delaymotor4 = english[i][3], delaymotor5 = english[i][4], delaymotor6 = english[i][5];
    }

    // if (alfa == 0 && train == 1){}

    // if (alfa == 0 && train == 0){}

    if (oldi != i){
      // Serial.println(oldi);
      // Serial.println(i);

      // file
      File file = SD.open(fileName, FILE_WRITE);
      if (file) {
        file.println(i);
        file.close();
        // Serial.print("New value written");
      }
      else {
        Serial.println("Error opening file!");
      }

      // privious motor down
      motor1.run(BACKWARD);  // Run motor in forward direction
      delay(olddelaymotor1); // Delay for 200 miliseconds
      motor1.run(RELEASE);   // Release motor (stop)
    
      motor2.run(BACKWARD);
      delay(olddelaymotor2);
      motor2.run(RELEASE);
    
      motor3.run(BACKWARD);
      delay(olddelaymotor3);
      motor3.run(RELEASE);

      motor4.run(BACKWARD);
      delay(olddelaymotor4);
      motor4.run(RELEASE);

      motor5.run(BACKWARD);
      delay(olddelaymotor5);
      motor5.run(RELEASE);
  
      motor6.run(BACKWARD);
      delay(olddelaymotor6);
      motor6.run(RELEASE);

      // next motor up
      motor1.run(FORWARD); // Run motor in forward direction
      delay(delaymotor1);  // Delay for 200 miliseconds
      motor1.run(RELEASE); // Release motor (stop)
    
      motor2.run(FORWARD);
      delay(delaymotor2);
      motor2.run(RELEASE);
    
      motor3.run(FORWARD);
      delay(delaymotor3);
      motor3.run(RELEASE);

      motor4.run(FORWARD);
      delay(delaymotor4);
      motor4.run(RELEASE);

      motor5.run(FORWARD);
      delay(delaymotor5);
      motor5.run(RELEASE);
  
      motor6.run(FORWARD);
      delay(delaymotor6);
      motor6.run(RELEASE);
    }
  }

  // divice off
  else{
    if(onvoice == 0){
      Serial.print("end");
      Serial.print('\n');
      onvoice = 1;
    }
  }
}
