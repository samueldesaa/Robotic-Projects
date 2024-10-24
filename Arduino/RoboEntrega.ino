#include <Adafruit_TCS34725softi2c.h>

#include "Wire.h"
#include "Adafruit_TCS34725.h"

#define SDApinD A4
#define SCLpinD A5

#define SDApinE 5
#define SCLpinE 4

#define SDApinC 21
#define SCLpinC 20

// Configuração do sensor de cores
/* Initialise with specific int time and gain values and custom SDA / SCL pin */
Adafruit_TCS34725softi2c tcsD = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X, SDApinD, SCLpinD);
Adafruit_TCS34725softi2c tcsE = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X, SDApinE, SCLpinE);
Adafruit_TCS34725softi2c tcsC = Adafruit_TCS34725softi2c(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X, SDApinC, SCLpinC);



void setup() {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Sensor encontrado");
  } else {
    Serial.println("Sensor não encontrado, cheque suas conexões.");
    while (1);
  }
  analogWrite(7, 200);
}

void loop() {
  uint16_t r, g, b, c;

  // Obtém os dados brutos de vermelho, verde, azul e a claridade
  tcs.getRawData(&r, &g, &b, &c);

  // Envia os valores de cor RGB para o serial no formato "R,G,B"
  Serial.print(r); Serial.print(",");
  Serial.print(g); Serial.print(",");
  Serial.println(b);

  delay(50);  // Atraso para diminuir a frequência das leituras
}
