#include "Hitter_Profile.h"

Hitter_Profile::Hitter_Profile(){}
Hitter_Profile::~Hitter_Profile(){}

void Hitter_Profile::getPlayerInfo(string nameIn, string id, string jerseyNumber, string pos, string bat, string hand){
    name = nameIn;
    player_id = id;
    jerseyNum = jerseyNumber;
    bats = bat;
    throws = hand;
    position = pos;
}

size_t handleHitterResp(char *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Hitter_Profile::setPlayerStats(){
    CURL *curlStat;
    CURLcode res;
    string readBuff;
    Document d;
    string base_url = "http://lookup-service-prod.mlb.com/json/named.sport_hitting_tm.bam?league_list_id='mlb'&game_type='R'&season='2020'&player_id=";
    string full_url = base_url + "'" + player_id + "'";

    curlStat = curl_easy_init();
    if (curlStat) {
        curl_easy_setopt(curlStat, CURLOPT_URL, full_url.c_str());

        curl_easy_setopt(curlStat, CURLOPT_WRITEFUNCTION, handleHitterResp);
        curl_easy_setopt(curlStat, CURLOPT_WRITEDATA, &readBuff);

        res = curl_easy_perform(curlStat);

        if (res != CURLE_OK) {
            printf("Failed");
        }
        
        d.Parse(readBuff.c_str());

        Value& querySize = d["sport_hitting_tm"]["queryResults"]["totalSize"];
        string queryString = querySize.GetString();
        if (stoi(queryString) == 1){
            Value& stats = d["sport_hitting_tm"]["queryResults"]["row"];
            at_bats = stats["ab"].GetString();
            runs = stats["r"].GetString();
            on_base_percent = stats["obp"].GetString();
            rbis = stats["rbi"].GetString();
            hits = stats["h"].GetString();
            hrs = stats["hr"].GetString();
            ops = stats["ops"].GetString();
            strike_outs = stats["so"].GetString();
            avg = stats["avg"].GetString();
            bb = stats["bb"].GetString();
            slugging = stats["slg"].GetString();
            stolen_bases = stats["sb"].GetString();
        }                
    }
    curl_easy_cleanup(curlStat);
}