#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

// GitHub Page = https://github.com/Tommrodrigues/homebridge-http-lock-mechanism

// Script Type = Relay Momentary

// D7 = Relay

/////////////////// CHANGE THESE VALUES //////////////////////
const char* ssid = "SSID"; //Name of your network
const char* password = "PASSWORD"; //Password for your network
const char* relay = "HIGH"; //Relay type (`HIGH` or `LOW`)
const char* mdns = "lock"; //mDNS name
const char* onKey = "/SECRETKEY"; //e.g. "/NjWymLQzyd3PPp9N"
const char* offKey = "/SECRETKEY"; //e.g. "/f3gZbxREJYFKRmz6"
const int momentaryOn = 1000; //Delay time for the on state (ms)
//////////////////////////////////////////////////////////////

const int relayPin = 13;

int relayOn, relayOff;
int state = 1;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  if (relay == "LOW") {
    relayOn = 0;
    relayOff = 1;
  } else {
    relayOn = 1;
    relayOff = 0;
  }

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, relayOff);

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

  // Start the server
  server.begin();

  // Print the IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin(mdns)) {
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS address: " + String(mdns) + ".local");
}

void loop() {

  MDNS.update();

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("New client");
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");

  if (request.indexOf(offKey) != -1)  {
    digitalWrite(relayPin, relayOn);
    delay(momentaryOn);
    digitalWrite(relayPin, relayOff);
    state = 1;
  }

  if (request.indexOf(onKey) != -1)  {
    digitalWrite(relayPin, relayOn);
    delay(momentaryOn);
    digitalWrite(relayPin, relayOff);
    state = 0;
  }


  if (request.indexOf("/status") != -1)  {
    client.print(String(state));
  }

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");

}
