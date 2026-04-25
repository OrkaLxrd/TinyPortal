#include "TinyPortal.h"

TinyPortal::TinyPortal()
  : _server(nullptr), _started(false), _path("/") {}

void TinyPortal::begin(TPServer& server) {
  begin(server, "/");
}

void TinyPortal::begin(TPServer& server, const String& path) {
  _server = &server;
  _path = path;

  if (!_path.startsWith("/")) {
    _path = "/" + _path;
  }

  IPAddress ip = WiFi.softAPIP();
  _dns.start(53, "*", ip);

  setupRoutes();
  _started = true;
}

void TinyPortal::redirect() {
  String url = "http://" + WiFi.softAPIP().toString() + _path;
  _server->sendHeader("Location", url, true);
  _server->send(302, "text/plain", "");
}

void TinyPortal::setupRoutes() {
  if (!_server) return;

  // Android
  _server->on("/generate_204", [this]() { redirect(); });
  _server->on("/gen_204", [this]() { redirect(); });

  // iOS / macOS
  _server->on("/hotspot-detect.html", [this]() { redirect(); });
  _server->on("/library/test/success.html", [this]() { redirect(); });

  // Windows
  _server->on("/connecttest.txt", [this]() { redirect(); });
  _server->on("/ncsi.txt", [this]() { redirect(); });
  _server->on("/fwlink", [this]() { redirect(); });

  // fallback
  _server->onNotFound([this]() {
    redirect();
  });
}

void TinyPortal::loop() {
  if (_started) {
    _dns.processNextRequest();
  }
}
