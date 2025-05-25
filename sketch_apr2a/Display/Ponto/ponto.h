
#ifndef PONTO_H
#define PONTO_H

struct Ponto{
  int x = 0;
  int y = 0;
} pontoreal;


Ponto inverterXDisplay(Ponto invert_x);

Ponto formatar_32x32_8x128(uint8_t coluna, uint8_t linha);

#endif // PONTO_H
