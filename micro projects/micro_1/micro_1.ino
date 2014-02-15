const int one = 2;
const int two = 3;
const int three = 4;
const int four = 5;
const byte debugPin = 13;

void setup() {
  pinMode(one, OUTPUT);
  pinMode(two, OUTPUT);
  pinMode(three, OUTPUT);
  pinMode(four, OUTPUT);  
}

void loop() {
  flick();
}
 

void flick (void) {
  glow(1, 0, 0, 0);
  delay(2000);
  glow(0, 1, 0, 0);
  delay(1000);
  glow(0, 0, 1, 0);
  delay(500);
  glow(0, 0, 0, 1);
  delay(250); 
  glow(1, 1, 1, 1);
  randomPlay() ;
}

void  glow(int a, int b, int c, int d) {
  if (a == 1) {
    digitalWrite(one, HIGH);
  } else {
    digitalWrite(one, LOW);
  }
  
  if (b == 1) {
    digitalWrite(two, HIGH);
  } else {
    digitalWrite(two, LOW);
  }
  
  if (c == 1) {
    digitalWrite(three, HIGH);
  } else {
    digitalWrite(three, LOW);
  }
  
  if (d == 1) {
    digitalWrite(four, HIGH);
  } else {
    digitalWrite(four, LOW);
  }
}

void randomPlay (void) {

  for (int i = 0; i <8; ++i) {
    glow(1, 0, 0, 0);
    delay(100);
    glow(0, 1, 0, 0);
    delay(100);
    glow(0, 0, 1, 0);
    delay(100);
    glow(0, 0, 0, 1);
    delay(100);
    glow(0, 0, 1, 0);
    delay(100);
    glow(0, 1, 0, 0);
    delay(100);
  }
}  
    
