//mini pushbuttons parallel to teensy pins:
int button[] = {35, 39, 14, 18, 20};
int ground[] = {33, 37, 16, 16, 22}; //third ground is actually a ground pin

void setup() {
  // put your setup code here, to run once:
  for (int x = 0; x < 5; x++) {
    pinMode(button[x], INPUT_PULLUP);
    pinMode(ground[x], OUTPUT);
    digitalWrite(ground[x], LOW);
  }
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}
int delayv=100;
void loop() {
  digitalWrite(13,HIGH);
  delay(50);
  digitalWrite(13,LOW);
  delay(delayv);
  // put your main code here, to run repeatedly:
  for (int x = 0; x < 5; x++) {
    if (digitalRead(button[x]) == LOW) {
    Serial.println(x);
    delayv = x*100;
    };
  }
}
