

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
for (int i = 0 ; i < 2000; ++i) {
drawScreen(O);
}
for (int i = 0 ; i < 2000; ++i) {
drawScreen(K);
}

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

