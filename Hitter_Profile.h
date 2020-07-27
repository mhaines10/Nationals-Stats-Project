#ifndef Hitter_Profile_H_
#define Hitter_Profile_H_
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

class Hitter_Profile : public Player_Info
{
protected:
    string at_bats;
    string runs;
    string on_base_percent;
    string hits;
    string rbis;
    string hrs;
    string ops;
    string avg;
    string bb;
    string strike_outs;
    string slugging;
    string stolen_bases;

public:
    Hitter_Profile();
    virtual ~Hitter_Profile();
    void getPlayerInfo(string nameIn, string id, string jerseyNumber, string pos, string bat, string hand);
    void setPlayerStats();
    string getAvg(){
        return avg;
    }

};

#endif /*Hitter_Profile_H_*/