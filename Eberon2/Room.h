#pragma once
#include<iostream>
#include <string>
using namespace std;

class Room {
private:
	string Title, Description;
	int Code;
public:
	Room(string Title, string Description, int code);
	Room();
	void get_Info(char tile);
	int get_Code();
	string get_Title();
	string get_Description();
};