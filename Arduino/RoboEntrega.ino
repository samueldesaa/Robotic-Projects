#include <Adafruit_TCS34725.h>

int ledS = 6;      // LED de iluminação
int lumin = 100;   // Brilho do LED
int velE = 2;      // Velocidade motor esquerdo
int velD = 3;      // Velocidade motor direito
int motoD1 = 22;   // Pino motor direito
int motoD2 = 24;
int motoE1 = 26;   // Pino motor esquerdo
int motoE2 = 28;

// Inicializa o sensor TCS34725
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_1X);

void setup() {
  Serial.begin(9600);
  
  // Configuração do LED
  pinMode(ledS, OUTPUT);
  analogWrite(ledS, lumin);

  // Inicializa os motores
  pinMode(motoD1, OUTPUT);
  pinMode(motoD2, OUTPUT);
  pinMode(motoE1, OUTPUT);
  pinMode(motoE2, OUTPUT);
  
  // Configura a velocidade dos motores
  pinMode(velE, OUTPUT);
  pinMode(velD, OUTPUT);
  
  // Inicia o sensor de cor
  if (tcs.begin()) {
    Serial.println("Sensor TCS34725 detectado!");
  } else {
    Serial.println("Sensor TCS34725 não detectado. Verifique a conexão.");
    while (1); // Aguarda indefinidamente se o sensor não for encontrado
  }
}

void loop() {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  
  // Imprime os valores RGB para diagnóstico
  Serial.print("R: "); Serial.print(r);
  Serial.print(" G: "); Serial.print(g);
  Serial.print(" B: "); Serial.println(b);

  int limite = 500;  // Ajuste conforme necessário

  if (r < limite && g < limite && b < limite) {
    // Linha detectada (preto ou cor mais escura)
    moverParaFrente();
  } else if (r >= limite && g < limite && b < limite) {
    // Condição de cor detectada indicando para virar à direita
    virarDireita();
  } else if (r < limite && g >= limite && b >= limite) {
    // Condição de cor detectada indicando para virar à esquerda
    virarEsquerda();
  } else {
    // Nenhuma condição específica atendida - parar
    parar();
  }

  delay(100);  // Ajuste conforme a velocidade desejada do robô
}

// Funções para controlar o movimento dos motores
void moverParaFrente() {
  analogWrite(velE, 150);  // Ajuste da velocidade do motor esquerdo
  analogWrite(velD, 150);  // Ajuste da velocidade do motor direito
  
  digitalWrite(motoD1, HIGH);
  digitalWrite(motoD2, LOW);
  digitalWrite(motoE1, HIGH);
  digitalWrite(motoE2, LOW);
}

void virarDireita() {
  analogWrite(velE, 150);  // Reduz a velocidade do motor esquerdo
  analogWrite(velD, 0);    // Para o motor direito para virar

  digitalWrite(motoD1, LOW);
  digitalWrite(motoD2, LOW);
  digitalWrite(motoE1, HIGH);
  digitalWrite(motoE2, LOW);
}

void virarEsquerda() {
  analogWrite(velE, 0);    // Para o motor esquerdo
  analogWrite(velD, 150);  // Ajuste da velocidade do motor direito

  digitalWrite(motoD1, HIGH);
  digitalWrite(motoD2, LOW);
  digitalWrite(motoE1, LOW);
  digitalWrite(motoE2, LOW);
}

void parar() {
  analogWrite(velE, 0);  // Para ambos os motores
  analogWrite(velD, 0);

  digitalWrite(motoD1, LOW);
  digitalWrite(motoD2, LOW);
  digitalWrite(motoE1, LOW);
  digitalWrite(motoE2, LOW);
}
