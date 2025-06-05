#include "hx711.h"

HX711 scale;

float pesoLote = 0;
bool lacrado = false;

void iniciarBalanca() {
  scale.begin(DT_HX, SCK_HX);
  scale.set_scale(420);  // Ajuste de calibração
  scale.tare();
  Serial.println("Balança pronta!");

  pinMode(BOTAO, INPUT_PULLUP);
}

float monitorarBalanca() {
  float pesoAtual = 0;

  if (scale.is_ready()) {
    pesoAtual = scale.get_units(5);

    // Botão de lacre
    if (digitalRead(BOTAO) == LOW) {
      pesoLote = pesoAtual;
      lacrado = true;
      Serial.println("Lote lacrado com peso de: " + String(pesoLote, 2) + " kg");
      delay(1000); // debounce
    }

    if (lacrado) {
      if (abs(pesoAtual - pesoLote) >= 0.3) {
        Serial.println("Alteração detectada no lote LACRADO!");
        Serial.println("Peso original: " + String(pesoLote, 2) + " kg");
        Serial.println("Peso atual: " + String(pesoAtual, 2) + " kg");
        Serial.println("POSSÍVEL EXTRAVIO OU VIOLAÇÃO!");
      } else {
        Serial.println("Lote lacrado e intacto. Peso atual: " + String(pesoAtual, 2) + " kg");
      }
    } else {
      Serial.println("Lote ABERTO. Peso atual: " + String(pesoAtual, 2) + " kg");
    }
  } else {
    Serial.println("HX711 não está pronto.");
  }

  return pesoAtual;
}
