int ledpin = 12;
int time = 1000;
// int offtime = 1000;
String wordinputed;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Serial.println(1);
  while (!Serial.available() ==0) {}
  wordinputed = Serial.readString();
  Serial.println(wordinputed);
  
  int len = wordinputed.length();
  Serial.println(len);
  
  // if (wordinputed == 'ASA'){
  //   digitalWrite(ledpin, HIGH);
  //   delay(5000);
  //   digitalWrite(ledpin, LOW);
  //   delay(1000);
  // }

  for(int i=0; i<len; i++){
    char h = wordinputed[i];
    // digitalWrite(ledpin, HIGH);
    // delay(2000);
    // digitalWrite(ledpin, LOW);
    // delay(1000);
    Serial.println(h);
    Serial.println(i);
  }
}
