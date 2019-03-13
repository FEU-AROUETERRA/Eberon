#include "Room.h"
#include "Painter.h"

Room::Room(string title, string description, int n) {
	Title = title;
	Description = description;
	Code = n;
}
Room::Room() {}

string forest_Description = "\nThis forest has seen better days, you reckon.\nYou are surrounded on each side by rows of tall evergreen trees.\nOut of the corner of your eye, you can spot animals darting through the shadows.\nIt would be best if you did not have to stay any longer.\n";
string grass_Description = "\nThe tall grass blocks your vision and your feet sink deep into mud.\nDespite the uneven footing, you can make your way across. Several insects inhabit this marsh.\n";
string road_Description = "\nThe royal road to New Estera is frequented by merchants and travellers alike.\nYour journey will take you away from the comforts of this castle.\nYou should be able to avoid any monster encounters if you stick to the road.\n";
string sand_Description = "\nLow sand and gravel make easy travel. Small creatures tend to hide themselves \nunder the pockets of sand here, best avoid resting anytime soon.\nYou quicken your stride.\n";
string bridge_Description = "\n\nA Victory! You've reached the exit of the labyrinth! \n";
string farm_Description = "\nThis plot of land has been struck by a serious case of drought.]nWhat was once full of greenery and life is now a barren waste.\nPerhaps this was the doing of evil, not nature?\n";
string door_Description = "\n\nYou stand at the entrance of the labyrinth. Where will you go?\n";

Room Forest("|Rain Forest", forest_Description, 4);
Room Grass("|Suspicious Grass", grass_Description, 3);
Room Road("|Royal Road", road_Description, 6);
Room Sand("|Sandy Shore", sand_Description, 10);
Room Bridge("|Old Bridge", bridge_Description, 9);
Room Door("|Massive Door", door_Description, 8);
Room Farm("|Farmlands", farm_Description, 8);

void Room::get_Info(char tile) {
	Colorize Format;
	switch (tile) {
	case 2:
	case '.':
		Format.WorldPaint(14, Forest.get_Title());
		Format.WorldPaint(1, "---------------------------------------------------------------------|\n");
		Format.WorldPaint(15, Forest.get_Description());
		break;
	case 3:
		Format.WorldPaint(14, Grass.get_Title());
		Format.WorldPaint(1, "---------------------------------------------------------------------|\n");
		Format.WorldPaint(15, Grass.get_Description());
		break;
	case 6:
		Format.WorldPaint(14, Road.get_Title());
		Format.WorldPaint(1, "---------------------------------------------------------------------|\n");
		Format.WorldPaint(15, Road.get_Description());
		break;
	case 8:
		Format.WorldPaint(14, Door.get_Title());
		Format.WorldPaint(1, "---------------------------------------------------------------------|\n");
		Format.WorldPaint(15, Door.get_Description());
		break;
	case 9:
		Format.WorldPaint(14, Bridge.get_Title());
		Format.WorldPaint(1, "--------------------------------------------------------------------|\n");
		Format.WorldPaint(15, Bridge.get_Description());
		break;
	case 10:
		Format.WorldPaint(14, Sand.get_Title());
		Format.WorldPaint(1, "--------------------------------------------------------------------|\n");
		Format.WorldPaint(15, Sand.get_Description());
		break;
	case 13:
		Format.WorldPaint(14, Farm.get_Title());
		Format.WorldPaint(1, "--------------------------------------------------------------------|\n");
		Format.WorldPaint(15, Farm.get_Description());
		break;
	}
}

string Room::get_Title() {
	return Title;
}
int Room::get_Code() {
	return Code;
}
string Room::get_Description() {
	return Description;
}