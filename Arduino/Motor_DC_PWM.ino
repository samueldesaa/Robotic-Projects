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
      Serial.print("Velocidade a ");
      Serial.println(vel);
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
      Serial.print("Velocidade a ");
      Serial.println(vel);
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
int prioridade;
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
      // Serial.print(l);
      // Serial.print(", ");
      // Serial.print(f);
      // Serial.print(", ");
      // Serial.print(r);
      // Serial.println();

      //TESTE LED
      // led.blue();
      // delay(200);

      //TESTE MOTOR
      // int vel = 200;
      // mt1.frente(vel);
      // mt2.frente(vel);

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
      // int velo = 2;
      // direita2(velo,velo,820);
      // break;

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
      //rotacao();

      //verificaCantos();

      //Giro
      //  int x = left.read();
      //  esquerda2(2, 2);
      //  while (f < x+5) {
      //    f = front.read();
      //  }
      //  esquerda2(2,2,200);
      //  para2();
      //  break;

      //SEGUE PAREDE
      if (f < 15) {
        para2();
        if (l < 20 && r < 20) {
          while (true) {
            direita2(2, 2, 200);
            esquerda2(2, 2, 200);
          }
        } else if (l > 20) {
          rotEsquerda();
          frente2(2, 200);
          prioridade = 2;
        } else if (r < 20) {
          rotDireita();
          frente2(2, 200);
          prioridade = 1;
        }
      } else if (l < 8 && prioridade == 1) {
        frente2(150, 110, 1000);
      } else if (r < 8 && prioridade == 1) {
        frente2(110, 150, 1000);
      } else if (r < 8) {
        frente2(110, 150, 1000);
      } else if (l < 8) {
        frente2(150, 110, 1000);
      } else if (r > 70 && l > 70 && f > 70) {
        break;
      } else {
        frente2(100);
      }
    }
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
  mt2.atras(vel2);
}
void esquerda2(int vel, int vel2) {
  mt1.atras(vel);
  mt2.frente(vel2);
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
