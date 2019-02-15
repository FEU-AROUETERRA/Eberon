#include "Graph.h"
#include "Painter.h"

Graph::Graph() {}





int Randomizer(int floor, int limit) {
	mt19937 rng;
	rng.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist6(floor, limit); // distribution in range [1, 6]
	return dist6(rng);
}

void Graph::Create()
{
	int node_number;
	cout << "We will now create your world. \n";
	cout << "Now, enter how many more location nodes you want generated (12 nodes are pre-generated): "; cin.ignore(1000, '\n');
	cin >> node_number;
	cout << "\nYour world is being generated... \n";
	Listing = new vector<Area>[node_number];
	Current = new Area;
	Start = Current;
	Start->code = 0001;
	Start->color = 6;
	Start->symbol = 'O';
	Start->yx.first = 0;
	Start->yx.second = 0;
	Start->title = "Starting area.";
	Start->description = "This place.";
	Add_Node(*Start, 00001, '.', 3, Start->yx, "Hallway", "Dark Halls", 1);
}


void Graph::Add_Node(Area before, int code, int symbol, int color, pair<int, int> yx, string title, string description, int coordinate){
	bool passed = true;
	do
	{
		Current = new Area;
		Current_Code++;
		Current->code = Current_Code;
		Current->symbol = symbol;
		Current->color = color;

		Current->title = title;
		Current->description = description;
		Area *ptr; ptr = &Connect_Nodes(before, yx);
		switch (coordinate) {
		case 1:
			if (before.north == NULL)
			{
				if (ptr != NULL) {
					
				}
				Current->yx.first = ++before.yx.first;
				Current->yx.second = before.yx.second;
				Exists[Current->yx] = *Current;
				before.north = Current;
				return;
			}
		case 2:
			if (before.east == NULL)
			{
				Current->yx.first = before.yx.first;
				Current->yx.second = ++before.yx.second;
				Exists[Current->yx] = *Current;
				before.east = Current;
				return;
			}
		case 3:
			if (before.south == NULL)
			{
				Current->yx.first = --before.yx.first;
				Current->yx.second = before.yx.second;
				Exists[Current->yx] = *Current;
				before.east = Current;
				return;
			}
		case 4:
			if (before.west == NULL)
			{
				Current->yx.first = before.yx.first;
				Current->yx.second = --before.yx.second;
				Exists[Current->yx] = *Current;
				before.east = Current;
				return;
			}
			else {
				cout << "All node paths are occupied." << endl;
				passed = false;
			}
		}
		Node_Count++;
	} while (passed == false);
}

Graph::Area Graph::Connect_Nodes(Area before, pair<int,int> yx) {
	map<pair<int, int>, Area>::iterator it;
	it = Exists.find(yx);
	if (it != Exists.end())
		return it->second;
}


//void Graph::Check_Neighbors() {
	//	int node = Randomizer(1, Node_Count);
	//	bool condition = false;
	//	
	//	while (condition == false)
	//	{
	//		if (Listing->at(node).north == NULL) {
	//			Add_Node(1, 0, 0, 0); condition = true;
	//		}
	//		else if (Listing->at(node).east == NULL) {
	//			Add_Node(0, 1, 0, 0); condition = true;
	//		}
	//		else if (Listing->at(node).south == NULL) {
	//			Add_Node(0, 0, 1, 0); condition = true;
	//		}
	//		else if (Listing->at(node).west == NULL) {
	//			Add_Node(0, 0, 0, 1); condition = true;
	//		}
	//		else {
	//			node = Randomizer(1, Node_Count);
	//		}
	//	}
	//}



//MAP
//Map::Map() {}
//
//void Map::Reveal(int player_y, int player_x) {
//	Colorize Format;
//	int Tile;
//	if (replacedCounter > 0)
//	{
//		for (int y = 0, x = 0; y < 10;)
//		{
//			if (Grid[y][x] == 20)
//				Grid[y][x] = replaced_Tile;
//			x++;
//			if (x == 40 && y != 10) {
//				y++;
//				cout << endl;
//				x = 0;
//			}
//		}
//	}
//	else {
//		replacedCounter++;
//	}
//	replaced_Tile = Grid[player_y][player_x];
//	Grid[player_y][player_x] = 20;
//	Format.WorldPaint(9, "[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~(");	Format.WorldPaint(14, "  EBERON  "); 	Format.WorldPaint(9, ")~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
//	for (int y = 0, x = 0; y < 10;)
//	{
//		cout << " ";
//		switch (Grid[y][x]) {
//		case 1:
//			Format.WorldPaint(15, "^");
//			break;
//		case 2:
//			Format.WorldPaint(2, "*");
//			break;
//		case 3:
//			Format.WorldPaint(2, "*");
//			break;
//		case 4:
//			Format.WorldPaint(10, "*");
//			break;
//		case 5:
//			Format.WorldPaint(3, "~");
//			break;
//		case 6:
//			Format.WorldPaint(14, "#");
//			break;
//		case 7:
//			Format.WorldPaint(13, "I");
//			break;
//		case 8:
//			Format.WorldPaint(14, "O");
//			break;
//		case 9:
//			Format.WorldPaint(14, "=");
//			break;
//		case 10:
//			Format.WorldPaint(6, ".");
//			break;
//		case 11:
//			Format.WorldPaint(13, "=");
//			break;
//		case 12:
//			Format.WorldPaint(9, "~");
//			break;
//		case 13:
//			Format.WorldPaint(6, "=");
//			break;
//		case 14:
//			Format.WorldPaint(8, "I");
//			break;
//		case 15:
//			Format.WorldPaint(0, "=");
//			break;
//		case 20:
//			Format.WorldPaint(13, "@");
//			break;
//		}
//		x++;
//		if (x == 40 && y != 10) {
//			y++;
//			cout << endl;
//			x = 0;
//		}
//	}
//	Format.WorldPaint(9, "[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~(");	Format.WorldPaint(15, " WEST MAP "); 	Format.WorldPaint(9, ")~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
//}
//int Map::get_Map_Tile(int y, int x) {
//	return Grid[y][x];
//}