#include "Pitcher_Profile.h"

Pitcher_Profile::Pitcher_Profile(){}
Pitcher_Profile::~Pitcher_Profile(){}

void Pitcher_Profile::getPlayerInfo(string nameIn, string id, string jerseyNumber, string pos, string bat, string hand){
    name = nameIn;
    player_id = id;
    jerseyNum = jerseyNumber;
    bats = bat;
    throws = hand;
    position = pos;
}

size_t handlePitcherResp(char *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Pitcher_Profile::setPlayerStats(){
    CURL *curlStat;
    CURLcode res;
    string readBuff;
    Document d;
    string base_url = "http://lookup-service-prod.mlb.com/json/named.sport_pitching_tm.bam?league_list_id='mlb'&game_type='R'&season='2020'&player_id=";
    string full_url = base_url + "'" + player_id + "'";

    curlStat = curl_easy_init();
    if (curlStat) {
        curl_easy_setopt(curlStat, CURLOPT_URL, full_url.c_str());

        curl_easy_setopt(curlStat, CURLOPT_WRITEFUNCTION, handlePitcherResp);
        curl_easy_setopt(curlStat, CURLOPT_WRITEDATA, &readBuff);

        res = curl_easy_perform(curlStat);

        if (res != CURLE_OK) {
            printf("Failed");
        }
        
        d.Parse(readBuff.c_str());

        Value& querySize = d["sport_pitching_tm"]["queryResults"]["totalSize"];
        string queryString = querySize.GetString();
        if (stoi(queryString) == 1){
            Value& stats = d["sport_pitching_tm"]["queryResults"]["row"];
            saves = stats["sv"].GetString();
            whip = stats["whip"].GetString();
            era = stats["era"].GetString();
            games = stats["g"].GetString();
            wins = stats["w"].GetString();
            loses = stats["l"].GetString();
            innings_pitched = stats["ip"].GetString();
            strike_outs = stats["so"].GetString();
            bb = stats["bb"].GetString();
            k_9 = stats["k9"].GetString();
        }                
    }
    curl_easy_cleanup(curlStat);
}