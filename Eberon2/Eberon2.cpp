#include "Graph.h"
#include "Player.h"
#include "Painter.h"
#include "Room.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <array>
#include <iterator>
#include <sstream>
#include <cctype>
#include <Windows.h>


#undef max

using namespace std;


pair<int, int> Direct_Node(pair<int, int> yx, int randomcell);
Graph graph;
Player player;
Map world;
Room Cell;

int Randomizer(int floor, int limit) {
	mt19937 rng;
	rng.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist6(floor, limit); // distribution in range [1, 6]
	return dist6(rng);
}

void Generate_Random(int n, int limit) {
	int existing[4]; bool passed = false;
	int randomcell, randomsymbol = Randomizer(1, 7);
	//graph.Node_Count = graph.Node_Count + limit;
	graph.temp = graph.Get_Start();
	cout << "NC:" << graph.Node_Count;
	for (graph.Node_Count; graph.Node_Count < limit;) {
		//Randomize local until null and add nodes
		do {
			randomcell = Randomizer(0, 3);
			int *a = graph.Check_Neighbors(graph.temp, existing);
			cout << "Randomcell is " << randomcell;
			if (a[randomcell] == 0) {
				//If null neighbor detected, run Add_Node()
				cout << " Space is free, creating... \n";
				if (graph.Node_Count == limit - 1) {
					if(graph.Add_Node(graph.temp, graph.Current_Code, 9, 12,
						Direct_Node(graph.Get_yx(graph.temp), randomcell),
						"2", "test", randomcell))
						world.Change(graph.Get_yx(graph.temp).first, graph.Get_yx(graph.temp).second, 9);
					cout << " Created exit! " << endl;
				}
				if (graph.Add_Node(graph.temp, graph.Current_Code, 1, 3,
					Direct_Node(graph.Get_yx(graph.temp), randomcell),
					"2", "test", randomcell) != 0) {
					if(world.get_Map_Tile(graph.Get_yx(graph.temp).first, graph.Get_yx(graph.temp).second) == 0)
						world.Change(graph.Get_yx(graph.temp).first, graph.Get_yx(graph.temp).second, 1);
					cout << " Created node!" << endl;
				}
				else {
					cout << "\nNode not created." << endl;
				}
				
				passed = true;
			}
			
		} while (passed == false);
		//Randomize neighbor to temp;
		randomcell = Randomizer(1, 4);
		cout << "\n Traversing!" << endl;
		if (randomcell == 1 && existing[0] == 1) {
			graph.temp = graph.temp->north;
		}
		else if (randomcell == 2 && existing[1] == 1)
			graph.temp = graph.temp->east;
		else if (randomcell == 3 && existing[2] == 1)
			graph.temp = graph.temp->south;
		else if (randomcell == 4 && existing[3] == 1)
			graph.temp = graph.temp->west;
	}
}

pair<int, int> Direct_Node(pair<int, int> yx, int randomcell) {
	pair<int, int> temp;
	switch (randomcell) {
	case 0:
		temp.first = yx.first++;
		temp.second = yx.second;
		break;
	case 1:
		temp.first = yx.first;
		temp.second = yx.second++;
		break;
	case 2:
		temp.first = yx.first--;
		temp.second = yx.second;
		break;
	case 3:
		temp.first = yx.first;
		temp.second = yx.second--;
		break;
	}
	return temp;
}

map<string, int> Command_List{
	{ "north", 1 },
	{ "n", 1 },
	{ "east", 2 },
	{ "e", 2 },
	{ "south", 3 },
	{ "s", 3 },
	{ "west", 4 },
	{ "w", 4 },
	{ "look", 5 },
	{ "help", 6 },
	{ "nodes", 7 },
	{ "get", 8 },
	{ "kill", 9 },
	{ "say", 10 }
};

vector<string> Split(string input) {
	stringstream ss(input);
	string output;
	vector<string> result;
	while (getline(ss, output, ' ')) {
		result.push_back(output);
	}
	return result;
}



void Receive_Command() {
	Colorize Format;
	string command;
	vector<string> split_Command;
	int existing[4];
	while (!(getline(cin, command)) || Split(command).size() > 2) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		Format.Paint(12, "Invalid input ignored; please enter a valid command.", "\n");
	}
	command = Format.Lower(command);
	string c;
	int counter = 0;
	for (char& c : command) {
		if (isspace(c)) {
			counter++;
		}
	}
	if (counter == 0)
	{
		int ordinate_x, ordinate_y, tile;
		map<string, int>::iterator itr = Command_List.find(command);
		int option;
		if (itr != Command_List.end()) {
			option = itr->second;//Command_List.find(command)->second;
		}
		else {
			//cout << "\nNo such command detected\n";
			return;
		}
		if (option == 1) {
			ordinate_y = player.get_Position()[0] - 1; ordinate_x = player.get_Position()[1];
			tile = world.get_Map_Tile(ordinate_y, ordinate_x);
			if (world.CheckMove(tile) == 1) {
				int *ex = graph.Check_Neighbors(graph.Get_Current(), existing);
				if (ex[option - 1] != 1) {
					Format.Paint(8, "\n There is no path from here to there.", "\n");
					for (int i = 0; i < 4; i++) {
						cout << graph.Check_Neighbors(graph.Get_Current(), existing)[i]  ;
					}
					return;
				}
				if (player.set_Position(ordinate_y, ordinate_x) != 0) {
					graph.Set_Current(option);
					Format.Paint(8, "\n You leave to the north.", "\n");
					Sleep(1500);
					Format.Paint(8, "\n You arrive from the south.", "\n");
					world.Reveal(player.get_Position()[0], player.get_Position()[1]);
					graph.Compass(ex);
					Cell.get_Info(tile);
					Format.Pseudo_Clear(6);
				}
			}

		}
		else if (option == 2) {
			ordinate_y = player.get_Position()[0]; ordinate_x = player.get_Position()[1] + 1;
			tile = world.get_Map_Tile(ordinate_y, ordinate_x);
			if (world.CheckMove(tile) == 1) {
				int *ex = graph.Check_Neighbors(graph.Get_Current(), existing);
				if (ex[option - 1] != 1) {
					Format.Paint(8, "\n There is no path from here to there.", "\n");
					for (int i = 0; i < 4; i++) {
						cout << graph.Check_Neighbors(graph.Get_Current(), existing)[i];
					}
					return;
				}
				if (player.set_Position(ordinate_y, ordinate_x) != 0) {
					graph.Set_Current(option);
					Format.Paint(8, "\n You leave to the east.", "\n");
					Sleep(1500);
					Format.Paint(8, "\n You arrive from the west.", "\n");
					world.Reveal(player.get_Position()[0], player.get_Position()[1]);
					graph.Compass(ex);
					Cell.get_Info(tile);
					Format.Pseudo_Clear(6);
				}
			}
		}
		else if (option == 3) {
			ordinate_y = player.get_Position()[0] + 1; ordinate_x = player.get_Position()[1];
			tile = world.get_Map_Tile(ordinate_y, ordinate_x);
			if (world.CheckMove(tile) == 1) {
				int *ex = graph.Check_Neighbors(graph.Get_Current(), existing);
				if (ex[option - 1] != 1) {
					Format.Paint(8, "\n There is no path from here to there.", "\n");
					for (int i = 0; i < 4; i++) {
						cout << graph.Check_Neighbors(graph.Get_Current(), existing)[i];
					}
					return;
				}
				if (player.set_Position(ordinate_y, ordinate_x) != 0)
				{
					graph.Set_Current(option);
					Format.Paint(8, "\n You leave to the south.", "\n");
					Sleep(1500);
					Format.Paint(8, "\n You arrive from the north.", "\n");
					world.Reveal(player.get_Position()[0], player.get_Position()[1]);
					graph.Compass(ex);
					Cell.get_Info(tile);
					Format.Pseudo_Clear(6);
				}
			}
		}
		else if (option == 4) {
			ordinate_y = player.get_Position()[0]; ordinate_x = player.get_Position()[1] - 1;
			tile = world.get_Map_Tile(ordinate_y, ordinate_x);
			if (world.CheckMove(tile) == 1) {
				int *ex = graph.Check_Neighbors(graph.Get_Current(), existing);
				if (ex[option - 1] != 1) {
					Format.Paint(8, "\n There is no path from here to there.", "\n");
					for (int i = 0; i < 4; i++) {
						cout << graph.Check_Neighbors(graph.Get_Current(), existing)[i];
					}
					return;
				}
				if (player.set_Position(ordinate_y, ordinate_x) != 0)
				{
					graph.Set_Current(option);
					Format.Paint(8, "\n You leave to the west.", "\n");
					Sleep(1500);
					Format.Paint(8, "\n You arrive from the east.", "\n");
					world.Reveal(player.get_Position()[0], player.get_Position()[1]);
					graph.Compass(ex);
					Cell.get_Info(tile);
					Format.Pseudo_Clear(6);
				}
			}
		}
		else if (option == 5) {
			Format.Paint(7, "\n You take a good look around.", "\n");
			Sleep(1500);
			//Format.Pseudo_Clear(1);
			world.Reveal(player.get_Position()[0], player.get_Position()[1]);
		}
		else if (option == 6) {
			Format.Paint(7, "\n You read the list of nodes.", "\n");
			Sleep(1500);
			player.Help();
		}
		else if (option == 7) {
			Format.Paint(7, "\n You read the list of nodes.", "\n");
			Sleep(1500);
			graph.Get_Nodes();
		}
	}
	else if (counter > 0 && counter < 2) {
		split_Command = Split(command);
		string command_1, command_2;
		command_1 = split_Command[0];
		command_2 = split_Command[1];
		int option;
		string monsterName;
		map<string, int>::iterator itr = Command_List.find(command_1);
		if (itr != Command_List.end()) {
			option = itr->second;
		}
		else {
			cout << "\nNo such command detected\n";
			return;
		}
		if (option == 8) {
			Format.Paint(7, "\n You get the item.", "\n");
			Sleep(1500);
		}
		else if (option == 10) {
			Sleep(1500);
			Format.Paint(11, "\n You say: ", ""); cout << "\"" << command_2 << "\"" << endl;
		}
	}
	else {
		Format.Paint(12, "Invalid compound input ignored; please enter a valid command.", "\n");
	}
}

void Generate() {
	graph.Add_Node(graph.Get_Start(), 00001, '.', 3, graph.Get_yx(graph.Get_Start()), "Hallway", "Dark Halls", 1);
}

void WorldView() {
	Colorize Format;
	player.set_Position(20, 15);
	graph.Create(player.get_Position()[0], player.get_Position()[1]);
	world.Change(20, 15, 8);
	//cout << "\n";
	//Format.Paint(14, "\n The labyrinth of Eberon lies before you...", "\n");
	
	int counter = 0;
	bool isValid = false;
	int node_number;
	cout << "We will now create your world. \n"; //cin.ignore(1000, '\n');
	cout << "Now, enter how many more location nodes you want generated (12 nodes are pre-generated): ";
	cin >> node_number;
	cout << "\nYour world is being generated... \n";
	Generate_Random(20, node_number);
	world.Reveal((player.get_Position()[0]), (player.get_Position()[1]));
	Format.Paint(15, "\n You may now freely enter any valid command: ", "\n");
	cout << " The "; 	Format.Paint(13, "@", ""); cout << " symbol denotes your player position on the map. Try moving around!" << endl;

	//graph.Add_Node(graph.Get_Start(), 00001, 4, 3, graph.Get_yx(graph.Get_Start()), "Hallway", "Dark Halls", 1);
	while (!(isValid)) {
		//Attribute();
		Receive_Command();
		counter++;
		if (counter == 1000) isValid = true;
	}
}



int main()
{
	while (true) {
		WorldView();
	}
}