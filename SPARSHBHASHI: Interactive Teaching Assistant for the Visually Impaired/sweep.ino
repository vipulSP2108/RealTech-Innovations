#include <AFMotor.h>
#include <PCM.h>
#include <Talkie.h>
#include "SD.h"
#define SD_ChipSelectPin 4
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
AF_DCMotor motor5(5);
AF_DCMotor motor6(6);

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

int fbPin = 22;
int bbPin = 40;
int alfatest = 28;
int alfatrain = 34;
int teston = 0;
int greetings = 0;
int onPin = 5;
int on = 0;

int test = 0;

int i = 0;
int oldi = 0;
int ivoice = 0;

const unsigned char sample[] PROGMEM = {126};

// test .... Now Test is starting. If the letter presented in Braille matches the heard letter, press the right side button; otherwise, press the left side button
// train...  Press the right side button if the letters match, otherwise press the left side button

const char* fileName = "last_words.txt";

void setup(){
  // file
  File file = SD.open(fileName);
  if (file) {
    i = file.parseInt();
    file.close();
  }

  // speaker
  tmrpcm.speakerPin = 9;
  if (!SD.begin(SD_ChipSelectPin)) {
  Serial.println("SD fail");
  return;
  }

  // forword and backword pin
  pinMode(fbPin, OUTPUT);
  pinMode(bbPin, OUTPUT);
  pinMode(onPin, OUTPUT);

  pinMode(alfatrain, INPUT_PULLUP);
  pinMode(alfatest, INPUT_PULLUP);

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

  Serial.begin(9600);
}

const char* voice[] = {"void.wav", "a.wav", "b.wav", "c.wav", "d.wav", "e.wav", "f.wav", "g.wav", "h.wav", "i.wav", "j.wav", "k.wav"};
int english[][6] = {{0,0,0,0,0,0},{200,0,0,0,0,0},{200,200,0,0,0,0},{200,0,0,200,0,0},{200,0,0,200,200,0},{200,0,0,0,200,0},{200,200,0,200,0,0},{200,200,0,200,200,0},{200,200,0,0,200,0},{0,200,0,200,0,0},{0,200,0,200,200,0}};    // {200,0,200,0,0,0},{200,200,200,0,0,0},{200,0,200,200,0,0},{200,0,200,200,200,0},{200,0,200,0,200,0},{200,200,200,200,0,0},{200,200,200,200,200,0},{200,200,200,0,200,0}, {0,200,0,200,200,200},{200,0,200,200,0,200},{200,0,200,200,200,200},{200,0,200,0,200,200}

const char* correct_greetings[] = { "cg1.wav", "cg2.wav", "cg3.wav", "cg4.wav", "cg5.wav", "cg6.wav" }; 
    // "Superb, that's the correct answer!",
    // "Well done, you got the correct answer!",
    // "Congratulations, that's the right answer!",
    // "Great job, you got it right!",
    // "Excellent work, you got the correct answer!",
    // "Fantastic, that's the right answer!"

const char* wrong_greetings[] = { "wg1.wav", "wg2.wav", "wg3.wav", "wg4.wav", "wg5.wav", "wg6.wav" };
    // "Oops, that's not the correct answer.",
    // "Sorry, that's incorrect.",
    // "Incorrect, try again.",
    // "Not quite right, give it another shot.",
    // "Wrong answer, keep trying.",
    // "Unfortunately, that's not the correct response."

void loop() {
  oldi = i;
  if (digitalRead(fbPin) == 1){
    delay(1000);
    if (digitalRead(fbPin) == 1){
      if (test == 0){
        test = 1;
      }
      else{
        test = 0;
      }
    }
    Serial.println(test);
  }
  Serial.println(test);


  // if (digitalRead(onPin) == 1) {
  //   on = 0;
  //   i = 0;
  //   /speak power off/
  //   delay(1000);
  // }

  // working to alfa train mode
  if (test == 0){
    tmrpcm.play("train.wav");
    if (i<26 && digitalRead(fbPin) == 1) {
      i++;
      // Serial.println("fb");
      // Serial.println(oldi);
      // Serial.println(i);
      tmrpcm.setVolume(5);
      tmrpcm.play("next_alfa.wav");
      tmrpcm.play(voice[i]); //speak from voice[i]
      delay(1000);
    }
    if (i>0 && digitalRead(bbPin) == 1) {
      i--;
      // Serial.println("bb");
      // Serial.println(oldi);
      // Serial.println(i);
      tmrpcm.setVolume(5);
      tmrpcm.play("privious_alfa.wav");
      tmrpcm.play(voice[i]); //speak from voice[i]
      delay(1000);
    }
    olddelaymotor1 = english[oldi][0], olddelaymotor2 = english[oldi][1], olddelaymotor3 = english[oldi][2], olddelaymotor4 = english[oldi][3], olddelaymotor5 = english[oldi][4], olddelaymotor6 = english[oldi][5];
    delaymotor1 = english[i][0], delaymotor2 = english[i][1], delaymotor3 = english[i][2], delaymotor4 = english[i][3], delaymotor5 = english[i][4], delaymotor6 = english[i][5];
    teston = 0;
  }

  // working to alfa test mode
  if (test == 1){
    tmrpcm.play("test.wav");
    
    // Serial.println("test");
    if (teston == 0){
      int rand(void);
      i = random(11);       //26
      ivoice = random(11);  //26
      greetings = random(5);
      tmrpcm.play(voice[ivoice]); //speak from voice[i]
      // Serial.println(i);
      // Serial.println(oldi);
      // Serial.println(ivoice);
      teston = 1;
    }

    if (digitalRead(fbPin) == 1){
      if (i == ivoice){
        teston = 0;
        tmrpcm.play(correct_greetings[greetings]);
        tmrpcm.play(voice[i]); //speak from voice[i]
      }
      else {
        teston = 0;
        delay(1000);                // hatana pad sakta hai
        tmrpcm.play(wrong_greetings[greetings]);
        tmrpcm.play(voice[i]); //speak from voice[i]
      }
      // teston = 0;
    }
    if (digitalRead(bbPin) == 1){
      if(i != ivoice){
        teston = 0;
        delay(1000);                // hatana pad sakta hai
        tmrpcm.play(correct_greetings[greetings]);
        tmrpcm.play(voice[i]); //speak from voice[i]
      }
      else{
        teston = 0;
        delay(1000);                // hatana pad sakta hai
        tmrpcm.play(wrong_greetings[greetings]);
        tmrpcm.play(voice[i]); //speak from voice[i]
      }
      // teston = 0;
    }
    olddelaymotor1 = english[oldi][0], olddelaymotor2 = english[oldi][1], olddelaymotor3 = english[oldi][2], olddelaymotor4 = english[oldi][3], olddelaymotor5 = english[oldi][4], olddelaymotor6 = english[oldi][5];
    delaymotor1 = english[i][0], delaymotor2 = english[i][1], delaymotor3 = english[i][2], delaymotor4 = english[i][3], delaymotor5 = english[i][4], delaymotor6 = english[i][5];
  }

  if (oldi != i){
    File file = SD.open(fileName, FILE_WRITE);
    if (file) {
      file.println(i);
      file.close();
      Serial.print("New value written");
    }
    else {
      Serial.println("Error opening file!");
    }

    Serial.println(oldi);
    Serial.println(i);

    // privious motor down
    motor1.run(BACKWARD); // Run motor in forward direction
    delay(olddelaymotor1); // Delay for 200 miliseconds
    motor1.run(RELEASE); // Release motor (stop)
    
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
    delay(delaymotor1); // Delay for 200 miliseconds
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
