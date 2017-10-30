#include <mine.h>

using namespace std;
int main(int argc, char** argv) {
    extern BWString WOEID;
    double min,max = 0;
    BWString city;
    BWString type = "WOEID";
    BWString url,querry;
    BWString temp;
    //inputs
    if( argc < 2) {
        cout << "No input city: Using default \n";
        city = "Athens";
    }
    else {
        city = argv[1];
    }
    cout <<"Accessing Database...\n";
    const char* dbfile = "/home/kostas/NetBeansProjects/StringSelection/WOEID.db";
    sqlite3 *db;
    char *szErrMsg = 0;
    int rc = sqlite3_open(dbfile, &db);
      if(rc)
        {
            std::cout << "Can't open database\n";
        } else {
          std::cout << "Open database successfully\n";
        } 
    temp = "SELECT * from test WHERE stamp = '" + city +"'";
    const char * query = temp.c_str();
    struct sqlite3_stmt *selectstmt;
    int result = sqlite3_prepare_v2(db, query, -1, &selectstmt, NULL);
    if (result == SQLITE_OK) {
        if (sqlite3_step(selectstmt) == SQLITE_ROW){
            //record found
            cout<<"Record for city " << city << " already exists! \n";
            // show record
            rc = sqlite3_exec(db, query, callback, 0, &szErrMsg);
            if(rc != SQLITE_OK)
                {
                    std::cout << "SQL Error: " << szErrMsg << std::endl;
                    sqlite3_free(szErrMsg);
                    return 1;
                } 
        }
        else{
            //record not found
            cout << "Record not found.\n";
            cout << "Accessing Web Services ..\n";
            //create query
            get_url_metaweather(city,url);
            get_web(url,querry);
            if (querry.length() < 10) {
                 cout << "City not found" << endl;
                 return 0;
            }
            WOEID_getter(querry,WOEID);
            cout << "Location : " << city << endl;
            cout << "WOEID = " << WOEID << endl;
            cout << "Saving Data..\n";
            temp = "INSERT INTO test(value, type, stamp) VALUES ('" + WOEID +  "', '"+ type + "', '" + city+"')";
            query = temp.c_str();
            rc = sqlite3_exec(db, query, callback, 0, &szErrMsg);
            if(rc != SQLITE_OK)
                {
                    std::cout << "SQL Error: " << szErrMsg << std::endl;
                    sqlite3_free(szErrMsg);
                   // break;
                } 
        }
        sqlite3_finalize(selectstmt);
       
        
    }
    // GETTING WEATHER DATA
    cout << "GETTING WEATHER DATA\n";
    get_url_data(WOEID,url);
    get_web(url,querry);
    //json 
    access_json(min,max,querry);
    cout << "AVERAGE Max TEMP = " <<max <<endl;
    cout << "AVERAGE Min TEMP = " <<min<<endl;

    if(db)
    {
        sqlite3_close(db);
    }
    return 0;
}


