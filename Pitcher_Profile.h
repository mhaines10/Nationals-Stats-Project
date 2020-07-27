#ifndef Pitcher_Profile_H_
#define Pitcher_Profile_H_
#include "Player_Info.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <curl/curl.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;

class Pitcher_Profile : public Player_Info
{
protected:
    string saves;
    string whip;
    string era;
    string games;
    string wins;
    string loses;
    string innings_pitched;
    string k_9;
    string bb;
    string strike_outs;


public:
    Pitcher_Profile();
    virtual ~Pitcher_Profile();
    void getPlayerInfo(string nameIn, string id, string jerseyNumber, string pos, string bat, string hand);
    void setPlayerStats();
};

#endif /*Pitcher_Profile_H_*/