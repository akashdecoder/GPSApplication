#include <iostream>
#include <cmath>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <mysql.h>
#include <limits>
#include <windows.h>
#include "GGAParser.h"
#include "RMCParser.h"
#include "GLLParser.h"


using namespace std;

int qstate;

int main() {
	int type;
	string data;
	string query;
	string s1;
	int choice;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	const char* q;
	char ipAddress[100];
	char username[100];
	char password[100];
	char databasename[100];
	system("Color E0");
	cout << "Wait Loading the screen";
	for (int i = 0; i < 5; i++) {
		cout << ".";
		cout.flush();
		Sleep(1000);
	}
	cout << endl;
	system("cls");
	system("Color F5");
	cout << "Enter IPAddress: ";
	cin >> ipAddress;
	cout << "Enter Username: ";
	cin >> username;
	cout << "Enter Database Server Password: ";
	cin >> password;
	cout << "Enter Database name(Create the database first then enter here..): ";
	cin >> databasename;
	system("cls");
	conn = mysql_init(0);
	conn = mysql_real_connect(
		conn,
		ipAddress,
		username,
		password,
		databasename,
		3306,
		NULL, 0);
	if (conn) {
		system("Color F4");
		cout << "Connecting To Database Server";
		for (int i = 0; i < 5; i++) {
			cout << ".";
			cout.flush();
			Sleep(1000);
		}
		cout << endl;
		system("cls");
		cout << "Connected to GPS Database Server";
		while (1) {
			cout << "\n\n1. Create Table in the Database\n2. Insert GGA Data into Database Query\n3. Insert RMC Data into Database Query\n4. Insert GLL Data into Database Query\n5. Select from Table Query\n6. Parse the GPS data\n7. Exit" << endl;
			cout << "Enter your choice: ";
			cin >> choice;
			switch (choice) {
			case 1:
				query = "create table gpsdata (Type varchar(10), Data varchar(200));";
				q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate) {
					cout << "Created Table: gpsdata(Type varchar(10), Data varchar(200))." << endl;
				}
				else {
					cout << "Error creating table" << mysql_error(conn) << endl;
				}
				break;
			case 2:
				cout << "Enter Data: ";
				cin.ignore();
				getline(cin, data);
				query = "insert into gpsdata(Type, Data) values('GGA', '" + data + "');";
				q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate) {
					cout << "Data Inserted into the database"<<endl;
				}
				else {
					cout << "Error inserting" << mysql_error(conn) << endl;
				}
				break;
			case 3:
				cout << "Enter Data: ";
				cin.ignore();
				getline(cin, data);
				query = "insert into gpsdata(Type, Data) values('RMC', '" + data + "');";
				q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate) {
					cout << "Data Inserted into the database" << endl;
				}
				else {
					cout << "Error inserting" << mysql_error(conn) << endl;
				}
				break;
			case 4:
				cout << "Enter Data: ";
				cin.ignore();
				getline(cin, data);
				query = "insert into gpsdata(Type, Data) values('GLL', '" + data + "');";
				q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate) {
					cout << "Data Inserted into the database" << endl;
				}
				else {
					cout << "Error inserting" << mysql_error(conn) << endl;
				}
				break;
			case 5:
				query = "select * from gpsdata;";
				q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate) {
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res)) {
						cout << "Type: " << row[0] << "\nData: " << row[1] << endl;
					}
				} else {
					cout << "Query Failed" << mysql_error(conn) << endl;
				}
				break;
			case 6:
				query = "select * from gpsdata;";
				q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate) {
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res)) {
						s1 = row[0];
						if (s1.compare("GGA") == 0) {
							cout << "\n\nParsed GGA Data\n";
							GGA obj;
							GGA obj1(row[1]);
						}
						else if (s1.compare("RMC") == 0) {
							cout << "\n\nParsed RMC Data\n";
							RMC obj2;
							RMC obj3(row[1]);
						}
						else if (s1.compare("GLL") == 0) {
							cout << "\n\nParsed GLL Data\n";
							GLL obj4;
							GLL obj5(row[1]);
						}
						else {
							cout << row[1] << " Not a valid data" << endl;
						}
					}
				}
				else {
					cout << "SQL Error" << mysql_error(conn) << endl;
				}
				break;
			case 7:
				exit(0);
			default:
				cout << "---Sorry---" << endl;
			}
		}
	}
	else {
		cout << "Errror" << mysql_error(conn) << endl;
	}
	
	return 0;
}