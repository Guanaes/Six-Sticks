#include "ponto.h"

Ponto inverterXDisplay(Ponto invert_x) {
  Ponto pontoreal;
  uint8_t module = invert_x.x / 8;          // 0 a 3, para cada módulo de 8 colunas
  uint8_t colInModule = invert_x.x % 8;     // posição dentro do módulo
  uint8_t invCol = 7 - colInModule;         // inverte dentro de 0..7
  pontoreal.x = module * 8 + invCol;        // remonta coluna global
  pontoreal.y = invert_x.y;
  return pontoreal;
}

Ponto formatar_32x32_8x128(uint8_t coluna, uint8_t linha) {
  Ponto valorReal;
  // Divide a matriz 32x32 em faixas de 8 linhas, alinhando colunas
  valorReal.x = linha + (coluna / 8) * 32;
  valorReal.y = coluna % 8;
  return inverterXDisplay(valorReal);
}