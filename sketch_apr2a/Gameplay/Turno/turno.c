#include "turno.h"

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
    piscar(&sticks[stick_selecionado]);
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

    piscar(&temporario);
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


