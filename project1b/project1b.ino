/*
Arduino Snake 
by Pratyush Tewari
*/

#define LED_ON 1
#define LED_OFF 0
// 2-dimensional array of row pin numbers:
const int row[8] = {18,17,12,7,11,5,4,15};
// 2-dimensional array of column pin numbers:
const int col[8] = {10,16,9,14,2,8,3,6};

// Button pin
const int button_Pin = 19;

/* the int defines the direction the snake will move
TOP  0
RIGHT 1
BOTTOM  2
LEFT  3
*/



 int A[8][8] = {
{0,1,1,1,1,1,1,0},
{1,0,0,0,0,0,0,1},
{1,0,1,0,0,1,0,1},
{1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,1},
{1,0,0,1,1,0,0,1},
{1,0,0,0,0,0,0,1},
{0,1,1,1,1,1,1,0}
};

 int B[8][8] = {
{0,1,1,1,1,1,1,0},
{1,0,0,0,0,0,0,1},
{1,0,1,0,0,1,0,1},
{1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,1},
{1,0,1,1,1,1,0,1},
{1,0,0,0,0,0,0,1},
{0,1,1,1,1,1,1,0}
};

 int C[8][8] = {
{0,1,1,1,1,1,1,0},
{1,0,0,0,0,0,0,1},
{1,0,1,0,0,1,0,1},
{1,0,0,0,0,0,0,1},
{1,0,1,0,0,1,0,1},
{1,0,1,1,1,1,0,1},
{1,0,0,0,0,0,0,1},
{0,1,1,1,1,1,1,0}
};

 int D[8][8] = {
{0,1,1,1,1,1,1,0},
{1,0,0,0,0,0,0,1},
{1,0,1,0,0,1,0,1},
{1,0,0,0,0,0,0,1},
{1,0,1,0,0,1,0,1},
{1,0,0,1,1,0,0,1},
{1,0,0,0,0,0,0,1},
{0,1,1,1,1,1,1,0}
};

 int head[8][8] = {
{0,1,1,1,1,1,1,0},
{1,0,0,0,0,0,0,1},
{1,0,1,0,0,1,0,1},
{1,0,0,1,1,0,0,1},
{0,1,0,0,0,0,1,0},
{0,1,0,1,1,0,1,0},
{0,0,1,0,0,1,0,0},
{0,0,1,1,1,1,0,0}
};

 int x[8][8] ={
{1,1,0,0,0,0,1,1},
{1,1,0,0,0,0,1,1},
{0,0,1,0,0,1,0,0},
{0,0,0,1,1,0,0,0},
{0,0,0,1,1,0,0,0},
{0,0,1,0,0,1,0,0},
{1,1,0,0,0,0,1,1},
{1,1,0,0,0,0,1,1}
};

unsigned long prevTime = 0;                        // for gamedelay (ms)
unsigned long delayTime = 500;                     // Game step in ms

void smile() {
  //speed up the game because you crossed a level
  delayTime /= 2;
  for (int j = 0; j < 4; ++j ) {
  for (int i = 0 ; i < 250; ++i) {
  drawScreen(A);
  }
  for (int i = 0 ; i < 250; ++i) {
  drawScreen(B);
  }
  for (int i = 0 ; i < 250; ++i) {
  drawScreen(C);
  }
  for (int i = 0 ; i < 250; ++i) {
  drawScreen(D);
  }
  }
}

void skull() {
   // Draw the skull to show death.
  for (int j = 0; j < 4; ++j) {
 
  for (int i = 0 ; i < 1000; ++i) {
  drawScreen(head);
  }
  for (int i = 0 ; i < 1000; ++i) {
  drawScreen(x);
  }
  }
  delay(500);
}

// Snake
const int MAX_SNAKE_LENGTH = 10;

int direction = 0;                               // direction of movement
int buttonState = LOW;
float timeCount = 0;

// snakeX[i] = "number" mean the x co-ordinates of the snake where the LED's are on.
// snakeX[i] = -1 mean the x co-ordinates of the snake where the LED's are off.

int snakeX[MAX_SNAKE_LENGTH];                      // X-coordinates of snake
int snakeY[MAX_SNAKE_LENGTH];                      // Y-coordinates of snake
int snakeLength = 1;                               


boolean buttonRead = false;                        // is button already read 



int pointX, pointY;
unsigned long pointPrevTime = 0;
unsigned long pointBlinkTime = 1000/250;


//Reset the game to start again.
void reset() {
  delayTime = 500;
  direction = random(0,4)  ;                            // direction of movement
  buttonState = LOW;
  timeCount = 0;
  snakeLength = 1;                               
  buttonRead = false;                        // is button already read 
  prevTime = 0;                        // for gamedelay (ms)

  clear();
    snakeX[0] = random(1, 6);
    snakeY[0] = random(1, 6);
    for(int i=1; i<MAX_SNAKE_LENGTH; i++){
      snakeX[i] = snakeY[i] = -1;
    }
    newPoint();
}  


void setup() {
  direction = random(0,4)  ; 
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
      snakeX[0] = random(1, 6);
    snakeY[0] = random(1, 6);
  for(int i=1; i<MAX_SNAKE_LENGTH; i++){
    snakeX[i] = snakeY[i] = -1;
  }
  newPoint();
  
}

//Clear the LED Matrix
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
    clear();
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
        direction = 0;
      }
    }
    buttonRead = (currentDirection != direction);
  }
}

void draw(){
  clear();
  drawSnake();
  clear();
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
    digitalWrite(row[pointX], LOW); 
    digitalWrite(col[pointY], HIGH);
     delay(.025);
    digitalWrite(row[pointX], HIGH); 
    digitalWrite(col[pointY], LOW);
}


// check if the number is within the LED matrix coordinates
boolean inPlayField(int x, int y){
  return (x>=0) && (x<8) && (y>=0) && (y<8);
}


void nextstep(){
  //increment all the x's and y's
  for(int i=snakeLength-1; i>0; i--){
    snakeX[i] = snakeX[i-1];
    snakeY[i] = snakeY[i-1];
  }
  
  //Based on the , change the value of the pixel.
  switch(direction){
    case 0:
      snakeY[0] = snakeY[0]-1;
      //reset if snake goes beyond top row
      if (snakeY[0] < 0 ) { skull();reset();
      }
      break;
    case 1:
      snakeX[0] = snakeX[0]+1;
            //reset if snake goes beyond rightest column
      if (snakeX[0] > 7 ) { skull();reset();
      }
      break;
    case 2:
      snakeY[0] = snakeY[0]+1;
            //reset if snake goes beyond bottom row
       if (snakeY[0] > 7 ) { skull();reset();
      }
      break;
    case 3:
      snakeX[0]=snakeX[0]-1;
            //reset if snake goes beyond leftest column
      if (snakeX[0] < 0 ) { skull();reset();
      }
      break;
  }

  // if snakes meets the point
  if((snakeX[0] == pointX) && (snakeY[0] == pointY)){
    snakeLength++;
     tone(20, 208,250);
    // make new point if the snake is not max.
    if(snakeLength < MAX_SNAKE_LENGTH){      
      newPoint();
    } 
    else {
      pointX = pointY = -1;  
      smile();  
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

void drawScreen(int character[8][8]) {
  for(int i = 0; i < 8; i++) {    
    for (int j = 0; j < 8; j++) {
      if ( character[i][j] == 1) {
      // draw some letter bits
       digitalWrite(col[j], HIGH);
       digitalWrite(row[i], LOW);
       delay(.025);
       digitalWrite(col[j], LOW);
       digitalWrite(row[i], HIGH);
      }
    }
  }
}


