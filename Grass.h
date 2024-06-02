#pragma once
#include "Plant.h"

class Grass :public Plant
{
private:
public:
	Grass(int position_X, int position_Y, int age, World* game);
	Grass(int x, int y, World* game);
	Grass(int position_X, int position_Y, int age, char symbol, int initiative, int strenght, World* game);
	Organism* Baby(int x, int y, World* game) override;
};

