#include "dht.h"

// === Pinos e Configurações ===
const int ONE_WIRE_BUS = 4;

// === Parâmetros de Controle ===
const float TEMP_MAXIMA = 25.0;
const float TEMP_MINIMA = 15.0;
const float VARIACAO_PERMITIDA = 3.0;
const unsigned long INTERVALO_VARIACAO = 60 * 60 * 1000; // 1 hora

// === Variáveis Globais ===
float ultimaTemperatura = 0;
unsigned long ultimoTempo = 0;

// === Objetos do Sensor ===
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// === Função de Inicialização ===
void iniciarSensor() {
  sensors.begin();
  Serial.println("DS18B20 iniciado!");
}

// === Função de Monitoramento ===
float monitorarTemperatura() {
  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);

  if (temperatura == DEVICE_DISCONNECTED_C) {
    Serial.println("Erro na leitura do sensor!");
    return -127.0;
  }

  Serial.print("Temperatura atual: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  if (temperatura > TEMP_MAXIMA) {
    Serial.println("ALERTA: Temperatura MUITO ALTA!");
  } else if (temperatura < TEMP_MINIMA) {
    Serial.println("ALERTA: Temperatura MUITO BAIXA!");
  } else {
    Serial.println("Temperatura dentro dos padrões.");
  }

  unsigned long tempoAtual = millis();
  if (ultimoTempo != 0) {
    float diferenca = abs(temperatura - ultimaTemperatura);
    unsigned long intervalo = tempoAtual - ultimoTempo;

    if (diferenca >= VARIACAO_PERMITIDA && intervalo <= INTERVALO_VARIACAO) {
      Serial.println("ALERTA: Variação brusca detectada!");
      Serial.print("Mudança de ");
      Serial.print(diferenca, 1);
      Serial.println("°C em menos de 1 hora.");
    }
  }

  ultimaTemperatura = temperatura;
  ultimoTempo = tempoAtual;

  return temperatura;
}
