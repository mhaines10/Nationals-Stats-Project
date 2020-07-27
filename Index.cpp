#include <stdio.h>
#include <string>
#include <curl/curl.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream> 
#include <vector> 
#include <algorithm>
#include "Hitter_Profile.h"
#include "Pitcher_Profile.h"

using namespace rapidjson;
using namespace std;

size_t handleResp(char *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void wait(){
    cin.get();
}

int main() {
    CURL *curl;
    CURLcode res;
    string readBuff;
    Document d;
    vector<Hitter_Profile*> hitter_profiles;
    vector<Pitcher_Profile*> pitcher_profiles;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://lookup-service-prod.mlb.com/json/named.roster_40.bam?team_id='120'");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleResp);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuff);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            printf("Failed");
        }
        
        d.Parse(readBuff.c_str());
        Value& rows = d["roster_40"]["queryResults"]["row"];
        for (SizeType i = 0; i < rows.Size(); i ++){
            string pos = rows[i]["position_txt"].GetString();
            if (strcmp(pos.c_str(), "P") != 0){
                Hitter_Profile * temp = new Hitter_Profile();
                temp->getPlayerInfo(rows[i]["name_display_first_last"].GetString(), rows[i]["player_id"].GetString(), rows[i]["jersey_number"].GetString(), rows[i]["position_txt"].GetString(), rows[i]["bats"].GetString(), rows[i]["throws"].GetString());
                temp->setPlayerStats();
                hitter_profiles.push_back(temp);
            }
            else {
                Pitcher_Profile * temp = new Pitcher_Profile();
                temp->getPlayerInfo(rows[i]["name_display_first_last"].GetString(), rows[i]["player_id"].GetString(), rows[i]["jersey_number"].GetString(), rows[i]["position_txt"].GetString(), rows[i]["bats"].GetString(), rows[i]["throws"].GetString());
                temp->setPlayerStats();
                pitcher_profiles.push_back(temp);
            }
        }
        curl_easy_cleanup(curl);
    }
    bool looping = true;
    while (looping) {
        int input;
        printf("Please Enter the Number of the option you wish to select: \n");
        printf("1. Sort Batters by Avg\n2. Sort Batters by Home Runs\n3. Sort Batters by OPS\n4. Sort Pitchers by ERA\n5. Sort Pitchers by Wins\n6. Sort Pitchers by Strike Outs\n7. Exit\n\n");

        if(scanf("%d", &input) == 1){
            switch(input){
                case 1:
                    sort(hitter_profiles.begin(), hitter_profiles.end(), CompbyAvg());
                    Hitter_Profile::displayTable(hitter_profiles);
                    printf("\nPress Enter When Done\n");
                    cin.ignore();
                    cin.ignore();
                    break;
                case 2:
                    sort(hitter_profiles.begin(), hitter_profiles.end(), CompbyHR());
                    Hitter_Profile::displayTable(hitter_profiles);
                    printf("\nPress Enter When Done\n");
                    cin.ignore();
                    cin.ignore();
                    break;
                case 3:
                    sort(hitter_profiles.begin(), hitter_profiles.end(), CompbyOPS());
                    Hitter_Profile::displayTable(hitter_profiles);
                    printf("\nPress Enter When Done\n");
                    cin.ignore();
                    cin.ignore();
                    break;
                case 7:
                    looping = false;
                    break;
                default:
                    break;
                

            }
        }
    }
    return 0;
}

