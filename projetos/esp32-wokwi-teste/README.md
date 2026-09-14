# ESP32: LEDs, botões e interface web

Projeto PlatformIO para um ESP32 DevKit C que controla dois LEDs de duas formas:

- botões físicos ligados aos GPIOs 4 e 18;
- interface HTTP servida pelo próprio ESP32.

O circuito de simulação está definido em `diagram.json` e pode ser aberto no Wokwi.

## Hardware e conexões

| Componente | GPIO do ESP32 |  
| -------------- | ------------ |  
| LED 1      |       2       |  
| LED 2      |       5       |  
| Botão 1    |       4       |  
| Botão 2    |       18      |  

Os botões usam `INPUT_PULLUP`: conecte o outro terminal de cada botão ao GND.

## Compilar o projeto

Pré-requisito: [PlatformIO](https://platformio.org/).

```bash
cd projetos/esp32-wokwi-teste
pio run
```

No VS Code, a forma recomendada é abrir o arquivo `prototipagem-eletronica.code-workspace` que fica na raiz do repositório. Ele abre esta pasta como a raiz do projeto PlatformIO.

## Simular no Wokwi

Pré-requisitos: extensões **PlatformIO IDE** e **Wokwi for VS Code** instaladas e licença do Wokwi ativada.

> **Licença do Wokwi:** ao executar **Wokwi: Start Simulator** pela primeira vez, o Wokwi pode solicitar que você informe ou ative uma licença. A simulação pelo VS Code só será iniciada depois que uma licença válida estiver configurada. Siga as instruções exibidas pelo Wokwi para ativá-la e, em seguida, execute o comando novamente.

1. Abra `prototipagem-eletronica.code-workspace` no VS Code.
2. Execute **PlatformIO: Build** (ícone ✓ na barra inferior) e aguarde `SUCCESS`.
3. Pare qualquer simulação anterior e pressione `F1`.
4. Escolha **Wokwi: Start Simulator**.
5. Mantenha a aba **Wokwi Simulator** aberta. O painel inferior **Wokwi Terminal** mostrará as mensagens da porta serial.
6. Para usar a interface web simulada, abra [http://localhost:8180](http://localhost:8180) enquanto a simulação estiver em execução.

O `wokwi.toml` encaminha a porta local `8180` para a porta `80` do ESP32. O `diagram.json` também conecta a UART virtual (`TX`/`RX`) do ESP32 ao monitor serial do Wokwi.

Você deve ver mensagens como:

```text
Conectando ao WiFi...
WiFi conectado!
IP: ...
Servidor HTTP iniciado!
```

## Gravar em um ESP32 físico

Não copie somente o `main.cpp` para a placa: ele precisa ser **compilado** e enviado como firmware. Conecte o ESP32 por USB e execute:

```bash
pio run --target upload
pio device monitor --baud 115200
```

No VS Code, você também pode usar os botões **Upload** (seta para a direita) e **Monitor** do PlatformIO. O Monitor do PlatformIO é apenas para a placa física conectada por USB; para a simulação, use sempre o **Wokwi Terminal**.

Antes de gravar na placa real, altere estas linhas em `src/main.cpp` para o Wi-Fi da sua casa ou laboratório:

```cpp
const char* ssid = "SEU_WIFI";
const char* password = "SUA_SENHA";
```

`Wokwi-GUEST` funciona somente na simulação. Na placa real, use o IP mostrado no monitor serial para abrir a interface web. Para o circuito físico, use um resistor de 220 Ω a 330 Ω em série com cada LED e mantenha os botões ligados entre os GPIOs 4/18 e GND.
