#include <stdint.h>

#ifndef POSICOES_H
#define POSICOES_H

struct Posicoes{
  uint8_t pontosXEmPe[8];
  uint8_t pontosYEmPe[8];

  uint8_t pontosXDeitado[8];
  uint8_t pontosYDeitado[8];

  bool soPodeDeitar;
  bool ocupado;
}posicoes[30];

void iniciarPosicoes();


#endif // POSICOES_H



