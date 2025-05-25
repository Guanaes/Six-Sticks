#include <MD_MAX72xx.h>

#include "defines.h"
#include "Som/pitches.c"
#include "Posicoes/posicoes.c"
#include "Display/display.c"
#include "Display/Ponto/ponto.c"
#include "Player/player.h"
#include "Sticks/stick.c"
#include "Display/Borda/borda.c"
#include "Gameplay/Mover/mover.c"
#include "Gameplay/Logica/logica.c"
#include "Gameplay/Rotacionar/rotacionar.c"
#include "Gameplay/Turno/turno.c"


void setup() {
  Serial.begin(115200);
  displayCentral.begin(); displayCentral.clear(); displayCentral.control(MD_MAX72XX::INTENSITY, 10);
  displayAux.begin();    displayAux.clear();    displayAux.control(MD_MAX72XX::INTENSITY, 10);

  
  // Configurações de entrada
  pinMode(VERT_PIN_P1, INPUT); pinMode(HORZ_PIN_P1, INPUT); pinMode(SEL_PIN_P1, INPUT_PULLUP);
  pinMode(VERT_PIN_P2, INPUT); pinMode(HORZ_PIN_P2, INPUT); pinMode(SEL_PIN_P2, INPUT_PULLUP);
  pinMode(BOTAO_ROTACIONAR_P1, INPUT_PULLUP); pinMode(BOTAO_MOVER_P1, INPUT_PULLUP);


  tocarSomInicio(BUZZER_PIN);
  borda();
  iniciarSticks();
  iniciarPosicoes();

  displayCentral.control(0, displayCentral.getDeviceCount() -1, MD_MAX72XX::INTENSITY, 1);
}

void loop() {
  player1.botaoRotacionar = BOTAO_ROTACIONAR_P1;
  player1.mover = BOTAO_MOVER_P1;
  player1.analogHor = HORZ_PIN_P1;
  player1.analoVert = VERT_PIN_P1;
  player1.turno = true;
  turno(&player1);
}









