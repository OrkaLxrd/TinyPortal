#include <WiFi.h>
#include <WebServer.h>
#include "TinyPortal.h"

WebServer server(80);
TinyPortal portal;

void setup() {
  WiFi.softAP("ESP32", "12345678");

  server.on("/", []() {
    server.send(200, "text/html",
      "<h1>Portal</h1><p>Добро пожаловать</p>");
  });

  portal.begin(server);

  server.begin();
}

void loop() {
  server.handleClient();
  portal.loop();
}