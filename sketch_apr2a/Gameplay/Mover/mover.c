#include "mover.h"

void moverPalito(Stick *palito, struct Posicoes *posicao) {
  if (palito->deitado) {
    for (int i = 0; i < 8; i++) {
      palito->pontosX[i] = posicao->pontosXDeitado[i];
      palito->pontosY[i] = posicao->pontosYDeitado[i];
    }
  } else {
    for (int i = 0; i < 8; i++) {
      palito->pontosX[i] = posicao->pontosXEmPe[i];
      palito->pontosY[i] = posicao->pontosYEmPe[i];
    }
  }
  posicao->ocupado = true;
}

void moverPontosTemp(int numero, bool deitado){
  apagarStick(&temporario);
  if (deitado) {
    for (int i = 0; i < 8; ++i) {
    temporario.pontosX[i] = posicoes[numero].pontosXDeitado[i];
    temporario.pontosY[i] = posicoes[numero].pontosYDeitado[i];
    }
  } else {
    for (int i = 0; i < 8; ++i) {
    temporario.pontosX[i] = posicoes[numero].pontosXEmPe[i];
    temporario.pontosY[i] = posicoes[numero].pontosYEmPe[i];
    }
  }
  displayStick(&temporario);
}

bool validarPosicao(int numPosicao, bool deitado) {
  if (!deitado && posicoes[numPosicao].soPodeDeitar) {
    return false;
  } else if (posicoes[numPosicao].ocupado) {
    return false;
  } else {
    return true;
  }
}