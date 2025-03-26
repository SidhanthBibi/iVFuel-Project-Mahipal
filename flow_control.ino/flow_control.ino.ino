#include <WiFiS3.h>
#include <Wire.h>
#include <ArduinoHttpClient.h>
#include <avr/pgmspace.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "website_files_progmem.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Wi-Fi credentials
const char ssid[] = "mahipal";
const char pass[] = "12345678";

WiFiServer server(80);
const char serverAddress[] = "ivfuels.vercel.app"; // Vercel endpoint
int port = 443; // HTTPS
WiFiSSLClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);

// Flow sensor setup
const int flowSensorPin = 2;
volatile int pulseCount = 0;
float calibrationFactor = 4.5;

unsigned long lastUpdate = 0;
float flowRate = 0;
float totalLitres = 0;

void displayStatus(String statusLine) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Flow: "); display.print(flowRate, 2); display.println(" L/min");
  display.print("Total: "); display.print(totalLitres, 2); display.println(" L");
  display.setCursor(0, 40);
  display.println(statusLine);
  display.display();
}

void sendProgmem(WiFiClient& client, const char* data) {
  char c;
  while ((c = pgm_read_byte(data++)) != 0) {
    client.write(c);
  }
}

void sendToVercel(float flow, float total) {
  String payload = "{\"flow\":" + String(flow, 2) + ",\"total\":" + String(total, 2) + "}";
  displayStatus("Sending ➤ 🔄");

  client.beginRequest();
  client.post("/api/update");
  client.sendHeader("Content-Type", "application/json");
  client.sendHeader("Content-Length", payload.length());
  client.beginBody();
  client.print(payload);
  client.endRequest();

  int status = client.responseStatusCode();
  String response = client.responseBody();
  Serial.print("Status: "); Serial.println(status);
  Serial.print("Response: "); Serial.println(response);

  if (status == 200) {
    displayStatus("Sent to Vercel ✔️");
  } else {
    displayStatus("Error ❌ Code: " + String(status));
  }
}

void setup() {
  Serial.begin(9600);
  delay(1000);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("\xF0\x9F\x9A\x80 Booting...");
  display.display();

  pinMode(flowSensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);

  Serial.print("\xF0\x9F\x93\xB6 Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(1000);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n\xE2\x9C\x85 WiFi connected");
    Serial.print("\xF0\x9F\x8C\x90 IP Address: ");
    Serial.println(WiFi.localIP());
    server.begin();
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("WiFi Connected!");
    display.setCursor(0, 10);
    display.print("IP: "); display.println(WiFi.localIP());
    display.display();
  } else {
    Serial.println("\n\xE2\x9D\x8C WiFi connection failed. Restarting...");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("WiFi Failed :(");
    display.display();
    delay(3000);
    NVIC_SystemReset();
  }
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastUpdate >= 1000) {
    detachInterrupt(digitalPinToInterrupt(flowSensorPin));

    flowRate = ((1000.0 / (currentMillis - lastUpdate)) * pulseCount) / calibrationFactor;
    float flowLitres = flowRate / 60.0;
    totalLitres += flowLitres;

    // Print the flow rate and total liters to the Serial Monitor
    Serial.print("Flow Rate: ");
    Serial.println(flowRate);
    Serial.print("Total Litres: ");
    Serial.println(totalLitres);

    lastUpdate = currentMillis;
    pulseCount = 0;

    attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);

    sendToVercel(flowRate, totalLitres);
  }

  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String req = client.readStringUntil('\r');
        client.flush();

        if (req.indexOf("GET /data") >= 0) {
          String json = "{\"flow\":" + String(flowRate, 2) + ",\"total\":" + String(totalLitres, 2) + "}";
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json");
          client.println("Connection: close");
          client.println();
          client.println(json);
        } else if (req.indexOf("GET /index.html") >= 0 || req.indexOf("GET /") >= 0) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          sendProgmem(client, index_html);
        } else if (req.indexOf("GET /home.html") >= 0) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          sendProgmem(client, home_html);
        } else if (req.indexOf("GET /fuel-flow.html") >= 0) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          sendProgmem(client, fuel_flow_html);
        } else if (req.indexOf("GET /style.css") >= 0) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/css");
          client.println("Connection: close");
          client.println();
          sendProgmem(client, style_css);
        } else if (req.indexOf("GET /script.js") >= 0) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/javascript");
          client.println("Connection: close");
          client.println();
          sendProgmem(client, script_js);
        } else {
          client.println("HTTP/1.1 404 Not Found");
          client.println("Content-Type: text/plain");
          client.println("Connection: close");
          client.println();
          client.println("404 Not Found");
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
