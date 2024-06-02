#pragma once
#include <iostream>
#include "constants.h"
#include "Organism.h"
#include "Wolf.h"
#include "Human.h"
using namespace std;



class World {
private:
	Organism* organisms[MAX_NR_OF_SPICIES];
	int nr_of_species = 0;
	int nr_of_species_at_current_turn = nr_of_species;
	int nr_of_messages = 0;
public:
	World();
	void SetNrOfSpieces(int n);
	void SetNrOfSpiecesRN(int n);
	Organism* GetOrganizmPointer(int posit);
	int GetNrOfSpieces();
	int GetNrOfMessages();
	void AddMessage();
	void makeTurn();
	void drawWorld();
	void addObject(Organism* new_object);
	void RemoveCreature(int posit);
	void Sort_Organism_By_Priority();

	bool CheckIfCollide(int x, int y, int courent_specie);
	void FreePositSpown(int xy[2], int parent1, int parent2);
	void FreePositSearch(int xy[2], int x, int y, int skip);
	bool FreePositCheck(int x, int y, int skip);
	
	void SaveGame();
	void LoadGame();
};

