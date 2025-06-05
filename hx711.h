#ifndef HX711_CUSTOM_H
#define HX711_CUSTOM_H

#include "HX711.h"

// HX711
#define DT_HX 32
#define SCK_HX 33

// Botão de lacre
#define BOTAO 2

extern HX711 scale;
extern float pesoLote;
extern bool lacrado;

void iniciarBalanca();
float monitorarBalanca();

#endif
