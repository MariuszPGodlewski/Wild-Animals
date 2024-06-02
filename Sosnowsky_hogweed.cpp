#include <iostream>
#include "Organism.h"
#include "Sosnowsky_hogweed.h"
#include "constants.h"
#include "World.h"

using namespace std;

Sosnowsky_hogweed::Sosnowsky_hogweed(int position_X, int position_Y, int age, World* game)
	:Plant(PLANT_INITIATIVE, SOSNOWSKY_HOGWEED_STRENGHT, age, SOSNOWSKY_HOGWEED_CHAR, position_X, position_Y, game) {
}
Sosnowsky_hogweed::Sosnowsky_hogweed(int x, int y, World* game)
	:Plant(PLANT_INITIATIVE, SOSNOWSKY_HOGWEED_STRENGHT, 1, SOSNOWSKY_HOGWEED_CHAR, x, y, game) {
}
Sosnowsky_hogweed::Sosnowsky_hogweed(int position_X_c, int position_Y_c, int age_c, char symbol_c, int initiative_c, int strenght_c, World* game)
	:Plant(strenght_c, initiative_c, age_c, symbol_c, position_X_c, position_Y_c, game) {
}
Organism* Sosnowsky_hogweed::Baby(int x, int y, World* game) {
	return new Sosnowsky_hogweed(x, y, game);
}
//add move that it kills all animals around it and later saw
void Sosnowsky_hogweed::Move(int nr_in_table) {
	for (int i = 0; i < game->GetNrOfSpieces(); i++){
		Organism* current = game->GetOrganizmPointer(i);
		if (current->IsAnimal() && current->GetSymbol() != CYBER_SHEEP_SYMBOL) {
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
	}
	Sawing(nr_in_table);
}

//in Collision add that it kills animal and kills itself
int Sosnowsky_hogweed::Collide(int my_id, int attacker_id) {
	int k = GetStrength();
	game->AddMessage();
	gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN);
	cout << "Fight between: " << GetSymbol() << " and " << game->GetOrganizmPointer(attacker_id)->GetSymbol();
	if (game->GetOrganizmPointer(attacker_id)->IsAnimal() && game->GetOrganizmPointer(attacker_id)->GetSymbol() != CYBER_SHEEP_SYMBOL) {
		gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN + 1);
		cout << "Remove animal     : " << game->GetOrganizmPointer(attacker_id)->GetSymbol();
		game->RemoveCreature(my_id);
		game->SetNrOfSpiecesRN(-1);
		return false;
	}
	gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN + 1);
	cout << "Strength     : " << GetStrength() << " and " << game->GetOrganizmPointer(attacker_id)->GetStrength();
	if (game->GetOrganizmPointer(attacker_id)->GetStrength() >= k || game->GetOrganizmPointer(attacker_id)->GetSymbol() == CYBER_SHEEP_SYMBOL)
		return true;
	return false;
}