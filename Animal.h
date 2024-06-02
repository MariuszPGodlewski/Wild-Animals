#pragma once
#include <iostream>
#include "Organism.h"

using namespace std;

class Animal : public Organism {
private:
public:
	Animal(int initiative, int strength, int age, char symbol, int position_X, int position_Y, World* game);
	bool Collision(int my_id, int other_Spiece_ID) override;
	void Move(int nr_in_table) override;
	void MoveInWorld(int nr_in_table);
	int Collide(int my_id, int strength_attacker) override;
	bool CollisionManager(int my_id, int other_Spiece_ID);
	virtual Organism* Baby(int xy[2], World* game) = 0;
};
