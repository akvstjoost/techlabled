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
#define STARS 100

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

int starX[STARS];
float starY[STARS];
int starTime[STARS];



void setup() {
  matrix.begin();

  matrix.setTextWrap(false);


  // fill the screen with 'black'
  matrix.fillScreen(matrix.Color333(0, 0, 0));

  // draw some text!
  matrix.setTextSize(1);    // size 1 == 8 pixels high

  // print each letter with a rainbow color
  //writeTechlab();

  initStars();
}
float p;
float dx = 0.15;
float xpos;

void loop() {
  matrix.fillScreen(0);
  p = p + 0.10;

  updateStars();
  drawStars();
  // matrix.drawPixel( 5,  5,    matrix.Color333(7,7,7));
  // delay(1);
  //matrix.drawPixel( random(32),  random(16),    matrix.Color333(7,7,7));
  writeTechlab();
  delay(10);
  matrix.swapBuffers(false);
  xpos = xpos+ dx;
  if (xpos > 10) dx = -dx;
    if (xpos < 0) dx = -dx;
}

void writeTechlab() {
  matrix.setTextColor(matrix.Color333(7, 4, 0));
  matrix.setCursor(xpos, 4-abs(sin(p)*6));
  matrix.print('T');
  matrix.print('E');
  matrix.print('C');
  matrix.print('H');
  matrix.setCursor(9, 9);   // start at top left, with one pixel of spacing
  matrix.print('L');
  matrix.print('A');
  matrix.print('B');

}

void initStars() {
  for (int i = 0; i < STARS; i++) {
    starX[i] = int(random(32));
    starY[i] = random(24) - 4;
    starTime[i] = random(50);
  }
}

void updateStars() {
  for (int i = 0; i < STARS; i++) {
    starX[i] = starX[i] - 0.8;
    starTime[i] = starTime[i] + 2;
    if (starTime[i] > 50) {
      starTime[i] = 0;
      starX[i] = int(random(32));
      starY[i] = random(24);
    }
  }
}

void drawStars() {

  for (int i = 0; i < 100; i++) {
    int c = (50 - starTime[i]) / 5;
    matrix.drawPixel( starX[i],   starY[i],    matrix.Color333(c, c, c));
  }
}


