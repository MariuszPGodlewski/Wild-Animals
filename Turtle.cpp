#include <iostream>
#include "Organism.h"
#include "Turtle.h"
#include "constants.h"
#include "World.h"

using namespace std;

Turtle::Turtle(int position_X, int position_Y, int age, World* game)
	:Animal(TURTLE_INITIATIVE, TURTLE_STRENGTH, age, 'T', position_X, position_Y, game) {
}

Turtle::Turtle(int xy[2], World* game)
	:Animal(TURTLE_INITIATIVE, TURTLE_STRENGTH, 1, 'T', xy[0], xy[1], game) {
}
Turtle::Turtle(int position_X_c, int position_Y_c, int age_c, char symbol_c, int initiative_c, int strenght_c, World* game)
	:Animal(strenght_c, initiative_c, age_c, symbol_c, position_X_c, position_Y_c, game) {
}
Organism* Turtle::Baby(int xy[2], World* game) {
	return new Turtle(xy, game);
}

void Turtle::Move(int nr_in_table) {
	int tmp = rand() % 4;
	if (tmp == 0) {
		MoveInWorld(nr_in_table);
	}
	else {
		SetMoved(true);
	}
}
int Turtle::Collide(int my_id, int attacker_id) {
	int my_strength = GetStrength();
	int opponent_strength = game->GetOrganizmPointer(attacker_id)->GetStrength();

	game->AddMessage();
	gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN);
	cout << "Fight between: " << GetSymbol() << " and " << game->GetOrganizmPointer(attacker_id)->GetSymbol();

	if (opponent_strength < TURTLE_REFLECTION) {
		gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN + 1);
		cout << "Strength     : " << "Reflected attack" << " and " << game->GetOrganizmPointer(attacker_id)->GetStrength();
		return false;
	}
	gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN + 1);
	cout << "Strength     : " << GetStrength() << " and " << game->GetOrganizmPointer(attacker_id)->GetStrength();
	if ( opponent_strength >= my_strength) 
		return true;
	return false;
}