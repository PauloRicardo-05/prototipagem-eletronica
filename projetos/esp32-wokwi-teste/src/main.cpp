#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// ========================================
// CONFIGURAÇÕES DO WI-FI
// ========================================

const char* ssid = "Gomes";
const char* password = "r12n15a16p01";


// ========================================
// SERVIDOR
// ========================================

WebServer server(80);


// ========================================
// PINOS
// ========================================

const int LED1_PIN = 2;
const int LED2_PIN = 5;

const int BUTTON1_PIN = 4;
const int BUTTON2_PIN = 18;


// ========================================
// ESTADOS
// ========================================

bool led1State = false;
bool led2State = false;


// ========================================
// CONTROLE DOS LEDs
// ========================================

void ligarLED1()
{
    digitalWrite(LED1_PIN, HIGH);
    led1State = true;

    Serial.println("LED 1 -> LIGADO");
}


void desligarLED1()
{
    digitalWrite(LED1_PIN, LOW);
    led1State = false;

    Serial.println("LED 1 -> DESLIGADO");
}


void alternarLED1()
{
    if (led1State)
        desligarLED1();
    else
        ligarLED1();
}


void ligarLED2()
{
    digitalWrite(LED2_PIN, HIGH);
    led2State = true;

    Serial.println("LED 2 -> LIGADO");
}


void desligarLED2()
{
    digitalWrite(LED2_PIN, LOW);
    led2State = false;

    Serial.println("LED 2 -> DESLIGADO");
}


void alternarLED2()
{
    if (led2State)
        desligarLED2();
    else
        ligarLED2();
}


// ========================================
// RESPOSTA JSON
// ========================================

void enviarEstado()
{
    String json = "{";

    json += "\"led1\":";
    json += led1State ? "true" : "false";

    json += ",";

    json += "\"led2\":";
    json += led2State ? "true" : "false";

    json += "}";

    server.send(200, "application/json", json);
}


// ========================================
// API - LED 1
// ========================================

void handleLED1On()
{
    ligarLED1();
    enviarEstado();
}


void handleLED1Off()
{
    desligarLED1();
    enviarEstado();
}


void handleLED1Toggle()
{
    alternarLED1();
    enviarEstado();
}


// ========================================
// API - LED 2
// ========================================

void handleLED2On()
{
    ligarLED2();
    enviarEstado();
}


void handleLED2Off()
{
    desligarLED2();
    enviarEstado();
}


void handleLED2Toggle()
{
    alternarLED2();
    enviarEstado();
}


// ========================================
// PÁGINA WEB
// ========================================

void handleRoot()
{
    String html = R"rawliteral(

<!DOCTYPE html>

<html lang="pt-BR">

<head>

<meta charset="UTF-8">

<meta name="viewport"
      content="width=device-width, initial-scale=1.0">

<title>ESP32 Control</title>


<style>

* {
    box-sizing: border-box;
}


body {

    margin: 0;

    font-family:
        Arial,
        Helvetica,
        sans-serif;

    background:
        linear-gradient(
            135deg,
            #101827,
            #18263d
        );

    color: white;

    min-height: 100vh;

    padding: 20px;
}


.container {

    max-width: 900px;

    margin: auto;
}


header {

    margin-bottom: 25px;
}


header h1 {

    margin: 0;

    font-size: 32px;
}


header p {

    color: #aebbd0;

    margin-top: 8px;
}


.grid {

    display: grid;

    grid-template-columns:
        repeat(
            auto-fit,
            minmax(250px, 1fr)
        );

    gap: 20px;
}


.card {

    background: #1d2a40;

    border: 1px solid #30415f;

    border-radius: 16px;

    padding: 22px;

    box-shadow:
        0 10px 30px
        rgba(0, 0, 0, 0.25);
}


.card h2 {

    margin-top: 0;
}


.status {

    display: flex;

    align-items: center;

    gap: 10px;

    margin: 18px 0;
}


.indicator {

    width: 14px;

    height: 14px;

    border-radius: 50%;

    background: #596579;

    transition:
        0.2s;
}


.indicator.on {

    background: #35e58a;

    box-shadow:
        0 0 15px
        rgba(53, 229, 138, 0.7);
}


.state {

    font-weight: bold;
}


.buttons {

    display: flex;

    gap: 10px;

    flex-wrap: wrap;
}


button {

    border: none;

    border-radius: 10px;

    padding: 11px 16px;

    font-size: 14px;

    font-weight: bold;

    cursor: pointer;

    transition:
        transform 0.1s,
        opacity 0.2s;
}


button:hover {

    opacity: 0.85;
}


button:active {

    transform:
        scale(0.96);
}


.btn-on {

    background: #35e58a;

    color: #07140d;
}


.btn-off {

    background: #ff647c;

    color: white;
}


.btn-toggle {

    background: #4f8cff;

    color: white;
}


.info {

    margin-top: 20px;

    background: #151f31;

    border-radius: 14px;

    padding: 18px;

    border: 1px solid #293852;
}


.info-row {

    display: flex;

    justify-content: space-between;

    padding: 7px 0;

    color: #b9c5d8;
}


.value {

    color: white;

    font-weight: bold;
}


footer {

    text-align: center;

    margin-top: 25px;

    color: #77859c;

    font-size: 13px;
}


</style>

</head>


<body>


<div class="container">


<header>

<h1>ESP32 Control</h1>

<p>
Painel de controle da nossa bancada virtual
</p>

</header>


<div class="grid">


<!-- LED 1 -->

<div class="card">

<h2>🔴 LED 1</h2>


<div class="status">

<div
    id="led1Indicator"
    class="indicator">
</div>

<span
    id="led1State"
    class="state">
DESLIGADO
</span>

</div>


<div class="buttons">

<button
    class="btn-on"
    onclick="controlLED(1, 'on')">

LIGAR

</button>


<button
    class="btn-off"
    onclick="controlLED(1, 'off')">

DESLIGAR

</button>


<button
    class="btn-toggle"
    onclick="controlLED(1, 'toggle')">

ALTERNAR

</button>

</div>

</div>


<!-- LED 2 -->

<div class="card">

<h2>🔵 LED 2</h2>


<div class="status">

<div
    id="led2Indicator"
    class="indicator">
</div>

<span
    id="led2State"
    class="state">
DESLIGADO
</span>

</div>


<div class="buttons">

<button
    class="btn-on"
    onclick="controlLED(2, 'on')">

LIGAR

</button>


<button
    class="btn-off"
    onclick="controlLED(2, 'off')">

DESLIGAR

</button>


<button
    class="btn-toggle"
    onclick="controlLED(2, 'toggle')">

ALTERNAR

</button>

</div>

</div>


<!-- BOTÕES -->

<div class="card">

<h2>🔘 Entradas</h2>

<p>
Botão físico 1 → LED 1
</p>

<p>
Botão físico 2 → LED 2
</p>

<p>
Os botões físicos continuam funcionando
independentemente da interface Web.
</p>

</div>


</div>


<!-- INFORMAÇÕES -->

<div class="info">

<h2>📡 Sistema</h2>


<div class="info-row">

<span>Wi-Fi</span>

<span
    class="value">
CONECTADO
</span>

</div>


<div class="info-row">

<span>Servidor</span>

<span
    class="value">
ONLINE
</span>

</div>


<div class="info-row">

<span>Comunicação</span>

<span
    class="value">
Fetch / JSON
</span>

</div>

</div>


<footer>

ESP32 • Wokwi • Projeto Base

</footer>


</div>


<script>


// ========================================
// CONTROLE DOS LEDs
// ========================================

async function controlLED(led, action)
{

    try
    {

        const response =
            await fetch(
                `/api/led${led}/${action}`
            );


        const data =
            await response.json();


        atualizarInterface(data);

    }

    catch (error)
    {

        console.error(
            "Erro:",
            error
        );

    }

}


// ========================================
// ATUALIZAR INTERFACE
// ========================================

function atualizarInterface(data)
{

    atualizarLED(
        1,
        data.led1
    );


    atualizarLED(
        2,
        data.led2
    );

}


// ========================================
// ATUALIZAR UM LED
// ========================================

function atualizarLED(
    numero,
    ligado
)
{

    const state =
        document.getElementById(
            `led${numero}State`
        );


    const indicator =
        document.getElementById(
            `led${numero}Indicator`
        );


    if (ligado)
    {

        state.textContent =
            "LIGADO";


        indicator.classList.add(
            "on"
        );

    }

    else
    {

        state.textContent =
            "DESLIGADO";


        indicator.classList.remove(
            "on"
        );

    }

}


</script>


</body>

</html>

)rawliteral";


    server.send(
        200,
        "text/html",
        html
    );
}


// ========================================
// SETUP
// ========================================

void setup()
{

    Serial.begin(115200);

    delay(1000);


    // LEDs

    pinMode(
        LED1_PIN,
        OUTPUT
    );

    pinMode(
        LED2_PIN,
        OUTPUT
    );


    desligarLED1();

    desligarLED2();


    // Botões

    pinMode(
        BUTTON1_PIN,
        INPUT_PULLUP
    );

    pinMode(
        BUTTON2_PIN,
        INPUT_PULLUP
    );


    // ====================================
    // WI-FI
    // ====================================

    Serial.println();

    Serial.println(
        "=============================="
    );

    Serial.println(
        "     ESP32 - PROJETO BASE"
    );

    Serial.println(
        "=============================="
    );


    Serial.println(
        "Conectando ao WiFi..."
    );


    WiFi.begin(
        ssid,
        password
    );


    while (
        WiFi.status()
        != WL_CONNECTED
    )
    {

        delay(500);

        Serial.print(".");
    }


    Serial.println();

    Serial.println(
        "WiFi conectado!"
    );


    Serial.print(
        "IP: "
    );

    Serial.println(
        WiFi.localIP()
    );


    // ====================================
    // ROTAS
    // ====================================

    server.on(
        "/",
        handleRoot
    );


    server.on(
        "/api/led1/on",
        handleLED1On
    );

    server.on(
        "/api/led1/off",
        handleLED1Off
    );

    server.on(
        "/api/led1/toggle",
        handleLED1Toggle
    );


    server.on(
        "/api/led2/on",
        handleLED2On
    );

    server.on(
        "/api/led2/off",
        handleLED2Off
    );

    server.on(
        "/api/led2/toggle",
        handleLED2Toggle
    );


    server.begin();


    Serial.println(
        "Servidor HTTP iniciado!"
    );

    Serial.println(
        "=============================="
    );
}


// ========================================
// LOOP
// ========================================

void loop()
{

    server.handleClient();


    // ====================================
    // BOTÃO 1
    // ====================================

    if (
        digitalRead(BUTTON1_PIN)
        == LOW
    )
    {

        alternarLED1();

        delay(200);
    }


    // ====================================
    // BOTÃO 2
    // ====================================

    if (
        digitalRead(BUTTON2_PIN)
        == LOW
    )
    {

        alternarLED2();

        delay(200);
    }

}
