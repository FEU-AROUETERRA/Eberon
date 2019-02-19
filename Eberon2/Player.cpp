#include "Player.h"
//#include "World.h"
const int cX = 40, cY = 35;

Player::Player() {}

//Setter

void Player::set_Name(std::string input) {
	Name = input;
}

int Player::set_Position(int y, int x) {
	Colorize Format;
	if (x > 0 && x < cX && y > 0 && y < cY) {
		Y = y;
		X = x;
		return 1;
	}
	else {
		Format.WorldPaint(4, "You cannot go that direction. \n");
		return 0;
	}
}


//Getter

std::vector<int> Player::get_Position() {
	std::vector<int> Position;
	Position.push_back(Y);
	Position.push_back(X);
	return Position;
}
std::vector<int> Player::get_NextMove(int y, int x) {
	std::vector<int> NextMove;
	NextMove.push_back(y);
	NextMove.push_back(x);
	return NextMove;
}

std::string Player::get_Name() {
	return Name;
}

void Player::Move(std::string command) {
	std::map<std::string, std::pair<int, int>> Move_Cmd
	{
		{ "n",{ 0,Y + 1 } },
		{ "e",{ X + 1,0 } },
		{ "s",{ 0,Y - 1 } },
		{ "w",{ X - 1,0 } },
		{ "look",{ 1,1 } },
	};
}



void Aligned(std::string input, int width) {
	std::cout << std::left << std::setw(width) << input;
}

void Player::Help() {
	Colorize Format;
	Format.Pseudo_Clear(1);
	Aligned("\nCommand", 10);
	Aligned("Description", 40);
	Aligned("Syntax", 50);
	Aligned("\n kill", 10);
	Aligned("Initiates combat with target", 40);
	Aligned("[kill] [target]", 50);
	Aligned("\n Heal", 10);
	Aligned("Cast a healing spell on yourself (If you are a mage)", 40);
	Aligned("[heal]", 50);
	Aligned("\n look", 10);
	Aligned("Pulls a description of your location", 40);
	Aligned("[look]", 50);
	Aligned("\n say", 10);
	Aligned("Speak out loud ", 40);
	Aligned("[say] [sentence]", 50);
	Aligned("\n buy", 10);
	Aligned("Purchases an item if in a shop location ", 40);
	Aligned("[buy] [1-10]", 50);
	Aligned("\n north", 10);
	Aligned("Go north ", 40);
	Aligned("[north] || [n]", 50);
	Aligned("\n east", 10);
	Aligned("Go east ", 40);
	Aligned("[east] [e]", 50);
	Aligned("\n west", 10);
	Aligned("Go west ", 40);
	Aligned("[west] [w]", 50);
	Aligned("\n south", 10);
	Aligned("Go south ", 40);
	Aligned("[south] [s] \n", 50);
}