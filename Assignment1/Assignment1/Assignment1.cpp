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


// Fighter class - represents one (of several) fighters lanched by a Carrier 
// during a battle 
class Fighter {
private:
	string m_fName;
	int m_damage;
	int m_structStrenght;
public:
	Fighter(string fName, int damage, int structStrenght) :m_fName(fName), m_damage(damage), m_structStrenght(structStrenght) {

	}
	void reduceStructure(int damage) {
	}
	string getFName() {
		return m_fName;
	}
	int getStructStrenght() {
		return m_structStrenght;
	}
	string getInfo() {
		return m_fName;
	}
};


// Carrier class - represents one (of possible several?) carriers on battle
class Carrier {
private:
	string m_name;
	Fighter *m_bayList;
	int m_maxBays;
	int m_numFighters;
public:
	Carrier(string name, int maxBays): m_name(name), m_maxBays(maxBays) {

	}
	void loadFighter(Fighter *fighter) {

	}
	void launchNextFigher() {
	}
};

// Main class - reads file, creates all the other classes and simulates the battle 
// between vessels
class BattleSimulator {
private:
	void battle(Carrier *c1, Carrier *c2) {
	}
	void mountCarrier(string carrierName, int maxBays, int fighter) {

	}
public:
	BattleSimulator(string filePath) {
		ifstream configFile(filePath);

		/* */
		/* After reading the file, let's battle it out! */
	}
};

void printInstructions() {
	cout << "Please, execute the program using the following syntax:" << endl;
	cout << "Assignment1.exe <path_configuration_file>" << endl;
	cout << "Where <path_configuration_file> is the path to the file containing data on carriers and fighters " << endl;
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
}
