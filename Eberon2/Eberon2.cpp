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
const int cX = 40, cY = 35;

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
	int randomcell, randomsymbol = Randomizer(1, 7), randomroom;
	pair<int, int> undirected, directed;
	//graph.Node_Count = graph.Node_Count + limit;
	graph.temp = graph.Get_Start();
	cout << "NC:" << graph.Node_Count;
	for (graph.Node_Count; graph.Node_Count < limit;) {
		//Randomize local until null and add nodes

			
		randomcell = Randomizer(0, 3);
		int *a = graph.Check_Neighbors(*graph.temp, existing);
		cout << "\nRandomcell is " << randomcell;
		if (a[randomcell] == 0) {
			//If null neighbor detected, run Add_Node()
			cout << "Space is free, creating... \n";
			undirected = graph.Get_yx(graph.temp);
			//directed = Direct_Node(graph.Get_yx(graph.temp),randomcell);

			if (graph.Node_Count == limit - 1) {
				int type = graph.Add_Node(graph.temp, graph.Current_Code, 9, 12, undirected, "Within the labyrinth", "cell", randomcell, directed);
				if (type == 1) {
					if (world.get_Map_Tile(directed.first, directed.second) == 0) {
						world.Change(directed.first, directed.second, 9);
					}
					cout << " Created exit! " << endl;
				}
				else if (type == 2) {
					world.Change(directed.first, directed.second, 10);
				}
				
			}
			else {
				int type = graph.Add_Node(graph.temp, graph.Current_Code, 1, 3, undirected, "Within the labyrinth", "cell", randomcell, directed);
				if (type == 1) {
					if (world.get_Map_Tile(directed.first, directed.second) == 0) {
						world.Change(directed.first, directed.second, 1);
						cout << " Created node!" << endl;
					}
				}
				else if (type == 2) {
						world.Change(directed.first, directed.second, 10);
					}
				else {
					cout << "\nNode not created." << endl;
				}
			}
			passed = true;
		}
		//Randomize neighbor to temp;
		randomroom = Randomizer(0, 3);
		cout << "\n Traversing to existing!" << endl;
		if (randomroom == 0 && existing[0] == 1) {
			graph.temp = graph.temp->north;
		}
		else if (randomroom == 1 && existing[1] == 1)
			graph.temp = graph.temp->east;
		else if (randomroom == 2 && existing[2] == 1)
			graph.temp = graph.temp->south;
		else if (randomroom == 3 && existing[3] == 1)
			graph.temp = graph.temp->west;
		else if (graph.Node_Count == 1)
			graph.temp = graph.Get_Start();
		else 
			graph.temp = graph.temp->previous;
		cout << "Node Count is: " << graph.Node_Count<<endl;
	}
}

void Generate_Fixed(int n, int limit) {
	int existing[4]; bool passed = false;
	int randomcell, randomsymbol = Randomizer(1, 7), randomroom;
	pair<int, int> undirected, directed;
	//graph.Node_Count = graph.Node_Count + limit;
	graph.temp = graph.Get_Start();
	cout << "NC:" << graph.Node_Count;
	for (graph.Node_Count; graph.Node_Count < limit;) {
		//Randomize local until null and add nodes


		randomcell = Randomizer(0,3);
		int *a = graph.Check_Neighbors(*graph.temp, existing);
		cout << "\n{Randomcell is " << randomcell << endl;
		if (a[randomcell] == 0) {
			//If null neighbor detected, run Add_Node()
			cout << " 0 detected, creating... \n";
			undirected = graph.Get_yx(graph.temp);
			//directed = Direct_Node(graph.Get_yx(graph.temp),randomcell);

			if (graph.Node_Count == limit - 1) {
				if (graph.temp == graph.Get_Start()) {
					continue;
				}
				int type = graph.Add_Node(graph.temp, graph.Current_Code, 9, 12, undirected, "Within the labyrinth", "cell", randomcell, directed);
				if (type == 1) {
					if (world.get_Map_Tile(directed.first, directed.second) == 0) {
						world.Change(directed.first, directed.second, 9);
					}
					cout << " Created exit! " << endl;
				}
				else if (type == 2) {
					if (world.get_Map_Tile(directed.first, directed.second) == 0) {
						world.Change(directed.first, directed.second, 10);
					}
				}

			}
			else {
				int type = graph.Add_Node(graph.temp, graph.Current_Code, 1, 3, undirected, "Within the labyrinth", "cell", randomcell, directed);
				if (type == 1) {
					if (world.get_Map_Tile(directed.first, directed.second) == 0) {
						world.Change(directed.first, directed.second, 1);
						cout << " Created node!" << endl;
					}
				}
				else if (type == 2) {
					if (world.get_Map_Tile(directed.first, directed.second) == 0) {
						world.Change(directed.first, directed.second, 10);
					}
				}
				else {
					cout << "\nNode not created." << endl;
					passed = false;
				}
			}
			
		}
		else {
			world.Change(undirected.first, undirected.second, 1);
			//graph.Connect_Nodes(graph.temp->yx, randomcell);
		}
		//Randomize neighbor to temp;
		randomroom = Randomizer(0, 3);
		cout << "\n Traversing to existing!" << endl;
		//graph.temp = graph.temp->north;
		if (randomroom == 0 && existing[0] == 1) {
			graph.temp = graph.temp->north;
			cout << "\n Found north path, moving.. \n";
		}
		else if (randomroom == 1 && existing[1] == 1) {
			graph.temp = graph.temp->east;

			cout << "\n Found north path, moving.. }\n";
		}
		else if (randomroom == 2 && existing[2] == 1) {
			graph.temp = graph.temp->south;
			cout << "\n Found north path, moving.. }\n";
		}
		else if (randomroom == 3 && existing[3] == 1) {
			graph.temp = graph.temp->west;
			cout << "\n Found north path, moving.. }\n";
		}
		else if (graph.Node_Count == 1) {
			graph.temp = graph.Get_Start();
			cout << "\n Going back to start }\n";
		}
		else {
			//graph.temp = graph.temp->north;
			cout << "\n No path found, receding.. }\n";
			graph.temp = graph.temp->previous;
		}
		cout << "Node Count is: " << graph.Node_Count << endl;
	}
}

pair<int, int> Direct_Node(pair<int, int> yx, int randomcell) {
	pair<int, int> temp;
	switch (randomcell) {
	case 0:
		temp.first = --yx.first;
		temp.second = yx.second;
		break;
	case 1:
		temp.first = yx.first;
		temp.second = ++yx.second;
		break;
	case 2:
		temp.first = ++yx.first;
		temp.second = yx.second;
		break;
	case 3:
		temp.first = yx.first;
		temp.second = --yx.second;
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
	{ "force", 8 },
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

void Draw_Nodes() {
	for (auto& x : graph.Exists) {
		int Y = x.first.first; int X = x.first.second;
		world.Change(Y, X, 1);
	}
}

void Force_East(int y, int x) {

	//world.Change(y, x, 1);

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
				int *ex = graph.Check_Neighbors(*graph.Get_Current(), existing);
				if (ex[option - 1] != 1) {
					Format.Paint(8, "\n There is no path from here to there.", "\n");
					for (int i = 0; i < 4; i++) {
						cout << endl << graph.Check_Neighbors(*graph.Get_Current(), existing)[i] << endl ;
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
				int *ex = graph.Check_Neighbors(*graph.Get_Current(), existing);
				if (ex[option - 1] != 1) {
					Format.Paint(8, "\n There is no path from here to there.", "\n");
					for (int i = 0; i < 4; i++) {
						cout << endl << graph.Check_Neighbors(*graph.Get_Current(), existing)[i] << endl;
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
				int *ex = graph.Check_Neighbors(*graph.Get_Current(), existing);
				if (ex[option - 1] != 1) {
					Format.Paint(8, "\n There is no path from here to there.", "\n");
					for (int i = 0; i < 4; i++) {
						cout << endl << graph.Check_Neighbors(*graph.Get_Current(), existing)[i] << endl;
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
				int *ex = graph.Check_Neighbors(*graph.Get_Current(), existing);
				if (ex[option - 1] != 1) {
					Format.Paint(8, "\n There is no path from here to there.", "\n");
					for (int i = 0; i < 4; i++) {
						cout << endl << graph.Check_Neighbors(*graph.Get_Current(), existing)[i] << endl;
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
			int *ex = graph.Check_Neighbors(*graph.Get_Current(), existing);
			graph.Compass(ex);
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
		else if (option == 8) {
		Format.Paint(7, "\n Force ", "\n");
		ordinate_y = player.get_Position()[0]; ordinate_x = player.get_Position()[1]+1;
		Sleep(1500);
		//Force_East(ordinate_y, ordinate_x);
		Draw_Nodes();
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

//void Generate() {
//	graph.Add_Node(graph.Get_Start(), 00001, '.', 3, graph.Get_yx(graph.Get_Start()), "Hallway", "Dark Halls", 1);
//}

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
	//Generate_Random(20, node_number);
	Generate_Fixed(20, node_number);
	//Generate_Random(20, node_number);
	//graph.Add_Node(graph.Get_Start(), graph.Current_Code, 1, 3, , "Within the labyrinth", "cell", randomcell, directed)
	world.Reveal((player.get_Position()[0]), (player.get_Position()[1]));
	Format.Paint(15, "\n You may now freely enter any valid command: ", "\n");
	cout << " The "; 	Format.Paint(13, "@", ""); cout << " symbol denotes your player position on the map. Try moving around!" << endl;
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