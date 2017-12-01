#ifndef Button_H
#define Button_H

#include <stdint.h>

class ButtonDelegate;
class SimpleTimer;

class Button {
public:
    Button(uint8_t buttonPin);
    void loop();
    void setDelegate(ButtonDelegate *delegate);
    bool isButtonPressed();
private:
    uint8_t buttonPin;
    bool buttonPressed;
    int previousReading = 0;
    unsigned long lastDebounceTime = 0;
    int doubleClickToken = -1;
    int longPressToken = -1;
    ButtonDelegate *delegate;
    SimpleTimer *timer;
    void updateButtonState();
};

#endif
