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

// ---------- FUNÇÃO PARA ENVIAR DADOS AO THINGSPEAK ----------
void enviarDados(int batimentos, float oximetria, float ax, float ay, float az) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = String(THINGSPEAK_HOST) + "?api_key=" + THINGSPEAK_API_KEY +
                 "&field1=" + String(batimentos) +
                 "&field2=" + String(oximetria) +
                 "&field3=" + String(ax) +
                 "&field4=" + String(ay) +
                 "&field5=" + String(az);

    http.begin(url);
    int httpCode = http.GET(); // envia GET

    if (httpCode > 0) {
      Serial.print("Dados enviados! Código: ");
      Serial.println(httpCode);
    } else {
      Serial.println("Erro ao enviar dados");
    }

    http.end();
  } else {
    Serial.println("WiFi não conectado!");
  }
}

// ---------- SETUP ----------
void setup() {
  Serial.begin(115200);
  conectarWiFi();
  inicializarMPU();
}

// ---------- LOOP ----------
void loop() {
  // Lê sensores
  int batimentos = lerBatimentos();
  float oximetria = lerOximetria();
  float ax, ay, az;
  lerMPU(ax, ay, az);

  // Mostra no Serial
  Serial.print("Batimentos: "); Serial.print(batimentos);
  Serial.print(" | Oximetria: "); Serial.print(oximetria);
  Serial.print(" | Acc X: "); Serial.print(ax);
  Serial.print(" Y: "); Serial.print(ay);
  Serial.print(" Z: "); Serial.println(az);

  // Envia ao ThingSpeak
  enviarDados(batimentos, oximetria, ax, ay, az);

  delay(15000); // envia a cada 15 segundos
}
