/**
   Programação para o torneio OBR 2018
   Desenvolvido por Giovanna Diodato, Rodrigo Cavalcanti, Fernanda Marcato, Matheus Pires;
   Equipe Robonaticos;
   Apoio: Sesi São Paulo
   http://facebook.com/robonaticos
*/
#include <Arduino.h>

void mpuStart(){
  
}

/**
   Função para acender os leds antes de calibrar
*/
void alertaDeInicio() {
  digitalWrite(ledDireita, HIGH);
  digitalWrite(ledEsquerda, HIGH);
  digitalWrite(ledAzul, HIGH);
  delay(25);
  digitalWrite(ledDireita, LOW);
  digitalWrite(ledEsquerda, LOW);
  digitalWrite(ledAzul, LOW);
  delay(50);
  digitalWrite(ledDireita, HIGH);
  digitalWrite(ledEsquerda, HIGH);
  digitalWrite(ledVermelho, HIGH);
  delay(25);
  digitalWrite(ledDireita, LOW);
  digitalWrite(ledEsquerda, LOW);
  digitalWrite(ledVermelho, LOW);
  delay(50);
  digitalWrite(ledDireita, HIGH);
  digitalWrite(ledEsquerda, HIGH);
  digitalWrite(ledVerde, HIGH);
  delay(25);
  digitalWrite(ledDireita, LOW);
  digitalWrite(ledEsquerda, LOW);
  digitalWrite(ledVerde, LOW);
}

/**
   Função para calibrar o QTR-8
*/
void calibrarArray() {

  Serial.println("Calibrando...");

  //Para 'i' igual a 0, até i ser menor que 100, incrementa a variavel
  for (int i = 0; i < 100; i++)  //Faz a calibração durar aproximadamente 10 segundos
  {
    digitalWrite(ledAzul, HIGH);
    //    if ( i  < 25 || i >= 75 ) // turn to the left and right to expose the sensors to the brightest and darkest readings that may be encountered
    //      turn_right();
    //    else
    //      turn_left();
    qtra.calibrate();       //Le todos os sensores 10 vezes
    digitalWrite(ledAzul, LOW);
    delay(10);
  }

  digitalWrite(ledAzul, LOW);
  Serial.println("Calibrado!");
  Serial.println("Inicializando...");
  delay(800);
}

/**
   Função para parar os motores
*/
void pararMotores() {
  analogWrite(motorE1, 0);
  analogWrite(motorE2, 0);
  analogWrite(motorD1, 0);
  analogWrite(motorD2, 0);
}

/**
   Função para mover
*/

void mover(int e, int d) {
  if (e > 0) {
    analogWrite(motorE1, e);
    analogWrite(motorE2, 0);
  }
  else if (e == 0) {
    analogWrite(motorE1, 0);
    analogWrite(motorE2, 0);
  }
  else {
    analogWrite(motorE1, 0);
    analogWrite(motorE2, abs(e));
  }
  if (d > 0) {
    analogWrite(motorD1, d);
    analogWrite(motorD2, 0);
  }
  else if (d == 0) {
    analogWrite(motorD1, 0);
    analogWrite(motorD2, 0);
  }
  else {
    analogWrite(motorD1, 0);
    analogWrite(motorD2, abs(d));
  }
};

/**
   Função para travar os motores
*/
void travarMotores() {
  analogWrite(motorE1, 255);
  analogWrite(motorE2, 255);
  analogWrite(motorD1, 255);
  analogWrite(motorD2, 255);
}

/**
   Função para fazer o PID
*/
void PID (double kP, double kI, double kD, double tP, int media) {

  int erro = lerTodosQTR() - media;

  P = kP * erro;
  I = I + (erro * kI);
  D = kD * (erro - lastError);

  ganho = P + I + D;

  lastError = erro;

  motorB = tP - ganho;
  motorC = tP + ganho;

  mover(motorB, motorC);
}
/*****************************************************************/

/****** 90 GRAUS ESQUERDA ******/
void curva90GrausEsquerda() {
  pararMotores();
  delay(250);

  //Deixa a leitura do encoder dos motores em 0
  encoderEsquerda.write(0); encoderDireita.write(0);

  //Enquanto a leitura dos encoders ser menor do que o
  //valor passado, continua fazendo a curva
  while ((encoderEsquerda.read() >= -1100) && (encoderDireita.read() <= 1100)) {
    mover(-140, 150);
  }
  pararMotores();
}
/*****************************************************************/

/****** 90 GRAUS ESQUERDA OBJETO ******/
void curva90GrausEsquerdaObjeto() {

  pararMotores();
  delay(250);

  //Deixa a leitura do encoder dos motores em 0
  encoderEsquerda.write(0); encoderDireita.write(0);

  //Enquanto a leitura dos encoders ser menor do que o
  //valor passado, continua fazendo a curva
  while ((encoderEsquerda.read() >= -1100) && (encoderDireita.read() <= 1100)) {
    mover(-140, 140);
  }
  pararMotores();
}
/*****************************************************************/

/****** 90 GRAUS DIREITA ******/
void curva90GrausDireita() {

  pararMotores();
  delay(250);

  //Deixa a leitura do encoder dos motores em 0
  encoderEsquerda.write(0); encoderDireita.write(0);

  //Enquanto a leitura dos encoders ser menor do que o
  //valor passado, continua fazendo a curva
  while ((encoderEsquerda.read() <= 1050) && (encoderDireita.read() >= -1050)) {
    mover(120, -120);
  }
  pararMotores();
}
/*****************************************************************/

/****** 90 GRAUS DIREITA OBJETO ******/
void curva90GrausDireitaObjeto() {

  pararMotores();
  delay(250);

  //Deixa a leitura do encoder dos motores em 0
  encoderEsquerda.write(0); encoderDireita.write(0);

  //Enquanto a leitura dos encoders ser menor do que o
  //valor passado, continua fazendo a curva
  while ((encoderEsquerda.read() <= 1100) && (encoderDireita.read() >= -1100)) {
    mover(150, -150);
  }
  pararMotores();
}
/*****************************************************************/



/****** 180 GRAUS ******/
void curva180Graus() {

  pararMotores();
  delay(250);

  //Deixa a leitura do encoder dos motores em 0
  encoderEsquerda.write(0); encoderDireita.write(0);

  //Enquanto a leitura dos encoders ser menor do que o
  //valor passado, continua fazendo a curva
  while ((encoderEsquerda.read() >= -2100) && (encoderDireita.read() <= 2100)) {
    mover(140, -155);
  }
  pararMotores();
}
/*****************************************************************/

/****** FRENTE COM ENCODER ******/
void frenteEncoder(int pulsos, int forcaEsquerda, int forcaDireita) {
  pararMotores();
  delay(250);

  //Deixa a leitura do encoder dos motores em 0
  encoderEsquerda.write(0);

  //Enquanto a leitura dos encoders ser menor do que o
  //valor passado, continua fazendo a curva
  while (encoderEsquerda.read() < pulsos) {
    mover(forcaEsquerda, forcaDireita);
  }
  pararMotores();
}
/*****************************************************************/

/****** TRAS COM ENCODER ******/
void trasEncoder(int pulsos, int forcaEsquerda, int forcaDireita) {
  pararMotores();
  delay(250);

  //Deixa a leitura do encoder dos motores em 0
  encoderEsquerda.write(0);

  //Enquanto a leitura dos encoders ser menor do que o
  //valor passado, continua fazendo a curva
  while (encoderEsquerda.read() > -pulsos) {
    mover(-forcaEsquerda, -forcaDireita);
  }
  pararMotores();
}
/*****************************************************************/

/****** FAZER OBJETO (ESQUERDA) ******/
void objeto() {
  travarMotores();
  delay(300);
  digitalWrite(ledAzul, LOW);
  digitalWrite(ledVermelho, HIGH);
  //Primeira curva
  curva90GrausEsquerdaObjeto();
  travarMotores();
  delay(300);
  //frente
  frenteEncoder(1400, 100, 100);
  travarMotores();
  delay(1000);
  //Segunda curva
  curva90GrausDireitaObjeto();
  travarMotores();
  delay(1000);
  //frente
  frenteEncoder(2800, 100, 100);
  travarMotores();
  delay(1000);
  //terceira curva
  curva90GrausDireitaObjeto();
  travarMotores();
  delay(1000);
  //frente
  frenteEncoder(1400, 100, 100);
  travarMotores();
  delay(1000);
  //Quarta curva (para seguir linha)
  curva90GrausEsquerdaObjeto();
  travarMotores();
  delay(1000);
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAzul, HIGH);
}
/*****************************************************************/
/****** FAZER OBJETO (ESQUERDA) ******/
void gap(int estado) {
  if (estado == salaoPrincipal) {
    mover(forcaBaixa, forcaBaixa);
  } else if (estado == salaoRampa) {
    mover(forcaRampa, forcaRampa);
  }
}
/*****************************************************************/

/****** SINALIZAR VITIMA ******/
void sinalizar() {
  digitalWrite(ledDireita, HIGH);
  digitalWrite(ledEsquerda, HIGH);
  delay(100);
  digitalWrite(ledDireita, LOW);
  digitalWrite(ledEsquerda, LOW);
  delay(100);
  digitalWrite(ledDireita, HIGH);
  digitalWrite(ledEsquerda, HIGH);
  delay(100);
  digitalWrite(ledDireita, LOW);
  digitalWrite(ledEsquerda, LOW);
  delay(100);
  digitalWrite(ledDireita, HIGH);
  digitalWrite(ledEsquerda, HIGH);
  delay(100);
  digitalWrite(ledDireita, LOW);
  digitalWrite(ledEsquerda, LOW);
}
/*****************************************************************/

void curva45GrausDireita() {
  pararMotores();
  delay(250);

  //Deixa a leitura do encoder dos motores em 0
  encoderEsquerda.write(0); encoderDireita.write(0);

  //Enquanto a leitura dos encoders ser menor do que o
  //valor passado, continua fazendo a curva
  while ((encoderEsquerda.read() <= 525) && (encoderDireita.read() >= -525)) {
    mover(120, -170);
  }
  pararMotores();
}

void curva45GrausEsquerda() {
  travarMotores();
  delay(250);

  //Deixa a leitura do encoder dos motores em 0
  encoderEsquerda.write(0); encoderDireita.write(0);

  //Enquanto a leitura dos encoders ser menor do que o
  //valor passado, continua fazendo a curva
  while ((encoderEsquerda.read() >= -600) && (encoderDireita.read() <= 600)) {
    mover(-120, 170);
  }
  travarMotores();
}

void pararGarra(boolean condicao) {
  while (condicao == true) {
    while (lerBtnGarraParar() == 1) {
      analogWrite(motorGarraCima, 150);
    }
    analogWrite(motorGarraCima, 0);
  }
}

const uint8_t IMUAddress = 0x68; // AD0 is logic low on the PCB
const uint16_t I2C_TIMEOUT = 1000; // Used to check for errors in I2C communication

uint8_t i2cRead(uint8_t registerAddress, uint8_t *data, uint8_t nbytes) {
  uint32_t timeOutTimer;
  Wire.beginTransmission(IMUAddress);
  Wire.write(registerAddress);
  uint8_t rcode = Wire.endTransmission(false); // Don't release the bus
  if (rcode) {
    Serial.print(F("i2cRead failed: "));
    Serial.println(rcode);
    return rcode; // See: http://arduino.cc/en/Reference/WireEndTransmission
  }
  Wire.requestFrom(IMUAddress, nbytes, (uint8_t)true); // Send a repeated start and then release the bus after reading
  for (uint8_t i = 0; i < nbytes; i++) {
    if (Wire.available())
      data[i] = Wire.read();
    else {
      timeOutTimer = micros();
      while (((micros() - timeOutTimer) < I2C_TIMEOUT) && !Wire.available());
      if (Wire.available())
        data[i] = Wire.read();
      else {
        Serial.println(F("i2cRead timeout"));
        return 5; // This error value is not already taken by endTransmission
      }
    }
  }
  return 0; // Success
}

uint8_t i2cWrite(uint8_t registerAddress, uint8_t *data, uint8_t length, bool sendStop) {
  Wire.beginTransmission(IMUAddress);
  Wire.write(registerAddress);
  Wire.write(data, length);
  uint8_t rcode = Wire.endTransmission(sendStop); // Returns 0 on success
  if (rcode) {
    Serial.print(F("i2cWrite failed: "));
    Serial.println(rcode);
  }
  return rcode; // See: http://arduino.cc/en/Reference/WireEndTransmission
}

uint8_t i2cWriteE(uint8_t registerAddress, uint8_t data, bool sendStop) {
  return i2cWrite(registerAddress, &data, 1, sendStop); // Returns 0 on success
}



