#include "pitches.h"

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