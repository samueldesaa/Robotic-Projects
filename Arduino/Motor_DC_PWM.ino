#include <Ultrasonic.h>

class motor {
private:
  int m1, m2, p1;
  float diminuicao = 0.36;
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
    //Se necessário diminuição de velocidade em um dos motores
    if (p1 == 2) {
      Serial.println("É o motor forte");
      vel -= vel * diminuicao;
    }
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
    //Se necessário diminuição de velocidade em um dos motores
    if (p1 == 2) {
      Serial.println("É o motor forte");
      vel -= vel * diminuicao;
    }
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


int f, r, l;
//Determinado as portas do led
// ledRGB led(3, 4, 2);
int botao = 53;
motor mt1(7, 6, 3);
motor mt2(5, 4, 2);
Ultrasonic right(24, 22);
Ultrasonic left(26, 28);
Ultrasonic front(32, 30);

void setup() {
  //configurando o botão
  pinMode(botao, INPUT_PULLUP);
  //semente do ramdom para maior diversidade de cores
  randomSeed(analogRead(0));
  //Iniciar monitor serial
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(botao) == LOW) {
    delay(2000);
    while (true) {
      // put your main code here, to run repeatedly:
      //Leitura de ULTRASONICOS
      f = front.read();
      l = left.read();
      r = right.read();


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

      //Frente e PARA
      // frente2(4);
      // while (true) {
      //   f = front.read();
      //   if (f < 20 || digitalRead(botao) == LOW) {
      //     direita2(2, 2, 600);
      //     break;
      //   }
      // }
      // break;

      //GIRO
      // led.green();
      // int velo = 2;
      // direita2(velo,velo,820);
      // rotDireita();
      // break;
      // led.red();
      // delay(5000);

      //PARA NA PAREDE E DÁ MEIA VOLTA
      // if( f > 20){
      //   frente2(2);
      //   while(f>20){
      //     f = front.read();
      //   }
      // }else{
      //   para2();
      //   rotDireita();
      // }

      //Graus
      rotacao();

      //SEGUE PAREDE
      // if (f < 15) {
      //   verificaCantos();
      //   frente2(100, 500);
      // } else if (l < 6) {
      //   frente2(150, 110, 1000);
      // } else if (r < 6) {
      //   frente2(110, 150, 1000);
      // } else if (r > 70 && l > 70 && f > 70) {
      //   break;
      // } else {
      //   frente2(100);
      // }
    }
  }
}

void rotacao() {
  while (f < 30) {
    l = left.read(), r = right.read() , f = front.read();
    esquerda2(70,70);
  }
  para2();
}

void verificaCantos() {
  if (l < 15 && r < 15) {
    rotDireita();
    para2(200);
    rotDireita();
  } else if (l < 15) {
    rotDireita();
  } else if (r < 15) {
    rotEsquerda();
  } else {
    rotEsquerda();
  }
}

void rotDireita() {
  direita2(2, 2, 950);
}
void rotEsquerda() {
  esquerda2(2, 2, 950);
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
  mt2.frente(vel2);
  mt1.frente(vel);
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
  mt2.frente(vel);
  mt1.frente(vel);
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
  mt2.frente(vel);
  mt1.frente(vel);
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
