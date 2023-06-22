int led1 = 4;
int led2 = 5;
int led3 = 6;
int led4 = 7;

int button1 = 9;
int button2 = 10;
int button3 = 11;
int button4 = 12;

int wordon = 0;

void setup(){
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
}

void loop(){
    
  int word = digitalRead(button1);
  int alfa = digitalRead(button2);

  if (word == 0){
    digitalWrite(led1, HIGH);
    // word
  }
  else{
    digitalWrite(led1, LOW);
  }
  if (alfa == 0){
    digitalWrite(led2, HIGH);
    // alfa
  }
  else{
    digitalWrite(led2, LOW);
  }

  int test = digitalRead(button3);
  int train = digitalRead(button4);

  if (test == 0){
    digitalWrite(led3, HIGH);
    // test
  }
  else{
    digitalWrite(led3, LOW);
  }
  if (train == 0){
    digitalWrite(led4, HIGH);
    // train
  }
  else{
    digitalWrite(led4, LOW);
  }
}
