#include <iostream>
#include "Organism.h"
#include "Plant.h"
#include "World.h"
#include "constants.h"
using namespace std;

Plant::Plant(int initiative, int strength, int age, char symbol, int position_X, int position_Y, World* game)
	:Organism(initiative, strength, age, symbol, position_X, position_Y, game, false) {
}

bool Plant::Collision(int my_id, int other_Spiece_ID) {
	return false;
}
bool Plant::IsSawingPosible(int nr_in_table) {
	if (game->CheckIfCollide(Get_X() + LEFT, Get_Y(), nr_in_table) ||
		game->CheckIfCollide(Get_X() + RIGHT, Get_Y(), nr_in_table) ||
		game->CheckIfCollide(Get_X(), Get_Y() + DOWN, nr_in_table) ||
		game->CheckIfCollide(Get_X(), Get_Y() + UP, nr_in_table)
		) {
		return true;
	}
	return false;
}

void Plant::PlantSow(int x, int y) {
	//ad chceck if it is on the board
	SetMoved(true);
	if (x >= 0 && x < SIZE_X && y >= 0 && y < SIZE_Y) {
		game->AddMessage();
		gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2+TOP_MARGIN);
		cout << "Sawd: " << GetSymbol();
 		Organism* baby = Baby(x, y, game);
		baby->SetMoved(true);
		game->addObject(baby);
	}
	
}

void Plant::Sawing(int nr_in_table) {
	if (IsSawingPosible(nr_in_table)) {
		int roll = rand() % 100;
		if (roll <= SOWING_CHANCE) {
			while (!GetMoved()) {
				int field_roll = rand() % 4;
				if (field_roll == 0 && game->CheckIfCollide(Get_X() + LEFT, Get_Y(), nr_in_table)) {
					PlantSow(Get_X() + LEFT, Get_Y());
				}
				else if (field_roll == 1 && game->CheckIfCollide(Get_X() + RIGHT, Get_Y(), nr_in_table)) {
					PlantSow(Get_X() + RIGHT, Get_Y());
				}
				else if (field_roll == 2 && game->CheckIfCollide(Get_X(), Get_Y() + DOWN, nr_in_table)) {
					PlantSow(Get_X(), Get_Y() + DOWN);
				}
				else if (field_roll == 3 && game->CheckIfCollide(Get_X(), Get_Y() + UP, nr_in_table)) {
					PlantSow(Get_X(), Get_Y() + UP);
				}
			}
		}
		else {
			SetMoved(true);
		}
	}
	else {
		SetMoved(true);
	}
}
void Plant::Move(int nr_in_table) {

	Sawing(nr_in_table);
	
}
