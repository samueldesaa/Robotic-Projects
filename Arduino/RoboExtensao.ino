
class motor {
private:
  int m1, m2, p1;
  float diminuicao = 0.3;
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

motor mt1(31, 33, 2);
motor mt2(35, 37, 3);

void setup() {
  Serial.begin(9600);
}

int speed = 150;
void loop() {
  char c = Serial.read();
  if(c == 'F'){
    frente2(speed);
  }
  if(c == 'D'){
    direita2(speed,speed);
  }
  if(c == 'E'){
    esquerda2(speed,speed);
  }
  if(c == 'A'){
    atras2(speed);
  }
  if(c == 'P'){
    para2();
  }
  if(c == 'B'){
    speed = 255;
  }
  if(c == 'N'){
    speed = 150;
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
