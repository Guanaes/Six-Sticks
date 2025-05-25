#include "sticks.h"


void rotacionarPontos(struct Stick *stick) {
    // 1) Encontra o bounding box atual (mínimos e máximos)
    uint8_t minX = stick->pontosX[0], maxX = stick->pontosX[0];
    uint8_t minY = stick->pontosY[0], maxY = stick->pontosY[0];
    for (int i = 1; i < 8; i++) {
        if (stick->pontosX[i] < minX) minX = stick->pontosX[i];
        if (stick->pontosX[i] > maxX) maxX = stick->pontosX[i];
        if (stick->pontosY[i] < minY) minY = stick->pontosY[i];
        if (stick->pontosY[i] > maxY) maxY = stick->pontosY[i];
    }

    // 2) Centro do quadrado que envolve o stick
    double cx = (minX + maxX) / 2.0;
    double cy = (minY + maxY) / 2.0;

    // 3) Computa os novos pontos
    uint8_t novosX[8], novosY[8];
    if (!stick->deitado) {
        // rota 90° CW:  (x', y') = ( cx + (y - cy),  cy - (x - cx) )
        for (int i = 0; i < 8; i++) {
            double x = stick->pontosX[i];
            double y = stick->pontosY[i];
            novosX[i] = (uint8_t)round(cx + (y - cy));
            novosY[i] = (uint8_t)round(cy - (x - cx));
        }
    } else {
        // rota 90° CCW: (x', y') = ( cx - (y - cy),  cy + (x - cx) )
        for (int i = 0; i < 8; i++) {
            double x = stick->pontosX[i];
            double y = stick->pontosY[i];
            novosX[i] = (uint8_t)round(cx - (y - cy));
            novosY[i] = (uint8_t)round(cy + (x - cx));
        }
    }

    // 4) Atualiza o struct e inverte o flag
    memcpy(stick->pontosX, novosX, sizeof(novosX));
    memcpy(stick->pontosY, novosY, sizeof(novosY));
    stick->deitado = !stick->deitado;
}

void iniciarSticks() {
  const uint8_t espaco = 1;
  sticks[0].pontosY[0] = 2; sticks[0].pontosX[0] = 15; sticks[0].posicao = 12;
  displayStickInicial(&sticks[0]);
  for (uint8_t i = 1; i < 6; i++) {
    sticks[i].pontosX[0] = 15;
    sticks[i].pontosY[0] = sticks[i-1].pontosY[0] + sticks[i-1].alturaEmPe + espaco;
    sticks[i].posicao = sticks[i - 1].posicao + 1;
    displayStickInicial(&sticks[i]);
  }
}

