/**
 * Programação para o torneio OBR 2018
 * Desenvolvido por Giovanna Diodato, Rodrigo Cavalcanti, Fernanda Marcato, Matheus Pires;
 * Equipe Robonaticos;
 * Apoio: Sesi São Paulo 
 * http://facebook.com/robonaticos
 */
 
#include <Arduino.h>
#include <QTRSensors.h>

int lerTodosQTR() {
  unsigned int position = qtra.readLine(sensorValues);
  return position;
}

unsigned int lerQTR(int pino) {
  return analogRead(QTR[pino]);
}

String allsensors;

void lerTodosSensores() {
  allsensors = "";
  allsensors += lerQTR(1);
  allsensors += " ";
  allsensors += lerQTR(2);
  allsensors += " ";
  allsensors += lerQTR(3);
  allsensors += " ";
  allsensors += lerQTR(4);
  allsensors += " ";
  allsensors += lerQTR(5);
  allsensors += " ";
  allsensors += lerQTR(6);
  allsensors += " ";
  allsensors += lerQTR(7);
  allsensors += " ";
  allsensors += lerQTR(8);

  Serial.println(allsensors);
  Serial.println();
}

int lerSharp(int pino) {
  return analogRead(Sharp[pino]);
}

int lerBtnSeguidor() {
  return digitalRead(btnSeguidor);
}
int lerBtnDesafio() {
  return digitalRead(btnDesafio);
}
int lerBtnRampa() {
  return digitalRead(btnRampa);
}
int lerBtnExtra() {
  return digitalRead(btnExtra);
}
int lerBtnGarraParar() {
  return digitalRead(btnGarraParar);
}

int lerBtnFrenteDireita() {
  return digitalRead(btnFrenteDireita);
}

int lerBtnFrenteEsquerda() {
  return digitalRead(btnFrenteEsquerda);
}

int lerBtnRedutor() {
  return digitalRead(btnRedutor);
}



