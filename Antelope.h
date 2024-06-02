#pragma once
#include <iostream>
#include "Animal.h"

using namespace std;


class Antelope : public Animal {
private:
public:
	Antelope(int position_X, int position_Y, int age, World* game);
	Antelope(int xy[2], World* game);
	Antelope(int position_X, int position_Y, int age, char symbol, int initiative, int strenght, World* game);
	Organism* Baby(int xy[2], World* game) override;
	void Move(int nr_in_table) override;
	int Collide(int my_id, int attacker_id) override;
};






