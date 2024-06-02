#include <iostream>
#include "Organism.h"
#include "Wolf.h"
#include "constants.h"

using namespace std;

Wolf::Wolf(int position_X, int position_Y, int age, World* game)
	:Animal(WOLFINITIATIVE, WOLFSTRENGTH, age, 'W', position_X, position_Y, game) {
}
Wolf::Wolf(int xy[2], World* game)
	:Animal(WOLFINITIATIVE, WOLFSTRENGTH, 1, 'W', xy[0], xy[1], game) {
}
Wolf::Wolf(int position_X_c, int position_Y_c, int age_c, char symbol_c, int initiative_c, int strenght_c, World* game)
	:Animal(strenght_c, initiative_c, age_c, symbol_c, position_X_c, position_Y_c, game) {
}
Organism* Wolf::Baby(int xy[2], World* game) {
	return new Wolf(xy, game);
}