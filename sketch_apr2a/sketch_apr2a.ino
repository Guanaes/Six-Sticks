#include "defines.h"
#include <MD_MAX72xx.h>
#include "pitches.h"
#include "posicoes.h"

// Varieveis globais - Display Central
MD_MAX72XX displayCentral = MD_MAX72XX(HARDWARE_TYPE, DIN_PIN_CENTRAL_DISPLAY, CLK_PIN_CENTRAL_DISPLAY, CS_PIN_CENTRAL_DISPLAY, MAX_DEVICES_CENTRAL_DISPLAY);
const uint8_t TOTAL_PIX_CENTRAL_X = MAX_DEVICES_CENTRAL_DISPLAY * 8; //128 para 16 mod
// Varieveis globais - Display Auxiliar
MD_MAX72XX displayAux = MD_MAX72XX(HARDWARE_TYPE, DIN_PIN_AUX_DISPLAY, CLK_PIN_AUX_DISPLAY, CS_PIN_AUX_DISPLAY, MAX_DEVICES_AUX_DISPLAY);
const uint8_t TOTAL_PIX_AUX_X = MAX_DEVICES_AUX_DISPLAY * 8; //128 para 16 mod


unsigned long lastBlinkTime = 0;
bool blinkState = false;


struct Ponto{
  int x = 0;
  int y = 0;
} pontoreal;

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


struct Stick{
  uint8_t pontosX[8];
  uint8_t pontosY[8];
  uint8_t display = 0;
  uint8_t ID = 0;
  uint8_t posicao = 0;
  const uint8_t alturaEmPe= 4;
  const uint8_t larguraEmpe = 2;
  const uint8_t alturaDeitado= 2;
  const uint8_t larguraDeitado = 4;
  bool deitado = false;
  bool inGame = true;
  bool travado = false;
} sticks[6], temporario;



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

  // Exibe todas as posições (para teste)
  /*displayCentral.clear();
  for (int i = 0; i < 30; ++i) {
    for (int j = 0; j < 8; ++j) {
      if (!posicoes[i].soPodeDeitar) {
        pontoreal = formatar_32x32_8x128(posicoes[i].pontosYEmPe[j], posicoes[i].pontosXEmPe[j]);
        displayCentral.setPoint(pontoreal.y, pontoreal.x, true);
      }
      pontoreal = formatar_32x32_8x128(posicoes[i].pontosYDeitado[j], posicoes[i].pontosXDeitado[j]);
      displayCentral.setPoint(pontoreal.y, pontoreal.x, true);
    }
  }*/
}

void loop() {
  player1.botaoRotacionar = BOTAO_ROTACIONAR_P1;
  player1.mover = BOTAO_MOVER_P1;
  player1.analogHor = HORZ_PIN_P1;
  player1.analoVert = VERT_PIN_P1;
  player1.turno = true;
  turno(&player1);
}

void bordaCartas() {
  for (uint8_t i = 0; i < 32; i++) {
    if (i == 0 || i == 31) {
      for (uint8_t j = 0; j < 32; j++) {
        pontoreal = formatar_32x32_8x128(j, i);
        displayAux.setPoint(pontoreal.y, pontoreal.x, true);
      }
    }
      pontoreal = formatar_32x32_8x128(0, i);
      displayAux.setPoint(pontoreal.y, pontoreal.x, true);
      pontoreal = formatar_32x32_8x128(31, i);
      displayAux.setPoint(pontoreal.y, pontoreal.x, true);
  }

  for (uint8_t x = 15; x <= 16; x++) {
    for (uint8_t y = 0; y < 32; y++) {
      pontoreal = formatar_32x32_8x128(x, y);
      displayAux.setPoint(pontoreal.y, pontoreal.x, true);
    }
  }

  uint8_t divisorias[3] = {7, 14, 21};
    for (uint8_t i = 0; i < 3; i++) {
      for (uint8_t x = 1; x < 31; x++) {  // evita sobrescrever a borda
        pontoreal = formatar_32x32_8x128(x, divisorias[i]);
        displayAux.setPoint(pontoreal.y, pontoreal.x, true);
      }
    }
}

void borda() {
  for (uint8_t i = 0; i < 32; i++) {
    if (i == 0 || i == 31) {
      for (uint8_t j = 0; j < 32; j++) {
        pontoreal = formatar_32x32_8x128(j, i);
        displayCentral.setPoint(pontoreal.y, pontoreal.x, true);
      }
    }
    if (i < 10 || i > 20) {
      pontoreal = formatar_32x32_8x128(0, i);
      displayCentral.setPoint(pontoreal.y, pontoreal.x, true);
      pontoreal = formatar_32x32_8x128(31, i);
      displayCentral.setPoint(pontoreal.y, pontoreal.x, true);
    }
  }
}

void iniciarSticks() {
  const uint8_t espaco = 1;
  sticks[0].pontosY[0] = 2; sticks[0].pontosX[0] = 15; sticks[0].ID = 0; sticks[0].posicao = 12;
  displayStickInicial(&sticks[0]);
  for (uint8_t i = 1; i < 6; i++) {
    sticks[i].pontosX[0] = 15;
    sticks[i].pontosY[0] = sticks[i-1].pontosY[0] + sticks[i-1].alturaEmPe + espaco;
    sticks[i].ID = i;
    sticks[i].posicao = sticks[i - 1].posicao + 1;
    displayStickInicial(&sticks[i]);
  }
}

void displayStickInicial(struct Stick* exemplo) {
  uint8_t posi = 0;
  for (uint8_t y = 0; y < exemplo->alturaEmPe; y++) {
    for (uint8_t x = 0; x < exemplo->larguraEmpe; x++) {
      uint8_t temp_x = exemplo->pontosX[0] + x;
      uint8_t temp_y = exemplo->pontosY[0] + y;
      exemplo->pontosX[posi] = temp_x;
      exemplo->pontosY[posi] = temp_y;
      posi++;
      pontoreal = formatar_32x32_8x128(temp_y, temp_x);
      displayCentral.setPoint(pontoreal.y, pontoreal.x, true);
    }
  }
}

Ponto formatar_32x32_8x128(uint8_t coluna, uint8_t linha) {
  Ponto valorReal;
  // Divide a matriz 32x32 em faixas de 8 linhas, alinhando colunas
  valorReal.x = linha + (coluna / 8) * 32;
  valorReal.y = coluna % 8;
  return inverterXDisplay(valorReal);
}

Ponto inverterXDisplay(Ponto invert_x) {
  Ponto pontoreal;
  uint8_t module = invert_x.x / 8;          // 0 a 3, para cada módulo de 8 colunas
  uint8_t colInModule = invert_x.x % 8;     // posição dentro do módulo
  uint8_t invCol = 7 - colInModule;         // inverte dentro de 0..7
  pontoreal.x = module * 8 + invCol;        // remonta coluna global
  pontoreal.y = invert_x.y;
  return pontoreal;
}

void piscarNonBlocking(Stick* exemplo) {
  unsigned long currentMillis = millis();
  if (currentMillis - lastBlinkTime >= 250) {
    lastBlinkTime = currentMillis;
    blinkState = !blinkState;
    for (uint8_t i = 0; i < 8; i++) {
      pontoreal = formatar_32x32_8x128(exemplo->pontosY[i], exemplo->pontosX[i]);
      displayCentral.setPoint(pontoreal.y, pontoreal.x, blinkState);
    }
    garantiStickLigado(exemplo);
  }
}

void rotacionarPontos(struct Stick *stick) {
    // 1) Encontra o bounding box atual (mínimos e máximos)
    uint8_t minX = stick->pontosX[0], maxX = stick->pontosX[0];
    uint8_t minY = stick->pontosY[0], maxY = stick->pontosY[0];
    for (int i = 1; i < 8; i++) {
        if (stick->pontosX[i] < minX) minX = stick->pontosX[i];
        if (stick->pontosX[i] > maxX) maxX = stick->pontosX[i];
        if (stick->pontosY[i] < minY) minY = stick->pontosY[i];
        if (stick->pontosY[i] > maxY) maxY = stick->pontosY[i];
    }

    // 2) Centro do quadrado que envolve o stick
    double cx = (minX + maxX) / 2.0;
    double cy = (minY + maxY) / 2.0;

    // 3) Computa os novos pontos
    uint8_t novosX[8], novosY[8];
    if (!stick->deitado) {
        // rota 90° CW:  (x', y') = ( cx + (y - cy),  cy - (x - cx) )
        for (int i = 0; i < 8; i++) {
            double x = stick->pontosX[i];
            double y = stick->pontosY[i];
            novosX[i] = (uint8_t)round(cx + (y - cy));
            novosY[i] = (uint8_t)round(cy - (x - cx));
        }
    } else {
        // rota 90° CCW: (x', y') = ( cx - (y - cy),  cy + (x - cx) )
        for (int i = 0; i < 8; i++) {
            double x = stick->pontosX[i];
            double y = stick->pontosY[i];
            novosX[i] = (uint8_t)round(cx - (y - cy));
            novosY[i] = (uint8_t)round(cy + (x - cx));
        }
    }

    // 4) Atualiza o struct e inverte o flag
    memcpy(stick->pontosX, novosX, sizeof(novosX));
    memcpy(stick->pontosY, novosY, sizeof(novosY));
    stick->deitado = !stick->deitado;
}

void displayStick(struct Stick *stick) {
  for (uint8_t ponto = 0; ponto < 8; ponto++) {
    pontoreal = formatar_32x32_8x128(stick->pontosY[ponto], stick->pontosX[ponto]);
    displayCentral.setPoint(pontoreal.y, pontoreal.x, true);
  }
}

void apagarStick(struct Stick *stick) {
  for (uint8_t ponto = 0; ponto < 8; ponto++) {
    pontoreal = formatar_32x32_8x128(stick->pontosY[ponto], stick->pontosX[ponto]);
    displayCentral.setPoint(pontoreal.y, pontoreal.x, false);
  }
}

void copiarStick(struct Stick *stick) {
  for (uint8_t ponto = 0; ponto < 8; ponto++) {
    temporario.pontosX[ponto] = stick->pontosX[ponto];
    temporario.pontosY[ponto] = stick->pontosY[ponto];
  }
}

void rotacionarStick(struct Stick *stick) {
  copiarStick(stick);
  apagarStick(stick);
  rotacionarPontos(stick);
  displayStick(stick);
}

void turno(struct Player *player) {

  int stick_selecionado = 0;
  int buzzerPin = BUZZER_PIN;
  int newValue = 0; 

  while (player->turno) {
    validarSticksTravados();
    player->vertical = analogRead(player->analoVert);
    player->horizontal = analogRead(player->analogHor);
    int rotacionar = digitalRead(player->botaoRotacionar);
    int mover = digitalRead(player->mover);
    piscarNonBlocking(&sticks[stick_selecionado]);
    //garantiStickLigado();
  	

    if (player->vertical < 300) {
      stick_selecionado--;
      if (stick_selecionado < 0) {
        stick_selecionado = 5;
      }
      tocarSomSelecao(stick_selecionado, buzzerPin);
      delay(200);
    }
    if (player->vertical > 700) {
      stick_selecionado++;
      if (stick_selecionado > 5) {
        stick_selecionado = 0;
      }
      tocarSomSelecao(stick_selecionado, buzzerPin);
      delay(200);
    }
    if (player->horizontal > 700) {
      // ação para direita
    }
    if (player->horizontal < 300) {
      // ação para esquerda
    }

    if (rotacionar == LOW) {
      rotacionarStick(&sticks[stick_selecionado]);
      delay(200);
    }
    
    if (mover == LOW) {
      moverPalitoJogador(player, &sticks[stick_selecionado]);
    }
  }
}

void tocarSomSelecao(int stick_selecionado, int buzzerPin) {
  // Um array de notas para cada posição do stick
  const int tones[] = {
    NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4
  };

  // Proteção para índice inválido
  if (stick_selecionado >= 0 && stick_selecionado < 6) {
    tone(buzzerPin, tones[stick_selecionado], 100);
    delay(120); // Dá tempo de ouvir
    noTone(buzzerPin);
  }
}

void tocarSomInicio(int buzzerPin) {
  tone(buzzerPin, NOTE_C4, 150);
  delay(150);
  tone(buzzerPin, NOTE_E4, 150);
  delay(150);
  tone(buzzerPin, NOTE_G4, 200);
  delay(200);
  noTone(buzzerPin);
}

void iniciarPosicoes() {
    const uint8_t baseXs[5] = {5, 10, 15, 20, 25};
    const uint8_t baseY = 2;
    struct Stick temporario;
    int idx = 0;

    for (int col = 0; col < 5; col++) {
        uint8_t x0 = baseXs[col];
        for (int s = 0; s < 6; s++) {
            uint8_t y0 = baseY + s * 5; // 4 de altura + 1 de espaçamento

            // Preenche orientação em pé (2x4)
            for (int i = 0; i < 8; i++) {
                // alterna entre x0 e x0+1, incrementa Y a cada dois pontos
                posicoes[idx].pontosXEmPe[i] = x0 + (i % 2);
                posicoes[idx].pontosYEmPe[i] = y0 + (i / 2);
            }
            // por enquanto, marca como permissivo deitar
            posicoes[idx].soPodeDeitar = (col == 1 || col == 3);

            // Copia para temporário antes da rotação
            for (int i = 0; i < 8; i++) {
                temporario.pontosX[i] = posicoes[idx].pontosXEmPe[i];
                temporario.pontosY[i] = posicoes[idx].pontosYEmPe[i];
            }

            // Gera orientação deitada
            rotacionarPontos(&temporario);

            // Salva pontos rotacionados
            for (int i = 0; i < 8; i++) {
                posicoes[idx].pontosXDeitado[i] = temporario.pontosX[i];
                posicoes[idx].pontosYDeitado[i] = temporario.pontosY[i];
            }
            
            idx++;
        }
    }
}

void atualizarOcupadoPosicoes() {
  // Para cada posição possível
  for (int i = 0; i < 30; i++) {
    bool ocupado = false;
    // Verifica orientação em pé
    for (int j = 0; j < 8; j++) {
      // Converte para coordenadas do display central
      pontoreal = formatar_32x32_8x128(posicoes[i].pontosYEmPe[j], posicoes[i].pontosXEmPe[j]);
      if (displayCentral.getPoint(pontoreal.y, pontoreal.x)) {
        ocupado = true;
        break;
      }
    }
    // Se ainda não encontrado, verifica orientação deitada
    if (!ocupado && posicoes[i].soPodeDeitar) {
      for (int j = 0; j < 8; j++) {
        pontoreal = formatar_32x32_8x128(posicoes[i].pontosYDeitado[j], posicoes[i].pontosXDeitado[j]);
        if (displayCentral.getPoint(pontoreal.y, pontoreal.x)) {
          ocupado = true;
          break;
        }
      }
    }
    posicoes[i].ocupado = ocupado;
  }
}

void validarSticksTravados() {
  // Primeiro, atualiza posicoes[] para refletir ocupação atual
  atualizarOcupadoPosicoes();
  // Para cada stick
  for (int i = 0; i < 6; i++) {
    int p = sticks[i].posicao;
    int countAdj = 0;
    int neighbors[4];
    int nCount = 0;
    // Acima
    if (p >= 6)     neighbors[nCount++] = p - 6;
    // Abaixo
    if (p < 24)     neighbors[nCount++] = p + 6;
    // Esquerda
    if ((p % 6) != 0) neighbors[nCount++] = p - 1;
    // Direita
    if ((p % 6) != 5) neighbors[nCount++] = p + 1;
    // Conta quantos vizinhos ocupados
    for (int k = 0; k < nCount; k++) {
      if (posicoes[neighbors[k]].ocupado) countAdj++;
    }
    sticks[i].travado = (countAdj >= 2);
    // Imprime estado de travado
  }
}

void moverPalito(Stick *palito, struct Posicoes *posicao) {
  if (palito->deitado) {
    for (int i = 0; i < 8; i++) {
      palito->pontosX[i] = posicao->pontosXDeitado[i];
      palito->pontosY[i] = posicao->pontosYDeitado[i];
    }
  } else {
    for (int i = 0; i < 8; i++) {
      palito->pontosX[i] = posicao->pontosXEmPe[i];
      palito->pontosY[i] = posicao->pontosYEmPe[i];
    }
  }
  posicao->ocupado = true;
}

void moverPalitoJogador(Player *jogador, Stick *palito) {
  uint8_t posicaoAtual = palito->posicao;
  bool movendo = true;

  copiarStick(palito);
  apagarStick(palito);
  displayStick(&temporario);

  while (movendo) {
    // Leitura do joystick
    int leituraVert = analogRead(jogador->analoVert);
    int leituraHor = analogRead(jogador->analogHor);

    int botaoMover = digitalRead(jogador->mover);

    piscarNonBlocking(&temporario);
    Serial.println(posicaoAtual);
    // Movimento para cima
    if (leituraVert < 300) {
      if (posicaoAtual % 6 == 5) {
        posicaoAtual -= 5;
      } else {
        posicaoAtual++;
      }

      moverPontosTemp(posicaoAtual, palito->deitado);
      delay(200);  // Delay para evitar múltiplos movimentos rápidos
    }

    // Movimento para baixo
    else if (leituraVert > 700) {
      if (posicaoAtual % 6 == 0) {
        posicaoAtual += 5;
      } else {
        posicaoAtual--;
      }
      moverPontosTemp(posicaoAtual, palito->deitado);
      delay(200);
    }

    // Movimento para a direita
    else if (leituraHor > 700) {
      if (posicaoAtual + 6 >= 30) {
        posicaoAtual -= 24;
      } else {
        posicaoAtual += 6;
      }
      moverPontosTemp(posicaoAtual, palito->deitado);
      delay(200);
    }

    // Movimento para a esquerda
    else if (leituraHor < 300) {
      if (posicaoAtual < 6) {
        posicaoAtual += 24;
      } else {
        posicaoAtual -= 6;
      }
      moverPontosTemp(posicaoAtual, palito->deitado);
      delay(200);
    }
  }
}

void moverPontosTemp(int numero, bool deitado){
  apagarStick(&temporario);
  if (deitado) {
    for (int i = 0; i < 8; ++i) {
    temporario.pontosX[i] = posicoes[numero].pontosXDeitado[i];
    temporario.pontosY[i] = posicoes[numero].pontosYDeitado[i];
    }
  } else {
    for (int i = 0; i < 8; ++i) {
    temporario.pontosX[i] = posicoes[numero].pontosXEmPe[i];
    temporario.pontosY[i] = posicoes[numero].pontosYEmPe[i];
    }
  }
  displayStick(&temporario);
}

bool validarPosicao(int numPosicao, bool deitado) {
  if (!deitado && posicoes[numPosicao].soPodeDeitar) {
    return false;
  } else if (posicoes[numPosicao].ocupado) {
    return false;
  } else {
    return true;
  }
}

void garantiStickLigado(Stick* exemplo){
    if(!displayCentral.getPoint(exemplo->pontosY[0], exemplo->pontosX[0])) {
      displayStick(exemplo);
    }
}



