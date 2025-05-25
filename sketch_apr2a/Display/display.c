#include "display.h"

void displayPontoReal(uint8_t coluna, uint8_t linha) {
  pontoreal = formatar_32x32_8x128(coluna, linha);
  displayCentral.setPoint(pontoreal.y, pontoreal.x, true);
}

void displayStick(struct Stick *stick) {
  for (uint8_t ponto = 0; ponto < 8; ponto++) 
    displayPontoReal(stick->pontosY[ponto], stick->pontosX[ponto]);
}

void apagarStick(struct Stick *stick) {
  for (uint8_t ponto = 0; ponto < 8; ponto++) {
    pontoreal = formatar_32x32_8x128(stick->pontosY[ponto], stick->pontosX[ponto]);
    displayCentral.setPoint(pontoreal.y, pontoreal.x, false);
  }
}

void copiarStick(struct Stick *stick) {
  for (uint8_t ponto = 0; ponto < 8; ponto++) {
    temporario.pontosX[ponto] = stick->pontosX[ponto];
    temporario.pontosY[ponto] = stick->pontosY[ponto];
  }
}

void piscar(Stick* exemplo) {
  unsigned long currentMillis = millis();
  if (currentMillis - lastBlinkTime >= 250) {
    lastBlinkTime = currentMillis;
    blinkState = !blinkState;
    for (uint8_t i = 0; i < 8; i++) {
      pontoreal = formatar_32x32_8x128(exemplo->pontosY[i], exemplo->pontosX[i]);
      displayCentral.setPoint(pontoreal.y, pontoreal.x, blinkState);
    }
    garantiStickLigado(exemplo);
  }
}


void displayStickInicial(struct Stick* exemplo) {
  uint8_t posi = 0;
  for (uint8_t y = 0; y < exemplo->alturaEmPe; y++) {
    for (uint8_t x = 0; x < exemplo->larguraEmpe; x++) {
      uint8_t temp_x = exemplo->pontosX[0] + x;
      uint8_t temp_y = exemplo->pontosY[0] + y;
      exemplo->pontosX[posi] = temp_x;
      exemplo->pontosY[posi] = temp_y;
      posi++;
      displayPontoReal(temp_y, temp_x);
    }
  }
}

void garantiStickLigado(Stick* exemplo){
    if(!displayCentral.getPoint(exemplo->pontosY[0], exemplo->pontosX[0])) {
      displayStick(exemplo);
    }
}
