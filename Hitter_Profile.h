#ifndef Hitter_Profile_H_
#define Hitter_Profile_H_
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
    int getAvgNum(){
        return stoi(avg.substr(1));
    }
    int getHRNum(){
        return stoi(hrs);
    }
    int getOPSNum(){
        if (ops.size() == 4){
            return stoi(ops.substr(1));
        }
        else {
            return stoi(ops.substr(2)) + 1000;
        }
    }
    string getRuns(){
        return runs;
    }
    string getOBP(){
        return on_base_percent;
    }
    string getHits(){
        return hits;
    }
    string getRbis(){
        return rbis;
    }
    string getHrs(){
        return hrs;
    }
    string getStrikeOuts(){
        return strike_outs;
    }
    string getOPS(){
        return ops;
    }
    string getSlugging(){
        return slugging;
    }
    string getBB(){
        return bb;
    }
    string getSB(){
        return stolen_bases;
    }
    string getName(){
        return name;
    }
    void setAvg(string new_avg) {
        avg = new_avg;
    }

    static void printElement(Hitter_Profile* elem){
        cout << left << "|" << setw(2) << elem->getNumber() << "|" << setw(20) << elem->getName() << "|" << setw(4) << elem->getPos() << "|" << setw(4) << elem->getAvg() << "|" << setw(3) << elem->getHrs() << "|" << setw(5) << elem->getOPS() << "|" << endl;
    }
    static void displayTable(vector<Hitter_Profile*> hitters){
        cout << "\n\n" << endl;
        cout << left << "|" << setw(2) << "#" << "|" << setw(20) << "Player" << "|" << setw(4) << "Pos" << "|" << setw(4) << "Avg" << "|" << setw(3) << "HRs" << "|" << setw(5) << "OPS" << "|" << endl;
        for (vector<Hitter_Profile*>::iterator curr = hitters.begin(); curr != hitters.end(); curr++){
            printElement(*curr);
        }
    }
};

class CompbyAvg{
    public:
        bool operator() (Hitter_Profile *a, Hitter_Profile *b) {
            return a->getAvgNum() > b->getAvgNum();
        }
};
class CompbyHR{
    public:
        bool operator() (Hitter_Profile *a, Hitter_Profile *b) {
            return a->getHRNum() > b->getHRNum();
        }
};
class CompbyOPS{
    public:
        bool operator() (Hitter_Profile *a, Hitter_Profile *b) {
            return a->getOPSNum() > b->getOPSNum();
        }
};

#endif /*Hitter_Profile_H_*/