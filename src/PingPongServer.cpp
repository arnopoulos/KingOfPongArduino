#include "PingPongServer.h"
#include <ArduinoJson.h>

#define host String("10.22.238.133:8888")

PingPongServer::PingPongServer(Team team) {
    client = new HTTPClient();
    this->team = team;
}

void PingPongServer::sendIncrementedScore(Team team, int increment) {
    int team1increment = 0;
    int team2increment = 0;
    if (team == team1) {
        team1increment = increment;
    } else {
        team2increment = increment;
    }
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.createObject();
    object.set("team1", team1increment);
    object.set("team2", team2increment);
    String json;
    object.printTo(json);
    client->begin("http://" + host + "/updateScore");
    client->addHeader("Content-Type", "application/json");
    client->POST(json);
    client->writeToStream(&Serial);
    client->end();
}

void PingPongServer::buttonClicked(Button *button) {
    sendIncrementedScore(team, 1);
}

void PingPongServer::buttonDoubleClicked(Button *button) {
    sendIncrementedScore(team, -1);
}

void PingPongServer::buttonLongPressed(Button *button) {
    String team = "team1";
    if (this->team == team2) {
        team = "team2";
    }
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.createObject();
    object.set("resetBy", team);
    String json;
    object.printTo(json);
    client->begin("http://" + host + "/resetGame");
    client->addHeader("Content-Type", "application/json");
    client->POST(json);
    client->writeToStream(&Serial);
    client->end();
}
