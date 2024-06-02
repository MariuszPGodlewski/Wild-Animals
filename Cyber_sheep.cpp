#include <iostream>
#include "Organism.h"
#include "Cyber_sheep.h"
#include "constants.h"
#include "World.h"


using namespace std;

Cyber_sheep::Cyber_sheep(int position_X, int position_Y, int age, World* game)
	:Animal(CYBER_SHEEP_INITIATIVE, CYBER_SHEEP_STRENGTH, age, CYBER_SHEEP_SYMBOL, position_X, position_Y, game) {
}
Cyber_sheep::Cyber_sheep(int xy[2], World* game)
	:Animal(CYBER_SHEEP_INITIATIVE, CYBER_SHEEP_STRENGTH, 1, CYBER_SHEEP_SYMBOL, xy[0], xy[1], game) {
}
Cyber_sheep::Cyber_sheep(int position_X_c, int position_Y_c, int age_c, char symbol_c, int initiative_c, int strenght_c, World* game)
	: Animal(strenght_c, initiative_c, age_c, symbol_c, position_X_c, position_Y_c, game) {
}
Organism* Cyber_sheep::Baby(int xy[2], World* game) {
	return new Cyber_sheep(xy, game);
}
void Cyber_sheep::Move(int nr_in_table) {
	int nr_of_spieces = game->GetNrOfSpieces();
	Organism* closed_hogweed_location = nullptr;
	int distance = SIZE_X*SIZE_Y;
	//searching for closesd hogweed location
	for (int i = 0; i < nr_of_spieces; i++) {
		Organism* current_organism = game->GetOrganizmPointer(i);
		if (current_organism->GetSymbol() == SOSNOWSKY_HOGWEED_CHAR) {
			int k = abs(Get_X() - current_organism->Get_X());
			int b = abs(Get_Y() - current_organism->Get_Y());
			int tmp = k + b;
			if (tmp < distance) {
				distance = tmp;
				closed_hogweed_location = current_organism;
			}
		}
	}
	//przekroczenie zkresu gdy jest pusty
	if (closed_hogweed_location == nullptr) {
		MoveInWorld(nr_in_table);
	}
	else {
		int hogweed_x = closed_hogweed_location->Get_X();
		int hogweed_y = closed_hogweed_location->Get_Y();
		// ma chodzic w dobra strone 
		if (hogweed_x > Get_X()) {
			if (game->CheckIfCollide(Get_X() + RIGHT, Get_Y(), nr_in_table))
				Move_X(RIGHT);
		}
		else if (hogweed_x < Get_X()) {
			if (game->CheckIfCollide(Get_X() + LEFT, Get_Y(), nr_in_table))
				Move_X(LEFT);
		}
		else if (hogweed_y < Get_Y()) {
			if (game->CheckIfCollide(Get_X(), Get_Y() + UP, nr_in_table))
				Move_Y(UP);
		}
		else if (hogweed_y > Get_Y()) {
			if (game->CheckIfCollide(Get_X(), Get_Y() + DOWN, nr_in_table))
				Move_Y(DOWN);
		}
	}
	
}