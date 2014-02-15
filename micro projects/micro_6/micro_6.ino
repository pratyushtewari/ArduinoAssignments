const int one = 2;
const int two = 3;
const int three = 4;
const int four = 5;
const int six = 6;
const int seven = 7;
int direction = 1; // 1 for left.
const byte debugPin = 13;

void setup() {
  pinMode(one, OUTPUT);
  pinMode(two, OUTPUT);
  pinMode(three, OUTPUT);
  pinMode(four, OUTPUT);
  pinMode(six, INPUT);
  pinMode(seven, INPUT);
}

void loop() {
  if (direction == 0) {
    playleft();
  } else {
    playright();
  }
  if (digitalRead(six) == HIGH) {
   direction = 1;
  }
   if (digitalRead(seven) == HIGH) {
    direction = 0;
  }
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

void playleft (void) {
    glow(1, 0, 0, 0);
    delay(70);
    glow(0, 1, 0, 0);
    delay(70);
    glow(0, 0, 1, 0);
    delay(70);
    glow(0, 0, 0, 1);
    delay(70);
}  

void playright (void) {
    glow(0, 0, 0, 1);
    delay(70);
    glow(0, 0, 1, 0);
    delay(70);
    glow(0, 1, 0, 0);
    delay(70);
    glow(1, 0, 0, 0);
    delay(70);
} 
    
