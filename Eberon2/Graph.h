#ifndef Graph_H
#define Graph_H
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <list>
#include <random>


using namespace std;

class Graph {
private:
	struct Area {
		int code;
		int symbol;
		int color;
		pair<int , int> yx;
		string title;
		string description;
		Area *north;
		Area *east;
		Area *south;
		Area *west;
	};
	Area *Start;
	Area *End;
	Area *Current;
	int Node_Count;
	int Current_Code = 0;
	vector<Area> *Listing;
	vector<pair<int, int>> Visited;
	map<pair<int, int>, Area> Exists;
public:
	Graph();
	int Get_Code();
	int Get_Title();

	void Create();
	void Add_Node(Area before, int code, int symbol, int color, pair<int,int> yx, string title, string description, int coordinate);
	Area Connect_Nodes(Area before, pair<int, int> yx);
	void Check_Neighbors();
};

class Map {
private:
	int X, Y;
	int current_Tile;
	int replaced_Tile;
	int replacedCounter;
	int position;
	//int Grid[5][5]{
	//	0,0,0,0,0,
	//	0,0,0,0,0,
	//	0,0,1,0,0,
	//	0,0,0,0,0,
	//	0,0,0,0,0
	//};
	int Grid
public:
	Map();
	void Reveal(int player_y, int player_x);
	int get_Map_Tile(int y, int x);
};

#endif
