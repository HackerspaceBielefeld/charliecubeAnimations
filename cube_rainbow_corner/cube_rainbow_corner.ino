#include "cubeplex.h"

byte spectrum[24][3] = {
  {8,0,0},{7,1,0},{6,2,0},{5,3,0},{4,4,0},{3,5,0},{2,6,0},{1,7,0},
  {0,8,0},{0,7,1},{0,6,2},{0,5,3},{0,4,4},{0,3,5},{0,2,6},{0,1,7},
  {0,0,8},{1,0,7},{2,0,6},{3,0,5},{4,0,4},{5,0,3},{6,0,2},{7,0,1},
};
byte offset    = 0;
byte shift[3]  = {0,0,0};
bool mirror[3] = {false,false,false};
byte anim[8]   = {0,2,0,1,0,2,0,1};

void setup() {initCube(); }

void drawCube() {
  for (byte x = 0; x <= 3; x++) {
    for (byte y = 0; y <= 3; y++) {
      for (byte z = 0; z <= 3; z++) {
        byte xx = shift[0] > x ? 0 : x - shift[0];
        byte yy = shift[1] > x ? 0 : y - shift[1];
        byte zz = shift[2] > x ? 0 : z - shift[2];
        xx = mirror[0] ? 3 - xx : xx;
        yy = mirror[1] ? 3 - yy : yy;
        zz = mirror[2] ? 3 - zz : zz;
        byte val = (offset + xx + yy + zz) % 24;
        drawLed(red,  spectrum[val][0],x,y,z);
        drawLed(green,spectrum[val][1],x,y,z);
        drawLed(blue, spectrum[val][2],x,y,z);
      }
    }
  }
  flushBuffer();
  clearBuffer();
  offset = offset == 0 ? 23 : offset - 1;
  delay(100);  
}

void moveAxis(byte axis) {
  for (int n = 1;n <= 3; n++) {
    shift[axis] = n;
    drawCube();
  }
  mirror[axis] = not mirror[axis];
  drawCube();
  for (int n = 2;n >= 0; n--) {
    shift[axis] = n;
    drawCube();
  }
}

void loop() {
  for (byte n = 0;n <= 7;n++) {
    for (byte m = 0;m < 50;m++) drawCube();
    moveAxis(anim[n]);
  }
}


