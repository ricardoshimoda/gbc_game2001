/*
	GAME2001 - Assignment 1
	Date: September 28, 2018
	Group:
		Ekin Karayalcin (101116005)
		Ricardo Shimoda Nakasako (101128885)
 */

#include "pch.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<sstream>
#include<fstream>


// Just to avoid unecessary typing
using namespace std;

//Perhaps the only constant
const int NUM_CARRIERS = 2;

// Fighter class - represents one (of several) fighters lanched by a Carrier 
// during a battle 
class Fighter {
private:
	string m_fName;
	int m_damage;
	int m_structStrength;
public:
	/* Default constructor just to create the array */
	Fighter() {}
	Fighter(string fName, int damage, int structStrenght) 
		   :m_fName(fName), m_damage(damage), m_structStrength(structStrenght) {
	}
	void reduceStructure(int damage) {
		m_structStrength -= damage;
		if (m_structStrength < 0) {
			m_structStrength = 0;
		}
	}
	string getFName() {
		return m_fName;
	}
	int getStructStrenght() {
		return m_structStrength;
	}
	string getInfo() {
		return "Fighter Name: " + m_fName + 
			   "\nStructural Strength: " + to_string(m_structStrength) + 
			   "\nDamage: " + to_string(m_damage) + "\n";
	}
	int getDamage() {
		return m_damage;
	}
};


// Carrier class - represents one (of possible several?) carriers on battle
class Carrier {
private:
	string m_name;
	Fighter **m_bayList;
	int m_maxBays;
	int m_numFighters;
public:
	/* Default constructor to build the Carrier Array */
	Carrier() {}
	Carrier(string name, int maxBays): m_name(name), m_maxBays(maxBays) {
		m_bayList = new Fighter*[maxBays];
	}
	~Carrier() {
		delete[] m_bayList;
		/*
		for (int fighterList = 0; fighterList < m_numFighters; fighterList++) {
			delete[] &m_bayList[fighterList];
		}*/
		m_bayList = NULL;
	}
	bool loadFighter(Fighter* fighter) {

		if (m_numFighters == m_maxBays) {
			cout << "Cannot load " << fighter->getFName() << " into " 
				 << m_name << ". The carrier is full." << endl;
			return false;
		}
		m_bayList[m_numFighters] = fighter;
		m_numFighters++;
	}
	Fighter* launchNextFighter() {
		if (m_numFighters == 0) {
			cout << "There are no fighters in " << m_name << endl;
			return 0;
		}
		Fighter* temp = m_bayList[0];
		for (int i = 0; i < m_numFighters - 1; i++) {
			m_bayList[i] = m_bayList[i + 1];
		}

		//cout << "Launching " << temp->getFName() << " from " << name << endl;
		m_numFighters--;
		return temp;
	}
	string printInfo() {
		string result = "\nCarrier Name: " + m_name + "\n";
		result += "----------BAY LIST START----------\n";
		for (int i = 0; i < m_numFighters; i++) {
			result += m_bayList[i]->getInfo();
		}
		result += "----------BAY LIST END----------\n";
		return result;
	}
	bool hasFighter() {
		if (m_numFighters > 0) {
			cout << m_name << " has " << to_string(m_numFighters) 
				 << " fighters available." << endl << endl;
			return true;
		}
		cout << m_name << " has no fighters available." << endl << endl;
		return false;
	}
	int getCapacity() {
		return m_maxBays;
	}
	string getName() {
		return m_name;
	}
	int getNumFighters() {
		return m_numFighters;
	}
};

// Main class - reads file, creates all the other classes and simulates the battle 
// between vessels
class BattleSimulator {
private:

	Carrier* carriers[NUM_CARRIERS];
	void battle(Carrier *c1, Carrier *c2) {
		srand((unsigned)time(0));
		cout << endl << "Commencing battle between " << c1->getName() << " and " << c2->getName() << ".\n";
		while (c1->getNumFighters() > 0 && c2->getNumFighters() > 0) {
			Fighter* f1 = c1->launchNextFighter();
			Fighter* f2 = c2->launchNextFighter();
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
			while (f1->getStructStrenght() > 0 && f2->getStructStrenght() > 0) {
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
			if (f1->getStructStrenght() == 0) {
				cout << f1->getFName() << " is destroyed.\n";
				c2->loadFighter(f2);
				delete f1;
				f1 = NULL;
			}
			else {
				cout << f2->getFName() << " is destroyed.\n";
				c1->loadFighter(f1);
				delete f2;
				f2 = NULL;
			}
		}
		if (c1->getNumFighters() == 0) {
			cout << endl << c1->getName() << " is out of fighters. " 
				         << c2->getName() << " wins the battle.\n";
		}
		else {
			cout << endl << c2->getName() << " is out of fighters. " 
				         << c1->getName() << " wins the battle.\n";
		}
	}
	enum readFileStatus {
		start, 
		carrierSetup,
		carrierFighter, 
		carrierFighterData,
	};
	void parseIntPair(string line, int *firstInt, int *secondInt) {
		size_t space = line.find(' ', 0);
		*firstInt = stoi(line.substr(0, space));
		*secondInt = stoi(line.substr(space, line.length() - space));
	}
	void readFile(string filePath) {
		ifstream configFile(filePath);
		string line;
		string nameVessel;
		readFileStatus currentStatus = start;
		int currentCarrier = 0;
		int firstData = 0;
		int secondData = 0;
		int expectedFighters = 0;
		int declaredFighters = 0;
		Fighter *newFighter;

		while (getline(configFile, line))
		{
			switch (currentStatus) {
				case start:
					nameVessel = line;
					currentStatus = carrierSetup;
					break;
				case carrierSetup:
					parseIntPair(line, &firstData, &secondData);
					currentStatus = carrierFighter;
					carriers[currentCarrier] = new Carrier(nameVessel, firstData);
					expectedFighters = secondData;
					break;
				case carrierFighter:
					if (line != "") {
						declaredFighters++;
						nameVessel = line;
						currentStatus = carrierFighterData;
					}
					else {
						currentStatus = start;
						currentCarrier++;
					}
					break;
				case carrierFighterData:
					parseIntPair(line, &firstData, &secondData);
					newFighter = new Fighter(nameVessel, firstData, secondData);
					carriers[currentCarrier]->loadFighter(newFighter);
					currentStatus = carrierFighter;
					break;
			}
		}
		if (currentStatus != carrierFighter) {
			/* Something is incomplete!!!! */
			/* We need to dealocate it all before battling it out */
			return;
		}


	}
public:
	BattleSimulator(string filePath) {
		readFile(filePath);
	}
	void battle() {
		/* After reading the file, let's battle it out! */
		battle(carriers[0], carriers[1]);
	}
	~BattleSimulator() {
		for (int listCarriers = 0; listCarriers < NUM_CARRIERS; listCarriers++) {
			delete carriers[listCarriers];
		}
	}
};

void printInstructions() {
	cout << "Please, execute the program using the following syntax:" << endl;
	cout << "Assignment1.exe <path_configuration_file>" << endl;
	cout << "Where <path_configuration_file> is the path to the file containing "
		 << "data on carriers and fighters " << endl;
	cout << "Thanks!" << endl;

}

int main(int argc, char *argv[])
{
	/*
	 * Check if file was passed as the first argument of the function
	 */
	if (argc != 2) {
		/*
		 * Where is the file?
		 */
		printInstructions();
		return -1;
	}
	/*
     * Check if file exists
     */
	ifstream f(argv[1]);
	if (f.bad())
	{
		cout << "Configuration file not found at" << endl;
		cout << argv[1] << endl;
		printInstructions();
		return -1;
	}
	
	cout << "****************************************" << endl;
	cout << "* Battle Simulator                     *" << endl;
	cout << "* GAME2001 - Assignment 1              *" << endl;
	cout << "* Date: September 28, 2018             *" << endl;
	cout << "* Ekin Karayalcin(101116005)           *" << endl;
	cout << "* Ricardo Shimoda Nakasako(101128885)  *" << endl;
	cout << "****************************************" << endl;

	/* Let's Battle */
	BattleSimulator sim(argv[1]);
	sim.battle();
}
