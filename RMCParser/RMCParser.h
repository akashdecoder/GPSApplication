#pragma once
#ifdef RMC_LIB
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // RMC_LIB


#include <iostream>
#include <vector>
#include <string>
using namespace std;


#define MINUTE_LENGTH 5
#define KNOTS_TO_MPS 0.514444444

class DECLSPEC RMC {
public:
    int Utc;
    double lat;
    double lon;
    double speed;
    double truecourse;
    int date;
    double mgv;
    RMC();
    RMC(string);
    void setGPS(string);
    bool validity(string);
    vector<string> splitstringbycomma(string);
    int checksum(string);
    string hexchecksum(int);
    double stringtodouble(string);
    double getCoordinates(string arr);
};
double degreestodecimal(int degrees, double minutes, double seconds);
