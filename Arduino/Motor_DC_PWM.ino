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
    if(vel==1){
      vel = 45;
    }
    if(vel==2){
      vel = 90;
    }
    if(vel==3){
      vel = 170;
    }
    if(vel==4){
      vel = 200;
    }
    if(vel==5){
      vel = 255;
    }
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    analogWrite(p1, vel);  // Use analogWrite for PWM
  };

  void atras(int vel) {
    if(vel==1){
      vel = 45;
    }
    if(vel==2){
      vel = 90;
    }
    if(vel==3){
      vel = 170;
    }
    if(vel==4){
      vel = 200;
    }
    if(vel==5){
      vel = 255;
    }
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    analogWrite(p1, vel);  // Use analogWrite for PWM
  };

  void para() {
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
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
  void white() {
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
motor mt1(9, 8, 10);
motor mt2(6, 7, 5);
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
  //IMPRIMIR ENTRADAS ULTRASONICO
  // Serial.print(r);
  // Serial.print(", ");
  // Serial.print(f);
  // Serial.print(", ");
  // Serial.print(l);
  // Serial.println();

  //GIRO
  led.green();
  int velo = 150;
  atras2(velo,500);
  direita2(velo,0,600);
  // esquerda2(3,3,200);
  led.red();
  delay(5000);
  //TESTE LED
  // led.ramdColor();
  // delay(200);

  //PARA NA PAREDE E DÁ MEIA VOLTA
  // if(f>120){
  //   led.white();
  //   frente2(100);
  // }
  // else if (f > 70) {
  //   led.blue();
  //   frente2(70);
  // } else if (f > 15) {
  //   led.green();
  //   frente2(20);
  // } else {
  //   if (l < 50) {
  //     led.color(255, 255, 0);
  //     direita2(5, 5,  700);
  //     atras2(20, 500);
  //   } else if (r < 50) {
  //     led.color(255, 255, 0);
  //     esquerda2(5,5,700);
  //   }else{
  //     led.red();
  //     atras2(20,500);
  //     direita2(5, 5,  1000);
  //   }
  // }

  //DESACELERAR
  // float veloc;
  // if(f>100){
  //   frente2(5);
  //   led.green();
  // }
  // else if(f>35){
  //   led.color(255,255,0);
  //   frente2(2);
  // }else{
  //   led.red();
  //   para2();
  //   Serial.println("para");
  // }

  //SEGUE PAREDE
  int dist = 6;
  int tol = 3;
  if(r<5){
    esquerda2(3,3,200);
    frente2(500);
  }else if(l<5){
    direita2(3,3,200);
    frente2(500);
  }else{
    frente2(3);
  }

  //TESTE GIROS
  // led.green();
  // direita2(5,5,1000);
  // led.red();
  // delay(2000);
}

void direita2(int vel, int vel2, int del) {
  mt1.frente(vel);
  mt2.atras(vel2);
  delay(del);
  para2();
}
void esquerda2(int vel, int vel2, int del) {
  mt1.atras(vel);
  mt2.frente(vel2);
  delay(del);
  para2();
}

void frente2(int vel, int vel2, int del) {
  mt1.frente(vel);
  mt2.frente(vel2);
  delay(del);
  para2();
}

void atras2(int vel, int vel2, int del) {
  mt1.atras(vel);
  mt2.atras(vel2);
  delay(del);
  para2();
};
void frente2(int vel, int del) {
  mt1.frente(vel);
  mt2.frente(vel);
  delay(del);
  para2();
}

void atras2(int vel, int del) {
  mt1.atras(vel);
  mt2.atras(vel);
  delay(del);
  para2();
};

void direita2(int vel, int vel2) {
  mt1.frente(vel);
  mt2.atras(vel);
}
void esquerda2(int vel, int vel2) {
  mt1.atras(vel);
  mt2.frente(vel);
}

void frente2(int vel) {
  mt1.frente(vel);
  mt2.frente(vel);
}
void para2(int del) {
  mt1.para();
  mt2.para();
  delay(del);
};
void atras2(int vel) {
  mt1.atras(vel);
  mt2.atras(vel);
};
void para2() {
  mt1.para();
  mt2.para();
};
