#ifndef PLAYER_H
#define PLAYER_H

struct Player{
  bool turno = false;
  int vertical = 512;
  int horizontal = 512;
  bool pressionadoR3 = false;
  int movimentos = 0;
  int botaoRotacionar;
  int analogHor;
  int analoVert;
  int mover;
}player1, player2;


#endif // PLAYER_H
