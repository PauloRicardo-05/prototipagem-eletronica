# Prototipagem e Eletrônica

Repositório para projetos de prototipagem, eletrônica embarcada e simulações.

## Projetos

| Projeto | Plataforma | Descrição |
| --- | --- | --- |
| [ESP32 + Wokwi](projetos/esp32-wokwi-teste/) | ESP32 / Arduino | Controle de dois LEDs por botões e por uma interface web. |

## Como executar um projeto

Cada projeto é independente e contém seu próprio `platformio.ini`, diagrama do Wokwi e instruções específicas. Entre na pasta do projeto desejado e siga o respectivo `README.md`.

### VS Code e PlatformIO

Abra o arquivo [prototipagem-eletronica.code-workspace](prototipagem-eletronica.code-workspace) no VS Code, em vez de abrir somente a pasta-raiz do repositório. Ele aponta o VS Code diretamente para o projeto PlatformIO ativo, permitindo que a extensão encontre o `platformio.ini`, as bibliotecas do ESP32 e o diagrama do Wokwi.

Para abrir pelo terminal:

```powershell
code .\prototipagem-eletronica.code-workspace
```

Este repositório executa uma compilação automática no GitHub Actions sempre que há alteração em um projeto PlatformIO.
