// const int ledPin = 13;
int i = 1;
int servo1Angle = 0;
int servo2Angle = 0;
int servo3Angle = 0;
int servo4Angle = 0;
int servo5Angle = 0;
int servo6Angle = 0;

// forword botton
int fbPin = 2;
int fbState = 0;
int lastfbState = LOW;
bool fbOn = false;

// backward botton
int bbPin = 7;
int bbState = 0;
int lastbbState = LOW;
bool bbOn = false;

void setup() {
  randomSeed(analogRead(A0));
  Serial.begin(9600);
  // pinMode(ledPin, OUTPUT);
  pinMode(fbPin, INPUT);
  pinMode(bbPin, INPUT);
}

char englishalpha[][1] = {{'A'}, {'B'}, {'C'}};
int english[][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 1, 1}};
bool readingpress(int NewbuttonState, int lastButtonState, bool buttonOn);

void loop() {
  fbState = digitalRead(fbPin);
  bbState = digitalRead(bbPin);

  if (fbState != lastfbState) {
    fbOn = readingpress(fbState, lastfbState, fbOn);
  }
  
  if (bbState != lastbbState) {
    bbOn = readingpress(bbState, lastbbState, bbOn);
  }
  
  fbOn == true ? i++ /*speak next*/: i=i;
  bbOn == true ? i-- /*speak previous*/: i=i;
  
  // Mode train
  // speak from englishalpha[i]
  servo1Angle = english[i][0], servo2Angle = english[i][1], servo3Angle = english[i][2], servo4Angle = english[i][3], servo5Angle = english[i][4], servo6Angle = english[i][5];
  
  // Mode test
  int rand(void);
  int i = random(10);
  Serial.println(i);
  delay(1000);
  
  lastfbState = fbState;
  lastbbState = bbState;
}

bool readingpress(int NewbuttonState, int lastButtonState, bool buttonOn){
  if (NewbuttonState != lastButtonState) {
    if (NewbuttonState == HIGH) {
      if (!buttonOn) {
        // digitalWrite(ledPin, HIGH);
        buttonOn = true;
      } else {
        // digitalWrite(ledPin, LOW);
        buttonOn = false;
      }
    }
    delay(50);
  }
  return buttonOn;
}
