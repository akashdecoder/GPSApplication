#include "pch.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cstdlib>
#include "RMCParser.h"
using namespace std;


RMC::RMC() {
    Utc = 0;
    lat = 0;
    lon = 0;
    speed = 0;
    truecourse = 0;
    date = 0;
    mgv = 0;
}
RMC::RMC(string str) {
    if (validity(str)) {
        setGPS(str);
    }
}
bool RMC::validity(string str) {
    bool ret = true;
    vector<string>ele = splitstringbycomma(str);
    if (ele[0] != "$GPRMC")  ret = false;
    //if(ele.size()!=12)  ret=false;
    if (ele[2] != "A") ret = false;
    if (ele[3].length() < MINUTE_LENGTH) ret = false;
    if (ele[5].length() < MINUTE_LENGTH) ret = false;
    return ret;
}
void RMC::setGPS(string str) {
    vector<string>ele = splitstringbycomma(str);
    assert(ele[0] == "$GPRMC");
    this->Utc = atoi(ele[1].c_str());
    cout << "UTC Time: " << Utc << endl;
    this->lat = getCoordinates(ele[3]);
    if (ele[4] == "S") this->lat = -this->lat;
    cout << "Latitude: " << lat << " " << ele[4] << endl;
    this->lon = getCoordinates(ele[5]);
    cout << "Longitude: " << lon << " " << ele[6] << endl;
    this->speed = stringtodouble(ele[7]);
    cout << "Speed in Knots: " << speed << endl;
    this->truecourse = stringtodouble(ele[8]);
    cout << "TrueCourse: " << truecourse << endl;
    this->date = atoi(ele[9].c_str());
    cout << "Date: " << date << endl;
    this->mgv = stringtodouble(ele[10]);
    cout << "Variation: " << mgv << " " << ele[11] << endl;
    cout << "RMC checksum = " << hexchecksum(checksum(str));
}

vector<string>RMC::splitstringbycomma(string str) {
    vector<string>ret;
    stringstream ss(str);
    string element;
    while (getline(ss, element, ',')) {
        ret.push_back(element);
    }
    return ret;
}

double RMC::stringtodouble(string str) {
    double r;
    stringstream st(str);
    st >> r;
    return r;
}

double degreestodecimal(int degrees, double minutes, double seconds) {
    double ret = 0;
    ret = degrees + minutes / 60 + seconds / 3600.0;
    return ret;
}
double RMC::getCoordinates(string arr) {
    double decimal = 0;
    string degarr;
    string minarr;
    if (arr.length() > MINUTE_LENGTH) {
        degarr.assign(arr.begin(), arr.end() - MINUTE_LENGTH);
        minarr.assign(arr.end() - MINUTE_LENGTH, arr.end());
        int deg;
        double mins;
        deg = atoi(degarr.c_str());
        mins = stringtodouble(minarr);
        decimal = degreestodecimal(deg, mins, 0);
    }
    return decimal;
}

int RMC::checksum(string nmea) {
    char ch;
    int checksum = 0;
    for (int i = 0; i < nmea.size(); ++i) {
        ch = nmea[i];
        switch (ch) {
        case '$':
            break;
        case '*':
            i = nmea.size();
            continue;
        default:
            if (checksum == 0) {
                checksum = ch;
            }
            else {
                checksum = checksum ^ ch;
            }
            break;
        }
    }
    return checksum;
}
string RMC::hexchecksum(int n) {
    string hex = "";
    char ch;
    while (n != 0) {
        int temp = 0;
        temp = n % 16;
        if (temp < 10) {
            ch = temp + 48;
            hex = hex + ch;
        }
        else {
            ch = temp + 55;
            hex = hex + ch;
        }
        n = n / 16;
    }
    reverse(hex.begin(), hex.end());
    return hex;
}
