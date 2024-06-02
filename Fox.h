#pragma once
#include <iostream>
#include "Animal.h"

using namespace std;


class Fox : public Animal {
private:
public:
	Fox(int position_X, int position_Y, int age, World* game);
	Fox(int xy[2], World* game);
	Fox(int position_X, int position_Y, int age, char symbol, int initiative, int strenght, World* game);
	Organism* Baby(int xy[2], World* game) override;
	bool CanMoveSafely(int nr_in_table);
	void Move(int nr_in_table) override;
	bool Collision(int my_id, int other_Spiece_ID) override;
};






