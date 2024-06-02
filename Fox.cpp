#include <iostream>
#include "Organism.h"
#include "Fox.h"
#include "World.h"
#include "constants.h"

using namespace std;

Fox::Fox(int position_X, int position_Y, int age, World* game)
	:Animal(FOXINITIATIVE, FOXSTRENGHT, age, 'F', position_X, position_Y, game) {
}

Fox::Fox(int xy[2], World* game)
	:Animal(FOXINITIATIVE, FOXSTRENGHT, 1, 'F', xy[0], xy[1], game) {
}
Fox::Fox(int position_X_c, int position_Y_c, int age_c, char symbol_c, int initiative_c, int strenght_c, World* game)
	:Animal(strenght_c, initiative_c, age_c, symbol_c, position_X_c, position_Y_c, game) {
}
Organism* Fox::Baby(int xy[2], World* game) {
	return new Fox(xy, game);
}


bool Fox::CanMoveSafely(int nr_in_table) {
	if (game->CheckIfCollide(Get_X() + LEFT, Get_Y(), nr_in_table) ||
		game->CheckIfCollide(Get_X() + RIGHT, Get_Y(), nr_in_table) ||
		game->CheckIfCollide(Get_X(), Get_Y() + DOWN, nr_in_table) ||
		game->CheckIfCollide(Get_X(), Get_Y() + UP, nr_in_table)
		) {
		return true;
	}
	return false;
}

void Fox::Move(int nr_in_table) {
	if (CanMoveSafely(nr_in_table)) {
		MoveInWorld(nr_in_table);
	}
	else {
		SetMoved(true);
	}
}

bool Fox::Collision(int my_id, int other_Spiece_ID) {
	Organism* other = game->GetOrganizmPointer(other_Spiece_ID);
	if (!other->Collide(other_Spiece_ID, my_id) && !(GetSymbol() == other->GetSymbol())) {
		return false;
	}
	return CollisionManager(my_id, other_Spiece_ID);
}