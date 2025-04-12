#include <ESP8266WiFi.h>
#include <WiFiManager.h>

#define FLASH_BUTTON 0
#define LED_BUILTIN 16

WiFiManager wm; 
bool wm_nonblocking = false;

void setup() {
  Serial.begin(115200);
  pinMode(FLASH_BUTTON, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.setDebugOutput(true);
  delay(1000);
  Serial.println("\n\nESP8266 Starting...");
  
  if(wm_nonblocking) wm.setConfigPortalBlocking(false);

  //std::vector<const char *> menu = {"wifi","info","param","sep","restart","exit"};
  std::vector<const char *> menu = {"wifi","info","restart","exit"};
  wm.setMenu(menu);
  wm.setConfigPortalTimeout(180); // 180s
  wm.setTitle("WiFi Setup"); //Title
  wm.setClass("invert"); //theme

  if (digitalRead(FLASH_BUTTON) == LOW) {
    Serial.println("Press and hold the FLASH_BUTTON for 3 s.");
    delay(3000);
    Serial.println("Button pressed. Resetting WiFi settings...");
    wm.resetSettings();
    delay(1000);
    for (int i = 0; i < 5; i++) {
      digitalWrite(LED_BUILTIN, HIGH); 
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);  
      delay(500);
    } 
  }
  connectToWiFi();       
}

void loop() {
  if(wm_nonblocking) {
    wm.process();
  }
  //run
  delay(100);
}

void connectToWiFi() {

  bool res = wm.autoConnect("ESP-PPXD", "12345678");

  if (!res) {
    Serial.println("Failed to connect or timeout. Restarting...");
    delay(3000);
    ESP.restart();
  }else{
    for (int i = 0; i < 3; i++) {
      digitalWrite(LED_BUILTIN, HIGH); 
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);  
      delay(500);
    }
    Serial.println("Connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());

    Serial.print("Connected SSID: ");
    Serial.println(WiFi.SSID());

    Serial.print("Signal Strength (RSSI): ");
    Serial.println(WiFi.RSSI());

    Serial.print("Gateway IP: ");
    Serial.println(WiFi.gatewayIP());

    Serial.print("Subnet Mask: ");
    Serial.println(WiFi.subnetMask());

    Serial.print("DNS Server: ");
    Serial.println(WiFi.dnsIP());

    Serial.print("Hostname: ");
    Serial.println(WiFi.hostname());

    Serial.print("WiFi Status: ");
    Serial.println(WiFi.status());

    Serial.print("Firmware Version: ");
    Serial.println(ESP.getFullVersion());
  }
}