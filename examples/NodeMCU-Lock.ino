#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>

// GitHub Page = https://github.com/Tommrodrigues/homebridge-http-lock-mechanism

// Script Type = Relay Momentary

// D7 = Relay

/////////////////// CHANGE THESE VALUES //////////////////////
const char* ssid = "SSID"; // Name of your network
const char* password = "PASSWORD"; // Password for your network
const char* www_username = "admin";
const char* www_password = "esp8266";
const String relay = "HIGH"; // Relay type (`HIGH` or `LOW`)
const char* mdns = "lock"; // mDNS name
const int momentaryOn = 1000; // Delay time for the on state (ms)
//////////////////////////////////////////////////////////////

// The certificate is stored in PMEM
static const uint8_t x509[] PROGMEM = {

};

// And so is the key.  These could also be in DRAM
static const uint8_t rsakey[] PROGMEM = {

};

const int relayPin = 13;

int relayOn, relayOff;
int state = 1;

ESP8266WebServerSecure server(443);

void setup() {
  if (relay.equals("LOW")) {
    relayOn = 0;
    relayOff = 1;
  } else {
    relayOn = 1;
    relayOff = 0;
  }

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, relayOff);

  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.println("Connecting to \"" + String(ssid) + "\"");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(String(++i) + " ");
  }
  Serial.println();
  Serial.println("Connected successfully");

  // Print the IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin(mdns)) {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS address: " + String(mdns) + ".local");

  server.getServer().setServerKeyAndCert_P(rsakey, sizeof(rsakey), x509, sizeof(x509));

  server.on("/setState", []() {
    if (server.authenticate(www_username, www_password)) {
      state = server.arg("value").toInt();
      if (state) {
        digitalWrite(relayPin, relayOn);
        delay(momentaryOn);
        digitalWrite(relayPin, relayOff);
      } else {
        digitalWrite(relayPin, relayOn);
        delay(momentaryOn);
        digitalWrite(relayPin, relayOff);
      }
      server.send(200);
    }
  });

  server.on("/status", []() {
    size_t capacity = JSON_OBJECT_SIZE(1);
    DynamicJsonDocument doc(capacity);

    doc["currentState"] = state;

    String json;
    serializeJson(doc, json);
    server.send(200, "application/json", json);
  });

  // Start the server
  server.begin();
}

void loop() {
  server.handleClient();
  MDNS.update();
}
