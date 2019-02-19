#ifndef Player_H
#define Player_H	
#include "Painter.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
class Player {
private:
	//Role
	std::string Name;
	//Logistics
	int Level = 1;
	//Location
	int X, Y;
public:
	Player();
	void Move(std::string command);
	int set_Position(int y, int x);
	std::vector<int> get_Position();
	std::vector<int> get_NextMove(int y, int x);
	void set_Name(std::string input);
	std::string get_Name();
	void Help();
};

#endif
