#include <Arduino.h>
#include <SimpleTimer.h>
#include "MockButtonDelegate.h"
#include "Button.h"
#include "ESP8266WiFi.h"
#include "PingPongServer.h"

#define buttonPin D8

Button *button;

const char *ssid = "workday-guest";
const char *password = "Welcome2Workday";

void setup() {
    Serial.begin(9600);

    WiFi.mode(WIFI_AP);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Waiting to connect");
    }

    Serial.println("Wi-Fi connected");
    Serial.println(WiFi.localIP());

    PingPongServer *server = new PingPongServer(team2);

    button = new Button(buttonPin);
    button->setDelegate(server);
}

void loop() {
    button->loop();
}
