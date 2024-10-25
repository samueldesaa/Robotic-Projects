#include <Adafruit_TCS34725.h>

// #include <Adafruit_TCS34725softi2c.h>
int ledS = 6;
int lumin = 100;
int segueE = 7;
int segueD = 8;
int porta = 9;
int velE = 2;
int velD = 3;
int motoD1 = 22;
int motoD2 = 24;
int motoE1 = 26;
int motoE2 = 28;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_1X);
// Adafruit_TCS34725softi2c tcsC = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X, 13, 12);
// Adafruit_TCS34725softi2c tcsE = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X, 5, 4);
// Adafruit_TCS34725softi2c tcsD = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X, 7, 6);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledS, OUTPUT);
  analogWrite(ledS, lumin);
  tcs.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  Serial.print(r);
  Serial.print(",");
  Serial.print(g);
  Serial.print(",");
  Serial.println(b);
}
