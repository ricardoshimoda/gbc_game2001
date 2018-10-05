#include "pch.h"
#include <iostream>
#include <string>
#include <stdlib.h>  
#include <time.h>   
using namespace std;

class Fighter {
private:
	string fName;
	int damage;
	int structStrength;
public:
	Fighter() {}
	Fighter(string name, int dmg, int str) {
		fName = name;
		damage = dmg;
		structStrength = str;
	}
	void reduceStructure(int dmg) {
		structStrength -= dmg;
		if (structStrength < 0) {
			structStrength = 0;
		}
	}
	string getInfo() {
		return "Fighter Name: " + fName + "\nStructural Strength: " + to_string(structStrength) + "\nDamage: " + to_string(damage) + "\n";
	}
	string getFName() {
		return fName;
	}
	int getStructStrength() {
		return structStrength;
	}
	int getDamage() {
		return damage;
	}
};

class Carrier {
private:
	string name;
	Fighter *bayList;
	int maxBays;
	int numFighters;
public:
	Carrier(string cName, int maxBayNum) {
		name = cName;
		maxBays = maxBayNum;
		bayList = new Fighter[maxBays];
		numFighters = 0;
	}
	bool loadFighter(Fighter* fighter) {
		if (numFighters == maxBays) {
			cout << "Cannot load " << fighter->getFName() << " into " << name << ". The carrier is full." << endl;
			return false;
		}
		bayList[numFighters] = *fighter;
		numFighters++;
		//cout << "Loaded " << fighter->getFName() << " into " << name << "." << endl;
		return true;
	}
	Fighter* launchNextFighter() {
		if (numFighters == 0) {
			cout << "There are no fighters in " << name << endl;
			return false;
		}
		Fighter *temp = new Fighter(bayList[0].getFName(), bayList[0].getDamage(), bayList[0].getStructStrength());
		for (int i = 0; i < numFighters-1; i++) {
			bayList[i] = bayList[i + 1];
		}
		//cout << "Launching " << temp->getFName() << " from " << name << endl;
		numFighters--;
		return temp;
	}
	string printInfo() {
		string result = "\nCarrier Name: " + name + "\n";
		result += "----------BAY LIST START----------\n";
		for (int i = 0; i < numFighters; i++) {
			result += bayList[i].getInfo();
		}
		result += "----------BAY LIST END----------\n";
		return result;
	}
	bool hasFighter() {
		if (numFighters > 0) {
			cout << name << " has " << to_string(numFighters) << " fighters available." << endl << endl;
			return true;
		}
		cout << name << " has no fighters available." << endl << endl;
		return false;
	}
	int getCapacity() {
		return maxBays;
	}
	string getName() {
		return name;
	}
	int getNumFighters() {
		return numFighters;
	}
};

void battle(Carrier *c1, Carrier *c2) {
	srand((unsigned)time(0));
	cout << endl << "Commencing battle between " << c1->getName() << " and " << c2->getName() << ".\n";
	while (c1->getNumFighters() > 0 && c2->getNumFighters() > 0) {
		Fighter *f1 = c1->launchNextFighter();
		Fighter *f2 = c2->launchNextFighter();
		cout << endl << f1->getFName() << " VS " << f2->getFName() << endl;
		Fighter *attacker, *defender;
		int attackTurn = rand() % 2 + 1;
		if (attackTurn == 1) {
			attacker = f1;
			defender = f2;
		}
		else {
			attacker = f2;
			defender = f1;
		}
		cout << attacker->getFName() << " is going to attack first.\n";
		while (f1->getStructStrength() > 0 && f2->getStructStrength() > 0) {
			int hitRoll = rand() % 100 + 1;
			if (hitRoll < 50) {
				cout << attacker->getFName() << " misses " << defender->getFName() << endl;
			}
			else {
				int damageRoll = rand() % attacker->getDamage() + 1;
				defender->reduceStructure(damageRoll);
				cout << attacker->getFName() << " hits " << defender->getFName() << " for " << damageRoll << endl;
			}
			// Switch the attacker and defender.
			if (attacker == f1) {
				attacker = f2;
				defender = f1;
			}
			else {
				attacker = f1;
				defender = f2;
			}
		}
		if (f1->getStructStrength() == 0) {
			cout << f1->getFName() << " is destroyed.\n";
			c2->loadFighter(f2);
		}
		else {
			cout << f2->getFName() << " is destroyed.\n";
			c1->loadFighter(f1);
		}
	}
	if (c1->getNumFighters() == 0) {
		cout << endl << c1->getName() << " is out of fighters. " << c2->getName() << " wins the battle.\n";
	}
	else {
		cout << endl << c2->getName() << " is out of fighters. " << c1->getName() << " wins the battle.\n";
	}
}

int main()
{
	Fighter *fighter1 = new Fighter("Alpha1", 50, 100);
	Fighter *fighter2 = new Fighter("Alpha2", 50, 100);
	Fighter *fighter3 = new Fighter("Alpha3", 50, 100);
	Fighter *fighter4 = new Fighter("Gamma1", 50, 100);
	Fighter *fighter5 = new Fighter("Gamma2", 50, 100);
	Fighter *fighter6 = new Fighter("Gamma3", 50, 100);

	Carrier *carrier1 = new Carrier("HaulerAlpha", 3);
	Carrier *carrier2 = new Carrier("HaulerGamma", 3);

	carrier1->loadFighter(fighter1);
	carrier1->loadFighter(fighter2); 
	carrier1->loadFighter(fighter3);
	carrier2->loadFighter(fighter4);
	carrier2->loadFighter(fighter5);
	carrier2->loadFighter(fighter6);

	cout << carrier1->printInfo();
	cout << carrier2->printInfo();

	battle(carrier1, carrier2);

	cout << carrier1->printInfo();
	cout << carrier2->printInfo();
}
