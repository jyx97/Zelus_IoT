# 🛰️ Sistema de Monitoramento de Temperatura e Peso

Este projeto realiza o monitoramento de temperatura e peso utilizando um **ESP32**, sensores **DS18B20** (temperatura) e **HX711** (peso com célula de carga), com transmissão de dados via **MQTT** e visualização em tempo real usando **Node-RED Dashboard**.

Ideal para aplicações como:
- Conservação de alimentos ou produtos sensíveis
- Controle de estoque e logística
- Detecção de violação de lacres de segurança

---

## 📦 Funcionalidades

✅ Leitura precisa de **temperatura** com sensor digital DS18B20  
✅ Medição de **peso** com célula de carga 50kg + amplificador HX711  
✅ Detecção de **variações bruscas de temperatura** (>3°C em 1h)  
✅ Sistema de **lacre com botão** que detecta alterações no peso  
✅ Envio de dados por **MQTT** para integração com outros sistemas  
✅ Visualização em tempo real com **Node-RED Dashboard**  
✅ Geração de **gráficos históricos** e notificações automáticas  

---

## 🛠️ Componentes Utilizados

| Componente         | Descrição                                 | Quantidade |
|--------------------|---------------------------------------------|------------|
| ESP32 DevKit       | Microcontrolador com Wi-Fi                  | 1          |
| Sensor DS18B20     | Sensor digital de temperatura               | 1          |
| Módulo HX711       | Amplificador para célula de carga           | 1          |
| Célula de carga    | Sensor de peso (50kg)                       | 1          |
| Botão (pushbutton) | Botão para ativar o modo "lacre"            | 1          |
| Jumpers            | Cabos de conexão                            | Diversos   |

---

## ⚙️ Estrutura de Arquivos

```bash
📁 projeto-monitoramento
├── sketch.ino           # Código principal ESP32
├── dht.h                # Cabeçalho do sensor de temperatura (DS18B20)
├── dht.cpp              # Implementação do sensor de temperatura
├── hx711.h              # Cabeçalho do sensor de peso e controle de lacre (HX711)
├── hx711.cpp            # Implementação do sensor de peso e controle de lacre
├── flows.json           # Fluxo Node-RED com dashboard e alertas
├── diagram.json         # Diagrama de montagem Wokwi
└── README.md            # Este documento

````

---

## 🔧 Montagem do Circuito

* O sensor **DS18B20** é conectado ao pino **D4** do ESP32.
* O **HX711** é ligado aos pinos **D32 (DT)** e **D33 (SCK)**.
* O botão de lacre é conectado ao pino **D2** com `INPUT_PULLUP`.
* A alimentação é feita com **5V e GND** do ESP32.

📌 Veja o `diagram.json` ou simule no [Wokwi](https://wokwi.com/) com facilidade.

---

## 🧠 Lógica de Funcionamento

### Temperatura (`dht.h`)

* Lê a temperatura do DS18B20.
* Alerta se:

  * > 25°C (alerta)
  * > 35°C ou < 10°C (crítico)
  * Variação ≥ 3°C em menos de 1h.

### Peso e Lacre (`hx711.h`)

* Lê o peso da carga.
* Botão de **lacre** salva o peso atual como "seguro".
* Se houver variação de ±0.3kg após o lacre: ⚠️ alerta de violação.

---

## 🌐 Comunicação MQTT

| Protocolo | Broker MQTT público: `broker.hivemq.com` |
| --------- | ---------------------------------------- |
| Porta     | 1883                                     |

### Tópicos Publicados

| Tópico                       | Conteúdo         |
| ---------------------------- | ---------------- |
| `esp32/conserva/temperatura` | Temperatura (°C) |
| `esp32/conserva/peso`        | Peso (Kg)        |

---

## 🖥️ Node-RED Dashboard

Interface web para monitoramento visual:

### Elementos Visuais

* **Gauge de Temperatura**
* **Gauge de Peso**
* **Status de Alerta Colorido**
* **Gráfico Histórico (Linha)**
* **Botão de Reset dos Alertas**
* **Notificações Toast**

📁 Para importar o fluxo:

1. Acesse o editor do Node-RED
2. Menu (☰) > Import > Cole o conteúdo de `flows.json`
3. Clique em **Deploy**

---

## 🚀 Como Executar

### ✅ Passo 1: Subir o código no ESP32

1. Conecte o ESP32 via USB
2. Use o **Arduino IDE** ou **Wokwi**
3. Faça upload de:

   * `sketch.ino`
   * `dht.h`
   * `hx711.h`
4. Verifique a saída no **Serial Monitor** (115200 baud)

### ✅ Passo 2: Configurar o Node-RED

1. Instale Node-RED (caso não tenha):

   ```bash
   npm install -g node-red
   ```
2. Inicie o serviço:

   ```bash
   node-red
   ```
3. Acesse via navegador: [http://localhost:1880](http://localhost:1880)
4. Importe o arquivo `flows.json` no editor

---

## 📊 Exemplo do Dashboard

```
+-------------------------+
|  🌡️ Temperatura: 22.5°C   |
|  ⚖️ Peso: 4.7 Kg         |
|  ✅ Todos os parâmetros OK |
+-------------------------+

📈 Gráficos ao vivo com atualização a cada 5 segundos.
```

---

## 📝 Possíveis Expansões

* Adição de sensor de umidade
* Armazenamento em banco de dados (InfluxDB, Firebase)
* Envio de alertas via Telegram ou Email
* Integração com Home Assistant

---

## 👩‍💻 Integrantes

| Nome Completo      | RM                           |
|--------------------|------------------------------|
| Hellen Marinho     | 558841                       |
| Heloisa Mesquita   | 559145                       |
| Júlia Soares       | 554609                       |