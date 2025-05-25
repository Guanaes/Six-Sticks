#include "logica.h"

void atualizarOcupadoPosicoes() {
  // Para cada posição possível
  for (int i = 0; i < 30; i++) {
    bool ocupado = false;
    // Verifica orientação em pé
    for (int j = 0; j < 8; j++) {
      // Converte para coordenadas do display central
      pontoreal = formatar_32x32_8x128(posicoes[i].pontosYEmPe[j], posicoes[i].pontosXEmPe[j]);
      if (displayCentral.getPoint(pontoreal.y, pontoreal.x)) {
        ocupado = true;
        break;
      }
    }
    // Se ainda não encontrado, verifica orientação deitada
    if (!ocupado && posicoes[i].soPodeDeitar) {
      for (int j = 0; j < 8; j++) {
        pontoreal = formatar_32x32_8x128(posicoes[i].pontosYDeitado[j], posicoes[i].pontosXDeitado[j]);
        if (displayCentral.getPoint(pontoreal.y, pontoreal.x)) {
          ocupado = true;
          break;
        }
      }
    }
    posicoes[i].ocupado = ocupado;
  }
}

void validarSticksTravados() {
  // Primeiro, atualiza posicoes[] para refletir ocupação atual
  atualizarOcupadoPosicoes();
  // Para cada stick
  for (int i = 0; i < 6; i++) {
    int p = sticks[i].posicao;
    int countAdj = 0;
    int neighbors[4];
    int nCount = 0;
    // Acima
    if (p >= 6)     neighbors[nCount++] = p - 6;
    // Abaixo
    if (p < 24)     neighbors[nCount++] = p + 6;
    // Esquerda
    if ((p % 6) != 0) neighbors[nCount++] = p - 1;
    // Direita
    if ((p % 6) != 5) neighbors[nCount++] = p + 1;
    // Conta quantos vizinhos ocupados
    for (int k = 0; k < nCount; k++) {
      if (posicoes[neighbors[k]].ocupado) countAdj++;
    }
    sticks[i].travado = (countAdj >= 2);
    // Imprime estado de travado
  }
}