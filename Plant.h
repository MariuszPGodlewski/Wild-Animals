#pragma once
#include <iostream>
#include "Organism.h"


using namespace std;

class Plant : public Organism {
private:
public:
	Plant(int initiative, int strength, int age, char symbol, int position_X, int position_Y, World* game);
	bool Collision(int my_id, int other_Spiece_ID) override;
	void Move(int nr_in_table) override;
	void Sawing(int nr_in_table);
	bool IsSawingPosible(int nr_in_table);
	void PlantSow(int x, int y);
	virtual Organism* Baby(int x, int y, World* game) = 0;
};
