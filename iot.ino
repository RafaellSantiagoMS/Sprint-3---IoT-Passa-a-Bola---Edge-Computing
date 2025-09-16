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
