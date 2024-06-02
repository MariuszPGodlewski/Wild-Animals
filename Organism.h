#pragma once
#include <iostream>
#include "conio2.h"
#include "constants.h"

using namespace std;

class World;

class Organism {
	friend class Animal;
	friend class Plant;
private:
	int strength;
	int initiative;
	int age;
	int position_X;
	int position_Y;
	char symbol;
	bool moved = false;
	bool animal;
protected:
	World* game;
public:
	
	Organism() = default;
	Organism(int initiative, int strength,int age, char symbol, int position_X, int position_Y, World* game, bool animal);
	int GetStrength();
	int GetInitiative();
	int GetAge();
	int Get_X();
	int Get_Y();
	char GetSymbol();
	bool GetMoved();
	bool IsAnimal();
	virtual void GetSpecialAbilities(int abilities[6]);

	void Set_XY(int x, int y);
	void SetMoved(bool move);
	void SetAge();
	void AddStrength(int boost);


	virtual void Move(int nr_in_table) = 0;
	void Move_Y(int move);
	void Move_X(int move);

	virtual bool Collision(int my_id, int other_Spiece_ID) = 0;
	virtual int Collide(int my_id, int attacker_id);
};