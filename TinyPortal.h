#pragma once

#if defined(ESP32)
  #include <WiFi.h>
  #include <WebServer.h>
  typedef WebServer TPServer;
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
  typedef ESP8266WebServer TPServer;
#else
  #error "TinyPortal supports only ESP32 and ESP8266"
#endif

#include <DNSServer.h>

class TinyPortal {
public:
  TinyPortal();

  void begin(TPServer& server);                 // "/"
  void begin(TPServer& server, const String&);  // кастом путь

  void loop();

private:
  TPServer* _server;
  DNSServer _dns;
  bool _started;
  String _path;

  void setupRoutes();
  void redirect();
};