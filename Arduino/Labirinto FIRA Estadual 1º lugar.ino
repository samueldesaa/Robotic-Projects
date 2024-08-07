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
  void randColor() {
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
  void color(int r, int g, int b, int del) {
    analogWrite(R, r);
    analogWrite(G, g);
    analogWrite(B, b);
    delay(del);
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
ledRGB led(10, 11, 8);

int f, r, l;
int prioridade = 1;
int esqInicio = 8;
int dirInicio = 8;
int botao = 51;
motor mt1(7, 6, 3);
motor mt2(4, 5, 2);
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

  while (true) {
    if (digitalRead(botao) == LOW) {
      led.white();
      frente2(2, 2, 800);
      esqInicio = left.read() - 2;
      dirInicio = right.read() - 1;
      for (int i = 0; i < 50; i++) {
        led.randColor();
        delay(30);
      }
      led.off();
      break;
    }
  }
  while (true) {
    // put your main code here, to run repeatedly:
    //Teste velocidade
    // frente2(100);

    f = front.read();
    l = left.read();
    r = right.read();

    //Cores
    // led.color(255,140,0);
    // while(digitalRead(botao)!=LOW);
    // led.off();
    // break;

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
    // direita2(velo,velo,720);
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
    int vlc = 70, vlc2 = 185;
    int giros = 0;
    int maior = 0;

    //SEGUE PAREDE
    led.off();
    if (f < 18) {
      led.red();
      if (l+5 > r) {
        rotEsquerda();
      } else {
        rotDireita();
      }
    } else if (l < esqInicio) {
      led.blue();
      frente2(vlc2, vlc, 100);
    } else if (r < dirInicio) {
      led.color(255, 100, 0);
      frente2(vlc, vlc2, 100);
    } else {
      led.green();
      frente2(100, 150, 100);
    }
  }
}
int rot = 600;

void rotDireita() {
  // direita2(2, 2, rot);
  para2(200);
  atras2(2, 2, 200);
  while (true) {
    direita2(2, 2);
    while (f < r) {
      f = front.read();
      delay(50);
    };
    frente2(2, 2, 200);
    para2();
    break;
  }
}
void rotEsquerda() {
  // esquerda2(2, 2, rot);
  para2(200);
  atras2(2, 2, 200);
  while (true) {
    esquerda2(2, 2);
    while (f < l) {
      f = front.read();
      delay(50);
    };
    frente2(2, 2, 200);
    para2();
    break;
  }
}

void rotAtras() {
  para2(200);
  atras2(2, 2, 200);
  while (true) {
    direita2(2, 2);
    while (f < 30) {
      f = front.read();
      delay(50);
    }
    frente2(2, 2, 200);
    para2();
    break;
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
