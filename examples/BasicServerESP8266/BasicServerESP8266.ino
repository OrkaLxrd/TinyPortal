#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "TinyPortal.h"

ESP8266WebServer server(80);
TinyPortal portal;

void setup() {
  WiFi.softAP("ESP8266", "12345678");  // точка доступа

  // страница портала
  server.on("/", []() {
    server.send(200, "text/html",
      "<h1>ESP8266 Portal</h1>"
      "<p>Вы подключились к Wi-Fi</p>");
  });

  portal.begin(server);  // редирект в "/"

  server.begin();
}

void loop() {
  server.handleClient();
  portal.loop();
}