int dataPin = 28;
int clockPin  = 30;
int latchPin = 31;
int enablePin = 32;
const int numPixels = 256;
unsigned int pixels[numPixels];

void setup() {
  // put your setup code here, to run once:
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);

}

void loop() {
  makegradient();
  writePixels();
}

float f = 0;
void makegradient() {
  f = f + 0.001;
  if (f>32) f =0;
  int x = int(f);
  for (int n = 0; n < 160; n++) {
    setPixel(n, n % x, (n / 3) % x, (n / 5) % x);
  }
}

void setPixel(int n, unsigned int r, unsigned int g, unsigned int b) {
  // r, g and b are 3 or 4-bit values
  pixels[n] = (r << 8) + (g << 4) + b;
}

byte getR(unsigned int pixel) {
  return pixel >> 8;
}

byte getG(unsigned int pixel) {
  return (pixel >> 4) & B00001111;
}

byte getB (unsigned int pixel) {
  return pixel & B00001111;
}

byte counter;
void writePixels() {

  for (int n = 0; n < numPixels / 2; n++) {
    byte out = 0; //XRGBXRGB
    byte r1 = getR(pixels[n * 2]);
    byte g1 = getG(pixels[n * 2]);
    byte b1 = getB(pixels[n * 2]);
    byte r2 = getR(pixels[n * 2 + 1]);
    byte g2 = getG(pixels[n * 2 + 1]);
    byte b2 = getB(pixels[n * 2 + 1]);
    if (r1 > counter) out |= 1 << 6;
    if (g1 > counter) out |= 1 << 5;
    if (b1 > counter) out |= 1 << 4;
    if (r2 > counter) out |= 1 << 2;
    if (g2 > counter) out |= 1 << 1;
    if (b2 > counter) out |= 1;
    shiftOut(dataPin, clockPin, MSBFIRST, out);
  }
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);

  counter = counter + 1;
  if (counter >= 16) counter = 0; //for 4 bit color
}
