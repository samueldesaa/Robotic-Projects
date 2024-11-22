#include <Wire.h>
#include <Ultrasonic.h>

class motor {
private:
  int m1, m2, p1;
  float diminuicao = 0.07;
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
    int Mforte = 9;
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
    if (p1 == Mforte) {
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
    if (p1 == 3) {
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
int prioridade = 1;
int esqInicio = 8;
int dirInicio = 8;
motor mt2(A5, A4, 9);
motor mt1(A7, A6, 10);
Ultrasonic right(4, 5);
Ultrasonic left(6, 7);
Ultrasonic front(2, 3);

void setup() {
  //Iniciar monitor serial
  Serial.begin(9600);  // Serve para limpar a tela do display
  frente2(150, 300);
  para2(500);
  esqInicio = left.read() - 1;
  dirInicio = right.read() - 1;
}

void loop() {

  // put your main code here, to run repeatedly:
  //Teste velocidade
  // frente2(100);

  l = left.read();
  f = front.read();
  r = right.read();
  // para2(1000);

  //Cores
  // led.color(255,140,0);
  // while(digitalRead(botao)!=LOW);
  // led.off();
  // break;

  //IMPRIMIR ENTRADAS ULTRASONICO
  Serial.print(l);
  if (l < 100) {
    Serial.print(" ");
  };
  if (l < 10) {
    Serial.print(" ");
  };
  Serial.print(",");
  Serial.print(f);
  if (f < 100) {
    Serial.print(" ");
  };
  if (f < 10) {
    Serial.print(" ");
  };
  Serial.print(",");
  Serial.print(r);
  Serial.println();

  if (f < 5) {
    if (l < 20 && r < 20) {
      while (f < 30) {
        f = front.read();
        direita2(150, 150, 50);
        para2(100);
      }
      direita2(150, 150, 100);
      frente2(150, 300);
    } else {
      while (f < 25) {
        f = front.read();
        esquerda2(150, 150, 50);
        para2(100);
      }
      esquerda2(150, 150, 100);
      frente2(150, 300);
    }
  } else if (l < esqInicio) {
    para2(100);
    direita2(150, 150, 100);
    frente2(150, 200);
  } 
  else if (l > esqInicio + 10) {
    frente2(150, 500);
  } 
  else {
    frente2(120, 160, 150);
  }
  para2();
  delay(50);
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
//Moto Direita, Motor Esquerda e Delay
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
};
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
