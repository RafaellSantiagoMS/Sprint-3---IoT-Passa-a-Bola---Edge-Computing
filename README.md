# 🚀 Projeto Challenge "Passa a Bola" – IoT com ESP32

## 👥 Integrantes

- Enzo Augusto Lima da Silva – RM: 562249  
- Gustavo Neres dos Santos – RM: 561785  
- Pedro Marchese – RM: 563339  
- Rafaell Santiago Martins da Silva – RM: 563486  

---

## 🎯 Descrição do Projeto

Este projeto desenvolve a primeira versão de uma arquitetura IoT para o desafio **"Passa a Bola"**, com foco em **monitoramento em tempo real** de sinais vitais e movimentação. Utilizamos um ESP32 com sensores simulados (potenciômetros e acelerômetro) que enviam dados para a nuvem via **HTTP**. 

---

## 🧠 Conceitos Aplicados

- **Internet das Coisas (IoT)**: Conexão de dispositivos físicos à internet para coleta e envio de dados.
- **Monitoramento em tempo real**: Visualização imediata de batimentos, oximetria e movimento.
- **Protocolo HTTP**: Comunicação do ESP32 com a plataforma **ThingSpeak**.

---

## 🏗️ Arquitetura Proposta

### Diagrama Resumido

[Usuário] ⇄ [ThingSpeak]
↑
(HTTP)
↑
[ESP32 com sensores]

### Componentes

- **ESP32**: coleta e transmite os dados  
- **Potenciômetros**: simulam batimentos cardíacos e oximetria  
- **MPU6050**: mede a movimentação  
- **ThingSpeak**: exibe os dados em tempo real via gráficos na web  

---

## 🧰 Recursos Necessários

### Hardware
- ESP32  
- 2x Potenciômetros  
- Sensor MPU6050  
- Cabos / Protoboard  

### Software
- Arduino IDE  
- Bibliotecas: `WiFi.h`, `HTTPClient.h`, `Adafruit_MPU6050`  
- Conta no [ThingSpeak](https://thingspeak.com)

---

## ▶️ Instruções de Uso

1. **Configure sua rede Wi-Fi e API Key no código**  
2. **Carregue o código no ESP32 via Arduino IDE**  
3. **Acesse o Monitor Serial para ver os dados locais**  
4. **Visualize os dados online pelo seu canal do ThingSpeak**

---

## 🎥 Vídeo Explicativo (Entrega 1)

> 📺 **Link para o vídeo (YouTube):**  
> [https://youtu.be/FhgQ1B5FJV4]

O vídeo cobre:
- Aplicação da IoT no desafio
- Conceitos fundamentais
- Diagrama da arquitetura
- Plataforma utilizada
- Demonstração da coleta e envio de dados

---

> **Link para o Wokwi**
> [https://wokwi.com/projects/441836157562785793]
