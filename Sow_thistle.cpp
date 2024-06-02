#include <iostream>
#include "Organism.h"
#include "Sow_thistle.h"
#include "World.h"
#include "constants.h"

using namespace std;

Sow_thistle::Sow_thistle(int position_X, int position_Y, int age, World* game)
	:Plant(PLANT_INITIATIVE, DEFAULT_PLANT_STRENGTH, age, 't', position_X, position_Y, game) {
}
Sow_thistle::Sow_thistle(int x, int y, World* game)
	:Plant(PLANT_INITIATIVE, DEFAULT_PLANT_STRENGTH, 1, 't', x, y, game) {
}
Sow_thistle::Sow_thistle(int position_X_c, int position_Y_c, int age_c, char symbol_c, int initiative_c, int strenght_c, World* game)
	:Plant(strenght_c, initiative_c, age_c, symbol_c, position_X_c, position_Y_c, game) {
}
Organism* Sow_thistle::Baby(int x, int y, World* game) {
	return new Sow_thistle(x, y, game);
}

void Sow_thistle::Move(int nr_in_table) {
	for (int i = 0; i < NR_SOWING_THISTLE; i++) {
		SetMoved(false);
		Sawing(nr_in_table);
		if(i == NR_SOWING_THISTLE - 1) {
			SetMoved(true);
		}
	}
}