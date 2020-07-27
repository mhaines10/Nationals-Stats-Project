#ifndef Player_Info_H_
#define Player_Info_H_
#include <stdio.h>
#include <string>

using namespace std;

class Player_Info
{
protected:
    string name;
    string jerseyNum;
    string throws;
    string position;
    string bats;
    string player_id;
public:
    Player_Info();
    virtual ~Player_Info();
    string getPlayerId(){
        return player_id;
    }
    string getName() {
        return name;
    }
    string getPos(){
        return position;
    }
    string getNumber(){
        return jerseyNum;
    }
};

#endif /*Player_Info_H_*/