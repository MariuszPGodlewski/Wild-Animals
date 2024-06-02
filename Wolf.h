#pragma once
#include <iostream>
#include "Animal.h"

using namespace std;


class Wolf : public Animal {
private:
public:
	Wolf(int position_X, int position_Y, int age, World* game);
	Wolf(int xy[2], World* game);
	Wolf(int position_X, int position_Y, int age, char symbol, int initiative, int strenght, World* game);
	Organism* Baby(int xy[2], World* game) override;
};






