#include "pch.h"
#include "GLLParser.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cstdlib>

using namespace std;

GLL::GLL() {
    UTC = 0;
    Latitude = 0;
    Longitude = 0;
}

GLL::GLL(string str) {
    if (validity2(str)) {
        setGLL(str);
    }
}

bool GLL::validity2(string str) {
    bool ret = true;
    vector<string>ele = splitstringbycomma2(str);
    if (ele[0] != "$GPGLL")  ret = false;
    if (ele[1].length() < MINUTE_LENGTH) ret = false;
    if (ele[3].length() < MINUTE_LENGTH) ret = false;
    return ret;
}
void GLL::setGLL(string str) {
    vector<string>ele = splitstringbycomma2(str);
    assert(ele[0] == "$GPGLL");
    this->Latitude = getCoordinates2(ele[1]);
    if (ele[2] == "S") this->Latitude = -this->Latitude;
    cout << "Latitude: " << Latitude << " " << ele[2] << endl;
    this->Longitude = getCoordinates2(ele[3]);
    cout << "Longitude: " << Longitude << " " << ele[4] << endl;
    this->UTC = atoi(ele[5].c_str());
    cout << "UTC Time: " << UTC << endl;
    cout << "GLL checksum = " << hexchecksum2(checksum2(str));
}

vector<string>GLL::splitstringbycomma2(string str) {
    vector<string>ret;
    stringstream ss(str);
    string element;
    while (getline(ss, element, ',')) {
        ret.push_back(element);
    }
    return ret;
}

double GLL::stringtodouble2(string str) {
    double r;
    stringstream st(str);
    st >> r;
    return r;
}

double degreestodecimal2(int degrees, double minutes, double seconds) {
    double ret = 0;
    ret = degrees + minutes / 60 + seconds / 3600.0;
    return ret;
}
double GLL::getCoordinates2(string arr) {
    double decimal = 0;
    string degarr;
    string minarr;
    if (arr.length() > MINUTE_LENGTH) {
        degarr.assign(arr.begin(), arr.end() - MINUTE_LENGTH);
        minarr.assign(arr.end() - MINUTE_LENGTH, arr.end());
        int deg;
        double mins;
        deg = atoi(degarr.c_str());
        mins = stringtodouble2(minarr);
        decimal = degreestodecimal2(deg, mins, 0);
    }
    return decimal;
}

int GLL::checksum2(string nmea) {
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
string GLL::hexchecksum2(int n) {
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
