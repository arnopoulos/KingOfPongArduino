#include "MockButtonDelegate.h"
#include "Button.h"

void MockButtonDelegate::buttonClicked(Button *button) {
    Serial.println("Button clicked");
}

void MockButtonDelegate::buttonDoubleClicked(Button *button) {
    Serial.println("Button double clicked");
}

void MockButtonDelegate::buttonLongPressed(Button *button) {
    Serial.println("Button long pressed");
}
