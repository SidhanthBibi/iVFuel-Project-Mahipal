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

// Web server setup
WiFiServer server(80);
String header;

// Flow sensor setup
const int flowSensorPin = 2;
volatile int pulseCount = 0;
float calibrationFactor = 4.5;
unsigned long lastUpdate = 0;
float flowRate = 0.0;
float totalLitres = 0.0;

// HTML content
#include "html_content.h"  // This includes your existing PROGMEM HTML files

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
    
    // Start web server
    server.begin();
    Serial.println("Web server started");
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
  // 1. Update flow sensor readings
  unsigned long currentMillis = millis();
  if (currentMillis - lastUpdate >= 1000) {  // Update once per second
    detachInterrupt(digitalPinToInterrupt(flowSensorPin));
    
    flowRate = ((1000.0 / (currentMillis - lastUpdate)) * pulseCount) / calibrationFactor;
    float flowLitres = flowRate / 60.0;
    totalLitres += flowLitres;
    
    lastUpdate = currentMillis;
    pulseCount = 0;
    
    attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);
    
    // Only send to Vercel if flow is detected (optimize data usage)
    if (flowRate > 0.1) {
      sendToVercel(flowRate, totalLitres);
    } else {
      showDisplay("Waiting for flow...");
    }
  }

  // 2. Handle web server client requests
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("New client connected");
    String currentLine = "";
    unsigned long currentTime = millis();
    unsigned long previousTime = currentTime;
    const unsigned long timeout = 2000;  // 2 seconds timeout
    
    while (client.connected() && currentTime - previousTime <= timeout) {
      currentTime = millis();
      
      if (client.available()) {
        char c = client.read();
        header += c;
        
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type: text/html");
            client.println("Connection: close");
            client.println();
            
            // Route handling
            if (header.indexOf("GET /index.html") >= 0 || header.indexOf("GET / ") >= 0) {
              client.print(index_html);
            } 
            else if (header.indexOf("GET /home.html") >= 0) {
              client.print(home_html);
            } 
            else if (header.indexOf("GET /fuel-flow.html") >= 0) {
              client.print(fuel_flow_html);
            } 
            else if (header.indexOf("GET /style.css") >= 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type: text/css");
              client.println("Connection: close");
              client.println();
              client.print(style_css);
            } 
            else if (header.indexOf("GET /script.js") >= 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type: text/javascript");
              client.println("Connection: close");
              client.println();
              client.print(script_js);
            }
            else if (header.indexOf("GET /api/flow-data") >= 0) {
              // API endpoint for flow data
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type: application/json");
              client.println("Connection: close");
              client.println();
              
              // Send JSON response with current flow data
              String jsonResponse = "{\"flow\":" + String(flowRate, 2) + 
                                  ",\"total\":" + String(totalLitres, 2) + "}";
              client.println(jsonResponse);
            }
            
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    
    header = "";
    client.stop();
    Serial.println("Client disconnected");
  }
}