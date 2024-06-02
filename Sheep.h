#pragma once
#include <iostream>
#include "Animal.h"

using namespace std;


class Sheep : public Animal {
private:
public:
	Sheep(int position_X, int position_Y, int age, World* game);
	Sheep(int xy[2], World* game);
	Sheep(int position_X, int position_Y, int age, char symbol, int initiative, int strenght, World* game);
	Organism* Baby(int xy[2], World* game) override;
};






