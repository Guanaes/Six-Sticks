#ifndef STICKS_H
#define STICKS_H

struct Stick{
  uint8_t pontosX[8];
  uint8_t pontosY[8];
  uint8_t display = 0;
  uint8_t posicao = 0;
  const uint8_t alturaEmPe= 4;
  const uint8_t larguraEmpe = 2;
  const uint8_t alturaDeitado= 2;
  const uint8_t larguraDeitado = 4;
  bool deitado = false;
  bool inGame = true;
  bool travado = false;
} sticks[6], temporario;

void rotacionarPontos(struct Stick *stick);
void iniciarSticks();

#endif // STICKS_H
