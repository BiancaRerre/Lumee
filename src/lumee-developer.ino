//PROJETO LUMEE

#include <Arduino.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>
#include "./infrastructure.h"
#include"./html.h"
#include"./js.h"
#include"./style.h"
;
int pinR = 12;
int pinG = 13;
int pinB = 14;

int R[] = {255, 0, 0, 23, 56, 217}; // red
int G[] = {255, 0, 255, 123, 156, 187}; // red
int B[] = {25, 158, 100, 0, 156, 87}; // red

//int modo = "fade";

// LED config
#define PIN 4
#define NUMPIXELS 4
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

ESP8266WebServer server(80);
String corRGB ="";

void hendleIndex() {                           // send HTML to the page
    Serial.println("GET /");
    server.send(200, "text/html", postForms);  // check HTML.h file
}
void handleStyle() {                           // send HTML to the page
    Serial.println("GET /style.css");
    server.send(200, "text/css", style);  // check HTML.h file
}
void handlejs() {                           // send HTML to the page
    Serial.println("GET /js");
    server.send(200, "application/javascript", js);  // check HTML.h file
}

void handleGetParam() {
 if (server.hasArg("cor")) {
    String corRGB = server.arg("cor");
    String r = corRGB.substring(4,corRGB.indexOf(','));
    corRGB = corRGB.substring(corRGB.indexOf(',')+1);
    String g = corRGB.substring(0,corRGB.indexOf(','));
    corRGB = corRGB.substring(corRGB.indexOf(',')+1);
    String b = corRGB.substring(0,corRGB.length()-1);
    pixels.setPixelColor(0,pixels.Color(r.toInt(),g.toInt(),b.toInt()));
    pixels.show();

    analogWrite(pinR, r.toInt());
    analogWrite(pinG, g.toInt());
    analogWrite(pinB, b.toInt());

    Serial.print("r: ");
    Serial.println(r.toInt());
    Serial.print("g: ");
    Serial.println(g.toInt());    
    Serial.print("b: ");
    Serial.println(b.toInt());
 }

}   

void handleconfig() { 
 if (server.hasArg("set")) {
   //Definir qual Gpio é cada cor
    pinR = server.arg("pinR").toInt();
    pinG = server.arg("pinG").toInt();
    pinB = server.arg("pinB").toInt();

    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);  
    
 }
    server.send(200, "text/html", configLumee);
    Serial.println("GET /config");
}   

void setup() {
    #ifdef ESP8266
    analogWriteFreq(8000);
    #endif
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW); //ACENDE O LED QUANDO O WIFI NÃO TIVER CONECTADO
    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);
    WiFi.mode(WIFI_STA);
    Serial.begin(115200);
    wmConfig(); // infrastructure.h

  

    //init server
    server.on("/", hendleIndex);
    server.on("/style.css", handleStyle);
    server.on("/js", handlejs);
    server.on("/config", handleconfig);
    server.on("/cor", handleGetParam);
    server.begin();

    //init leds
    pixels.begin();
    pixels.clear();
    pixels.setPixelColor(0,pixels.Color(0,255,0));
    //pixels.fill(0,pixels.Color(0,255,0));
    pixels.show();
    delay(30);
    digitalWrite(LED_BUILTIN, HIGH);// APAGA O LED QUE INFORMA O WIFI


    

}

void loop() {
    while (!WiFi.isConnected()) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
    }

    MDNS.update();
    server.handleClient();
    anima();
}

void anima(){
  

}


