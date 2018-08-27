/**
 * Programação para o torneio OBR 2018
 * Desenvolvido por Giovanna Diodato, Rodrigo Cavalcanti, Fernanda Marcato, Matheus Pires;
 * Equipe Robonaticos;
 * Apoio: Sesi São Paulo 
 * http://facebook.com/robonaticos
 */
 
#include <Arduino.h>

/********************** BOTÕES **********************/
//Quais portas os botões estão
int btnSeguidor = 28; 
int btnDesafio = 4; 
int btnRampa = 5;
int btnExtra = 6;
int btnGarraParar = 49; //Ao contrario
//int btnRedutor = 47;
int btnFrenteDireita = 46;
int btnFrenteEsquerda = 42;
int btnRedutor = 42;

//Método para ligar os botões
void ligarBotoes() {
  pinMode(btnSeguidor, INPUT_PULLUP);
  pinMode(btnDesafio, INPUT_PULLUP);
  pinMode(btnDesafio, INPUT_PULLUP);
  pinMode(btnExtra, INPUT_PULLUP);
  pinMode(btnGarraParar, INPUT_PULLUP); 
  pinMode(btnRedutor, INPUT_PULLUP); 
  pinMode(btnFrenteDireita, INPUT_PULLUP); 
  pinMode(btnFrenteEsquerda, INPUT_PULLUP); 
  pinMode(btnRedutor, INPUT_PULLUP); 
}

/********************** LEDs **********************/
#define ledDireita  41
#define ledEsquerda  29 
#define ledAzul  26
#define ledVerde  24
#define ledVermelho 22

void ligarLeds() {
  pinMode(ledDireita, OUTPUT);
  pinMode(ledEsquerda, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
}

/********************** ENCODER **********************/
Encoder encoderEsquerda(2, 3);
Encoder encoderDireita(19, 18);

/********************** MOTORES **********************/
//Utilizamos motores de LEGO EV3
#define motorE1 11
#define motorE2 12
#define motorD1 8
#define motorD2 9

#define motorGarraCima 10
#define motorGarraBaixo 13

void ligarMotores() {
  pinMode(motorE1, OUTPUT);
  pinMode(motorE2, OUTPUT);
  pinMode(motorD1, OUTPUT);
  pinMode(motorD2, OUTPUT);
  pinMode(motorGarraCima, OUTPUT);
  pinMode(motorGarraBaixo, OUTPUT);
}

/********************** SERVO **********************/
Servo servoCacamba;

/********************** SENSOR QTR-8 POLOLU **********************/
#define sensorLinha1  A0
#define sensorLinha2  A1
#define sensorLinha3  A2
#define sensorLinha4  A3
#define sensorLinha5  A4
#define sensorLinha6  A5
#define sensorLinha7  A6
#define sensorLinha8  A7

//Vetor com os sensores
int QTR[] = {
  0,
  sensorLinha1,
  sensorLinha2,
  sensorLinha3,
  sensorLinha4,
  sensorLinha5,
  sensorLinha6,
  sensorLinha7,
  sensorLinha8,

};

#define NUM_SENSORS             8  //Número de sensores usados
#define NUM_SAMPLES_PER_SENSOR  5  //Mais ou menos 5 leituras analógicas por sensor 

// Sensores de 0 a 8 que estão conectados nas portas analógicas
QTRSensorsAnalog qtra((unsigned char[]) {
  sensorLinha1, sensorLinha2, sensorLinha3, sensorLinha4, sensorLinha5, sensorLinha6, sensorLinha7
},

NUM_SENSORS, NUM_SAMPLES_PER_SENSOR);
unsigned int sensorValues[NUM_SENSORS];

/************************ SENSOR DE COR ************************/
#define s0Esquerda 31
#define s1Esquerda 33
#define s2Esquerda 25
#define s3Esquerda 27
#define outEsquerda 23

#define s0Direita 39
#define s1Direita 43
#define s2Direita 37
#define s3Direita 45
#define outDireita 35

void ligarSensorDeCor() {
  pinMode(s0Esquerda, OUTPUT);
  pinMode(s1Esquerda, OUTPUT);
  pinMode(s2Esquerda, OUTPUT);
  pinMode(s3Esquerda, OUTPUT);
  pinMode(outEsquerda, INPUT);
  digitalWrite(s0Esquerda, HIGH);
  digitalWrite(s1Esquerda, LOW);

  pinMode(s0Direita, OUTPUT);
  pinMode(s1Direita, OUTPUT);
  pinMode(s2Direita, OUTPUT);
  pinMode(s3Direita, OUTPUT);
  pinMode(outDireita, INPUT);
  digitalWrite(s0Direita, HIGH);
  digitalWrite(s1Direita, LOW);
}

/************************ SHARP ANALÓGICO ************************/
int sharpTrasCima = A8;
int sharpTrasBaixo = A11;
int sharpCacamba = A13; //Não sei
int sharpFrente = A12;
int sharpLado = A14;


void ligarSharps(){
 pinMode(sharpTrasCima, INPUT);
 pinMode(sharpTrasBaixo, INPUT);
 pinMode(sharpCacamba, INPUT);
 pinMode(sharpFrente, INPUT);
 pinMode(sharpLado, INPUT);
}

int Sharp[] {
  0,
  sharpTrasCima,
  sharpTrasBaixo,
  sharpCacamba,
  sharpFrente,
  sharpLado
};

void setSharp(){
  sharpTrasCima = analogRead(A8);
  sharpTrasBaixo = analogRead(A11);
  sharpCacamba = analogRead(A5);
  sharpFrente = analogRead(A12);
  sharpLado = analogRead(A14);
}

/************************ VARIÁVEIS DO ROBÔ ************************/

int i;

/************** PID **************/
int P; int I; int D; int ganho;
double motorB; double motorC;

float KP = 0.16;
float KI = 0;
float KD = 0.34;

float KP_redutor = 0.2;
float KI_redutor = 0;
float KD_redutor = 0;

int setPoint = 3500;
int lastError = 0;
/*********************************/

/** Quanto o robô vê no preto e no branco (+-) **/
int preto = 800;
int branco = 550;
int silverTape = 600;
/************************************************/

/*** Forças padrão ***/
int forca = 110;
int forcaPID = 80;
int forcaBaixa = 70;
int forcaRampa = 230;
int forcaRedutor = 200;
/*********************/

/******** Estados do robô ********/
#define esquerda -1
#define direita 1
#define salaoPrincipal 2
#define salaoRampa 4
/*********************************/

#define RESTRICT_PITCH

double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
double pitch,roll;

uint32_t timer;
uint8_t i2cData[14];


