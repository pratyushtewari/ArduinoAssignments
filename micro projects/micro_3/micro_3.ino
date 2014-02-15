const int one = 2;
const int two = 3;
const int three = 4;
const int four = 5;
const int six = 6;
const int seven = 7;
int direction = 1; // 1 for left.
const byte debugPin = 13;

int potPin = 14;    // select the input pin for the potentiometer
int val = 0;       // variable to store the value coming from the sensor


void setup() {
  pinMode(one, OUTPUT);
  pinMode(two, OUTPUT);
  pinMode(three, OUTPUT);
  pinMode(four, OUTPUT);
  pinMode(six, INPUT);
  pinMode(seven, INPUT);
}

void loop() {
  val = analogRead(potPin);
  playleft(val);
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

void playleft (int time) {
    glow(1, 0, 0, 0);
    delay(time);
    glow(0, 1, 0, 0);
    delay(time);
    glow(0, 0, 1, 0);
    delay(time);
    glow(0, 0, 0, 1);
    delay(time);
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
    
