#ifndef DHT_H
#define DHT_H

#include <OneWire.h>
#include <DallasTemperature.h>

// === Pinos e Configurações ===
extern const int ONE_WIRE_BUS;

// === Parâmetros de Controle ===
extern const float TEMP_MAXIMA;
extern const float TEMP_MINIMA;
extern const float VARIACAO_PERMITIDA;
extern const unsigned long INTERVALO_VARIACAO;

// === Variáveis Globais ===
extern float ultimaTemperatura;
extern unsigned long ultimoTempo;

// === Objetos do Sensor ===
extern OneWire oneWire;
extern DallasTemperature sensors;

// === Funções ===
void iniciarSensor();
float monitorarTemperatura();

#endif // DHT_H
