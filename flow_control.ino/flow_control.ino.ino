#include <WiFiS3.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Wi-Fi credentials
const char ssid[] = "mahipal";
const char pass[] = "12345678";

WiFiServer server(80);

// Flow sensor setup
const int flowSensorPin = 2;
volatile int pulseCount = 0;
float calibrationFactor = 4.5;

unsigned long lastUpdate = 0;
float flowRate = 0;
float totalLitres = 0;

void setup() {
  Serial.begin(9600);

  // Flow sensor interrupt
  pinMode(flowSensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);

  // OLED startup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("❌ OLED not found"));
    while (true); // Halt if OLED fails
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Connecting to WiFi...");
  display.display();

  // Wi-Fi connect
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\n✅ WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("WiFi Connected!");
  display.setCursor(0, 10);
  display.print("IP: ");
  display.println(WiFi.localIP());
  display.display();

  server.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  // Update values every second
  if (currentMillis - lastUpdate >= 1000) {
    detachInterrupt(digitalPinToInterrupt(flowSensorPin));

    flowRate = ((1000.0 / (currentMillis - lastUpdate)) * pulseCount) / calibrationFactor;
    float flowLitres = flowRate / 60.0;
    totalLitres += flowLitres;

    lastUpdate = currentMillis;
    pulseCount = 0;

    // Update OLED
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Flow: ");
    display.print(flowRate, 2);
    display.print(" L/min");
    display.setCursor(0, 20);
    display.print("Total: ");
    display.print(totalLitres, 2);
    display.print(" L");
    display.display();

    attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);
  }

  // Web client response
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String req = client.readStringUntil('\r');
        client.flush();

        // Serve JSON if requested
        if (req.indexOf("GET /data") >= 0) {
          String json = "{\"flow\":" + String(flowRate, 2) + ",\"total\":" + String(totalLitres, 2) + "}";
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json");
          client.println("Connection: close");
          client.println();
          client.println(json);
        } else {
          // Serve dashboard UI
          String html = R"=====(<!DOCTYPE html>
<html>
<head>
  <meta charset='UTF-8'>
  <meta name='viewport' content='width=device-width, initial-scale=1.0'>
  <title>Fuel Monitor</title>
  <style>
    body {
      background: #0f172a;
      color: #f8fafc;
      font-family: Arial, sans-serif;
      display: flex;
      flex-direction: column;
      align-items: center;
      padding: 40px;
    }
    h1 {
      font-size: 2rem;
      margin-bottom: 20px;
    }
    .card {
      background: #1e293b;
      padding: 20px 30px;
      border-radius: 16px;
      box-shadow: 0 10px 25px rgba(0,0,0,0.2);
      width: 300px;
      text-align: center;
    }
    .value {
      font-size: 2.2rem;
      margin: 10px 0;
      font-weight: bold;
    }
    .label {
      color: #94a3b8;
      font-size: 1rem;
    }
  </style>
  <script>
    function fetchData() {
      fetch('/data')
        .then(res => res.json())
        .then(data => {
          document.getElementById('flow').innerText = data.flow + ' L/min';
          document.getElementById('total').innerText = data.total + ' L';
        });
    }
    setInterval(fetchData, 1000);
    window.onload = fetchData;
  </script>
</head>
<body>
  <h1>Fuel Flow Monitor</h1>
  <div class="card">
    <div class="label">Flow Rate</div>
    <div class="value" id="flow">--</div>
    <div class="label">Total Volume</div>
    <div class="value" id="total">--</div>
  </div>
</body>
</html>)=====";

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println(html);
        }

        break;
      }
    }
    delay(1);
    client.stop();
  }
}

void pulseCounter() {
  pulseCount++;
}