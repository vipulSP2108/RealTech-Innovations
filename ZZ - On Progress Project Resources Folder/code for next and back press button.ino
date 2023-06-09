// const int ledPin = 13;
int i = 0;

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
  // pinMode(ledPin, OUTPUT);
  pinMode(fbPin, INPUT);
  pinMode(bbPin, INPUT);
}

bool readingpress(int NewbuttonState, int lastButtonState, bool buttonOn);

void loop() {
  fbState = digitalRead(fbPin);
  bbState = digitalRead(bbPin);

  fbOn = readingpress(fbState, lastfbState, fbOn);
  bbOn = readingpress(bbState, lastbbState, bbOn);
  fbOn == true ? i++ : i=i;
  bbOn == true ? i-- : i=i;
  
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
  return buttonOn;
}
