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

  void para(){
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
  }
};

void frente2(motor &m1, motor &m2, int vel) {
  m1.frente(vel);
  m2.frente(vel);
};

void atras2(motor &m1, motor &m2, int vel) {
  m1.atras(vel);
  m2.atras(vel);
};
void para2(motor &m1, motor &m2){
  m1.para();
  m2.para();
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
ledRGB led(6, 8, 7);
motor mt1(5, 4, 13);
motor mt2(3, 2, 12);
Ultrasonic right(24, 22);
Ultrasonic front(26, 28);
Ultrasonic left(11, 9);

void setup() {
  // put your setup code here, to run once:
  //semente do ramdom para maior diversidade de cores
  randomSeed(analogRead(0));
  //Iniciar monitor serial
  Serial.begin(9600);
  int f;

}

void loop() {
  // put your main code here, to run repeatedly:
  int f = front.read();
  Serial.println(f);
  if(f>30){
    led.green();
    frente2(mt1,mt2,150);
  }else{
    led.red();
    para2(mt1,mt2);
  }
}
