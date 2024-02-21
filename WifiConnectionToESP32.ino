#include <WiFi.h>
#include <HardwareSerial.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "BELL603";
const char* password = "AD744EAC157D";

AsyncWebServer server(80);

const char* onPath = "/turnon";
const char* offPath = "/turnoff";

void handleRootRequest(AsyncWebServerRequest *request) {
    String html = "<html><body>";
    html += "<h1>DAC Control</h1>";
    html += "<button onclick=\"turnOnDAC()\">Turn On DAC</button>";
    html += "<button onclick=\"turnOffDAC()\">Turn Off DAC</button>";
    html += "<script>";
    html += "function turnOnDAC() { fetch('/turnon'); }";
    html += "function turnOffDAC() { fetch('/turnoff'); }";
    html += "</script>";
    html += "</body></html>";

    request->send(200, "text/html", html);
}

void handleTurnOnRequest(AsyncWebServerRequest *request) {
    Serial1.begin(9600);
    Serial1.print("ON");
    Serial1.end();

    request->send(200, "text/plain", "DAC turned on");
}

void handleTurnOffRequest(AsyncWebServerRequest *request) {
    Serial1.begin(9600);
    Serial1.print("OFF");
    Serial1.end();

    request->send(200, "text/plain", "DAC turned off");
}

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    server.on("/", HTTP_GET, handleRootRequest);
    server.on(onPath, HTTP_GET, handleTurnOnRequest);
    server.on(offPath, HTTP_GET, handleTurnOffRequest);

    server.begin();
}

void loop() {
    // Add any necessary code for the loop here
}

