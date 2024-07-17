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
    if (vel == 1) {
      vel = 45;
    }
    if (vel == 2) {
      vel = 90;
    }
    if (vel == 3) {
      vel = 170;
    }
    if (vel == 4) {
      vel = 200;
    }
    if (vel == 5) {
      vel = 255;
    }
    // if( p1 == 7){
    //   Serial.println("É o motor forte");
    //   vel-=80;
    // }
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    analogWrite(p1, vel);  // Use analogWrite for PWM
  };

  void frente(int vel, int del) {
    frente(vel);
    delay(del);
    para();
  }

  void atras(int vel) {
    if (vel == 1) {
      vel = 45;
    }
    if (vel == 2) {
      vel = 90;
    }
    if (vel == 3) {
      vel = 170;
    }
    if (vel == 4) {
      vel = 200;
    }
    if (vel == 5) {
      vel = 255;
    }
    // if( p1 == 7){
    //   Serial.println("É o motor forte");
    //   vel-=80;
    // }
    digitalWrite(m1, HIGH);
    digitalWrite(m2, LOW);
    analogWrite(p1, vel);  // Use analogWrite for PWM
  };
  void atras(int vel, int del) {
    atras(vel);
    delay(del);
    para();
  }

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
ledRGB led(3, 4, 2);
motor mt1(8, 7, 5);
motor mt2(9, 10, 6);
Ultrasonic right(24, 22);
Ultrasonic left(26, 28);
Ultrasonic front(32, 30);

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

  //TESTE LED
  // led.blue();
  // delay(200);

  //TESTE MOTOR
  // mt1.frente(3);
  // mt2.frente(3);
  frente2(3);

  //GIRO
  // led.green();
  // int velo = 2;
  // direita2(velo,velo,900);
  // led.red();
  // delay(5000);

  //PARA NA PAREDE E DÁ MEIA VOLTA
  // if( f > 20){
  //   led.green();
  //   frente2(5);
  //   while(f>20){
  //     f = front.read();
  //   }
  // }else{
  //   led.red();
  //   para2();
  //   rotDireita();
  //   while(true);
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
  // int dist = 8;
  // int v = 150;
  // if (f < dist+5) {
  //   led.color(142, 3, 252);
  //   atras2(500);
  //   if (r > 15) {
  //     direita2(v, v, 200);
  //   } else if (l > 15) {
  //     esquerda2(v, v, 200);
  //   } else if (r > 30 && l > 30) {
  //     led.color(255, 255, 0);
  //   } else {
  //     direita2(v, v, 400);
  //   }
  // } else if (r < dist) {
  //   led.green();
  //   frente2(0,v,200);
  //   frente2(v,500);
  //   // }else if(r>dist+5){
  //   //   frente2(3,200);
  //   //   direita2(3,3,200);
  // } else if (l < dist) {
  //   led.red();
  //   frente2(v,0,200);
  //   frente2(v,500);
  //   // }else if(l>dist+5){
  //   //   frente2(3,200);
  //   //   esquerda2(3,3,200);
  // } else {
  //   led.white();
  //   frente2(v);
  // }
}

void rotDireita() {
  direita2(2, 2, 1000);
}
void rotEsquerda() {
  esquerda2(2, 2, 1000);
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
