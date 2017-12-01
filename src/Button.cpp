#include "Button.h"
#include "ButtonDelegate.h"
#include <SimpleTimer.h>
#include <Arduino.h>

Button::Button(uint8_t buttonPin) {
    timer = new SimpleTimer();
    this->buttonPin = buttonPin;
    pinMode(buttonPin, INPUT);
}

void Button::setDelegate(ButtonDelegate *delegate) {
    this->delegate = delegate;
}

bool Button::isButtonPressed() {
    return buttonPressed;
}

void Button::updateButtonState() {
    int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != previousReading) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > 50) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonPressed) {
      buttonPressed = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonPressed) {
        if (longPressToken != -1) {
            timer->deleteTimer(longPressToken);
            longPressToken = -1;
        }
        longPressToken = timer->setTimeout(750, [this]() {
            if (this->isButtonPressed()) {
                this->delegate->buttonLongPressed(this);
            }
            longPressToken = -1;
        });
        if (doubleClickToken == -1) {
            doubleClickToken = timer->setTimeout(250, [this]() {
                if (!this->isButtonPressed()) {
                    this->delegate->buttonClicked(this);
                }
                doubleClickToken = -1;
            });
        } else {
            timer->deleteTimer(doubleClickToken);
            doubleClickToken = -1;
            delegate->buttonDoubleClicked(this);
        }

      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  previousReading = reading;
}

void Button::loop() {
    updateButtonState();
    timer->run();
}
