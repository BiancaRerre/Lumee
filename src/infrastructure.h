#include <WiFiManager.h>

void wmConfig() {
  // cria o objeto WiFiManager
  WiFiManager wm;
  // define a URL da página de autenticação
  //wm.setCaptivePortalAuthURL("/wifi");

  // tenta se conectar à rede WiFi armazenada ou inicia o portal cativo
  bool res = wm.autoConnect("𝑳𝒖𝒎𝒆𝒆🚨");

  if (!MDNS.begin("Lumee")) {
    Serial.println("Error setting up MDNS responder!");
  }
  MDNS.addService("http", "tcp", 80);
  WiFi.hostname("𝑳𝒖𝒎𝒆𝒆🚨");

      // Loop para piscar o LED enquanto não estiver conectado ao WiFi




}
