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
    vel = (int)(80+((vel%100)*1.75));
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    analogWrite(p1, vel);  // Use analogWrite for PWM
  };

  void atras(int vel) {
    vel = (int)(80+((vel%100)*1.75));
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    analogWrite(p1, vel);  // Use analogWrite for PWM
  };

  void para(){
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
  }
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
ledRGB led(3, 2, 4);
motor mt1(7, 6, 5);
motor mt2(8, 9, 10);
Ultrasonic right(24, 22);
Ultrasonic front(28, 26);
Ultrasonic left(30, 32);

void setup() {
  // put your setup code here, to run once:
  //semente do ramdom para maior diversidade de cores
  randomSeed(analogRead(0));
  //Iniciar monitor serial
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int f = front.read();
  int l = left.read();
  int r = right.read();
  if(f>100){
    led.green();
    frente2(70);
  }else if(f>50){
    led.color(255,255,0);
    frente2(40);
  }else{
    led.red();
    atras2(20);
    delay(2000);
    mt1.frente(20);
    delay(2000);
    mt2.atras(20);
    delay(2000);
  }
}

void frente2(int vel) {
  mt1.frente(vel);
  mt2.frente(vel);
}

void atras2(int vel) {
  mt1.atras(vel);
  mt2.atras(vel);
};
void para2(){
  mt1.para();
  mt2.para();
};
