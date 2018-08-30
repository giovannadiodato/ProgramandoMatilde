/**
   Programação para o torneio OBR 2018
   Desenvolvido por Giovanna Diodato, Rodrigo Cavalcanti, Fernanda Marcato, Matheus Pires;
   Equipe Robonaticos;
   Apoio: Sesi São Paulo
   http://facebook.com/robonaticos

   posicao servo fechar(105)
   posicao servo abrir(180)
*/

#include <QTRSensors.h>       //Biblioteca utilizada pelo sensor QTR
#include <Encoder.h>          //Biblioteca utilizada para mecher os motores com o encoder
#include <Servo.h>
#include <Wire.h>
#include "Kalman.h"

#include "Config.h"           //Configurações(Declaração de portas, variaveis...)
#include "Readings.h"         //Métodos para as leituras de sensores
#include "Actions.h"          //Ações que o robô executa
#include "Controllers.h"

void setup() {

  Serial.begin(115200);
  /*** Todas essas funções se encontram na aba 'Config.h' ***/
  ligarMotores();
  ligarSensorDeCor();
  ligarLeds();
  ligarBotoes();
  ligarSharps();
  while (lerBtnGarraParar() == 1) {
    analogWrite(motorGarraCima, 150);
  }
  analogWrite(motorGarraCima, 0);



  //  analogWrite(motorGarraCima, 150);
  //  delay(200);
  //  analogWrite(motorGarraCima, 0);
  /**********************************************************/

  /*** Todas essas funções se encontram na aba 'Actions.h' ***/
  alertaDeInicio();
  delay(500);
  //calibrarArray();

  Wire.begin();
  TWBR = ((F_CPU / 400000L) - 16) / 2; // Set I2C frequency to 400kHz

  i2cData[0] = 7; // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
  i2cData[1] = 0x00; // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
  i2cData[2] = 0x00; // Set Gyro Full Scale Range to ±250deg/s
  i2cData[3] = 0x00; // Set Accelerometer Full Scale Range to ±2g
  delay(100);

  while (i2cWrite(0x19, i2cData, 4, false)); // Write to all four registers at once
  while (i2cWriteE(0x6B, 0x01, true));


  /***********************************************************/
}

void loop() {

  setSharp();

  if (lerBtnSeguidor() == 1) {
    digitalWrite(ledAzul, HIGH);
    delay(1000);
    // pararGarra(true);
    Seguidor(true);
    delay(300);
    digitalWrite(ledAzul, LOW);
  }

  if (lerBtnDesafio() == 1) {
    //digitalWrite(ledVerde, HIGH);
    delay(1000);
    terceiroSalao(true);
    delay(300);
    //digitalWrite(ledVerde, LOW);
  }

  if (lerBtnRampa() == 1) {
    digitalWrite(ledVermelho, HIGH);
    delay(1000);
    //terceiroSalao(true);
    delay(300);
    digitalWrite(ledVermelho, LOW);
  }


  //Esquerda
//    if (green_color < -800) {
//      digitalWrite(ledDireita, HIGH);
//    } else {
//      digitalWrite(ledDireita, LOW);
//    }

  //Direita
  //      if (green_color < -900) {
  //        digitalWrite(ledDireita, HIGH);
  //      } else {
  //        digitalWrite(ledDireita, LOW);
  //      }

  //Direita para esquerda
  lerTodosSensores();
  delay(300);

  //       > 180
  //       > 278

  //PID(0.15, KI, 0, 200, setPoint);
  //  PID(KP, KI, KD, forcaPID, setPoint);
  //  Serial.println("***** PID *****");
  //          curva90GrausDireitaObjeto();
  //          travarMotores();
  //          delay(2000);


}

