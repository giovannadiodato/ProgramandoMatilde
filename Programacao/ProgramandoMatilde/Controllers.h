/**
   Programação para o torneio OBR 2018
   Desenvolvido por Giovanna Diodato, Rodrigo Cavalcanti, Fernanda Marcato, Matheus Pires;
   Equipe Robonaticos;
   Apoio: Sesi São Paulo
   http://facebook.com/robonaticos

*/
#include <Arduino.h>

/**** Método boolean para verificar Gap ****/
boolean verificaGap() {
  if (lerQTR(1) <= branco && lerQTR(2) <= branco && lerQTR(3) <= branco && lerQTR(4) <= branco && lerQTR(5) <= branco && lerQTR(6) <= branco && lerQTR(7) <= branco && lerQTR(8) <= branco) {
    return true;
  } else {
    return false;
  }
}
/*******************************************/

/**** Método boolean para verificar 90 para a direita ****/
boolean verifica90Esquerda() {
  if (lerQTR(1) <= branco && lerQTR(2) <= branco && lerQTR(7) >= preto && lerQTR(8) >= preto) {
    return true;
  } else {
    return false;
  }
}
/*********************************************************/

/**** Método boolean para verificar 90 para a esquerda ****/
boolean verifica90Direita() {
  if (lerQTR(1) >= preto && lerQTR(2) >= preto && lerQTR(7) <= branco && lerQTR(8) <= branco) {
    return true;
  } else {
    return false;
  }
}
/*********************************************************/

/****** Método boolean para verificar encruzilhada ******/
boolean verificaEncruzilhada() {
  if (lerQTR(1) >= preto && lerQTR(2) >= preto && lerQTR(3) >= preto && lerQTR(4) >= preto && lerQTR(5) >= preto && lerQTR(6) >= preto && lerQTR(7) >= preto && lerQTR(8) >= preto) {
    return true;
  } else {
    return false;
  }
}
/*******************************************************/

/****** Método boolean para verificar verde para a esquerda ******/
boolean verificaVerdeEsquerda() {

  digitalWrite(s2Esquerda, HIGH);
  digitalWrite(s3Esquerda, HIGH);
  int green_color = pulseIn(outEsquerda, LOW);

  green_color = map(green_color, 30, 90, 255, 0);

  if ((green_color < -650) && (green_color < -250)) {
    return true;
  } else {
    return false;
  }
}
/*****************************************************************/

/****** Método boolean para verificar verde para a direita ******/
boolean verificaVerdeDireita() {
  digitalWrite(s2Direita, HIGH);
  digitalWrite(s3Direita, HIGH);
  int green_color = pulseIn(outDireita, LOW);

  green_color = map(green_color, 30, 90, 255, 0);

  if (green_color < -700/*) && (green_color < -300)*/) {
    return true;
  } else {
    return false;
  }
}
/*****************************************************************/

/****** Método boolean para verificar verde para objeto ******/
boolean verificaObjeto() {

  if (lerSharp(4) >= 413) {
    return true;
  } else {
    return false;
  }
}

boolean verificaRedutor() {
  if (lerBtnRedutor() == 1) {
    return true;
  }
  return false;
}

boolean verificaSilverTap() {
  if (lerQTR(1) >= silverTape && lerQTR(2) >= silverTape && lerQTR(3) >= silverTape && lerQTR(4) >= silverTape && lerQTR(5) >= silverTape && lerQTR(6) >= silverTape && lerQTR(7) >= silverTape && lerQTR(8) >= silverTape) {
    return true;
  } else {
    return false;
  }
}

/********* TERCEIRO SALAO ************/
boolean verificaParede() {
  if (lerBtnFrenteDireita() == 0 || lerBtnFrenteEsquerda() == 0) {
    return true;
  }
  return false;
}
boolean verificaAreaResgate() {
  if ((lerSharp(1) > 310) && (lerSharp(2) > 100)) {
    return true;
  }
  return false;
}


boolean verificaRampa() {

  if ((pitch < -30) && (lerSharp(5) >= 324)) {
    return true;
  } else {
    return false;
  }

}

int p = 0;
int s = 0;
int t = 0;
int aux = 0;

void terceiroSalao(boolean condicao) {
  while (condicao == true) {
    digitalWrite(ledDireita, LOW);
    digitalWrite(ledEsquerda, LOW);
    //digitalWrite(ledAzul, HIGH);
    digitalWrite(ledVerde,  HIGH);
    digitalWrite(ledVermelho, HIGH);
    analogWrite(motorGarraBaixo, 100);
    delay(200);
    analogWrite(motorGarraBaixo, 0);
    curva90GrausEsquerdaObjeto();
    mover(-100, -100);
    delay(2000);
    frenteEncoder(1900, 90, 90);
    curva90GrausDireitaObjeto();
    mover(-100, -100);
    delay(2000);
    travarMotores();
    delay(1000);

    aux = 1;
    while (aux == 1) {
      mover(80, 80);
      if (verificaParede() == true) {
        travarMotores();
        delay(22000);
      }

    }
  }
}


  void Seguidor(boolean condicao) {
    while (condicao == true) {

      while (i2cRead(0x3B, i2cData, 14));
      accX = ((i2cData[0] << 8) | i2cData[1]);
      accY = ((i2cData[2] << 8) | i2cData[3]);
      accZ = ((i2cData[4] << 8) | i2cData[5]);
      //tempRaw = (i2cData[6] << 8) | i2cData[7];
      gyroX = (i2cData[8] << 8) | i2cData[9];
      gyroY = (i2cData[10] << 8) | i2cData[11];
      gyroZ = (i2cData[12] << 8) | i2cData[13];

#ifdef RESTRICT_PITCH // Eq. 25 and 26
      roll  = atan2(accY, accZ) * RAD_TO_DEG;
      pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
#endif



      //pararGarra(true);
      //    if (verificaRedutor() == true) {
      //      digitalWrite(ledAzul, LOW);
      //      digitalWrite(ledVermelho, HIGH);
      //      //int b = 1;
      //      mover(200, 200);
      //      delay(300);
      //      //b = 0;
      //      digitalWrite(ledVermelho, LOW);
      //      digitalWrite(ledAzul, HIGH);
      //    } else {
      //      PID(KP, KI, KD, forcaPID, setPoint);
      //    }

      if (verificaRampa() == true) {
        Serial.println("******************************* RAMPA *****************************");
        //      travarMotores();
        //      delay(500);
        analogWrite(motorGarraBaixo, 100);
        delay(200);
        analogWrite(motorGarraBaixo, 0);
        //digitalWrite(ledAzul, LOW);
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledDireita, HIGH);
        digitalWrite(ledEsquerda, HIGH);
        while (verificaSilverTap() == false) {
          PID(0.15, KI, 0, 170, setPoint);
          if (verificaGap() == true) {
            Serial.println("******************************* GAP *****************************");
            while (verificaGap() == true) {
              gap(salaoRampa);
            }
          }
          //        if (verificaRedutorRampa() == true) {
          //          digitalWrite(ledAzul, LOW);
          //          digitalWrite(ledVermelho, HIGH);
          //          int b = 1;
          //          mover(200, 230);
          //          delay(600);
          //          b = 0;
          //          digitalWrite(ledVermelho, LOW);
          //          digitalWrite(ledAzul, HIGH);
          //        } else {
          //          PID(KP, KI, KD, forcaPID, setPoint);
          //        }
        }

        frenteEncoder(1700, 100, 100);
        travarMotores();
        delay(1000);
        digitalWrite(ledDireita, LOW);
        digitalWrite(ledEsquerda, LOW);
        //digitalWrite(ledAzul,  HIGH);
        digitalWrite(ledVerde,  HIGH);
        while (true) {
          terceiroSalao(true);
        }
      }


      PID(KP, KI, KD, forcaPID, setPoint);
      Serial.println("***** PID *****");

      if (verificaObjeto() == true) {
        objeto();
      }

      if (verificaGap() == true) {
        digitalWrite(ledAzul, LOW);
        digitalWrite(ledDireita, HIGH);
        digitalWrite(ledEsquerda, HIGH);
        digitalWrite(ledVermelho, HIGH);
        travarMotores();
        delay(1000);
        frenteEncoder(60, 80, 80);
        curva45GrausDireita();
        if (verificaGap() == true) {
          curva90GrausEsquerda();
          travarMotores();
          delay(1000);
          if (verificaGap() == true) {
            curva45GrausDireita();
            while (verificaGap() == true) {
              gap(salaoPrincipal);
            }
          } else {
            //Se ele encontrar algo fazer PID ou virar? Ir para trás?
            curva45GrausDireita();
            trasEncoder(200, 70, 70); // Para trás para voltar pro segue linha
            digitalWrite(ledDireita, LOW);
            digitalWrite(ledEsquerda, LOW);
            digitalWrite(ledVermelho, LOW);
            digitalWrite(ledAzul, HIGH);
            PID(KP, KI, KD, forcaPID, setPoint);
          }
        } else {
          //Se ele encontrar algo fazer PID ou virar? Ir para trás?
          curva45GrausEsquerda();
          trasEncoder(200, 70, 70); // Para trás para voltar pro segue linha
          digitalWrite(ledDireita, LOW);
          digitalWrite(ledEsquerda, LOW);
          digitalWrite(ledVermelho, LOW);
          digitalWrite(ledAzul, HIGH);
          PID(KP, KI, KD, forcaPID, setPoint);
        }
        digitalWrite(ledDireita, LOW);
        digitalWrite(ledEsquerda, LOW);
        digitalWrite(ledVermelho, LOW);
        digitalWrite(ledAzul, HIGH);
      }


      if (verifica90Direita() ==  true) {
        travarMotores();
        delay(1000);
        trasEncoder(45, 100, 100);
        travarMotores();
        delay(1000);
        int g = 0;
        if ((verificaVerdeDireita() == true) && (g == 0)) {
          Serial.println("*********** VERDE DIREITA ************");
          digitalWrite(ledAzul, LOW);
          digitalWrite(ledDireita, HIGH);
          digitalWrite(ledVerde, HIGH);
          frenteEncoder(150, 100, 100);
          curva90GrausDireitaObjeto();
          trasEncoder(120, 100, 100);
          digitalWrite(ledDireita, LOW);
          digitalWrite(ledVerde, LOW);
          digitalWrite(ledAzul, HIGH);
          g = 1;
        }
        if (g == 0) {
          frenteEncoder(200, 100, 100);
          if (lerQTR(1) <= branco && lerQTR(2) <= branco && lerQTR(3) <= branco && lerQTR(4) <= branco && lerQTR(5) <= branco && lerQTR(6) <= branco && lerQTR(7) <= branco && lerQTR(8) <= branco) {
            Serial.println("*********** 90 DIREITA ************");
            digitalWrite(ledAzul, LOW);
            digitalWrite(ledDireita, HIGH);
            curva90GrausDireitaObjeto();
            travarMotores();
            delay(1000);
            trasEncoder(120, 100, 100);
            digitalWrite(ledDireita, LOW);
            digitalWrite(ledAzul, HIGH);
          } else {
            mover(100, 100);
            delay(300);
          }
        }
      }

      if (verifica90Esquerda() ==  true) {
        travarMotores();
        delay(1000);
        trasEncoder(45, 100, 100);
        travarMotores();
        delay(1000);
        int ge = 0;
        if ((verificaVerdeEsquerda() == true) && (verificaVerdeDireita() == false) && (ge == 0)) {
          Serial.println("*********** VERDE ESQUERDA ************");
          digitalWrite(ledAzul, LOW);
          digitalWrite(ledEsquerda, HIGH);
          digitalWrite(ledVerde, HIGH);
          frenteEncoder(250, 100, 100);
          curva90GrausEsquerdaObjeto();
          travarMotores();
          delay(1000);
          trasEncoder(120, 100, 100);
          digitalWrite(ledEsquerda, LOW);
          digitalWrite(ledVerde, LOW);
          digitalWrite(ledAzul, HIGH);
          ge = 1;
        } if (ge == 0) {
          frenteEncoder(210, 100, 100);
          if (lerQTR(1) <= branco && lerQTR(2) <= branco && lerQTR(3) <= branco && lerQTR(4) <= branco && lerQTR(5) <= branco && lerQTR(6) <= branco && lerQTR(7) <= branco && lerQTR(8) <= branco) {
            Serial.println("*********** 90 ESQUERDA ************");
            digitalWrite(ledAzul, LOW);
            digitalWrite(ledEsquerda, HIGH);
            curva90GrausEsquerdaObjeto();
            travarMotores();
            delay(1000);
            trasEncoder(120, 100, 100);
            digitalWrite(ledEsquerda, LOW);
            digitalWrite(ledAzul, HIGH);
          } else {
            mover(100, 100);
            delay(300);
          }
        }
      }

      if (verificaEncruzilhada() == true) {
        travarMotores();
        delay(1000);
        //trasEncoder(45, 100, 100);
        trasEncoder(50, 100, 100);
        travarMotores();
        delay(1000);

        int e = 0;
        Serial.println("*********** ENCRUZILHADA ************");

        if ((verificaVerdeEsquerda() == true) && (verificaVerdeDireita() == false) && (e == 0)) {
          Serial.println("*********** VERDE ESQUERDA ************");
          digitalWrite(ledAzul, LOW);
          digitalWrite(ledEsquerda, HIGH);
          digitalWrite(ledVerde, HIGH);
          frenteEncoder(250, 100, 100);
          curva90GrausEsquerdaObjeto();
          travarMotores();
          delay(1000);
          trasEncoder(150, 100, 100);
          digitalWrite(ledEsquerda, LOW);
          digitalWrite(ledVerde, LOW);
          digitalWrite(ledAzul, HIGH);
          e = 1;
        }
        if ((verificaVerdeEsquerda() == false) && (verificaVerdeDireita() == true) && (e == 0)) {
          Serial.println("*********** VERDE DIREITA ************");
          digitalWrite(ledAzul, LOW);
          digitalWrite(ledDireita, HIGH);
          digitalWrite(ledVerde, HIGH);
          frenteEncoder(250, 100, 100);
          curva90GrausDireitaObjeto();
          trasEncoder(150, 100, 100);
          digitalWrite(ledDireita, LOW);
          digitalWrite(ledVerde, LOW);
          digitalWrite(ledAzul, HIGH);
          e = 1;
        } else if ((verificaVerdeEsquerda() == true) && (verificaVerdeDireita() == true) && (e == 0)) {
          Serial.println("*********** VERDE ESQUERDA E DIREITA ************");
          digitalWrite(ledAzul, LOW);
          digitalWrite(ledEsquerda, HIGH);
          digitalWrite(ledDireita, HIGH);
          digitalWrite(ledVerde, HIGH);
          curva90GrausEsquerdaObjeto();
          travarMotores();
          delay(700);
          curva90GrausEsquerdaObjeto();
          trasEncoder(150, 100, 100);
          digitalWrite(ledDireita, LOW);
          digitalWrite(ledEsquerda, LOW);
          digitalWrite(ledVerde, LOW);
          digitalWrite(ledAzul, HIGH);
          e = 1;
        }
        if (e == 0) {
          //while (verificaEncruzilhada() == true) {
          frenteEncoder(70, 100, 100);
          //} //Fim do while(verificaEncruzilhada())
        } //Fim do if(e == 0)
      } //Fim do if(verificaEncruzilhada())
    } //Fim do while(condicao)
  } //Fim do método seguidor


