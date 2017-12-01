#ifndef MockButtonDelegate_H
#define MockButtonDelegate_H

#include "ButtonDelegate.h"
#include <Arduino.h>

class MockButtonDelegate: public ButtonDelegate {
public:
    void buttonClicked(Button *button);
    void buttonDoubleClicked(Button *button);
    void buttonLongPressed(Button *button);
};

#endif
