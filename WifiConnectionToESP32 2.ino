#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>

//const char* ssid = "BELL603";
//const char* password = "AD744EAC157D";

const char* ssid = "Matts Phone";
const char* password = "MattsHotspot";

const int uartTxPin = 4; // TX pin on ESP32

AsyncWebServer server(80);

bool isSignalOn = true; // Variable to track the signal state

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 2, uartTxPin);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting to WiFi...");
  }
  Serial.print("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // HTTP server routes
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<html><body>"
      "<button onclick=\"sendData('n/frwd')\">Forward</button>"
      "<button onclick=\"sendData('n/bkwd')\">Backwards</button>"
      "<button onclick=\"sendData('n/left')\">Left</button>"
      "<button onclick=\"sendData('n/rigt')\">Right</button>"
      "<button onclick=\"sendData('n/stop')\">Stop</button>"
      "<button onclick=\"sendData('n/kick')\">Kick</button>"
      "<button onclick=\"sendData('n/drbl')\">Dribble</button>"
      "<button onclick=\"sendData('n/serv')\">Servo</button>"
      "<script>"
      "function sendData(value) {"
      "  fetch('/serial?data=' + value);"
      "}"
      "</script></body></html>");
  });

  // Add a new endpoint for sending data directly to Serial2
  server.on("/serial", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("data")) {
      String data = request->getParam("data")->value();
      Serial2.print(data); // Send data directly to Serial2
    }
    request->send(200, "text/plain", "OK");
  });

  // Define HTTP endpoint for receiving kicks
  server.on("/kick", HTTP_GET, [](AsyncWebServerRequest *request) {
    // Handle the kick request here
    kick();
    request->send(200, "text/plain", "Kicked!");
  });

  server.begin();
}

void kick() {
  Serial2.print("\nKick");
  Serial.println("Kicked!");
}

void loop() {
  // Handle other tasks in the loop
}