#include "Human.h"
#include <iostream>
#include "Organism.h"
#include "World.h"
#include "constants.h"

Human::Human(int position_X, int position_Y, int age, World* game)
	:Organism(HUMAN_STRENGTH,	HUMAN_INITIATIVE, age, 'H', position_X, position_Y, game , true) {
}
Human::Human(int position_X_c, int position_Y_c, int age_c, char symbol_c, int initiative_c, int strenght_c,
	bool used_ability_c, bool alzur_shield_c, bool magic_potion_c, bool antelope_speed_c, bool immortal_c,
	int ability_counter_c, World* game) 
	:Organism(strenght_c, initiative_c, age_c, symbol_c, position_X_c, position_Y_c, game, true) {
	bool used_ability = used_ability_c;
	bool alzur_shield = alzur_shield_c;
	bool magic_potion = magic_potion_c;
	bool antelope_speed = antelope_speed_c;
	bool immortal = immortal_c;
	int ability_counter = ability_counter_c;
}
void Human::Abilities(int nr_in_table, char key) {
	used_ability = true;
	ability_counter = HUMAN_ABILITY_LENGHT;
	switch (key)
	{
	case '0':
		// Human cannot be killed.In case of confrontation with stronger
		// opponent he is moved to a random free neighboring cell.
		immortal = true;
		break;
	case '1':
		//Human strength rises to 10 in first turn and decreases by "1" per
		//round until it returns to original value
		AddStrength(MAGIC_POTION);
		magic_potion = true;
		break;
	case '2':
		//Human's movement range is 2 for 3 rounds. In next 2 rounds
		//probability that he moves by 2 cells is 50 % .
		antelope_speed = true;
		break;
	case '3':
		//Human deters all animals. Animal which collides with Human is moved
		//to a random free neighboring cell.
		alzur_shield = true;
		break;
	case '4':
		//Human destroys all animals and plants that are adjacent to his
		//position.
		for (int i = 0; i < game->GetNrOfSpieces(); i++) {
			Organism* current = game->GetOrganizmPointer(i);
			if (Get_X() + LEFT == current->Get_X() && Get_Y() == current->Get_Y()) {
				game->RemoveCreature(i);
				game->SetNrOfSpiecesRN(-1);
			}
			else if (Get_X() + RIGHT == current->Get_X() && Get_Y() == current->Get_Y()) {
				game->RemoveCreature(i);
				game->SetNrOfSpiecesRN(-1);
			}
			else if (Get_X() == current->Get_X() && Get_Y() + DOWN == current->Get_Y()) {
				game->RemoveCreature(i);
				game->SetNrOfSpiecesRN(-1);
			}
			else if (Get_X() == current->Get_X() && Get_Y() + UP == current->Get_Y()) {
				game->RemoveCreature(i);
				game->SetNrOfSpiecesRN(-1);
			}
		}
		break;
	default:
		break;
	}
}
void Human::MoveExtention() {
	if(ability_counter >0)
		ability_counter--;
	if (magic_potion) {
		AddStrength(-1);
	}
}
// add desctipions and log on the board
void Human::Move(int nr_in_table) {
	if (ability_counter == 0) {
		alzur_shield = false;
		used_ability = false;
		magic_potion = false;
		antelope_speed = false;
		immortal = false;
	}
	char key = getch();
	int speed = 1;
	if (antelope_speed) {
		if (ability_counter > HUMAN_ABILITY_LENGHT - 3) {
			speed = 2;
		}
		else{
			int roll = rand() % 2;
			if (roll == 0)
				speed = 2;
			else
				speed = 1;
		}
	}

	switch (key)
	{
	case UP_ARROW:
		if (game->CheckIfCollide(Get_X(), Get_Y() + UP * speed, nr_in_table)) {
			Move_Y(UP * speed);
			MoveExtention();
		}
		break;
	case DOWN_ARROW:
		if (game->CheckIfCollide(Get_X(), Get_Y() + DOWN * speed, nr_in_table)) {
			Move_Y(DOWN * speed);
			MoveExtention();
		}
		break;
	case LEFT_ARROW:
		if (game->CheckIfCollide(Get_X() + LEFT * speed, Get_Y(), nr_in_table)) {
			Move_X(LEFT * speed);
			MoveExtention();
		}
		break;
	case RIGHT_ARROW:
		if (game->CheckIfCollide(Get_X() + RIGHT * speed, Get_Y(), nr_in_table)) {
			Move_X(RIGHT * speed);
			MoveExtention();
		}
		break;
	default:
		break;
	}

	if (!used_ability && key >= '0' && key <= '4') {
		Abilities(nr_in_table, key);
	}
}

void Human::Reposition(int move, int skip) {
	int xy[2] = { -1, 0 };
	game->FreePositSearch(xy, Get_X(), Get_Y(), skip);
	if (xy[0] == -1) {
		game->RemoveCreature(move);
		game->SetNrOfSpiecesRN(-1);
	}
	else {
		game->GetOrganizmPointer(move)->Set_XY(xy[0], xy[1]);
		game->GetOrganizmPointer(move)->SetMoved(true);
	}
}

bool Human::Collision(int my_id, int other_spiece_id) {

	Organism* other = game->GetOrganizmPointer(other_spiece_id);
	SetMoved(true);
	//game->drawWorld();	other->SetMoved(true);
	if (immortal) {
		Reposition(my_id, other_spiece_id);
		gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, +TOP_MARGIN);
		cout << "Fight between: " << GetSymbol() << " and " << game->GetOrganizmPointer(other_spiece_id)->GetSymbol();
		gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, +TOP_MARGIN + 1);
		cout << "Strength     : " << "immortal" << " and " << game->GetOrganizmPointer(other_spiece_id)->GetStrength();
		return false;
	}

	int attacker_won = other->Collide(other_spiece_id,my_id);
	//Move all spieces by one place to the left starting from the losing side;
	if (attacker_won == ANTELOPE_RUN_AWAY) {
		return true;
	}
	else if (attacker_won) {
		game->RemoveCreature(other_spiece_id);
		game->SetNrOfSpiecesRN(-1);
		return true;
	}
	else {
		game->RemoveCreature(my_id);
		game->SetNrOfSpiecesRN(-1);
		return false;
	}
}

int Human::Collide(int my_id, int attacker_id) {
	int k = GetStrength();
	game->AddMessage();
	gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN);
	cout << "Fight between: " << GetSymbol() << " and " << game->GetOrganizmPointer(attacker_id)->GetSymbol();
	if (immortal) {
		gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN + 1);
		cout << "Strength     : " << "Immortal" << " and " << game->GetOrganizmPointer(attacker_id)->GetStrength();
		Reposition(my_id, my_id);
		return IMMORTAL;
	}
	else if (alzur_shield) {
		gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN + 1);
		cout << "Strength     : " << "Alzur" << " and " << game->GetOrganizmPointer(attacker_id)->GetStrength();
		Reposition(attacker_id, -1);
		return AZUR_SHIELD;
	}
	gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN + 1);
	cout << "Strength     : " << GetStrength() << " and " << game->GetOrganizmPointer(attacker_id)->GetStrength();
	if (game->GetOrganizmPointer(attacker_id)->GetStrength() >= k)
		return true;
	return false;
}
void Human::GetSpecialAbilities(int abilities[6]) {/*
	bool used_ability = false;
	bool alzur_shield = false;
	bool magic_potion = false;
	bool antelope_speed = false;
	bool immortal = false;
	int ability_counter = 0;*/
	abilities[0] = used_ability;
	abilities[1] = alzur_shield;
	abilities[2] = magic_potion;
	abilities[3] = antelope_speed;
	abilities[4] = immortal;
	abilities[5] = ability_counter;
	int k = 5;
}