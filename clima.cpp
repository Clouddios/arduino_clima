#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_BMP280.h>
#include "config.h"  // Inclui as credenciais do arquivo de configuração

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// BMP280
Adafruit_BMP280 bmp;

// Wi-Fi
const char* ssid = "StarDestroyer";
const char* password = "Almeida23";

// WeatherAPI
const String apiKey = "a81ec63c1ac64d57bcb191022250305";
const String city = "Aracoiaba da Serra";

// Variáveis globais
String condicaoClima = "Sem dados";
int codigoClima = 1000; // Valor padrão
float tempExterna = 0.0;
int umidade = 0;  // Para armazenar a umidade

void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado!");
}

void getWeatherData() {
  HTTPClient http;
  String cidadeFormatada = "Aracoiaba%20da%20Serra";  // Espaços precisam ser %20
  String url = "http://api.weatherapi.com/v1/current.json?key=" + apiKey + "&q=" + cidadeFormatada + "&aqi=no";
  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, payload);
    if (!error) {
      condicaoClima = doc["current"]["condition"]["text"].as<String>();
      //codigoClima = doc["current"]["condition"]["code"].as<int>();
      tempExterna = doc["current"]["temp_c"].as<float>();
      umidade = doc["current"]["humidity"].as<int>();  // Pega a umidade da API
    } else {
      Serial.println("Erro ao analisar o JSON");
    }
  } else {
    Serial.println("Erro HTTP: " + String(httpCode));
  }

  http.end();
}

// Função para exibir as informações no display OLED
void showDataOnDisplay(String titulo, String valor) {
  display.clearDisplay();
  
  display.setTextSize(2);  // Tamanho grande para o título
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(titulo);

  display.setTextSize(3);  // Tamanho maior para o valor
  display.setCursor(0, 30);
  display.println(valor);
  
  display.display();
}

void setup() {
  Serial.begin(115200);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("Erro no display!");
    while (true);
  }

  if (!bmp.begin(0x76)) {
    Serial.println("Erro no BMP280!");
    while (true);
  }

  connectToWiFi();
  getWeatherData();
}

void loop() {
  // Obter dados do sensor BMP280
  float temp = bmp.readTemperature();
  float press = bmp.readPressure() / 100.0F;

  // Mostrar Temperatura Interna
  showDataOnDisplay("Temp Inter", String(temp, 1) + " C");
  delay(3000);

  // Mostrar Pressão
  showDataOnDisplay("Pressao", String(press, 1) + " hPa");
  delay(3000);

  // Mostrar Temperatura Externa
  showDataOnDisplay("Temp Exter", String(tempExterna, 1) + " C");
  delay(3000);

  // Mostrar Condição do Clima
  showDataOnDisplay("Clima", condicaoClima);
  delay(3000);

  // Mostrar Umidade
  showDataOnDisplay("Umidade", String(umidade) + "%");
  delay(3000);

  // Atualizar a cada 10 segundos
  static int contador = 0;
  contador++;
  if (contador >= 5) {
    getWeatherData();
    contador = 0;
  }
}
