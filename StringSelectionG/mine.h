/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mine.h
 * Author: kostas
 *
 * Created on September 27, 2017, 4:23 PM
 */
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <BWString.h>
#include <iostream>
#include <sqlite3.h>
#include <curl/curl.h>
#include <string.h>
#include <jsoncpp/json/json.h> // or jsoncpp/json.h , or json/json.h etc.


#ifndef MINE_H
#define MINE_H

// function definitions
int callback(void *NotUsed, int argc, char **argv, char **szColName);
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
void  WOEID_getter(const BWString & ,  BWString & );
void get_url_metaweather( const BWString & city, BWString &url);
void get_url_data( BWString & , BWString & url);
BWString & get_web( const BWString & url, BWString & data);
void access_json(double & min, double & max, BWString & querry);


//const char* api_host = "https://www.metaweather.com/api/location/search/?query=";  

#endif /* MINE_H */

