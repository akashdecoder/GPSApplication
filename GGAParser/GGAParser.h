#pragma once
#ifdef GGA_LIB
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif // GGA_LIB


#include <iostream>
#include <vector>
#include <string>
using namespace std;


#define MINUTE_LENGTH 5

class DECLSPEC GGA{
public:
	int Utc;
	double Latitude;
	double Longitude;
	int quality;
	int altitude;
	int heigth;
	int nos;
	GGA();
	GGA(string);
	void setGGA(string);
	bool validity1(string);
	vector<string> splitstringbycomma1(string);
	int checksum1(string);
	string hexchecksum1(int);
	double stringtodouble1(string);
	double getCoordinates1(string arr);
};
double degreestodecimal1(int degrees, double minutes, double seconds);

