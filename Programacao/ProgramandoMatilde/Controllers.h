
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

  if (green_color < -600) {
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

  if (green_color < -650/*) && (green_color < -300)*/) {
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


boolean verificaSilverTap() {
  if (lerQTR(1) >= silverTape && lerQTR(2) >= silverTape && lerQTR(3) >= silverTape && lerQTR(4) >= silverTape && lerQTR(5) >= silverTape && lerQTR(6) >= silverTape && lerQTR(7) >= silverTape && lerQTR(8) >= silverTape) {
    return true;
  } else {
    return false;
  }
}

/********* TERCEIRO SALAO ************/
boolean verificaParede() {
  if ((lerBtnFrenteDireita() == 0) || (lerBtnFrenteEsquerda() == 0)) {
    return true;
  }
  return false;
}

boolean verificaBase() {
  if ((lerSharp(1) > 150) && (lerSharp(2) > 230)) {
    return true;
  }
  return false;
}

boolean verificaPitch1() {
  if (pitch < -22) {
    return true;
  } else {
    return false;
  }
}

boolean verificaPitch2() {
  if (pitch < -30) {
    return true;
  } else {
    return false;
  }
}

boolean verificaRampa() {
  if ((verificaPitch1() == true) &&  (verificaPitch2() == true) && (lerSharp(5) >= 320)) {
    return true;
  } else {
    return false;
  }
}

boolean verificaVitima() {
  if (lerSharp(3) > 250) {
    return true;
  } else {
    return false;
  }
}

boolean verificaRedutor() {
  if (lerBtnRedutor() == 0) {
    return true;
  }
  return false;
}

int p = 0;
int s = 0;
int t = 0;
int aux = 0;

void terceiroSalao(boolean condicao) {
  while (condicao == true) {
    servoCacamba.attach(7);
    servoCacamba.write(105);
    digitalWrite(ledDireita, LOW);
    digitalWrite(ledEsquerda, LOW);
    digitalWrite(ledAzul, HIGH);
    digitalWrite(ledVermelho, HIGH);
    analogWrite(motorGarraBaixo, 150);
    delay(2000);
    analogWrite(motorGarraBaixo, 0);
    curva90GrausEsquerdaObjeto();
    mover(-100, -150);
    delay(2500);
    frenteEncoder(2000, 90, 90);
    curva90GrausDireitaObjeto();
    mover(-100, -150);
    delay(2500);
    travarMotores();
    delay(1000);

    aux = 1;
    while (aux == 1) {
      mover(80, 90);
      if (verificaParede() == true) {
        trasEncoder(100, 100, 100);
        frenteEncoder(100, 200, 200);
        trasEncoder(100, 100, 100);
        frenteEncoder(100, 200, 200);
        trasEncoder(500, 90, 90);
        travarMotores();
        delay(1000);
        analogWrite(motorGarraCima, 180);
        delay(2000);
        analogWrite(motorGarraCima, 0);
        travarMotores();
        delay(1000);
        if (verificaVitima() == true) {
          sinalizar();
          analogWrite(motorGarraBaixo, 150);
          delay(2000);
          analogWrite(motorGarraBaixo, 0);
          curva90GrausEsquerdaObjeto();
          travarMotores();
          delay(1000);
          trasEncoder(400, 90, 90);
          travarMotores();
          delay(1000);
          if (verificaBase() == true) {
            digitalWrite(ledEsquerda, HIGH);
            delay(700);
            digitalWrite(ledEsquerda, LOW);
            curva45GrausEsquerda();
            travarMotores();
            delay(1000);
            mover(-90, -90);
            delay(2000);
            servoCacamba.write(180);
            travarMotores();
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            servoCacamba.write(105);
            //
            frenteEncoder(100, 100, 100);
            curva45GrausDireita();
            while (verificaParede() == false) {
              mover(80, 90);
            }
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(500, 90, 90);
            while (lerBtnGarraParar() == 1) {
              analogWrite(motorGarraCima, 150);
            }
            analogWrite(motorGarraCima, 0);
            delay(1000);
            if (verificaVitima() == true) {
              sinalizar();
              trasEncoder(2300, 100, 100);
              curva45GrausEsquerda();
              mover(-90, -90);
              delay(2000);
              servoCacamba.write(180);
              travarMotores();
              delay(1000);
              frenteEncoder(100, 100, 100);
              trasEncoder(100, 200, 200);
              delay(1000);
              frenteEncoder(100, 100, 100);
              trasEncoder(100, 200, 200);
              delay(1000);
              servoCacamba.write(105);
              //
              frenteEncoder(100, 100, 100);
              curva45GrausDireita();
              //Ir até o lugar da segunda ronda
              frenteEncoder(2200, 100, 100);
              curva90GrausEsquerdaRodrigo();
              mover(-90, -100);
              delay(2000);
              travarMotores();
              delay(1000);
              analogWrite(motorGarraBaixo, 150);
              delay(2000);
              analogWrite(motorGarraBaixo, 0);
              p = 1;
              aux = 2;
            } else {
              trasEncoder(500, 100, 100);
              curva90GrausEsquerdaObjeto();
              mover(-90, -90);
              delay(2000);
              travarMotores();
              delay(1000);
              analogWrite(motorGarraBaixo, 150);
              delay(2000);
              analogWrite(motorGarraBaixo, 0);
              p = 1;
              aux = 2;
            }
          } else {
            frenteEncoder(1300, 90, 90);
            travarMotores();
            delay(1000);
            curva90GrausEsquerdaObjeto();
            curva90GrausEsquerdaObjeto();
            travarMotores();
            delay(1000);
            if (verificaBase() == true) {
              digitalWrite(ledDireita, HIGH);
              delay(700);
              digitalWrite(ledDireita, LOW);
              curva45GrausDireita();
              travarMotores();
              delay(1000);
              mover(-90, -90);
              delay(2000);
              servoCacamba.write(180);
              travarMotores();
              delay(1000);
              frenteEncoder(100, 100, 100);
              trasEncoder(100, 200, 200);
              delay(1000);
              frenteEncoder(100, 100, 100);
              trasEncoder(100, 200, 200);
              delay(1000);
              servoCacamba.write(105);
              curva45GrausEsquerda();
              frenteEncoder(300, 100, 100);
              curva90GrausDireitaObjeto();
              mover(-90, -90);
              delay(2000);
              s = 1;
              aux = 2;
            } else {
              curva90GrausDireitaObjeto();
              mover(-90, -90);
              delay(2000);
              while (verificaParede() == false) {
                mover(80, 90);
              }
              digitalWrite(ledDireita, HIGH);
              delay(700);
              digitalWrite(ledDireita, LOW);
              trasEncoder(100, 100, 100);
              frenteEncoder(100, 200, 200);
              trasEncoder(100, 100, 100);
              frenteEncoder(100, 200, 200);
              trasEncoder(900, 90, 90);
              travarMotores();
              delay(1000);
              analogWrite(motorGarraCima, 180);
              delay(2000);
              analogWrite(motorGarraCima, 0);
              curva90GrausEsquerdaObjeto();
              travarMotores();
              delay(1000);
              curva45GrausEsquerda();
              mover(-90, -90);
              delay(2000);
              servoCacamba.write(180);
              travarMotores();
              delay(1000);
              frenteEncoder(100, 100, 100);
              trasEncoder(100, 200, 200);
              delay(1000);
              frenteEncoder(100, 100, 100);
              trasEncoder(100, 200, 200);
              delay(1000);
              servoCacamba.write(105);
              analogWrite(motorGarraBaixo, 180);
              delay(3000);
              analogWrite(motorGarraBaixo, 0);
              travarMotores();
              delay(1000);
              frenteEncoder(200, 90, 90);
              curva45GrausDireita();
              frenteEncoder(200, 90, 90);
              curva90GrausEsquerdaObjeto();
              mover(-90, -90);
              delay(2000);
              frenteEncoder(200, 90, 90);
              curva90GrausDireitaObjeto();
              travarMotores();
              delay(1000);
              t = 1;
              aux = 3;
            }
          }
        } else {
          analogWrite(motorGarraBaixo, 150);
          delay(1000);
          analogWrite(motorGarraBaixo, 0);
          curva90GrausEsquerdaObjeto();
          trasEncoder(100, 90, 90);
          travarMotores();
          delay(1000);
          if (verificaBase() == true) {
            digitalWrite(ledDireita, HIGH);
            delay(700);
            digitalWrite(ledDireita, LOW);
            //frenteEncoder(2200, 90, 90);
            while (verificaParede() == false) {
              mover(80, 90);
            }
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(200, 90, 90);
            // trasEncoder(100, 100, 100);
            while (lerBtnGarraParar() == 1) {
              analogWrite(motorGarraCima, 200);
            }
            analogWrite(motorGarraCima, 0);
            delay(1000);
            if (verificaVitima() == true) {
              sinalizar();
              trasEncoder(2300, 100, 100);
              curva45GrausEsquerda();
              mover(-90, -90);
              delay(2000);
              servoCacamba.write(180);
              travarMotores();
              delay(1000);
              frenteEncoder(100, 100, 100);
              trasEncoder(100, 200, 200);
              delay(1000);
              frenteEncoder(100, 100, 100);
              trasEncoder(100, 200, 200);
              delay(1000);
              servoCacamba.write(105);
              //
              frenteEncoder(100, 100, 100);
              curva45GrausDireita();
              //Ir até o lugar da segunda ronda
              frenteEncoder(2200, 100, 100);
              curva90GrausEsquerdaRodrigo();
              mover(-90, -100);
              delay(2000);
              travarMotores();
              delay(1000);
              analogWrite(motorGarraBaixo, 150);
              delay(2000);
              analogWrite(motorGarraBaixo, 0);
              p = 1;
              aux = 2;
            } else {
              /////////////////////////
              trasEncoder(500, 100, 100);
              curva90GrausEsquerdaObjeto();
              mover(-90, -90);
              delay(2000);
              travarMotores();
              delay(1000);
              analogWrite(motorGarraBaixo, 150);
              delay(2000);
              analogWrite(motorGarraBaixo, 0);
              p = 1;
              aux = 2;
            }
          } else {
            frenteEncoder(900, 90, 90);
            travarMotores();
            delay(1000);
            curva90GrausEsquerdaObjeto();
            curva90GrausEsquerdaObjeto();
            travarMotores();
            delay(1000);
            if (verificaBase() == true) {
              digitalWrite(ledDireita, HIGH);
              delay(700);
              digitalWrite(ledDireita, LOW);
              curva90GrausDireitaObjeto();
              mover(-90, -100);
              delay(2000);
              s = 1;
              aux = 2;
            } else {
              curva90GrausDireitaObjeto();
              mover(-90, -120);
              delay(2000);
              travarMotores();
              delay(1000);
              t = 1;
              aux = 2;
            }
          }
        }
      }
    }


    while (aux = 2) {
      mover(80, 85);
      if (verificaParede() == true) {
        trasEncoder(100, 100, 100);
        frenteEncoder(100, 200, 200);
        trasEncoder(100, 100, 100);
        frenteEncoder(100, 200, 200);
        trasEncoder(400, 90, 90);
        travarMotores();
        delay(1000);
        while (lerBtnGarraParar() == 1) {
          analogWrite(motorGarraCima, 150);
        }
        analogWrite(motorGarraCima, 0);
        delay(1000);
        travarMotores();
        delay(1000);
        if ((p == 0) && (s == 1) && (t == 0)) {
          frenteEncoder(400, 90, 90);
          curva90GrausDireitaObjeto();
          analogWrite(motorGarraBaixo, 150);
          delay(2000);
          analogWrite(motorGarraBaixo, 0);
          while (verificaParede() == false) {
            mover(80, 90);
          }
          trasEncoder(100, 100, 100);
          frenteEncoder(100, 200, 200);
          trasEncoder(100, 100, 100);
          frenteEncoder(100, 200, 200);
          trasEncoder(300, 90, 90);
          while (lerBtnGarraParar() == 1) {
            analogWrite(motorGarraCima, 150);
          }
          analogWrite(motorGarraCima, 0);
          delay(1000);
          if (verificaVitima() == true) {
            sinalizar();
            trasEncoder(600, 90, 90);
            curva90GrausEsquerdaObjeto();
            trasEncoder(2600, 100, 115);
            curva45GrausEsquerda();
            mover(-90, -90);
            delay(2000);
            servoCacamba.write(180);
            travarMotores();
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            servoCacamba.write(105);
            //
            frenteEncoder(500, 100, 100);
            curva45GrausEsquerda();
            mover(-90, -90);
            delay(2000);
            analogWrite(motorGarraBaixo, 150);
            delay(2000);
            analogWrite(motorGarraBaixo, 0);
            while (verificaParede() == false) {
              mover(80, 90);
            }
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(300, 90, 90);
            while (lerBtnGarraParar() == 1) {
              analogWrite(motorGarraCima, 150);
            }
            analogWrite(motorGarraCima, 0);
            delay(1000);
            curva90GrausEsquerdaObjeto();
            analogWrite(motorGarraBaixo, 150);
            delay(2000);
            analogWrite(motorGarraBaixo, 0);
            while (verificaParede() == false) {
              mover(80, 90);
            }
            trasEncoder(200, 100, 100);
            frenteEncoder(200, 200, 200);
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(600, 90, 90);
            while (lerBtnGarraParar() == 1) {
              analogWrite(motorGarraCima, 150);
            }
            analogWrite(motorGarraCima, 0);
            delay(1000);
            curva90GrausDireitaObjeto();
            trasEncoder(300, 200, 200);
            analogWrite(motorGarraBaixo, 150);
            delay(2000);
            analogWrite(motorGarraBaixo, 0);
            mover(90, 90);
            delay(2000);
            trasEncoder(3000, 90, 90);
            curva45GrausDireita();
            mover(-90, -90);
            delay(2000);
            servoCacamba.write(180);
            travarMotores();
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            servoCacamba.write(105);
          } else {
            curva90GrausDireitaObjeto();
            curva90GrausDireitaObjeto();
            mover(-90, -90);
            delay(2000);
            analogWrite(motorGarraBaixo, 150);
            delay(2000);
            analogWrite(motorGarraBaixo, 0);
            while (verificaParede() == false) {
              mover(80, 90);
            }
            trasEncoder(200, 100, 100);
            frenteEncoder(200, 200, 200);
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(600, 90, 90);
            while (lerBtnGarraParar() == 1) {
              analogWrite(motorGarraCima, 150);
            }
            analogWrite(motorGarraCima, 0);
            delay(1000);
            //frenteEncoder(200, 100, 100);
            curva90GrausEsquerdaObjeto();
            analogWrite(motorGarraBaixo, 150);
            delay(2000);
            analogWrite(motorGarraBaixo, 0);
            while (verificaParede() == false) {
              mover(80, 90);
            }
            trasEncoder(200, 100, 100);
            frenteEncoder(200, 200, 200);
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(600, 90, 90);
            while (lerBtnGarraParar() == 1) {
              analogWrite(motorGarraCima, 150);
            }
            analogWrite(motorGarraCima, 0);
            delay(1000);
            trasEncoder(200, 100, 100);
            curva90GrausDireitaObjeto();
            analogWrite(motorGarraBaixo, 150);
            delay(2000);
            analogWrite(motorGarraBaixo, 0);
            mover(90, 90);
            delay(2000);
            trasEncoder(3000, 100, 100);
            curva45GrausDireita();
            mover(-90, -90);
            delay(2000);
            servoCacamba.write(180);
            travarMotores();
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            servoCacamba.write(105);
            travarMotores();
            delay(200000);
            //            frenteEncoder(400, 90, 90);
            //            curva90GrausDireitaObjeto();
            //            analogWrite(motorGarraBaixo, 150);
            //            delay(2000);
            //            analogWrite(motorGarraBaixo, 0);
            //            mover(-90, -90);
            //            delay(2000);
            //            frenteEncoder(2700, 80, 80);
            //            curva90GrausDireitaObjeto();
            //            mover(-90, -90);
            //            delay(2000);
            //            while (verificaParede() == false) {
            //              mover(80, 90);
            //            }
            //            trasEncoder(100, 100, 100);
            //            frenteEncoder(100, 200, 200);
            //            trasEncoder(100, 100, 100);
            //            frenteEncoder(100, 200, 200);
            //            trasEncoder(300, 90, 90);
            //            while (lerBtnGarraParar() == 1) {
            //              analogWrite(motorGarraCima, 150);
            //            }
            //            analogWrite(motorGarraCima, 0);
            //            delay(1000);
            //            frenteEncoder(400, 90, 90);
            //            curva90GrausEsquerdaObjeto();
            //            analogWrite(motorGarraBaixo, 150);
            //            delay(2000);
            //            analogWrite(motorGarraBaixo, 0);
            //            while (verificaParede() == false) {
            //              mover(80, 90);
            //            }
            //            travarMotores();
            //            delay(200000000000000);
          }
          //          curva45GrausEsquerda();
          //          trasEncoder(100, 100, 100);
          //          frenteEncoder(300, 200, 200);
          //          trasEncoder(100, 100, 100);
          //          frenteEncoder(300, 200, 200);
          //          trasEncoder(600, 90, 90);
          //          while (lerBtnGarraParar() == 1) {
          //            analogWrite(motorGarraCima, 150);
          //          }
          //          analogWrite(motorGarraCima, 0);
          //          delay(1000);
          //          curva45GrausDireita();
          //          curva90GrausDireitaObjeto();
          //          curva90GrausDireitaObjeto();
          //          curva45GrausEsquerda();
          //          mover(-90, -90);
          //          delay(2000);
          //          sinalizar();
          //          servoCacamba.write(180);
          //          travarMotores();
          //          delay(1000);
          //          frenteEncoder(100, 100, 100);
          //          trasEncoder(100, 200, 200);
          //          delay(1000);
          //          frenteEncoder(100, 100, 100);
          //          trasEncoder(100, 200, 200);
          //          delay(1000);
          //          servoCacamba.write(105);
          //          travarMotores();
          //          delay(1000);

        }
        if (verificaVitima() == true) {
          if ((p == 0) && (s == 0) && (t == 1)) {
            trasEncoder(500, 100, 100);
            sinalizar();
            analogWrite(motorGarraBaixo, 150);
            delay(2000);
            analogWrite(motorGarraBaixo, 0);
            curva90GrausEsquerdaObjeto();
            curva45GrausEsquerda();
            mover(-90, -90);
            delay(2000);
            servoCacamba.write(180);
            travarMotores();
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            servoCacamba.write(105);
            travarMotores();
            delay(1000);
            frenteEncoder(300, 100, 100);
            curva45GrausDireita();
            curva90GrausEsquerdaObjeto();
            frenteEncoder(1800, 100, 100);
            travarMotores();
            delay(1000);
            curva90GrausEsquerdaObjeto();
            while (verificaParede() == false) {
              mover(80, 90);
            }
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(500, 90, 90);
            while (lerBtnGarraParar() == 1) {
              analogWrite(motorGarraCima, 150);
            }
            analogWrite(motorGarraCima, 0);
            curva90GrausDireitaObjeto();
            curva90GrausDireitaObjeto();
            analogWrite(motorGarraBaixo, 150);
            delay(2000);
            analogWrite(motorGarraBaixo, 0);
            mover(-90, -90);
            delay(2000);
            while (verificaParede() == false) {
              mover(80, 90);
            }
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(400, 90, 90);
            while (lerBtnGarraParar() == 1) {
              analogWrite(motorGarraCima, 150);
            }
            analogWrite(motorGarraCima, 0);
            curva90GrausEsquerdaObjeto();
            analogWrite(motorGarraBaixo, 150);
            delay(2000);
            analogWrite(motorGarraBaixo, 0);
            while (verificaParede() == false) {
              mover(80, 90);
            }
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(400, 90, 90);
            while (lerBtnGarraParar() == 1) {
              analogWrite(motorGarraCima, 150);
            }
            analogWrite(motorGarraCima, 0);
            curva90GrausEsquerdaObjeto();
            analogWrite(motorGarraBaixo, 150);
            delay(2000);
            analogWrite(motorGarraBaixo, 0);
            while (verificaParede() == false) {
              mover(80, 90);
            }
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(400, 90, 90);
            while (lerBtnGarraParar() == 1) {
              analogWrite(motorGarraCima, 150);
            }
            analogWrite(motorGarraCima, 0);
            curva90GrausDireitaObjeto();
            trasEncoder(2000, 100, 100);
            curva45GrausDireita();
            mover(-90, -90);
            delay(2000);
            servoCacamba.write(180);
            travarMotores();
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            servoCacamba.write(105);
            travarMotores();
            delay(1000);
            travarMotores();
            delay(100000000);
          }
          if ((p == 1) && (s == 0) && (t == 0)) {
            sinalizar();
            analogWrite(motorGarraBaixo, 150);
            delay(2000);
            analogWrite(motorGarraBaixo, 0);
            curva90GrausDireitaObjeto();
            curva90GrausDireitaObjeto();
            mover(-90, -100);
            delay(2000);
            while (verificaParede() == false) {
              mover(80, 90);
            }
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(500, 90, 90);
            analogWrite(motorGarraCima, 180);
            delay(2000);
            analogWrite(motorGarraCima, 0);
            trasEncoder(900, 90, 90); // aqui é o problema
            curva90GrausEsquerdaRodrigo();
            analogWrite(motorGarraBaixo, 150);
            delay(2000);
            analogWrite(motorGarraBaixo, 0);
            travarMotores();
            delay(1000);
            trasEncoder(2300, 90, 90); //andarMais
            travarMotores();
            delay(1000);
            curva45GrausEsquerda();
            travarMotores();
            delay(1000);
            mover(-90, -90);
            delay(2000);
            servoCacamba.write(180);
            travarMotores();
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            servoCacamba.write(105);
            travarMotores();
            delay(1000);
          }
        } else {
          if ((p == 1) && (s == 0) && (t == 0)) {
            frenteEncoder(400, 90, 90);
            curva90GrausDireitaObjeto();
            analogWrite(motorGarraBaixo, 180);
            delay(2000);
            analogWrite(motorGarraBaixo, 0);
            while (verificaParede() == false) {
              mover(80, 90);
            }
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(100, 100, 100);
            while (lerBtnGarraParar() == 1) {
              analogWrite(motorGarraCima, 150);
            }
            analogWrite(motorGarraCima, 0);
            delay(1000);
            frenteEncoder(200, 100, 100);
            curva90GrausDireitaObjeto();
            mover(-90, -100);
            delay(2000);
            analogWrite(motorGarraBaixo, 180);
            delay(2000);
            analogWrite(motorGarraBaixo, 0);
            while (verificaParede() == false) {
              mover(80, 90);
            }
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(100, 100, 100);
            frenteEncoder(100, 200, 200);
            trasEncoder(500, 90, 90);
            while (lerBtnGarraParar() == 1) {
              analogWrite(motorGarraCima, 150);
            }
            analogWrite(motorGarraCima, 0);
            delay(1000);
            curva45GrausEsquerda();
            trasEncoder(900, 100, 100);
            curva45GrausEsquerda();
            trasEncoder(2200, 100, 100);
            curva45GrausEsquerda();
            mover(-90, -100);
            delay(3000);
            servoCacamba.write(180);
            travarMotores();
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            frenteEncoder(100, 100, 100);
            trasEncoder(100, 200, 200);
            delay(1000);
            servoCacamba.write(105);

          }
        }
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



    if (verificaRedutor() == true) {
      digitalWrite(ledAzul, LOW);
      digitalWrite(ledVermelho, HIGH);
      int b = 1;
      mover(170, 180);
      delay(300);
      b = 0;
      digitalWrite(ledVermelho, LOW);
      digitalWrite(ledAzul, HIGH);
    } else {
      PID(KP, KI, KD, forcaPID, setPoint);
    }

    if (verificaRampa() == true) {
      Serial.println("******************************* RAMPA *****************************");
      //      travarMotores();
      //      delay(500);
      analogWrite(motorGarraBaixo, 100);
      delay(200);
      analogWrite(motorGarraBaixo, 0);
      digitalWrite(ledAzul, LOW);
      digitalWrite(ledDireita, HIGH);
      digitalWrite(ledEsquerda, HIGH);
      while (verificaSilverTap() == false) {
        PID(0.15, KI, 0, 200, setPoint);
        if (verificaGap() == true) {
          Serial.println("******************************* GAP *****************************");
          while (verificaGap() == true) {
            gap(salaoRampa);
          }
        }
        if (verificaRedutor() == true) {
          digitalWrite(ledAzul, LOW);
          digitalWrite(ledVermelho, HIGH);
          int b = 1;
          mover(180, 230);
          delay(1000);
          b = 0;
          digitalWrite(ledVermelho, LOW);
          digitalWrite(ledAzul, HIGH);
        } else {
          PID(KP, KI, KD, forcaPID, setPoint);
        }
      }

      frenteEncoder(1700, 100, 100);
      travarMotores();
      delay(1000);
      digitalWrite(ledDireita, LOW);
      digitalWrite(ledEsquerda, LOW);
      digitalWrite(ledAzul,  HIGH);
      while (true) {
        terceiroSalao(true);
      }
    }


    PID(KP, KI, KD, forcaPID, setPoint);
    Serial.println("***** PID *****");

    if (verificaObjeto() == true) {
      obstaculoCount++;
      if (obstaculoCount == 1) {
        objeto(esquerda);
      } else if (obstaculoCount == 2) {
        objeto(esquerda);
      } else if (obstaculoCount == 3) {
        objeto(esquerda);
      } else {
        objeto(direita);
      }
    }

    if (verificaGap() == true) {
      Serial.println("*********** GAP ************");
      digitalWrite(ledAzul, LOW);
      digitalWrite(ledDireita, HIGH);
      digitalWrite(ledEsquerda, HIGH);
      digitalWrite(ledVermelho, HIGH);
      Serial.println("******* GAP *******");
      while (verificaGap() == true) {
        gap(salaoPrincipal);
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


