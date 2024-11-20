#include <Servo.h>
#include <Adafruit_TCS34725.h>


class motor {
private:
  int m1, m2, p1;
  float diminuicao = 0.4;
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
    if (p1 == 3) {
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

int ledS = 6;     // LED de iluminação
int lumin = 100;  // Brilho do LED
int velE = 2;     // Velocidade motor esquerdo
int velD = 3;     // Velocidade motor direito
int motoD1 = 22;  // Pino motor direito
int motoD2 = 24;
int motoE1 = 26;  // Pino motor esquerdo
int motoE2 = 28;
int sE = 31;
int sD = 53;

// Inicializa o sensor TCS34725
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_600MS, TCS34725_GAIN_1X);
motor mt1(motoD1, motoD2, velE);
motor mt2(motoE1, motoE2, velD);
Servo servo;

void setup() {
  Serial.begin(9600);

  // Configuração do LED
  pinMode(ledS, OUTPUT);
  analogWrite(ledS, lumin);

  // servo.attach(9);
  // servo.write(170);
  // Inicia o sensor de cor
  if (tcs.begin()) {
    Serial.println("Sensor TCS34725 detectado!");
  } else {
    Serial.println("Sensor TCS34725 não detectado. Verifique a conexão.");
    // while (1)
      ;  // Aguarda indefinidamente se o sensor não for encontrado
  }
}

void loop() {
  // uint16_t r, g, b, c;
  // tcs.getRawData(&r, &g, &b, &c);

  // Imprime os valores RGB para diagnóstico
  // Serial.print("R: ");
  // Serial.print(r);
  // Serial.print(" G: ");
  // Serial.print(g);
  // Serial.print(" B: ");
  // Serial.println(b);

  //Mexe o servo
  // servo.write(180);
  // delay(1000);
  // servo.write(0);
  // delay(1000);

  int sensorD = digitalRead(sD);
  int sensorE = digitalRead(sE);
  Serial.print(sensorD);
  Serial.print(", ");
  Serial.println(sensorE);
  int velMot = 150;
  int delMot = 100;
  int paraMot = 500; 
  if(sensorD){
    esquerda2(velMot,velMot,delMot);
  }else if(sensorE){
    direita2(velMot,velMot,delMot);
  }else{
    frente2(velMot);
    delay(delMot);
    para2(paraMot);
  }
}

int rot = 600;

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