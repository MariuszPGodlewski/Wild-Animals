#include <iostream>
#include "Organism.h"
#include "Grass.h"
#include "constants.h"

using namespace std;

Grass::Grass(int position_X, int position_Y, int age, World* game)
	:Plant(PLANT_INITIATIVE, DEFAULT_PLANT_STRENGTH, age, ',', position_X, position_Y, game) {
}
Grass::Grass(int x ,int y, World* game)
	:Plant(PLANT_INITIATIVE, DEFAULT_PLANT_STRENGTH, 1, ',', x, y, game) {
}
Grass::Grass(int position_X_c, int position_Y_c, int age_c, char symbol_c, int initiative_c, int strenght_c, World* game)
	:Plant(strenght_c, initiative_c, age_c, symbol_c, position_X_c, position_Y_c, game) {
}
Organism* Grass::Baby(int x, int y, World* game) {
	return new Grass(x, y, game);
}