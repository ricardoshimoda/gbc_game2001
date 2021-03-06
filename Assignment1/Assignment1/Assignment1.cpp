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

//The only global constant
const int NUM_CARRIERS = 2;

// Fighter class - represents one (of several) fighters lanched by a Carrier 
// during a battle 
class Fighter {
private:
	// private members of the class
	string m_fName;			// Fighter Name
	int m_damage;			// Fighter Damage
	int m_structStrength;	// Fighter Structural Strength
public:
	// Constructor with three parameters:
	// fName          - sets the fighter name
	// damage         - sets the maximum damage it can inflict when its attack is successful
	// structStrength - sets the Fighter's initial structural strength
	Fighter(string fName, int damage, int structStrenght) 
		   :m_fName(fName), m_damage(damage), m_structStrength(structStrenght) {
	}
	// Empty class destructor (nothing is allocated dynamically)
	~Fighter() {}
	// reduceStructure: method to inflict damage to a fighter when it is hit
	// by another one
	// damage - parameter containing the damage inflicted by an attack
	// returns: true if the Fighter can still fight, false if the fighter 
	// has its structural strength reduced to 0
	bool reduceStructure(int damage) {
		m_structStrength -= damage;
		if (m_structStrength < 0) {
			m_structStrength = 0;
			return false;
		}
		return true;
	}
	// getFName: method that simply returns the fighter's name
	const string getFName() {
		return m_fName;
	}
	// getStructStrength: method that simply returns the fighter's structural strength
	const int getStructStrength() {
		return m_structStrength;
	}
	// getDamage: method that returns the damage the fighter can inflict when 
	// it is successful in attacking another fighter
	const int getDamage() {
		return m_damage;
	}
	// getInfo: method that returns a string containing the fighter's:
	// name, 
	// structural strenght and 
	// the damage it can possibly inflict
	const string getInfo() {
		ostringstream fighterInfo;
		fighterInfo << "Fighter Name: " << m_fName << endl;
		fighterInfo << "Structural Strength: " << m_structStrength << endl;
		fighterInfo << "Damage: " << m_damage << endl;
		return fighterInfo.str();
	}
};

// Carrier class - represents one of the two opposing carriers on battle
class Carrier {
private:
	// Private members of the class
	string m_name;			// Carrier name
	Fighter **m_bayList;	// Array of pointers to Fighters - which are hosted by the carrier
	int m_maxBays;			// Total number of possible bays to hold fighters
	int m_numFighters;		// Current number of Fighters
public:
	// Constructor with two parameters
	// name    - sets the carrier name
	// maxBays - sets the maximum number of fighter bays
	Carrier(string name, int maxBays): m_name(name), m_maxBays(maxBays) {
		m_bayList = new Fighter*[maxBays];
	}
	// Destructor - since we are allocating fighters, we must also
	// delete them and the array of pointers
	~Carrier() {
		// At the end of the battle deletes all remaining (surviving) fighters
		for (int fighterList = 0; fighterList < m_numFighters; fighterList++) {
			delete m_bayList[fighterList];
			m_bayList[fighterList] = NULL;
		}
		delete[] m_bayList;
		m_bayList = NULL;
	}
	// loadFigher: method that receives a pointer to a fighter and loads it into 
	// the carrier's bay
	// fighter: pointer to the fighter that needs to be inserted into the carrier's
	// array of pointers
	bool loadFighter(Fighter* fighter) {
		// Check if we are not exceeding the maximum limit (once more)
		if (m_numFighters >= m_maxBays) {
			return false;
		}
		// Assign the fighter, returning or not, to the end of the array
		m_bayList[m_numFighters] = fighter;
		m_numFighters++;
		return true;
	}
	// launchNextFighter: method that represents "launching" a fighter into battle
	// by returning a Fighter pointer
	// The fighter to be launched into battle is always the first element of the array
	Fighter* launchNextFighter() {
		// Check if we are still able to launch any fighter
		if (m_numFighters == 0) {
			return false;
		}
		// "Detaches" the first fighter from the array
		Fighter* warrior = m_bayList[0];
		// Repositions all the other fighters in the array - FIFO
		for (int i = 0; i < m_numFighters - 1; i++) {
			m_bayList[i] = m_bayList[i + 1];
		}
		// Now we have one less fighter inside the carrier
		m_numFighters--;
		return warrior;
	}
	// printInfo: method that return a string with the following carrier information:
	// Name
	// Information of each fighter in the carrier
	const string printInfo() {
		ostringstream carrierInfo;
		carrierInfo << endl << "Carrier Name: " << m_name << endl;
		if (m_numFighters > 0) {
			carrierInfo << "----------BAY LIST START----------" << endl;
			for (int i = 0; i < m_numFighters; i++) {
				carrierInfo << m_bayList[i]->getInfo();
			}
			carrierInfo << "----------BAY LIST END----------" << endl;
		}
		else {
			carrierInfo << "-----NO FIGHTERS AVAILABLE------" << endl;
		}
		return carrierInfo.str();
	}
	// hasFighters: method that returns if the carrier still has fighters available
	const bool hasFighter() {
		return m_numFighters > 0;
	}
	// getCapacity: method that returns the total capacity of the carrier
	const int getCapacity() {
		return m_maxBays;
	}
	// getName: method that returns the name of the carrier
	const string getName() {
		return m_name;
	}
	// getNumFighters: method that returns the number of Fighters on the carrier
	int getNumFighters() {
		return m_numFighters;
	}
};

// Main class - reads file, creates all the other classes and simulates the battle 
// between vessels
class BattleSimulator {
private:
	// private members of Battle Simulator
	Carrier* carriers[NUM_CARRIERS];
	// battle: main method - receives two carriers data and simulates the battle
	// between them both until one of them no longer can deploy a fighter
	void battle(Carrier *c1, Carrier *c2) {
		// Initializes random number generator - to randomly define the results of attacks
		// the order of attacks
		srand((unsigned)time(0));
		cout << endl << "******************B*A*T*T*L*E***S*I*M*U*L*A*T*O*R******************" << endl;
		cout << endl << "- Commencing battle between " << c1->getName() << " and " << c2->getName() << endl;
		cout << endl << "*******************************************************************" << endl;
		// While both carriers have fighters to battle it out		
		while (c1->hasFighter() && c2->hasFighter()) {
			Fighter* f1 = c1->launchNextFighter();
			Fighter* f2 = c2->launchNextFighter();
			// Check if fighters from both carriers could really be launched
			bool live1 = f1; 
			bool live2 = f2;
			cout << endl << "*********F*I*G*H*T*E*R*S****B*A*T*T*L*E*************" << endl;
			cout << f1->getFName() << " VS " << f2->getFName() << endl;
			Fighter *attacker, *defender;
			bool *damaged;
			// Using pointers to avoid repetition and if statements
			// during battle
			int attackTurn = rand() % 2 + 1;
			if (attackTurn == 1) {
				attacker = f1;
				defender = f2;
				damaged = &live2;
			}
			else {
				attacker = f2;
				defender = f1;
				damaged = &live1;
			}
			cout << attacker->getFName() << " is going to attack first." << endl;
			cout << "****************************************************" << endl << endl;
			// while both fighters are still "alive"
			while (live1 && live2) {
				int hitRoll = rand() % 100 + 1;
				// verify if attack was successful or not
				if (hitRoll < 50) {
					cout << "**** " << attacker->getFName() << " misses ****" << defender->getFName() << endl;
				}
				else {
					// "calculates" the damage done
					int damageRoll = rand() % attacker->getDamage() + 1;
					// inflic damage on the defender and verifies its 
					// structural strength
					*damaged = defender->reduceStructure(damageRoll);
					cout << "**** " << attacker->getFName() 
						 << " hits " << defender->getFName() 
						<< " for " << damageRoll << " ****"<< endl;
				}
				// Switch the attacker and defender.
				if (attacker == f1) {
					attacker = f2;
					defender = f1;
					damaged = &live1;
				}
				else {
					attacker = f1;
					defender = f2;
					damaged = &live2;
				}
			}
			// Now it's time to print the result of said battle between fighters
			bool back = true;
			cout << "BOOOOOMMMM ";
			if (live2) {
				cout << f1->getFName();
				back = c2->loadFighter(f2);
				delete f1;
				f1 = NULL;
			}
			else {
				cout << f2->getFName();
				back = c1->loadFighter(f1);
				delete f2;
				f2 = NULL;
			}
			cout << " destroyed!!!!!";
			if (!back) {
				cout << "A fighter could not make it back to the carrier - unexpected error - aborting execution." << endl;
				return;
			}
			cout << endl << endl << "***********E*N*D****O*F****R*O*U*N*D************" << endl;
			cout << c1->printInfo() << endl;
			cout << c2->printInfo() << endl;
			cout << "************************************************" << endl << endl;
		}
		// Finally, we print the result of the battle between carriers as a whole
		cout << "***********E*N*D****O*F****B*A*T*T*L*E***********" << endl;
		if (!c1->hasFighter()) {
			cout << endl << c1->getName() << " is out of fighters. "
				<< c2->getName() << " wins the battle." << endl;
		}
		else if (!c2->hasFighter()) {
			cout << endl << c2->getName() << " is out of fighters. "
				<< c1->getName() << " wins the battle." << endl;
		}
		cout << c1->printInfo();
		cout << c2->printInfo();
		cout << "************************************************" << endl;
	}
	// readFileStatus: Enum created for the state-machine file reader
	enum readFileStatus {
		start, 
		carrierSetup,
		carrierFighter, 
		carrierFighterData,
		formatError
	};
	// parseIntPair: Function created to better read lines comprised of
	// two numbers
	// line: the string representation of the line read from the config file
	// firstInt: pointer to output the first integer in the line
	// secondInt: pointer to output the second integer in the line
	void parseIntPair(string line, int *firstInt, int *secondInt) {
		size_t space = line.find(' ', 0);
		*firstInt = stoi(line.substr(0, space));
		*secondInt = stoi(line.substr(space, line.length() - space));
	}
	// readFile: Funciona to read the configuration file
	// filePath: the path of the config file
	bool readFile(string filePath) {
		// stream to read the file 
		ifstream configFile(filePath);
		string line;
		// the generic name for a vesses (carriers and fighters)
		string nameVessel;
		// Initial status for file reading
		readFileStatus currentStatus = start;
		// Varies the carrier in the carrier array
		int currentCarrier = 0;
		// Variables to parse lines with two integers
		int firstData = 0;
		int secondData = 0;
		// Control to see how many fighters are reallty out there and
		// how many are expected on each carrier
		int expectedFighters = 0;
		int declaredFighters = 0;
		// Temporary Fighter pointer to load it to the carrier
		Fighter *newFighter;
		// reads until the end of the file
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
				declaredFighters = 0; // starting a new carrier
				break;
			case carrierFighter:
				if (line != "") {
					declaredFighters++;
					if (declaredFighters > expectedFighters) {
						currentStatus = formatError;
						break;
					}
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
				newFighter = new Fighter(nameVessel, secondData, firstData);
				carriers[currentCarrier]->loadFighter(newFighter);
				currentStatus = carrierFighter;
				break;
			}
		}
		if (currentStatus != carrierFighter) {
			return false;
		}
		return true;
	}
public:
	// Just an empty constructor
	BattleSimulator() {
	}
	//battle: main function - battles without exposing the carriers and reading the file
	void battle(string filePath) {
		if (readFile(filePath)) {
			battle(carriers[0], carriers[1]);
		}
		else {
			cout << "Error while reading battle configuration file " << filePath << " simulation aborted" << endl;
		}
	}
	// Destructor: removes the carriers
	~BattleSimulator() {
		for (int listCarriers = 0; listCarriers < NUM_CARRIERS; listCarriers++) {
			if(carriers[listCarriers]){
				delete carriers[listCarriers];
			}
		}
	}
};
// printInstructions: just a small global function to be used for the main class before 
// anything else can be done
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
	BattleSimulator sim;
	sim.battle(argv[1]);
	return 1;
}
