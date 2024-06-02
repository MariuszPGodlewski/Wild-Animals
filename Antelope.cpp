#include "Antelope.h"
#include <iostream>
#include "Organism.h"
#include "Antelope.h"
#include "constants.h"
#include "World.h"

using namespace std;

Antelope::Antelope(int position_X, int position_Y, int age, World* game)
	:Animal(ANTELOPE_INITIATIVE, ANTELOPE_STRENGTH, age, 'A', position_X, position_Y, game) {
}

Antelope::Antelope(int xy[2], World* game)
	:Animal(ANTELOPE_INITIATIVE, ANTELOPE_STRENGTH, 1, 'A', xy[0], xy[1], game) {
}
Antelope::Antelope(int position_X_c, int position_Y_c, int age_c, char symbol_c, int initiative_c, int strenght_c, World* game)
	:Animal(strenght_c, initiative_c, age_c, symbol_c, position_X_c, position_Y_c, game) {
}
Organism* Antelope::Baby(int xy[2], World* game) {
	return new Antelope(xy, game);
}


//make it stay in the map
void Antelope::Move(int nr_in_table) {
	int roll = rand() % 4;
	if (roll == 0) {
		if (game->CheckIfCollide(Get_X() + LEFT * 2, Get_Y(), nr_in_table))
			Move_X(LEFT * 2);
	}
	else if (roll == 1) {
		if (game->CheckIfCollide(Get_X() + RIGHT * 2, Get_Y(), nr_in_table))
			Move_X(RIGHT * 2);
	}
	else if (roll == 2) {
		if (game->CheckIfCollide(Get_X(), Get_Y() + UP * 2, nr_in_table))
			Move_Y(UP * 2);
	}
	else {
		if (game->CheckIfCollide(Get_X(), Get_Y() + DOWN * 2, nr_in_table))
			Move_Y(DOWN * 2);
	}
}

int Antelope::Collide(int my_id, int attacker_id) {
	int roll = rand() % 2;
	game->AddMessage();
	gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN);
	cout << "Fight between: " << GetSymbol() << " and " << game->GetOrganizmPointer(attacker_id)->GetSymbol();
	if (roll == 0) {
		int k = GetStrength();	
		gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN + 1);
		cout << "Strength     : " << GetStrength() << " and " << game->GetOrganizmPointer(attacker_id)->GetStrength();
		if (game->GetOrganizmPointer(attacker_id)->GetStrength() >= k) {
			return true;
		}
		return false;
	}
	gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN + 1);
	cout << "Strength     : " << "Run away" << " and " << game->GetOrganizmPointer(attacker_id)->GetStrength();
	SetMoved(false);
	while (!GetMoved()) {
		Move(my_id);
	}
	return ANTELOPE_RUN_AWAY;

}