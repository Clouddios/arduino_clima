# Arduino Clima

Este projeto utiliza um Arduino com suporte a Wi-Fi, um sensor BMP280 e um display OLED para monitorar condições climáticas internas e externas. Ele também se conecta à API WeatherAPI para obter dados climáticos em tempo real.

## Funcionalidades

- **Monitoramento interno**: Mede temperatura e pressão atmosférica usando o sensor BMP280.
- **Monitoramento externo**: Obtém informações climáticas externas, como temperatura, umidade e condições climáticas, via API WeatherAPI.
- **Exibição em OLED**: Mostra os dados no display OLED de forma clara e organizada.

## Requisitos

### Hardware
- Arduino com suporte a Wi-Fi (ESP32 ou ESP8266 recomendado)
- Sensor BMP280
- Display OLED (128x64)
- Jumpers e protoboard

### Software
- [Arduino IDE](https://www.arduino.cc/en/software)
- Bibliotecas necessárias:
  - `WiFi.h` (inclusa no ESP32/ESP8266)
  - `HTTPClient.h`
  - `ArduinoJson`
  - `Adafruit_SSD1306`
  - `Adafruit_GFX`
  - `Adafruit_BMP280`

## Configuração

1. **Clone o repositório**:
   ```bash
   git clone https://github.com/seu-usuario/arduino_clima.git
   cd arduino_clima
   ```

2. **Instale as bibliotecas necessárias**:
   - Abra o Arduino IDE.
   - Vá em **Sketch > Incluir Biblioteca > Gerenciar Bibliotecas**.
   - Pesquise e instale as bibliotecas:
     - `ArduinoJson`
     - `Adafruit SSD1306`
     - `Adafruit GFX`
     - `Adafruit BMP280`

3. **Configure o arquivo `config.h`**:
   - Crie um arquivo `config.h` na raiz do projeto com as credenciais Wi-Fi e a chave da API:
     ```cpp
     #ifndef CONFIG_H
     #define CONFIG_H

     // Credenciais Wi-Fi
     const char* ssid = "SEU_SSID";
     const char* password = "SUA_SENHA";

     // Chave da API WeatherAPI
     const String apiKey = "SUA_CHAVE_API";

     #endif
     ```
   - Certifique-se de que o arquivo `config.h` está listado no `.gitignore` para evitar expor informações sensíveis.

4. **Faça o upload do código para o Arduino**:
   - Conecte o Arduino ao computador.
   - Abra o arquivo `clima.cpp` no Arduino IDE.
   - Selecione a placa e a porta correta em **Ferramentas**.
   - Clique em **Upload**.

## Uso

- Após o upload, o Arduino irá:
  1. Conectar-se ao Wi-Fi.
  2. Obter dados do sensor BMP280.
  3. Buscar informações climáticas externas da API WeatherAPI.
  4. Exibir os dados no display OLED.

## Estrutura do Projeto

```plaintext
arduino_clima/
├── clima.cpp         # Código principal do projeto
├── config.example.h  # Exemplo de configuração (sem informações sensíveis)
├── .gitignore        # Arquivos ignorados pelo Git
└── README.md         # Documentação do projeto
```

## Exemplo de Saída no Display

- **Temperatura Interna**: `25.3 C`
- **Pressão**: `1013.2 hPa`
- **Temperatura Externa**: `30.1 C`
- **Condição Climática**: `Ensolarado`
- **Umidade**: `60%`

## API Utilizada

- [WeatherAPI](https://www.weatherapi.com/): Fornece dados climáticos externos.

## Licença

Este projeto é licenciado sob a MIT License.

---

**Nota**: Certifique-se de proteger suas credenciais Wi-Fi e chave da API. Nunca compartilhe o arquivo `config.h` publicamente.