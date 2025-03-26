#include <WiFiS3.h>
#include <Wire.h>
#include <ArduinoHttpClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Wi-Fi credentials
const char ssid[] = "mahipal";
const char pass[] = "12345678";

// Vercel API settings
const char serverAddress[] = "ivfuels.vercel.app";
int port = 443; // HTTPS
WiFiSSLClient wifi;
HttpClient client(wifi, serverAddress, port);

// Flow sensor setup
const int flowSensorPin = 2;
volatile int pulseCount = 0;
float calibrationFactor = 4.5;

unsigned long lastUpdate = 0;
float flowRate = 0.0;
float totalLitres = 0.0;

void pulseCounter() {
  pulseCount++;
}

void showDisplay(String statusLine) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Flow: ");
  display.print(flowRate, 2);
  display.println(" L/min");

  display.print("Total: ");
  display.print(totalLitres, 2);
  display.println(" L");

  display.setCursor(0, 40);
  display.println(statusLine);
  display.display();
}

void sendToVercel(float flow, float total) {
  String payload = "{\"flow\":" + String(flow, 2) + ",\"total\":" + String(total, 2) + "}";
  showDisplay("Sending -->");

  client.beginRequest();
  client.post("/api/update");
  client.sendHeader("Content-Type", "application/json");
  client.sendHeader("Content-Length", payload.length());
  client.beginBody();
  client.print(payload);
  client.endRequest();

  int status = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status: ");
  Serial.println(status);
  Serial.print("Response: ");
  Serial.println(response);

  if (status == 200) {
    showDisplay("Sent to Vercel OK");
  } else {
    showDisplay("Err Code: " + String(status));
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
  display.println("Booting...");
  display.display();

  pinMode(flowSensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);

  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(1000);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("WiFi Connected ✓");
    display.setCursor(0, 10);
    display.print("IP: ");
    display.println(WiFi.localIP());
    display.display();
  } else {
    Serial.println("\nWiFi failed. Restarting...");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("WiFi Failed ❌");
    display.display();
    delay(3000);
    NVIC_SystemReset(); // Auto-reset
  }
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastUpdate >= 200) {  // Faster: 200ms
    detachInterrupt(digitalPinToInterrupt(flowSensorPin));

    flowRate = ((1000.0 / (currentMillis - lastUpdate)) * pulseCount) / calibrationFactor;
    float flowLitres = flowRate / 60.0;
    totalLitres += flowLitres;

    lastUpdate = currentMillis;
    pulseCount = 0;

    attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);

    sendToVercel(flowRate, totalLitres);
  }
}
