#pragma once
#include "Plant.h"

class Sosnowsky_hogweed :public Plant
{
private:
public:
	Sosnowsky_hogweed(int position_X, int position_Y, int age, World* game);
	Sosnowsky_hogweed(int x, int y, World* game);
	Sosnowsky_hogweed(int position_X, int position_Y, int age, char symbol, int initiative, int strenght, World* game);
	Organism* Baby(int x, int y, World* game) override;
	int Collide(int my_id, int attacker_id) override;
	void Move(int nr_in_table) override;
};

