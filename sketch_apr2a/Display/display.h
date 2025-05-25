#include "../defines.h"
#include "Ponto/ponto.h"
#include "../Sticks/sticks.h"

#ifndef DISPLAY_H
#define DISPLAY_H

// Varieveis globais - Display Central
MD_MAX72XX displayCentral = MD_MAX72XX(HARDWARE_TYPE, DIN_PIN_CENTRAL_DISPLAY, CLK_PIN_CENTRAL_DISPLAY, CS_PIN_CENTRAL_DISPLAY, MAX_DEVICES_CENTRAL_DISPLAY);
const uint8_t TOTAL_PIX_CENTRAL_X = MAX_DEVICES_CENTRAL_DISPLAY * 8; //128 para 16 mod

// Varieveis globais - Display Auxiliar
MD_MAX72XX displayAux = MD_MAX72XX(HARDWARE_TYPE, DIN_PIN_AUX_DISPLAY, CLK_PIN_AUX_DISPLAY, CS_PIN_AUX_DISPLAY, MAX_DEVICES_AUX_DISPLAY);
const uint8_t TOTAL_PIX_AUX_X = MAX_DEVICES_AUX_DISPLAY * 8; //128 para 16 mod

unsigned long lastBlinkTime = 0;
bool blinkState = false;


void displayPontoReal(uint8_t coluna, uint8_t linha);
void displayStick(struct Stick *stick);
void apagarStick(struct Stick *stick);
void copiarStick(struct Stick *stick);
void displayStickInicial(struct Stick* exemplo);
void garantiStickLigado(Stick* exemplo);

#endif // DISPLAY_H