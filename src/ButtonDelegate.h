#ifndef ButtonDelegate_H
#define ButtonDelegate_H

class Button;

class ButtonDelegate {
public:
    virtual void buttonClicked(Button *button) = 0;
    virtual void buttonDoubleClicked(Button *button) = 0;
    virtual void buttonLongPressed(Button *button) = 0;
};

#endif
