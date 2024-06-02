#pragma once
#include "Plant.h"

class Guarana :public Plant
{
private:
public:
	Guarana(int position_X, int position_Y, int age, World* game);
	Guarana(int x, int y, World* game);
	Guarana(int position_X, int position_Y, int age, char symbol, int initiative, int strenght, World* game);
	Organism* Baby(int x, int y, World* game) override;
	int Collide(int my_id, int attacker_id) override;
};

