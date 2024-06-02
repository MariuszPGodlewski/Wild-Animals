#include <iostream>
#include "Organism.h"
#include "Sheep.h"
#include "constants.h"

using namespace std;

Sheep::Sheep(int position_X, int position_Y, int age, World* game)
	:Animal(SHEEPINITIATIVE, SHEEPSTRENGHT, age, 'S', position_X, position_Y, game) {
}
Sheep::Sheep(int xy[2], World* game)
	:Animal(SHEEPINITIATIVE, SHEEPSTRENGHT, 1, 'S', xy[0], xy[1], game) {
}
Sheep::Sheep(int position_X_c, int position_Y_c, int age_c, char symbol_c, int initiative_c, int strenght_c, World* game)
	:Animal(strenght_c, initiative_c, age_c, symbol_c, position_X_c, position_Y_c, game) {
}
Organism* Sheep::Baby(int xy[2], World* game) {
	return new Sheep(xy, game);
}