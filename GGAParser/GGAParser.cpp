#include "pch.h"
#include "GGAParser.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cstdlib>

using namespace std;

GGA::GGA() {
	Utc = 0;
	Latitude = 0;
	Longitude = 0;
	quality = 0;
	altitude = 0;
	heigth = 0;
	nos = 0;
}

GGA::GGA(string str) {
	if (validity1(str)) {
		setGGA(str);
	}
}

bool GGA::validity1(string str) {
    bool ret = true;
    vector<string>ele = splitstringbycomma1(str);
    if (ele[0] != "$GPGGA")  ret = false;
    if (atoi(ele[6].c_str()) == 0) ret = false;
    if (ele[2].length() < MINUTE_LENGTH) ret = false;
    if (ele[4].length() < MINUTE_LENGTH) ret = false;
    if (atoi(ele[7].c_str()) == 0) ret = false;
    return ret;
}
void GGA::setGGA(string str) {
    vector<string>ele = splitstringbycomma1(str);
    assert(ele[0] == "$GPGGA");
    this->Utc = atoi(ele[1].c_str());
    cout << "UTC Time: " << Utc << endl;
    this->Latitude = getCoordinates1(ele[2]);
    if (ele[3] == "S") this->Latitude = -this->Latitude;
    cout << "Latitude: " << Latitude << " " << ele[3] << endl;
    this->Longitude = getCoordinates1(ele[4]);
    cout << "Longitude: " << Longitude << " " << ele[5] << endl;
    this->nos = atoi(ele[7].c_str());
    cout << "No of Satellites: " << nos << endl;
    cout << "HDOP: " << ele[8] << endl;
    this->altitude = stringtodouble1(ele[9]);
    cout << "Altitude: " << altitude << ele[10] << endl;
    this->heigth = stringtodouble1(ele[11]);
    cout << "Height: " << ele[11] << ele[12] << endl;
    cout << "GGA checksum = " << hexchecksum1(checksum1(str));
}

vector<string>GGA::splitstringbycomma1(string str) {
    vector<string>ret;
    stringstream ss(str);
    string element;
    while (getline(ss, element, ',')) {
        ret.push_back(element);
    }
    return ret;
}

double GGA::stringtodouble1(string str) {
    double r;
    stringstream st(str);
    st >> r;
    return r;
}

double degreestodecimal1(int degrees, double minutes, double seconds) {
    double ret = 0;
    ret = degrees + minutes / 60 + seconds / 3600.0;
    return ret;
}
double GGA::getCoordinates1(string arr) {
    double decimal = 0;
    string degarr;
    string minarr;
    if (arr.length() > MINUTE_LENGTH) {
        degarr.assign(arr.begin(), arr.end() - MINUTE_LENGTH);
        minarr.assign(arr.end() - MINUTE_LENGTH, arr.end());
        int deg;
        double mins;
        deg = atoi(degarr.c_str());
        mins = stringtodouble1(minarr);
        decimal = degreestodecimal1(deg, mins, 0);
    }
    return decimal;
}

int GGA::checksum1(string nmea) {
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
string GGA::hexchecksum1(int n) {
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
