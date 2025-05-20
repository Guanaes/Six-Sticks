#include <stdint.h>
struct Posicoes{
  uint8_t pontosXEmPe[8];
  uint8_t pontosYEmPe[8];

  uint8_t pontosXDeitado[8];
  uint8_t pontosYDeitado[8];

  bool soPodeDeitar;
  bool ocupado;
}posicoes[30];


