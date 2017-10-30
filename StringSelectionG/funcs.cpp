/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "mine.h"
using namespace std;
BWString WOEID;


void  WOEID_getter(const BWString & querry, BWString & WOEID){
    vector<BWString> lineparts = querry.split("woeid");
 //   cout << "lineparts = "<< lineparts.size() << endl;
    lineparts = lineparts[1].split(",");
   // cout << lineparts[0] << endl;
    WOEID = lineparts[0];
    lineparts =WOEID.split(":");
    WOEID = lineparts[1];
   // cout << WOEID << endl;


    return ;
}

void get_url_metaweather( const BWString & city, BWString &url){
    url = "https://www.metaweather.com/api/location/search/?query=";
    url += city;
    return;
}
int callback(void *NotUsed, int argc, char **argv, char **szColName)
{
  for(int i = 0; i < argc; i++)
  {
    std::cout << szColName[i] << " = " << argv[i] << std::endl; //showing
    WOEID = argv[0];
  }

  std::cout << "\n";

  return 0;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
void get_url_data( BWString & WOEID, BWString & url){
    url = "https://www.metaweather.com/api/location/";
    url += WOEID;
    return;
}

BWString & get_web( const BWString & url, BWString & data){
    CURL *curl;
    CURLcode res;
    string readBuffer;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
        curl_easy_cleanup(curl);
      //  cout << readBuffer << endl;

    }
    data = readBuffer;
    return data;
}

void access_json(double & min, double & max, BWString & querry){
    Json::Value obj;
    Json::Reader reader;
    reader.parse(querry.c_str(), obj); // reader can also read strings
    const Json::Value& characters = obj["consolidated_weather"]; // array of characters
    for (int i = 0; i < characters.size(); i++){
        cout << "max temp = : " << characters[i]["max_temp"].asDouble();
        cout << " min temp = : " << characters[i]["min_temp"].asDouble();
        min += characters[i]["min_temp"].asDouble();
        max += characters[i]["max_temp"].asDouble();
        cout << endl;
    }
    min = min/characters.size();
    max = max/characters.size();
    return;
}


