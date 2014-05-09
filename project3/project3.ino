// Hydrometer sensor for plants
// By Pratyush Tewari

//number of LEDS to light up
int leds=0;




// 2-dimensional array of row pin numbers:
const int row[8] = {
  18,17,12,7,11,5,4,15};

// 2-dimensional array of column pin numbers:
const int col[8] = {
  10,16,9,14,2,8,3,6};
  float timeCount = 0;

// 2-dimensional array of pixels:
int O[8][8] = {
  {0,1,1,1,1,1,1,0},
  {1,1,1,1,1,1,1,1},
  {1,1,1,0,0,1,1,1},
  {1,1,0,0,0,0,1,1},
  {1,1,0,0,0,0,1,1},
  {1,1,1,0,0,1,1,1},
  {1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,0}
};           

int K[8][8] = {
  {0,1,1,0,0,0,1,1},
  {0,1,1,0,0,1,1,0},
  {0,1,1,0,1,1,0,0},
  {0,1,1,1,1,0,0,0},
  {0,1,1,0,1,1,0,0},
  {0,1,1,0,0,1,1,0},
  {0,1,1,0,0,0,1,1},
  {0,1,1,0,0,0,0,1}
}; 

void setup() {
  Serial.begin(9600);
  // initialize the I/O pins as outputs
  // iterate over the pins:
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT); 
    pinMode(row[thisPin], OUTPUT); 
    digitalWrite(row[thisPin], HIGH); 
    digitalWrite(col[thisPin], LOW); 
  }
}

void loop() {


// read the input on analog pin 0:
  int sensorValue = analogRead(A6);
    
  sensorValue = constrain(sensorValue, 0, 730);
  // print out the value you read:
  //Serial.println(sensorValue);

  //map the value to a percentage
  leds = map(sensorValue, 0, 730, 1, 64);
  
  // print out the soil water percentage you calculated:
  Serial.println(leds);
  
 for (int delay = 0; delay < 500; ++delay) {
  drawLEDS(leds);
 }

  

}

//Light up number of LEDS
void drawLEDS(int leds) {
  boolean complete = false;
  for(int i = 0; i < 8 && !complete; i++) {    
    for (int j = 0; j < 8; j++) {
      if (--leds <= 0 ) {
        complete = true;
        break;
      }
       digitalWrite(col[j], HIGH);
       digitalWrite(row[i], LOW);
       //delay(.999);
       digitalWrite(col[j], LOW);
       digitalWrite(row[i], HIGH);
      
    }
  }
  
}
void drawScreen(int character[8][8]) {
  for(int i = 0; i < 8; i++) {    
    for (int j = 0; j < 8; j++) {
      if ( character[i][j] == 1) {
      // draw some letter bits
       digitalWrite(col[j], HIGH);
       digitalWrite(row[i], LOW);
       //delay(.999);
       digitalWrite(col[j], LOW);
       digitalWrite(row[i], HIGH);
      }
    }
  }
}

