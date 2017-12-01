#ifndef PingPongServer_H
#define PingPongServer_H

#include <ESP8266HTTPClient.h>
#include "Button.h"
#include "ButtonDelegate.h"

enum Team {
    team1, team2
};

class PingPongServer: public ButtonDelegate {
public:
    PingPongServer(Team team);
    // void loop();
    void buttonClicked(Button *button);
    void buttonDoubleClicked(Button *button);
    void buttonLongPressed(Button *button);
private:
    HTTPClient *client;
    Team team;
    void sendIncrementedScore(Team team, int increment);
};

#endif
