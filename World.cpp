#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "constants.h"
#include "World.h"
#include "Organism.h"

#include "Human.h"
#include "conio2.h"

#include "Animal.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"
#include "Cyber_sheep.h"

#include "Plant.h"
#include "Grass.h"
#include "Sow_thistle.h"
#include "Guarana.h"
#include "Belladonna.h"
#include "Sosnowsky_hogweed.h"
using namespace std;

int World::GetNrOfSpieces() {
	return nr_of_species;
}

void World::SetNrOfSpieces(int n) {
	nr_of_species += n;
}

void World::SetNrOfSpiecesRN(int n) {
	nr_of_species_at_current_turn += n;
}

Organism* World::GetOrganizmPointer(int posit) {
	return organisms[posit];
}

bool World::FreePositCheck(int x ,int y, int skip) {
	if (x < 0 || x >= SIZE_X || y < 0 || y >= SIZE_Y)
		return false;

	for (int i = 0; i < nr_of_species; i++) {
		if (i != skip) {
			if (organisms[i] != nullptr && organisms[i]->Get_X() == x && organisms[i]->Get_Y() == y) {
				return false;
			}
		}
	}
	return true;
}

void World::FreePositSearch(int xy[2], int x, int y, int skip) {
	if (FreePositCheck(x + LEFT, y, skip)) {
		xy[0] = x + LEFT;
		xy[1] = y;
	}
	else if (FreePositCheck(x + RIGHT, y, skip)) {
		xy[0] = x + RIGHT;
		xy[1] = y;
	}
	else if (FreePositCheck(x, y + DOWN, skip)) {
		xy[0] = x;
		xy[1] = y + DOWN;
	}
	else if (FreePositCheck(x, y + UP, skip)) {
		xy[0] = x;
		xy[1] = y + UP;
	}
}

void World::FreePositSpown(int xy[2], int parent1, int parent2) {
	int x1 = organisms[parent1]->Get_X();
	int x2 = organisms[parent2]->Get_X();
	int y1 = organisms[parent1]->Get_Y();
	int y2 = organisms[parent2]->Get_Y();
	xy[0] = -1;

	FreePositSearch(xy, x1, y1, -1);
	if(xy[0] == -1)
		FreePositSearch(xy, x2, y2, -1);
}

void World::RemoveCreature(int posit) {
	organisms[posit] = nullptr;
	for (int j = posit; j < nr_of_species -1; j++) {
		organisms[j] = organisms[j + 1];
	}
	nr_of_species--;
}

bool World::CheckIfCollide(int x, int y, int courent_specie) {
	for (int i = 0; i < nr_of_species; i++) {
		if (courent_specie != i) {
			int k = organisms[i]->Get_X();
			int ay = organisms[i]->Get_Y();
			if (x == organisms[i]->Get_X() && 
				y == organisms[i]->Get_Y()) {
				return organisms[courent_specie]->Collision(courent_specie, i);
				
			}
		}
	}
	return true;
}

World::World() {
	srand(std::time(nullptr));
	for (int i = 0; i < MAX_NR_OF_SPICIES; i++) {
		organisms[i] = nullptr;
	}
	_setcursortype(_NOCURSOR);
}

void ClearMessages(int nr_of_messages) {
	for (int i = 0; i < nr_of_messages; i++) {
		gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5,i*2 +TOP_MARGIN);
		cout << "                                                ";
		gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, i*2+TOP_MARGIN + 1);
		cout << "                                                ";
	}
}

void World::makeTurn() {
	ClearMessages(nr_of_messages);
	nr_of_messages = 0;
	Sort_Organism_By_Priority();
	for (int i = 0; i < nr_of_species; i++) {
		organisms[i]->SetMoved(false);
		organisms[i]->SetAge();
	}
	nr_of_species_at_current_turn = nr_of_species;
	for (int i = 0; i < nr_of_species_at_current_turn; i++) {
		//gotoxy(RIGHT_MARGIN + SIZE_X * 2 + 5, TOP_MARGIN - 1);
		//cout << "Turn: " << organisms[i]->GetSymbol();
		//getch();
		//ClearMessages();
		while (i < nr_of_species_at_current_turn && !organisms[i]->GetMoved()) {
			organisms[i]->Move(i);
			
		}

		//drawWorld();
	}
	Sort_Organism_By_Priority();
}
int World::GetNrOfMessages() {
	return nr_of_messages;
}
void World::AddMessage() {
	nr_of_messages++;
}
void World::drawWorld() {

	
	for (int i = 0; i < SIZE_Y; i++) {
		for (int j = 0; j < SIZE_X; j++) {
			gotoxy(j * 2 + RIGHT_MARGIN, i + TOP_MARGIN);
			cout << ".";
		}
	}
	for (int i = 0; i < nr_of_species; i++) {
		gotoxy(organisms[i]->Get_X() * 2 + RIGHT_MARGIN, organisms[i]->Get_Y() + TOP_MARGIN);
		cout << organisms[i]->GetSymbol();
	}
}

void World::addObject(Organism* new_object) {
	if (nr_of_species < MAX_NR_OF_SPICIES) {
		organisms[nr_of_species] = new_object;
		nr_of_species++;
	}
}

void World::Sort_Organism_By_Priority() {
	// Using Bubble  for simplicity, you can replace it with more efficient algorithms like QuickSort or MergeSort
	for (int i = 0; i < nr_of_species - 1; ++i) {
		for (int j = 0; j < nr_of_species - i - 1; ++j) {
			// Compare by initiative first
			if (organisms[j]->GetInitiative() != organisms[j + 1]->GetInitiative()) {
				// Sort by initiative in descending order
				if (organisms[j]->GetInitiative() < organisms[j + 1]->GetInitiative()) {
					Organism* temp = organisms[j];
					organisms[j] = organisms[j + 1];
					organisms[j + 1] = temp;
				}
			}
			else { // If initiative is equal, compare by age
				// Sort by age in descending order
				if (organisms[j]->GetAge() < organisms[j + 1]->GetAge()) {
					Organism* temp = organisms[j];
					organisms[j] = organisms[j + 1];
					organisms[j + 1] = temp;
				}
			}
		}
	}

}

void World::SaveGame() {
	FILE* file;
	file = fopen("save.txt", "w");
	//check if memory was allocated
	if (file == NULL) {
		printf("Unable to open the file.\n");

	}
	fprintf(file, "%i\n", nr_of_species);

	for (int i = 0; i < nr_of_species; i++) {
		fprintf(file, "%c ", organisms[i]->GetSymbol());
		fprintf(file, "%i ", organisms[i]->GetStrength());
		fprintf(file, "%i ", organisms[i]->GetInitiative());
		fprintf(file, "%i ", organisms[i]->GetAge());
		fprintf(file, "%i ", organisms[i]->Get_X());
		fprintf(file, "%i ", organisms[i]->Get_Y());
		if (organisms[i]->GetSymbol() == 'H') {/*
abilities[0] = used_ability;
abilities[1] = alzur_shield;
abilities[2] = magic_potion;
abilities[3] = antelope_speed;
abilities[4] = immortal;
abilities[5] = ability_counter;*/
			int abilities[6];
			organisms[i]->GetSpecialAbilities(abilities);
			fprintf(file, "%i ", abilities[0]);
			fprintf(file, "%i ", abilities[1]);
			fprintf(file, "%i ", abilities[2]);
			fprintf(file, "%i ", abilities[3]);
			fprintf(file, "%i ", abilities[4]);
			fprintf(file, "%i ", abilities[5]);

		}

		fprintf(file, "\n");

	}
	fclose(file);
}

void World::LoadGame() {
	FILE* file;
	file = fopen("save.txt", "r");
	//check if memory was allocated
	if (file == NULL) {
		printf("Unable to open the file.\n");
	}
	int strength;
	int initiative;
	int age;
	int position_X;
	int position_Y;
	char symbol;
	int nr_of_spieces_in_file;
	fscanf(file, "%i", &nr_of_spieces_in_file);

	Human* adi = nullptr;
	Wolf* wolf = nullptr;
	Sheep* sheep = nullptr;
	Fox* fox = nullptr;
	Turtle* turtle = nullptr;
	Antelope* antelope = nullptr;
	Cyber_sheep* cyber_sheep = nullptr;
	Grass* grass = nullptr;
	Sow_thistle* sow_thistle = nullptr;
	Guarana* guarana = nullptr;
	Belladonna* belladonna = nullptr;
	Sosnowsky_hogweed* hogweed = nullptr;

	for (int i = 0; i < nr_of_spieces_in_file; i++) {
		fscanf(file, "\n%c: ", &symbol);
		fscanf(file, "%i: ", &strength);
		fscanf(file, "%i: ", &initiative);
		fscanf(file, "%i: ", &age);
		fscanf(file, "%i: ", &position_X);
		fscanf(file, "%i: ", &position_Y);

		switch (symbol)
		{
		case'H':/*
			abilities[0] = used_ability;
			abilities[1] = alzur_shield;
			abilities[2] = magic_potion;
			abilities[3] = antelope_speed;
			abilities[4] = immortal;
			abilities[5] = ability_counter; */
			int abilities[6];
			fscanf(file, "%i: ", &abilities[0]);
			fscanf(file, "%i: ", &abilities[1]);
			fscanf(file, "%i: ", &abilities[2]);
			fscanf(file, "%i: ", &abilities[3]);
			fscanf(file, "%i: ", &abilities[4]);
			fscanf(file, "%i: ", &abilities[5]);
			adi = new Human(position_X, position_Y, age, symbol, initiative, strength,
				abilities[0], abilities[1], abilities[2], abilities[3], abilities[4], abilities[5], this);
			addObject(adi);
			break;
		case 'W':
			wolf = new Wolf(position_X, position_Y, age, symbol, initiative, strength, this);
			addObject(wolf);
			break;
		case 'S':
			sheep = new Sheep(position_X, position_Y, age, symbol, initiative, strength, this);
			addObject(sheep);
			break;
		case 'F':
			fox = new Fox(position_X, position_Y, age, symbol, initiative, strength, this);
			addObject(fox);
			break;
		case 'T':
			turtle = new Turtle(position_X, position_Y, age, symbol, initiative, strength, this);
			addObject(turtle);
			break;
		case 'A':
			antelope = new Antelope(position_X, position_Y, age, symbol, initiative, strength, this);
			addObject(antelope);
			break;
		case 'C':
			cyber_sheep = new Cyber_sheep(position_X, position_Y, age, symbol, initiative, strength, this);
			addObject(cyber_sheep);
			break;
		case ','://Grass
			grass = new Grass(position_X, position_Y, age, symbol, initiative, strength, this);
			addObject(grass);
			break;
		case 'g':
			guarana = new Guarana(position_X, position_Y, age, symbol, initiative, strength, this);
			addObject(guarana);
			break;
		case 't':
			sow_thistle = new Sow_thistle(position_X, position_Y, age, symbol, initiative, strength, this);
			addObject(sow_thistle);
			break;
		case 'b':
			belladonna = new Belladonna(position_X, position_Y, age, symbol, initiative, strength, this);
			addObject(belladonna);
			break;
		case 's':
			hogweed = new Sosnowsky_hogweed(position_X, position_Y, age, symbol, initiative, strength, this);
			addObject(hogweed);
			break;
		default:
			break;
		}

	}
	
}