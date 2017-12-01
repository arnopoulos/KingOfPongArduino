#include <Arduino.h>
#include <SimpleTimer.h>

#define buttonPin D0

boolean holding = false;
boolean isLongPress = false;
boolean doubleClickPossible = false;
SimpleTimer timer;
int longPressTimerToken = -1;
int doubleClickTimerToken = -1;

void clickEvent() {
  Serial.println("Single Click");
}

void doubleClickEvent() {
  Serial.println("Double Click");
}

void holdEvent() {
  Serial.println("Hold");
}

void setup() {
  Serial.begin(9600);
  // Set button input pin
  pinMode(buttonPin, INPUT);

  timer = SimpleTimer();
  timer.setInterval(50, []() {
    boolean currentValue = digitalRead(buttonPin);
    if (currentValue && !holding && !doubleClickPossible) {
      longPressTimerToken = timer.setTimeout(750, []() {
        isLongPress = true;
        holdEvent();
      });
    }
    if (currentValue && !holding && doubleClickPossible) {
      Serial.println("Double click timer will invalidate");
      timer.deleteTimer(doubleClickTimerToken);
      doubleClickTimerToken = -1;
      doubleClickEvent();
      doubleClickPossible = false;
    }
    if (!currentValue && holding && !isLongPress) {
      if (longPressTimerToken != -1) {
        timer.deleteTimer(longPressTimerToken);
        longPressTimerToken = -1;
      }
      doubleClickTimerToken = timer.setTimeout(250, []() {
        doubleClickPossible = false;
        clickEvent();
      });
      doubleClickPossible = true;
    }
    if (!currentValue && holding && isLongPress) {
      isLongPress = false;
    }
    holding = currentValue;
  });
}

void loop() {
  timer.run();
}
