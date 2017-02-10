#include "cubeplex.h"

byte spectrum[24][3] = {
  {8,0,0},{7,1,0},{6,2,0},{5,3,0},{4,4,0},{3,5,0},{2,6,0},{1,7,0},
  {0,8,0},{0,7,1},{0,6,2},{0,5,3},{0,4,4},{0,3,5},{0,2,6},{0,1,7},
  {0,0,8},{1,0,7},{2,0,6},{3,0,5},{4,0,4},{5,0,3},{6,0,2},{7,0,1},
};

byte cube[4][4][4];

void setup() {
  initCube(); 
  randomSeed(analogRead(0));
  for (byte x = 0; x <= 3; x++) {
    for (byte y = 0; y <= 3; y++) {
      for (byte z = 0; z <= 3; z++) {
        cube[x][y][z] = random(24);
      }
    }
  }
}

void loop() {
  for (byte x = 0; x <= 3; x++) {
    for (byte y = 0; y <= 3; y++) {
      for (byte z = 0; z <= 3; z++) {
        byte val = cube[x][y][z];
        drawLed(red,  spectrum[val][0],x,y,z);
        drawLed(green,spectrum[val][1],x,y,z);
        drawLed(blue, spectrum[val][2],x,y,z);
        if ((x+y+z) % 2 == 0) { cube[x][y][z] = (val+1) % 24;}
        else                  { cube[x][y][z] = val == 0 ? 23 : val-1;}
      }
    }
  }
  flushBuffer();
  clearBuffer();
  delay(30);
}


