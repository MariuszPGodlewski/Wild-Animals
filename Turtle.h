#pragma once
#include <iostream>
#include "Animal.h"

using namespace std;


class Turtle : public Animal {
private:
public:
	Turtle(int position_X, int position_Y, int age, World* game);
	Turtle(int xy[2], World* game);
	Turtle(int position_X, int position_Y, int age, char symbol, int initiative, int strenght, World* game);
	Organism* Baby(int xy[2], World* game) override;
	void Move(int nr_in_table) override;
	int Collide(int my_id, int attacker_id) override;
};






