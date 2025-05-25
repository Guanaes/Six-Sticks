#include "rotacionar.h"

void rotacionarStick(struct Stick *stick) {
  copiarStick(stick);
  apagarStick(stick);
  rotacionarPontos(stick);
  displayStick(stick);
}