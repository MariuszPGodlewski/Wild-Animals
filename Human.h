#pragma once
#include <iostream>
#include "Organism.h"


class Human : public Organism{
private:
	bool used_ability = false;
	bool alzur_shield = false;
	bool magic_potion = false;
	bool antelope_speed = false;
	bool immortal = false;
	int ability_counter = 0;
public:
	Human(int position_X, int position_Y, int age, World* game);
	Human(int position_X, int position_Y, int age, char symbol, int initiative, int strenght,
		bool used_ability, bool alzur_shield, bool magic_potion,bool antelope_speed,bool immortal,
		int ability_counter,  World* game);
	void Move(int nr_in_table) override;
	bool Collision(int my_id, int other_Spiece_ID) override;
	int Collide(int my_id, int attacker_id) override;
	void Abilities(int nr_in_table, char key);
	void Reposition(int my_id, int other_spiece_id);
	void GetSpecialAbilities(int abilities[6]);
	void MoveExtention();
};

