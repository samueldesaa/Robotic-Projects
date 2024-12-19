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
}

void loop() {
  esqInicio = left.read() - 1;
  dirInicio = right.read() - 1;
  frente2(150, 300);
  para2(500);

  while (true) {
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

    // frente2(150);

    // lcd.clear();
    // lcd.setCursor(1, 0);

    //SEGUE ESQUERDA
    if (f < esqInicio) {
      if (l < 20 && r < 20) {
        direita2(150, 150, 300);
        para2(200);
        direita2(150, 150, 300);
        atras2(150,100);
        para2(200);
      } else{
        direita2(150, 150, 300);
        para2(200);
      }
    } else if (l < esqInicio) {
      direita2(150, 150, 100);
    } else if (l > esqInicio + 10) {
      frente2(150, 150);
      esquerda2(150, 150, 300);
      frente2(150, 150);
    } else {
      frente2(120, 160, 150);
    }
    para2();
    delay(200);
    // if (f < 5) {
    //   lcd.clear();
    //   lcd.setCursor(1,0);
    //   lcd.print("Girando");
    //   lcd.setCursor(1,1);
    //   lcd.print(f);
    //   atras()
    //   esquerda2(150,150,400);
    // }else if(l>esqInicio){
    //   lcd.clear();
    //   lcd.setCursor(1,0);
    //   lcd.print("Alinhando");
    //   lcd.setCursor(1,1);
    //   lcd.print("Esq: ");
    //   lcd.print(l);
    //   lcd.print("Ini: ");
    //   lcd.print(esqInicio);
    //   para2();
    //   delay(100);
    //   esquerda2(150,150,50);
    //   delay(100);
    //   frente2(150,300);
    // } else {
    //   lcd.clear();
    //   lcd.setCursor(1,0);
    //   lcd.print("Frente");
    //   lcd.setCursor(1,1);
    //   lcd.print("Esq: ");
    //   lcd.print(l);
    //   lcd.print("Ini: ");
    //   lcd.print(esqInicio);
    //   frente2(150,130,300);
    // }

    // int vlc = 100, vlc2 = 185;
    // int giros = 0;
    // int maior = 0;

    //SEGUE PAREDE


    //SEGUE PAREDE
    // if (f < 18) {
    //   if (l+5 > r) {
    //     rotEsquerda();
    //   } else {
    //     rotDireita();
    //   }
    // } else if (l < esqInicio) {
    //   frente2(vlc2, vlc, 100);
    // } else if (r < dirInicio) {
    //   frente2(vlc, vlc2, 100);
    // } else {
    //   frente2(100, 150, 100);
    // }

    //TESTE LED
    // led.blue();
    // delay(200);

    //TESTE MOTOR
    // int vel = 200;
    // led.white();
    // frente2(2);

    //Frente e PARA
    // frente2(4);u
    // while (true) {
    //   f = front.read();\
    //   if (f < 20 || digitalRead(botao) == LOW) {
    //     direita2(2, 2, 600);
    //     break;
    //   }
    // }
    // break;

    //GIRO
    // delay(5000);
    // int velo = 150;
    // direita2(velo,velo,500);

    // if(f<15){
    //   atras2(150,100);
    //   direita2(150,150,200);
    // }
    // else if(l<esqInicio){
    //   direita2(150,150,50);
    // }else{
    //   frente2(200,150,100);
    // }

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


    //TABELA
    //VERMELHO: SÓ VIU A FRENTE E NAO LADOS
    //VERDE: VIU PAREDE
    //AZUL:
    //AMARELO(255,200,0):
    //LARANJA(255,100,0):
    //AZUL BEBE(0,255,255):
    //CIANO(0,255,100):
    //LILAS(255,0,255):
    //ROXO(100,0,255):
    //ROSA(255,0,100):
    //BRANCO:


    //Giro
    // int vlc = 70, vlc2 = 185;
    // int giros = 0;
    // int maior = 0;

    // //SEGUE PAREDE
    // led.off();
    // if (f < 18) {
    //   led.red();
    //   if (l + 5 > r) {
    //     rotEsquerda();
    //   } else {
    //     rotDireita();
    //   }
    // } else if (l < esqInicio) {
    //   led.blue();
    //   frente2(vlc2, vlc, 100);
    // } else if (r < dirInicio) {
    //   led.color(255, 100, 0);
    //   frente2(vlc, vlc2, 100);
    // } else {
    //   led.green();
    //   frente2(100, 150, 100);
    // }
  }
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
