#include <iostream>
#include "Organism.h"
#include "Belladonna.h"
#include "constants.h"
#include "World.h"

using namespace std;

Belladonna::Belladonna(int position_X, int position_Y, int age, World* game)
	:Plant(PLANT_INITIATIVE, BELLADONNA_STRENGTH, age, 'b', position_X, position_Y, game) {
}
Belladonna::Belladonna(int x, int y, World* game)
	:Plant(PLANT_INITIATIVE, BELLADONNA_STRENGTH, 1, 'b', x, y, game) {
}
Belladonna::Belladonna(int position_X_c, int position_Y_c, int age_c, char symbol_c, int initiative_c, int strenght_c, World* game)
	:Plant(strenght_c, initiative_c, age_c, symbol_c, position_X_c, position_Y_c, game) {
}
Organism* Belladonna::Baby(int x, int y, World* game) {
	return new Belladonna(x, y, game);
}

int Belladonna::Collide(int my_id, int attacker_id) {
	int k = GetStrength();
	game->AddMessage();
	gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN);
	cout << "Fight between: " << GetSymbol() << " and " << game->GetOrganizmPointer(attacker_id)->GetSymbol();
	gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN + 1);
	cout << "Strength     : " << GetStrength() << " and " << game->GetOrganizmPointer(attacker_id)->GetStrength();
	if (game->GetOrganizmPointer(attacker_id)->IsAnimal()) {
		game->RemoveCreature(my_id);
		game->SetNrOfSpiecesRN(-1);
		return false;
	}
	if (game->GetOrganizmPointer(attacker_id)->GetStrength() >= k)
		return true;
	return false;
}
