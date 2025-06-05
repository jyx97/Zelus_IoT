#include <WiFi.h>
#include "hx711.h"
#include "dht.h"
#include <PubSubClient.h>

// Dados Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Dados MQTT
const char* mqtt_server = "broker.hivemq.com";  
const int mqtt_port = 1883;
const char* mqtt_client_id = "esp32_monitoramento";
const char* mqtt_topic_temp = "esp32/conserva/temperatura";
const char* mqtt_topic_peso = "esp32/conserva/peso";

// WiFi e MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Conectar ao Wi-Fi
void conectarWiFi() {
  Serial.println("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado! IP: " + WiFi.localIP().toString());
}

// Conectar ao MQTT
void conectarMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect(mqtt_client_id)) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 3s...");
      delay(3000);
    }
  }
}

// --- Setup ---
void setup() {
  Serial.begin(115200);

  conectarWiFi();
  client.setServer(mqtt_server, mqtt_port);

  iniciarSensor();   // Sensor DHT
  iniciarBalanca();

  Serial.println("🔗 Sistema de monitoramento iniciado.");
}

// --- Loop ---
void loop() {
  if (!client.connected()) {
    conectarMQTT();
  }
  client.loop();

  // Ler dados dos sensores
  float temperatura = monitorarTemperatura();  // Função do dht.h
  float peso = monitorarBalanca();             // Função do hx711.h

  // Mostrar no Serial
  Serial.println("Temperatura: " + String(temperatura) + " °C");
  Serial.println(" Peso: " + String(peso) + " Kg");

  // Enviar dados para MQTT
  client.publish(mqtt_topic_temp, String(temperatura, 2).c_str());
  client.publish(mqtt_topic_peso, String(peso, 2).c_str());

  Serial.println("--------------------------------------");
  delay(5000);
}
