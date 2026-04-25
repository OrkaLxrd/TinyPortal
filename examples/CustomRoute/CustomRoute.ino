#include <WiFi.h>
#include <WebServer.h>
#include "TinyPortal.h"

WebServer server(80);
TinyPortal portal;

void setup() {
  WiFi.softAP("ESP32", "12345678");

  server.on("/home", []() {
    server.send(200, "text/html",
      "<h1>HOME</h1><p>Это портал</p>");
  });

  server.on("/", []() {
    server.send(200, "text/plain", "API root");
  });

  portal.begin(server, "/home");

  server.begin();
}

void loop() {
  server.handleClient();
  portal.loop();
}