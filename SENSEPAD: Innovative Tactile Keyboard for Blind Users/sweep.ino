int pressbutton1 = 2;
int pressbutton2 = 3;
int pressbutton3 = 7;
int pressbutton4 = 8;
int pressbutton5 = 9;
int pressbutton6 = 12;

int space = 10;
int caps = 5;
int backspace = 13;

int numon = 0;
int numoff = 0;
int capspos = 0;
int numpos = 0;
int len = 26;
String alfatyped = "000000";

String nums[] ={"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
String alpha[] ={"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "'", "/", ":", ",", ".", "$", "!", "_", "-", "#", "(", ")", "?", ";"};

String alfamatch[] = {
  // "000001",
  // "000010",
  // "000100",
  // "001000",
  // "010000",
  // "100000",

  "100000", //a
  "110000", //b
  "100100", //c
  "100110", //d
  "100010", //e
  "110100", //f
  "110110", //g
  "110010", //h
  "010100", //i
  "010110", //j
  "101000", //k
  "111000", //l
  "101100", //m
  "101110", //n
  "101010", //o
  "111100", //p
  "111110", //q
  "111010", //r
  "011100", //s
  "011110", //t
  "101001", //u
  "111001", //v
  "010111", //w
  "101101", //x
  "101111", //y
  "101011", // z
  
  "001000", // Pharmaceutical
  "001100",
  "010010",
  "010000",
  "000101",
  "010011",
  "011010",
  "001100",
  "001001",
  "001111",
  "011011",
  "011011",
  "011001",
  "011000"
};

void setup() {
  pinMode(pressbutton1, OUTPUT);
  pinMode(pressbutton2, OUTPUT);
  pinMode(pressbutton3, OUTPUT);
  pinMode(pressbutton4, OUTPUT);
  pinMode(pressbutton5, OUTPUT);
  pinMode(pressbutton6, OUTPUT);
  
  pinMode(space, OUTPUT);
  pinMode(caps, OUTPUT);
  pinMode(backspace, INPUT_PULLUP); 
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(space) == 1) { 
    delay(500);
    if (digitalRead(space) == 0){   // shortpress space
      // Serial.print(" ");
      // Serial.flush();
      Serial.print("\n");
    }
    else{                           // longpress newline
      Serial.print("end");
      // Serial.println();
      // Serial.flush(); 
      delay(1000);
      // Serial.print(" #newline# ");
    }
  }

  numpos = 1;
  if (digitalRead(caps) == 1) { 
    delay(500);
    if (digitalRead(caps) == 1){      // longpress numlock
      if (numon == 0){
        numon = 1;
        // Serial.print(" #numson# ");
      }
      else {
        numon = 0;
        // Serial.print(" #numsoff# ");
      }
    }

    else{                             // shortpress caps
      if (capspos == 1){
        capspos = 0;
        // Serial.print(" #capsoff# ");
      }
      else{
        capspos = 1;
        // Serial.print(" #capson# ");
      } 
    }
  }
  
  if (digitalRead(pressbutton1) == 1) { // motor 1
    alfatyped[0] = '1';
  }

  if (digitalRead(pressbutton2) == 1) {
    alfatyped[1] = '1';
  }

  if (digitalRead(pressbutton3) == 1) {
    alfatyped[2] = '1';
  }

  if (digitalRead(pressbutton4) == 1) {
    alfatyped[3] = '1';
  }

  if (digitalRead(pressbutton5) == 1) {
    alfatyped[4] = '1';
  }

  if (digitalRead(pressbutton6) == 1) { // motor 6
    alfatyped[5] = '1';
  }
  
  // Serial.println(alfatyped);
  
 if (alfatyped != "000000") {
    if ((digitalRead(pressbutton1) == 0) && (digitalRead(pressbutton2) == 0) && (digitalRead(pressbutton3) == 0) && (digitalRead(pressbutton4) == 0) && (digitalRead(pressbutton5) == 0) && (digitalRead(pressbutton6) == 0)) {
      for (int i = 0; i < len; i++) {
        if (alfamatch[i] == alfatyped){
          if (numon == 0){
            if (capspos == 1){
              char uppercaseChar = alpha[i][0] - 32;
              Serial.print(uppercaseChar);
              Serial.flush();
            }
            else{
              Serial.print(alpha[i]);
              Serial.flush();
            }
          }
          else{
            Serial.print(nums[i]);
            //Serial.flush();
          }
        }
      }
      alfatyped = "000000";
    }
  }
  
  //if (digitalRead(backspace) == 1) {
  //  Serial.print("backspace");
  //  delay(200);
  //}
}
