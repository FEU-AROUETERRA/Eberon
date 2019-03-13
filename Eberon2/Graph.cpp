#include "Graph.h"
#include "Painter.h"
#include "Player.h"
const int cX = 40, cY = 35;
using namespace std;

Graph::Graph() {}







void Graph::Create(int y, int x)
{
	init = new Area;
	init->code = 0001;
	init->color = 6;
	init->symbol = 8;
	init->yx.first = y;
	init->yx.second = x;
	init->title = "Starting area.";
	init->description = "This place.";
	init->previous = init;
	Exists[init->yx] = *init;
	Current = Start = init;
	Node_Count++;
	Current_Code++;
	cout << "\nStart node created.\n";
}


int Graph::Add_Node(Area *before, int code, int symbol, int color, pair<int, int> yx, string title, string description, int coordinate, pair<int,int>& out){
	bool passed = true;
	//Check if YX is occupied, if true, connect current to yx instead
	pair<int, int> directed = Get_Directed(yx, coordinate);
	if ((directed.first < 0 || directed.first > cX) || (directed.second < 0 || directed.second > cY)) {
		return 0;
	}

	Area* ptr = Connect_Nodes(yx, coordinate);
	//before->yx = yx;
	if (ptr != nullptr && Contiguous_Paths == true) {
		//ptr->yx = Get_Directed(before->yx, coordinate);
		switch (coordinate) {
		case 0:
			before->Adjacent[NORTH] = ptr;
			ptr-> Adjacent[SOUTH] = before;
			return 2;
			break;
		case 1:
			before->Adjacent[EAST] = ptr;
			ptr->Adjacent[WEST] = before;
			return 2;
			break;
		case 2:
			before->Adjacent[SOUTH] = ptr;
			ptr->Adjacent[NORTH] = before;
			return 2;
			break;
		case 3:
			before->Adjacent[WEST] = ptr;
			ptr->Adjacent[EAST] = before;
			return 2;
			break;
		}
	}
	else {
		pair<int, int> temp = before->yx;
		switch (coordinate) {
		case 0:
			if (before->Adjacent[NORTH] == nullptr)
			{
				cout << "\nCreating north node...\n";
				init = new Area;
				Current_Code++;
				
				init->code = Current_Code;
				init->symbol = symbol;
				init->color = color;
				init->previous = before;
				init->title = title;
				init->description = description;
				init->yx.first = --(temp.first);
				init->yx.second = temp.second;
				Exists[init->yx] = *init;
				cout << before->yx.first << " " << before->yx.second << "," << init->yx.first  << " "<<  init->yx.second<< endl;
				cout << "\nCreating north node...\n";

				init->Adjacent[SOUTH] = before;
				before->Adjacent[NORTH] = init; 
				
				out = init->yx;
				Node_Count++;
				cout << "\nNorth node created.\n";
				return 1;
			}
			else
				return 3;
			break;
		case 1:
			if (before->Adjacent[EAST] == NULL)
			{
				cout << "\nCreating east node...\n";

				init = new Area;
				Current_Code++;
				init->code = Current_Code;
				init->symbol = symbol;
				init->color = color;
				init->previous = before;
				init->title = title;
				init->description = description;
				init->yx.first = temp.first;
				init->yx.second = ++(temp.second);
				Exists[init->yx] = *init;
				init->Adjacent[WEST] = before;
				before->Adjacent[EAST] = init; 
				cout << before->yx.first << " " << before->yx.second << "," << init->yx.first << " " << init->yx.second << endl;
				
				out = init->yx;
				Node_Count++;
				cout << "\nEast node created.\n";

				return 1;
			} 
			else
				return 3;
			break;
		case 2:
			if (before->Adjacent[SOUTH] == NULL)
			{
				cout << "\nCreating south node...\n";

				init = new Area;
				Current_Code++;
				init->code = Current_Code;
				init->symbol = symbol;
				init->color = color;
				init->previous = before;
				init->title = title;
				init->description = description;
				init->yx.first = ++(temp.first);
				init->yx.second = temp.second;
				Exists[init->yx] = *init;
				init->Adjacent[NORTH] = before;
				before->Adjacent[SOUTH] = init; 
				cout << before->yx.first << " " << before->yx.second << "," << init->yx.first << " " << init->yx.second << endl;
				out = init->yx;
				Node_Count++;
				cout << "\nSouth node created.\n";

				return 1;
			}
			else
				return 3;
			break;
		case 3:
			if (before->Adjacent[WEST] == NULL)
			{
				cout << "\nCreating west node...\n";

				init = new Area;
				Current_Code++;
				init->code = Current_Code;
				init->symbol = symbol;
				init->color = color;
				init->previous = before;
				init->title = title;
				init->description = description;
				init->yx.first = temp.first;
				init->yx.second = --(temp.second);
				Exists[init->yx] = *init;
				init->Adjacent[EAST] = before;
				before->Adjacent[WEST] = init; 
				cout << before->yx.first << " " << before->yx.second << "," << init->yx.first << " " << init->yx.second << endl;
				out = init->yx;
				Node_Count++;
				cout << "\nWest node created.\n";

				return 1;
			}
			else
				return 3;
			break;
		default:
			cout << "All node paths are occupied." << endl;
			return 0;
			break;
		}
		return 0;
	}
	return 0;
}

void Graph::Get_Nodes() {
	
	for (map<pair<int, int>, Area>::iterator it = Exists.begin(); it != Exists.end(); ++it) {
		cout << "\n Node found at: " << it->first.first << " & "<< it->first.second << "\n";
	}
}


set<pair<int, int>> Graph::BFS(Area* Source) {
	// Mark all the vertices as not visited 
	bool *visited = new bool[Node_Count];
	for (int i = 0; i < Node_Count; i++)
		visited[i] = false;

	// Create a queue for BFS 
	list<Area*> queue;
	map<pair<int,int>, bool> visits;

	// Mark the current node as visited and enqueue it 
	visits[Source->yx] = true;
	queue.push_back(Source);

	while (!queue.empty())
	{
		// Dequeue a vertex from queue and print it 
		cout << "\nAt Node: " << Source->code << endl;
		Source = queue.front();
		// For world reveal, first popped is first node (Start)
		print_list.insert(Source->yx);
		queue.pop_front();

		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it 
		for (int i = 0; i < 4; i++) {
			//Get coordinates for directions
			cout << "\nChecking " << i << endl;
			if (Source->Adjacent[i] == nullptr) {
				
				cout << "\n No Path! \n";
				continue;
			}
			if (Source->Adjacent[i]->code == 0) {
				Source->Adjacent[i]->yx = Get_Directed(Source->yx, i);
				cout << "Void node detected";
			}
			pair<int, int> temp = Source->Adjacent[i]->yx;
			cout << Source->Adjacent[i]->code << ">" << endl;
			//If direction is not visited, mark it visited. Prevents infinite loop.
			if (visits.find(temp) == visits.end()) {
				visits[temp] = true;
				queue.push_back(Source->Adjacent[i]);
			}
		}
	}
	return print_list;
}


Graph::Area* Graph::Connect_Nodes(pair<int, int> yx, int coordinate) {
	pair<int, int> coordinates, temp = yx;
	switch (coordinate) {
	case 1:
		coordinates.first = --temp.first;
		coordinates.second = temp.second;
		break;
	case 2:
		coordinates.first = temp.first;
		coordinates.second = ++temp.second;
		break;
	case 3:
		coordinates.first = ++temp.first;
		coordinates.second = temp.second;
		break;
	case 4:
		coordinates.first = temp.first;
		coordinates.second = --temp.second;
		break;
	}
	if (Exists.find(coordinates) == Exists.end())
		return nullptr;
	else {
		cout << "\n Connecting nodes.. \n";
		return &Exists.at(coordinates);
	}
}

void Graph::Display() {
	int counter = 0; Area *ptr; ptr = Start;
	do {
		cout << "\nGetting data of [" << counter << "] = " << ptr->title << endl;
		ptr = ptr->Adjacent[NORTH]; counter++;
	} while (counter <= 1);
}

Graph::Area* Graph::Get_Start() {
	Area *ptr = Start;
	return ptr;
}

Graph::Area* Graph::Get_Current() {
	Area *ptr = Current;
	return ptr;
}

void Graph::Set_Current(int option) {
	Area *ptr;
	switch (option) {
	case 1:
		ptr = Current->Adjacent[NORTH];
		Current = ptr;
		break;
	case 2:
		ptr = Current->Adjacent[EAST];
		Current = ptr;
		break;
	case 3:
		ptr = Current->Adjacent[SOUTH];
		Current = ptr;
		break;
	case 4:
		ptr = Current->Adjacent[WEST];
		Current = ptr;
		break;
	}
}

Graph::Area* Graph::Directed_Pointer(int option) {
	switch (option) {
	case 0:
		pointer = temp->Adjacent[NORTH];
		break;
	case 1:
		pointer = temp->Adjacent[EAST];
		break;
	case 2:
		pointer = temp->Adjacent[SOUTH];
		break;
	case 3:
		pointer = temp->Adjacent[WEST];
		break;
	}
	return pointer;
}

pair<int, int> Graph::Get_yx(Area* area) {
	return area->yx;
}

pair<int, int> Graph::Get_Directed(pair<int,int> yx, int direction) {
	pair<int, int> temp, temp2 = yx;
	switch (direction) {
	case 0:
		temp.first = --temp2.first;
		temp.second = temp2.second;
		break;
	case 1:
		temp.first = temp2.first;
		temp.second = ++(temp2.second);
		break;
	case 2:
		temp.first = ++(temp2.first);
		temp.second = temp2.second;
		break;
	case 3:
		temp.first = temp2.first;
		temp.second = --(temp2.second);
		break;
	}
	return temp;
}


int* Graph::Check_Neighbors(Area* before, int existing[]) {
		//int node = Randomizer(1, Node_Count);
	bool condition = false; 
	if (!before) {
		cout << "\n[Area does not exist]\n";
		return existing;
	}
	if (before->Adjacent[NORTH] != NULL) {
		existing[0] = 1;
	}
	else { existing[0] = 0; }
	if (before->Adjacent[EAST] != NULL) {
		existing[1] = 1;
	}
	else { existing[1] = 0; }
	if (before->Adjacent[SOUTH] != NULL) {
		existing[2] = 1;
	}
	else { existing[2] = 0; }
	if (before->Adjacent[WEST] != NULL) {
		existing[3] = 1;
	}
	else { existing[3] = 0; }
	return existing;
}

void Graph::Compass(int existing[]) {
	Colorize Format;
	int north = 6, east = 6, south = 6, west = 6;
	int *ex; ex = Check_Neighbors(Get_Current(), existing);
	for (int i = 0; i < 4; i++) {
		if (ex[i] == 1) {
			switch (i) {
			case 0:
				north = 14;
				break;
			case 1:
				east = 14;
				break;
			case 2:
				south = 14;
				break;
			case 3:
				west = 14;
				break;
			}

			//cout << Check_Neighbors(Get_Current(), existing)[i];
		}
	}
	//Format.WorldPaint(14, "  Wandering the labyrinth - where to?");
	//Format.WorldPaint(9, "(~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");	
	cout << endl;
	Format.WorldPaint(north, "\tN\n"); 	
	Format.WorldPaint(west, " W");	Format.WorldPaint(9, " <---(");	Format.WorldPaint(13, "@");Format.WorldPaint(9, ")---> "); Format.WorldPaint(east, "E\n");
	Format.WorldPaint(south, "\tS"); cout << endl;
}




//MAP
Map::Map() {

	for (int y = 0, x = 0; y < cY;)
	{
		Grid[0][0] = 7;
		Grid[cY-1][0] = 7;
		x++;
		if (y == 0) {
			Grid[y][x] = 7; 
		}
		else if (y == cY - 1) {
			Grid[y][x] = 7;
		}
		if (x == 0) {
			Grid[y][x] = 6;
			
		}
		else if (x == cX - 1) {
			Grid[y][x] = 6;
		}
		if (x == cX && y != cY) {
			y++;
			cout << endl;
			x = 0;
		}
	}
}

void Map::Reveal(int player_y, int player_x) {
	Colorize Format;
	Format.Pseudo_Clear(5);
	if (replacedCounter > 0)
	{
		for (int y = 0, x = 0; y < cY;)
		{
			if (Grid[y][x] == 20)
				Grid[y][x] = replaced_Tile;
			x++;
			if (x == cX && y != cY) {
				y++;
				cout << endl;
				x = 0;
			}
		}
	}
	else {
		replacedCounter++;
	}
	replaced_Tile = Grid[player_y][player_x];
	Grid[player_y][player_x] = 20;
	Format.WorldPaint(9, "[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~(");	Format.WorldPaint(14, "  LABYRINTH  "); 	Format.WorldPaint(9, ")~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
	for (int y = 0, x = 0; y < cY;)
	{
		cout << " ";
		switch (Grid[y][x]) {
		case 0:
			Format.WorldPaint(4, " ");
			break;
		case 1:
			Format.WorldPaint(15, ".");
			break;
		case 2:
			Format.WorldPaint(2, "*");
			break;
		case 3:
			Format.WorldPaint(2, "*");
			break;
		case 4:
			Format.WorldPaint(10, "*");
			break;
		case 5:
			Format.WorldPaint(3, "~");
			break;
		case 6:
			Format.WorldPaint(13, "|");
			break;
		case 7:
			Format.WorldPaint(13, "-");
			break;
		case 8:
			Format.WorldPaint(10, ":");
			break; //Entrance
		case 9:
			Format.WorldPaint(12, ":");
			break; //Exit
		case 10:
			Format.WorldPaint(6, "+");
			break; //Cross
		case 11:
			Format.WorldPaint(13, "=");
			break;
		case 12:
			Format.WorldPaint(9, "~");
			break;
		case 13:
			Format.WorldPaint(6, "=");
			break;
		case 14:
			Format.WorldPaint(8, "I");
			break;
		case 15:
			Format.WorldPaint(0, "=");
			break;
		case 20:
			Format.WorldPaint(13, "@");
			break;
		}
		x++;
		if (x == cX && y != cY) {
			y++;
			cout << endl;
			x = 0;
		}
	}
	Format.WorldPaint(9, "[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~(");	Format.WorldPaint(15, " WEST MAP "); 	Format.WorldPaint(9, ")~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
}
int Map::get_Map_Tile(int y, int x) {
	return Grid[y][x];
}

int Map::CheckMove(int Move) {
	Colorize Format;
	switch (Move) {
	case 1:
	case 10:
		//Format.WorldPaint(4, "The mountain looks difficult to climb, you choose to go elsewhere.\n");
		return 1;
		break;
	case 5:
	case 8:
		Format.WorldPaint(4, "This is where your journey began. \n");
		return 1;
		break;
	case 9:
		Format.WorldPaint(4, "Congratulations! You've reached the exit!. \n");
		return 1;
		break;
	case 6:
	case 7:
		Format.WorldPaint(4, "The building walls block your path.\n");
		return 0;
		break;
	case 13:
		Format.WorldPaint(4, "You cannot enter this way.\n");
		return 0;
		break;
	default:
		Format.WorldPaint(4, "The path is dark.\n");
		return 1;
		break;
	}
	return 1;
}

void Map::Change(int y, int x, int symbol) {
	Grid[y][x] = symbol;
}