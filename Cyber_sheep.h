#pragma once
#include <iostream>
#include "Animal.h"

using namespace std;


class Cyber_sheep : public Animal {
private:
public:
	Cyber_sheep(int position_X, int position_Y, int age, World* game);
	Cyber_sheep(int xy[2], World* game);
	Cyber_sheep(int position_X, int position_Y, int age, char symbol, int initiative, int strenght, World* game);
	Organism* Baby(int xy[2], World* game) override;
	void Move(int nr_in_table) override;
};






