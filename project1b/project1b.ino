#define LED_ON 1
#define LED_OFF 0
// 2-dimensional array of row pin numbers:
const int row[8] = {18,17,12,7,11,5,4,15};
// 2-dimensional array of column pin numbers:
const int col[8] = {10,16,9,14,2,8,3,6};



// Button pin
const int button_Pin = 19;



// direction
const int TOP    = 0;
const int RIGHT  = 1;
const int BOTTOM = 2;
const int LEFT   = 3;

// Snake
const int MAX_SNAKE_LENGTH = 10;

int direction = TOP;                               // direction of movement
int buttonState = LOW;
float timeCount = 0;
int snakeX[MAX_SNAKE_LENGTH];                      // X-coordinates of snake
int snakeY[MAX_SNAKE_LENGTH];                      // Y-coordinates of snake
int snakeLength = 1;                               


boolean buttonRead = false;                        // is button already read 

unsigned long prevTime = 0;                        // for gamedelay (ms)
unsigned long delayTime = 500;                     // Game step in ms

int pointX, pointY;
unsigned long pointPrevTime = 0;
unsigned long pointBlinkTime = 1000/250;
int pointLed = LED_ON;


void reset() {
  direction = TOP;                               // direction of movement
  buttonState = LOW;
  timeCount = 0;
  snakeLength = 1;                               
  buttonRead = false;                        // is button already read 
  prevTime = 0;                        // for gamedelay (ms)
  delayTime = 500;                     // Game step in ms
  pointPrevTime = 0;
  pointBlinkTime = 1000/250;
  pointLed = LED_ON;
  clear();
    snakeX[0] = 4;
    snakeY[0] = 6;
    for(int i=1; i<MAX_SNAKE_LENGTH; i++){
      snakeX[i] = snakeY[i] = -1;
    }
    newPoint();
}  


void setup() {
  Serial.begin(9600);
  Serial.println("Game is started");
  //pinMode(speakerOut, OUTPUT);
  // initialize the I/O pins as outputs
  // iterate over the pins:
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT); 
    pinMode(row[thisPin], OUTPUT); 

    digitalWrite(row[thisPin], HIGH); 
    digitalWrite(col[thisPin], LOW); 
  }

  // init snake
  snakeX[0] = 4;
  snakeY[0] = 6;
  for(int i=1; i<MAX_SNAKE_LENGTH; i++){
    snakeX[i] = snakeY[i] = -1;
  }

  newPoint();
  
}


void clear (){
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    digitalWrite(row[thisPin], HIGH); 
    digitalWrite(col[thisPin], LOW);
}
}


void loop() {
  checkButtons();
  unsigned long currentTime = millis();
  if(currentTime - prevTime >= delayTime){
    nextstep(); 
    buttonRead = false;
    prevTime = currentTime;
  }
  draw();
}


void checkButtons(){
  if(!buttonRead){
    int currentDirection = direction;
     if(buttonClicked()){
      direction++;
      if(direction > 3){
        direction = TOP;
      }
    }
    buttonRead = (currentDirection != direction);
  }
}

void draw(){
  clear();
  drawSnake();
  drawpoint();
}

void drawSnake(){
  for(int i=0; i<snakeLength; i++){
    digitalWrite(row[snakeX[i]], LOW); 
    digitalWrite(col[snakeY[i]], HIGH);
     delay(.025);
    digitalWrite(row[snakeX[i]], HIGH); 
    digitalWrite(col[snakeY[i]], LOW);
  }
}

void drawpoint(){
  if(inPlayField(pointX, pointY)){
    unsigned long currenttime = millis();
    if(currenttime - pointPrevTime >= pointBlinkTime){
      pointLed = (pointLed == LED_ON) ? LED_OFF : LED_ON;
      pointPrevTime = currenttime;
     
    }
     if(pointLed) {
      digitalWrite(row[pointX], LOW); 
      digitalWrite(col[pointY], HIGH);
      } else {
      digitalWrite(row[pointX], HIGH); 
      digitalWrite(col[pointY], LOW);
      }
    
  }
}

boolean inPlayField(int x, int y){
  return (x>=0) && (x<8) && (y>=0) && (y<8);
}


void nextstep(){
  //increment all the x's and y's
  for(int i=snakeLength-1; i>0; i--){
    snakeX[i] = snakeX[i-1];
    snakeY[i] = snakeY[i-1];
  }
  
  //Based on the direction, change the value of the pixel.
  switch(direction){
    case TOP:
      snakeY[0] = snakeY[0]-1;
      break;
    case RIGHT:
      snakeX[0] = snakeX[0]+1;
      break;
    case BOTTOM:
      snakeY[0] = snakeY[0]+1;
      break;
    case LEFT:
      snakeX[0]=snakeX[0]-1;
      break;
  }

  // if snakes meets the point
  if((snakeX[0] == pointX) && (snakeY[0] == pointY)){
    snakeLength++;
    // make new point if the snake is not max.
    if(snakeLength < MAX_SNAKE_LENGTH){      
      newPoint();
    } 
    else {
      pointX = pointY = -1;
      clear();
      delay(2000);
      reset();
    }
  }
}

// return a coordinate which is not part of the snake.
void newPoint(){
  int x, y;
  x = random(1, 6);
  y = random(1, 6);
  while(isPartOfSnake(x, y)){
    x = random(1, 6);
    y = random(1, 6);
  }

  pointX = x;
  pointY = y;
}


boolean isPartOfSnake(int x, int y){
  for(int i=0; i<snakeLength-1; i++){
    if((x == snakeX[i]) && (y == snakeY[i])){
      return true;
    }
  }
  return false;
}




boolean buttonClicked(){
  // current state
  int state = digitalRead(button_Pin);
  boolean buttonClick = false;
  // button has pressed
  if(buttonState == HIGH){
    if(state == LOW){
      buttonClick = true;
    }
  }
  buttonState = state; 
  return buttonClick;
}


