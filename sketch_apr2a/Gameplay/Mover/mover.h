#include "../../Sticks/sticks.h"
#include "../../Posicoes/posicoes.h"

#ifndef MOVER_H
#define MOVER_H

void moverPalito(Stick *palito, struct Posicoes *posicao);
bool validarPosicao(int numPosicao, bool deitado);
void moverPontosTemp(int numero, bool deitado);

#endif // MOVER_H
