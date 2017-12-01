#include <Arduino.h>
#include <SimpleTimer.h>
#include "MockButtonDelegate.h"
#include "Button.h"

#define buttonPin D8

Button *button;

void setup() {
    Serial.begin(9600);

    button = new Button(buttonPin);
    button->setDelegate(new MockButtonDelegate());
}

void loop() {
    button->loop();
}
