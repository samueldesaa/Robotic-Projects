#include <Ultrasonic.h>

class motor {
private:
  int m1, m2, p1;
public:
  motor(int M1, int M2, int P1) {
    m1 = M1;
    m2 = M2;
    p1 = P1;
    pinMode(m1, OUTPUT);
    pinMode(m2, OUTPUT);
    pinMode(p1, OUTPUT);
  };

  void frente(int vel) {
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    analogWrite(p1, vel);  // Use analogWrite for PWM
  };

  void atras(int vel) {
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    analogWrite(p1, vel);  // Use analogWrite for PWM
  };
};

void frente2(motor &m1, motor &m2, int vel) {
  m1.frente(vel);
  m2.frente(vel);
};

void atras2(motor &m1, motor &m2, int vel) {
  m1.atras(vel);
  m2.atras(vel);
};

//Criação de classe para led RGB
class ledRGB {
  int R, G, B;

public:
  //Construtor do LED
  ledRGB(int r, int g, int b) {
    R = r;
    G = g;
    B = b;
    pinMode(R, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(B, OUTPUT);
  }
  //Função de cor aleatória
  void ramdColor() {
    analogWrite(R, random(256));
    analogWrite(G, random(256));
    analogWrite(B, random(256));
  }
  //Função de escolher cor específica
  void color(int r, int g, int b) {
    analogWrite(R, r);
    analogWrite(G, g);
    analogWrite(B, b);
  }
  //Função de ligar todas as cores
  void OnALL() {
    digitalWrite(R, HIGH);
    digitalWrite(G, HIGH);
    digitalWrite(B, HIGH);
  }
  //Led vermelho
  void red() {
    digitalWrite(R, HIGH);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
  }
  //Led verde
  void green() {
    digitalWrite(R, LOW);
    digitalWrite(G, HIGH);
    digitalWrite(B, LOW);
  }
  //Led azul
  void blue() {
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, HIGH);
  }
  //Desligar
  void off() {
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
  }
};

//Determinado as portas do led
ledRGB led(14, 16, 15);

motor mt1(5, 4, 13);
motor mt2(3, 2, 12);
Ultrasonic direita(7, 6);
Ultrasonic front(9, 8);
Ultrasonic esquerda(11, 10);

void setup() {
  // put your setup code here, to run once:
  //semente do ramdom para maior diversidade de cores
  randomSeed(analogRead(0));
  //Iniciar monitor serial
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int fr = front.read();
  if (fr > 200) {
    frente2(mt1, mt2, 200);
    led.green();
  } else if (fr > 100) {
    frente2(mt1, mt2, 150);
    led.color(132, 255, 0);
  } else if (fr > 50) {
    frente2(mt1, mt2, 70);
    led.color(208, 255, 0);
  } else if (fr > 20) {
    frente2(mt1, mt2, 20);
    led.color(255, 132, 0);
  } else if (fr > 10) {
    led.color(255, 72, 0);
    while (fr < 250) {
      fr = front.read();  // Update fr inside the loop
      if (fr < 10) {
        atras2(mt1, mt2, 20);
        led.color(255, 72, 0);
      } else if (fr < 20) {
        atras2(mt1, mt2, 70);
        led.color(255, 132, 0);
      } else if (fr < 50) {
        atras2(mt1, mt2, 150);
        led.color(208, 255, 0);
      } else if (fr < 100) {
        atras2(mt1, mt2, 150);
        led.color(132, 255, 0);
      } else if (fr < 200) {
        atras2(mt1, mt2, 200);
        led.green();
      }
    }
  }
}
