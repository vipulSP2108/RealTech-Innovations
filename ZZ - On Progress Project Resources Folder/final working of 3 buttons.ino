int fbPin = 2;
int bbPin = 3;
int testPin = 4;
int i = 0;
int test = 0;
void setup() {
  pinMode(fbPin, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(bbPin, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(testPin, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
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
    /*speak priveous*/
  } 
  else {
    digitalWrite(12, LOW);
  }

  if (digitalRead(testPin) == 1) {
    // test mode
    if (test == 1){
      test = 0;
    }
    else{
      test = 1;
    }
    digitalWrite(11, HIGH);
    delay(1000);
    /*speak mode change*/
  }
  Serial.println(i);
  Serial.println(test);
}
