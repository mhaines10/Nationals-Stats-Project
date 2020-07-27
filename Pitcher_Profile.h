#ifndef Pitcher_Profile_H_
#define Pitcher_Profile_H_
#include "Player_Info.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <regex>
#include <iostream>
#include <iomanip>
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
    
    int getWinsNum(){
        return stoi(wins);
    }
    int getEraNum(){
        return stoi(era);
    }
    int getStrikeoutNum(){
        return stoi(strike_outs);
    }
    string getEra(){
        return era;
    }
    string getWins(){
        return wins;
    }
    string getInnings(){
        return innings_pitched;
    }
    string getStrikeouts(){
        return strike_outs;
    }

    static void printElement(Pitcher_Profile* elem){
        cout << left << "|" << setw(2) << elem->getNumber() << "|" << setw(20) << elem->getName() << "|" << setw(3) << elem->getPos() << "|" << setw(5) << elem->getEra() << "|" << setw(4) << elem->getWins()<< "|" << setw(3) << elem->getStrikeouts() << "|" << endl;
    }
    static void displayTable(vector<Pitcher_Profile*> pitchers){
        cout << "\n\n" << endl;
        cout << left << "|" << setw(2) << "#" << "|" << setw(20) << "Player" << "|" << setw(3) << "Pos" << "|" << setw(5) << "ERA" << "|" << setw(3) << "Wins" << "|" << setw(3) << "SOs" << "|" << endl;
        for (vector<Pitcher_Profile*>::iterator curr = pitchers.begin(); curr != pitchers.end(); curr++){
            printElement(*curr);
        }
    }
};

class CompbyEra{
    public:
        bool operator() (Pitcher_Profile *a, Pitcher_Profile *b) {
            return a->getEraNum() > b->getEraNum();
        }
};
class CompbyWins{
    public:
        bool operator() (Pitcher_Profile *a, Pitcher_Profile *b) {
            return a->getWinsNum() > b->getWinsNum();
        }
};
class CompbySO{
    public:
        bool operator() (Pitcher_Profile *a, Pitcher_Profile *b) {
            return a->getStrikeoutNum() > b->getStrikeoutNum();
        }
};

#endif /*Pitcher_Profile_H_*/