// ---------- Importação de Bibliotecas ----------
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// ---------- CONFIGURAÇÃO WIFI ----------
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

// ---------- CONFIGURAÇÃO THINGSPEAK ----------
const char* THINGSPEAK_HOST = "http://api.thingspeak.com/update";
const char* THINGSPEAK_API_KEY = "30TUBORX1EBYN3AO"; 


// ---------- PINOS DOS POTENCIÔMETROS ----------
const int pinBatimentos = 34; // simula batimentos cardíacos
const int pinOximetro = 35;   // simula oximetria

// ---------- OBJETO MPU6050 ----------
Adafruit_MPU6050 mpu;

// ---------- FUNÇÃO DE CONEXÃO WIFI ----------
void conectarWiFi() {
  Serial.print("Conectando ao WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado!");
  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.localIP());
}

// ---------- FUNÇÃO PARA INICIALIZAR MPU6050 ----------
void inicializarMPU() {
  if (!mpu.begin()) {
    Serial.println("Erro ao inicializar MPU6050!");
    while (1) {
      delay(100);
    }
  }
  Serial.println("MPU6050 inicializado com sucesso!");
}

// ---------- FUNÇÃO PARA LER DADOS DO MPU6050 ----------
void lerMPU(float &ax, float &ay, float &az) {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  ax = a.acceleration.x;
  ay = a.acceleration.y;
  az = a.acceleration.z;
}

// ---------- FUNÇÃO PARA LER DADOS DOS POTENCIÔMETROS ----------
int lerBatimentos() {
  int val = analogRead(pinBatimentos);       // 0 - 4095
  return map(val, 0, 4095, 40, 250);        // converte para batimentos
}

float lerOximetria() {
  int val = analogRead(pinOximetro);        // 0 - 4095
  return map(val, 0, 4095, 800, 1000) / 10.0; // converte para 95.0 - 100.0
}