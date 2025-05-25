#include "borda.h"

void bordaCartas() {
  for (uint8_t i = 0; i < 32; i++) {
    if (i == 0 || i == 31) {
      for (uint8_t j = 0; j < 32; j++)
        displayPontoReal(j,i);
    }
    displayPontoReal(0,i);
    displayPontoReal(31, i);
  }

  for (uint8_t x = 15; x <= 16; x++) 
    for (uint8_t y = 0; y < 32; y++)
      displayPontoReal(x, y);
  

  uint8_t divisorias[3] = {7, 14, 21};
    for (uint8_t i = 0; i < 3; i++) {
      for (uint8_t x = 1; x < 31; x++) { 
        displayPontoReal(x, divisorias[i]);
      }
    }
}

void borda() {
  for (uint8_t i = 0; i < 32; i++) {
    if (i == 0 || i == 31) {
      for (uint8_t j = 0; j < 32; j++) {
        displayPontoReal(j, i);
      }
    }
    if (i < 10 || i > 20) {
      displayPontoReal(0, i);
      displayPontoReal(31, i);
    }
  }
}