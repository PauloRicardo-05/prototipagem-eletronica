# ESP32: LEDs, botões e interface web

Projeto PlatformIO para um ESP32 DevKit C que controla dois LEDs de duas formas:

- botões físicos ligados aos GPIOs 4 e 18;
- interface HTTP servida pelo próprio ESP32.

O circuito de simulação está definido em `diagram.json` e pode ser aberto no Wokwi.

## Hardware e conexões

| Componente | GPIO do ESP32 |
| --- | --- |
| LED 1 | 2 |
| LED 2 | 5 |
| Botão 1 | 4 |
| Botão 2 | 18 |

Os botões usam `INPUT_PULLUP`: conecte o outro terminal de cada botão ao GND.

## Executar localmente

Pré-requisito: [PlatformIO](https://platformio.org/).

```bash
cd projetos/esp32-wokwi-teste
pio run
```

Para gravar em uma placa conectada:

```bash
pio run --target upload
pio device monitor --baud 115200
```

## Simular no Wokwi

1. Abra esta pasta no VS Code com a extensão Wokwi instalada.
2. Compile o firmware com `pio run`.
3. Inicie a simulação pelo comando **Wokwi: Start Simulator**.

O arquivo `wokwi.toml` aponta para os arquivos de firmware produzidos pelo PlatformIO. No console serial, anote o endereço IP exibido pelo ESP32 e abra-o no navegador para usar a interface web.

## Rotas HTTP

| Rota | Efeito |
| --- | --- |
| `/` | Interface de controle no navegador |
| `/api/led1/on`, `/api/led1/off`, `/api/led1/toggle` | Controla o LED 1 |
| `/api/led2/on`, `/api/led2/off`, `/api/led2/toggle` | Controla o LED 2 |

As rotas de API retornam o estado atual em JSON, por exemplo: `{"led1":true,"led2":false}`.
