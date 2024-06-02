#pragma once
#include "Plant.h"

class Sow_thistle :public Plant
{
private:
public:
	Sow_thistle(int position_X, int position_Y, int age, World* game);
	Sow_thistle(int x, int y, World* game);
	Sow_thistle(int position_X, int position_Y, int age, char symbol, int initiative, int strenght, World* game);
	void Move(int nr_in_table);
	Organism* Baby(int x, int y, World* game) override;
};

