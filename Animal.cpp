#include <iostream>
#include "Organism.h"
#include "Animal.h"
#include "World.h"

using namespace std;

Animal::Animal(int initiative, int strength, int age, char symbol, int position_X, int position_Y, World* game)
	:Organism(initiative, strength, age, symbol, position_X, position_Y, game, true) {

}



bool Animal::CollisionManager(int my_id, int other_Spiece_ID) {
	Organism* other = game->GetOrganizmPointer(other_Spiece_ID);
	if (GetSymbol() == other->GetSymbol()) {
		int xy[2];
		game->FreePositSpown(xy, my_id, other_Spiece_ID);
		SetMoved(true);
		if (xy[0] != -1 && !other->GetMoved()) {
			game->AddMessage();
			gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 + TOP_MARGIN + 1);
			cout << "New animal     : " << GetSymbol();
			Organism* baby = Baby(xy, game);
			other->SetMoved(true);
			baby->SetMoved(true);
			game->addObject(baby);
		}
		return false;
	}
	else {
		SetMoved(true);
		other->SetMoved(true);
		int attacker_won = other->Collide(other_Spiece_ID, my_id);
		//Move all spieces by one place to the left starting from the losing side;
		if (attacker_won == AZUR_SHIELD) {
			return false;
		}
		else if (attacker_won == IMMORTAL) {
 			return false;
		}
		else if (attacker_won == ANTELOPE_RUN_AWAY) {
			return true;
		}
		else if (attacker_won) {
			game->RemoveCreature(other_Spiece_ID);
			game->SetNrOfSpiecesRN(-1);
			return true;
		}
		else {
			game->RemoveCreature(my_id);
			game->SetNrOfSpiecesRN(-1);
			return false;
		}

	}
}

bool Animal::Collision(int my_id,int other_Spiece_ID) {
	return CollisionManager(my_id, other_Spiece_ID);
}

void Animal::MoveInWorld(int nr_in_table) {
	int roll = rand() % 4;
	if (roll == 0) {
		if (game->CheckIfCollide(Get_X() + LEFT, Get_Y(), nr_in_table))
			Move_X(LEFT);
	}
	else if (roll == 1) {
		if (game->CheckIfCollide(Get_X() + RIGHT, Get_Y(), nr_in_table))
			Move_X(RIGHT);
	}
	else if (roll == 2) {
		if (game->CheckIfCollide(Get_X(), Get_Y() + UP, nr_in_table))
			Move_Y(UP);
	}
	else {
		if (game->CheckIfCollide(Get_X(), Get_Y() + DOWN, nr_in_table))
			Move_Y(DOWN);
	}
}

void Animal::Move(int nr_in_table) {
	MoveInWorld(nr_in_table);
}

int Animal::Collide(int my_id, int attacker_id) {
	int k = GetStrength();
	game->AddMessage();
	gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN);
	cout << "Fight between: " << GetSymbol() << " and " << game->GetOrganizmPointer(attacker_id)->GetSymbol();
	gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2+ TOP_MARGIN + 1);
	cout << "Strength     : " << GetStrength() << " and " << game->GetOrganizmPointer(attacker_id)->GetStrength();
	if (game->GetOrganizmPointer(attacker_id)->GetStrength() >= k) {
		return true;
	}
	return false;
}