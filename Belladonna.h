#pragma once
#include "Plant.h"

class Belladonna :public Plant
{
private:
public:
	Belladonna(int position_X, int position_Y, int age, World* game);
	Belladonna(int x, int y, World* game);
	Belladonna(int position_X, int position_Y, int age, char symbol, int initiative, int strenght, World* game);

	Organism* Baby(int x, int y, World* game) override;
	int Collide(int my_id, int attacker_id) override;
};

