#include <iostream>
#include "Organism.h"
#include "Guarana.h"
#include "constants.h"
#include "World.h"

using namespace std;

Guarana::Guarana(int position_X, int position_Y, int age, World* game)
	:Plant(PLANT_INITIATIVE, DEFAULT_PLANT_STRENGTH, age, 'g', position_X, position_Y, game) {
}
Guarana::Guarana(int x, int y, World* game)
	:Plant(PLANT_INITIATIVE, DEFAULT_PLANT_STRENGTH, 1, 'g', x, y, game) {
}
Guarana::Guarana(int position_X_c, int position_Y_c, int age_c, char symbol_c, int initiative_c, int strenght_c, World* game)
	:Plant(strenght_c, initiative_c, age_c, symbol_c, position_X_c, position_Y_c, game) {
}
Organism* Guarana::Baby(int x, int y, World* game) {
	return new Guarana(x, y, game);
}
int Guarana::Collide(int my_id , int attacker_id) {
	game->AddMessage();
	gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 + TOP_MARGIN);
	cout << "Strength bonus for : " << game->GetOrganizmPointer(attacker_id)->GetSymbol();
	game->GetOrganizmPointer(attacker_id)->AddStrength(GUARANA_ST_BOOST);
	return true;
}