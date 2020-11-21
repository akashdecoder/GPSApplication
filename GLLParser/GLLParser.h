#pragma once
#ifdef GLL_LIB
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // GLL_LIB


#include <iostream>
#include <vector>
#include <string>
using namespace std;


#define MINUTE_LENGTH 5

class DECLSPEC GLL {
public:
	double UTC;
	double Latitude;
	double Longitude;
	int quality;
	int altitude;
	int heigth;
	int nos;
	GLL();
	GLL(string);
	void setGLL(string);
	bool validity2(string);
	vector<string> splitstringbycomma2(string);
	int checksum2(string);
	string hexchecksum2(int);
	double stringtodouble2(string);
	double getCoordinates2(string arr);
};
double degreestodecimal2(int degrees, double minutes, double seconds);
