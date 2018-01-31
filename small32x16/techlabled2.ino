// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
#define STARS 60

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

float starX[STARS];
float starY[STARS];
float starSpeed[STARS];
boolean colorSwap = true;
int c1,c2,c3;


void setup() {
  matrix.begin();

  matrix.setTextWrap(false);


  // fill the screen with 'black'
  matrix.fillScreen(matrix.Color333(0, 0, 0));

  // draw some text!
  matrix.setTextSize(1);    // size 1 == 8 pixels high

  // print each letter with a rainbow color
  //writeTechlab();
  for (int i = 0; i < STARS; i++) {
    starX[i] = random(32);
    starY[i] = random(16);
    starSpeed[i] = (random(4) * random(4) + 1) / 8.0;
  }
}
float p;
float dx = 0.15;
float xpos;

void loop() {
  matrix.fillScreen(0);
  p = p + 0.17;
  if (p > (PI)) {
    p = p - PI;
    colorSwap = !colorSwap;
    c1 = random(10);
        c2 = random(10);
            c3 = random(10);
    
  }
  updateStars();
  drawStars();
  // matrix.drawPixel( 5,  5,    matrix.Color333(7,7,7));
  // delay(1);
  //matrix.drawPixel( random(32),  random(16),    matrix.Color333(7,7,7));
  writeTechlab();
  delay(8);
  matrix.swapBuffers(false);
  xpos = xpos + dx;
  if (xpos > 10) dx = -dx;
  if (xpos < 0) dx = -dx;
}

void writeTechlab() {
  matrix.setTextColor(matrix.Color333(7, 4, 0));

  matrix.setCursor(xpos, 4 - abs(sin(p) * 6));
  matrix.print('T');
  matrix.print('E');
  matrix.print('C');
  matrix.print('H');
  int y = 8;
  if (p < 0.5) y = 9;
  //if (!colorSwap) matrix.setTextColor(matrix.Color333(7, 0, 3));
  //  if (colorSwap) matrix.setTextColor(matrix.Color333(0, 4, 7));

    matrix.setTextColor(matrix.Color333(c1, c2, c3));
    matrix.setCursor(9, y);   // start at top left, with one pixel of spacing
  matrix.print('L');
  matrix.print('A');
  matrix.print('B');

}





void updateStars() {
  for (int i = 0; i < STARS; i++) {
    starX[i] = starX[i] - starSpeed[i];

    if (starX[i] < 0) {
      starX[i] = 33;

    }
  }
}

void drawStars() {

  for (int i = 0; i < STARS; i++) {
    //int c = (50 - starTime[i]) / 5;
    int c = starSpeed[i] * 2 + 0.1;
    matrix.drawPixel( int(starX[i]),  int( starY[i]),    matrix.Color333(c, c, c ));
  }
}



