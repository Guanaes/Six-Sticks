#include "posicoes.h"
#include "../Sticks/sticks.h"

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