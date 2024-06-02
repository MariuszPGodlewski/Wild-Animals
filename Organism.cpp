#include <iostream>
#include "Organism.h"
#include "constants.h"
#include "World.h"

using namespace std;

Organism::Organism(int initiative, int strength, int age, char symbol, int position_X, int position_Y, World* game, bool animal)
	: initiative(initiative), strength(strength), age(age), symbol(symbol), 
	position_X(position_X), position_Y(position_Y), game(game), animal(animal){

}

int Organism::GetStrength() {
	return strength;
}
int Organism::GetAge() {
	return age;
}
int Organism::GetInitiative() {
	return initiative;
}
int Organism::Get_X() {
	return position_X;
}
int Organism::Get_Y() {
	return position_Y;
}
char Organism::GetSymbol() {
	return symbol;
}
bool Organism::GetMoved() {
	return moved;
}
bool Organism::IsAnimal() {
	return animal;
}
int Organism::Collide(int my_id, int attacker_id) {
	int k = GetStrength();
	game->AddMessage();
	gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN);
	cout << "Fight between: " << GetSymbol() << " and " << game->GetOrganizmPointer(attacker_id)->GetSymbol();
	gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, game->GetNrOfMessages() * 2 +TOP_MARGIN + 1);
	cout << "Strength     : " << GetStrength() << " and " << game->GetOrganizmPointer(attacker_id)->GetStrength();
	if (game->GetOrganizmPointer(attacker_id)->GetStrength() >= k)
		return true;
	return false;
}
void Organism::GetSpecialAbilities(int abilities[6]) {
}
void Organism::SetMoved(bool move) {
	moved = move;
}
void Organism::SetAge() {
	age++;
}
void Organism::AddStrength(int boost) {
	char k = GetSymbol();
	strength += boost;
}
void Organism::Set_XY(int x, int y) {
	if (x >= 0 && x < SIZE_X && y >= 0 && y < SIZE_Y) {
		position_X = x;
		position_Y = y;
	}
}

//This might couse debbug ing problems in the futrure if the spice would noo move
void Organism::Move_X(int move) {
	//positive move we go to the right negative to the left
	if (move < 0 && position_X > 0 - move - 1) {
		position_X = position_X + move;
		moved = true;
	}
	else if (move > 0 && position_X < SIZE_X - 1 - move + 1 ) {
		position_X = position_X + move;
		moved = true;
	}
}

void Organism::Move_Y(int move) {
	//positive move we go down negative up
	if (move < 0 && position_Y > 0 - move - 1 ) {
		position_Y = position_Y + move;
		moved = true;
	}
	else if (move > 0 && position_Y < SIZE_Y - 1 - move + 1) {
		position_Y = position_Y + move;
		moved = true;
	}
}