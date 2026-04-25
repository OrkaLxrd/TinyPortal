# TinyPortal

Minimal captive portal library for ESP32 and ESP8266.

TinyPortal provides DNS hijack and automatic redirect to your web
interface without interfering with your existing WebServer.

------------------------------------------------------------------------

## ✨ Features

-   Works with **ESP32** and **ESP8266**
-   Uses your existing `WebServer`
-   No Wi-Fi control (you manage it yourself)
-   Automatic captive portal detection:
    -   iOS
    -   Android
    -   Windows
-   DNS hijack + redirect
-   Custom redirect path support

------------------------------------------------------------------------

## 🚀 Installation

### Arduino Library Manager (recommended)

Search for:

TinyPortal

and install.

### Manual install

Download ZIP and place into:

Arduino/libraries/

------------------------------------------------------------------------

## 🔧 Usage

### Basic example

``` cpp
#include <WiFi.h>
#include <WebServer.h>
#include <TinyPortal.h>

WebServer server(80);
TinyPortal portal;

void setup() {
  WiFi.softAP("TinyPortal", "12345678");

  server.on("/", []() {
    server.send(200, "text/html", "<h1>Portal</h1>");
  });

  portal.begin(server);

  server.begin();
}

void loop() {
  server.handleClient();
  portal.loop();
}
```

------------------------------------------------------------------------

### Custom redirect path

``` cpp
portal.begin(server, "/home");
```

``` cpp
server.on("/home", []() {
  server.send(200, "text/html", "<h1>Home Portal</h1>");
});
```

------------------------------------------------------------------------

## 📡 How it works

TinyPortal:

1.  Starts DNS server (`* → AP IP`)
2.  Intercepts OS connectivity checks
3.  Redirects all traffic to your page


------------------------------------------------------------------------

## ⚠️ Notes

-   Wi-Fi must be started manually: WiFi.softAP(...)
-   You must define the redirect page (`/` or custom path)
-   Captive portal auto-opens mostly on mobile devices
-   Call portal.begin(server) AFTER defining your routes:
``` cpp
server.on("/", ...);
server.on("/home", ...);
portal.begin(server);
```
------------------------------------------------------------------------

## 📄 License

MIT License

------------------------------------------------------------------------

## 🤝 Contributing

Pull requests and ideas are welcome.

------------------------------------------------------------------------

## ⭐ Support

If you like the project, give it a star ⭐
