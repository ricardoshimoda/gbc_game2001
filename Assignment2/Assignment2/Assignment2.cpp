/*
	GAME2001 - Assignment 2
	Date: December 2, 2018
	Group:
		Ekin Karayalcin (101116005)
		Ricardo Shimoda Nakasako (101128885)
 */


#include "pch.h"
#include <string>
#include<iostream>

using namespace std;

/*
 * Ok, I know this is not optimized - but it is the only way you'll see this code is mine.
 */
const bool DOOMSDAY = false;

class Weapon {
public:
	string weaponName;
	int range;
	int damage;
	float weight;
	float cost;

	Weapon(string n, int rang, int dam, float w, float c) {
		weaponName = n;
		damage = dam;
		range = rang;
		weight = w;
		cost = c;
	}

	void print() {
		cout << "Name: " << weaponName << "   Damage:" << damage << "    Cost:" << cost << endl;
	}
	string getKey() {
		return weaponName;
	}
};
/*
Olde code - not to be used anymore
class hashTable {

public:
	int tableLength;    // records the max size of the table
	int numItems;       // records number of items in the list
	Weapon **table; //hashtable itself

	hashTable(int size) {
		tableLength = size;
		numItems = 0;
		table = new Weapon*[tableLength];
		for (int i = 0; i < tableLength; i++) {
			table[i] = NULL;
		}
	}


	int hash(string key)
	{
		int value = 0;
		for (int i = 0; i < key.length(); i++)
			value = value + key[i];
		return value % tableLength;
	}

	void put(Weapon *item) {
		int location = hash(item->weaponName); //gets location in table based on name
		while (table[location] != NULL) {
			location = (location + 1);      // look one down
			location = location % tableLength; // to ensure wraparound at end of array
		}
		table[location] = item;
		numItems++;
	}

	Weapon* get(string key) {
		int location = hash(key); //gets location in table based on key
		while (table[location] != NULL && key.compare(table[location]->weaponName) != 0) {  // not empty and not item
			location = (location + 1);      // look one down
			location = location % tableLength; // to ensure wraparound at end of array
		}
		return table[location];
	}

	void printTable() {
		int count = 0;
		for (int x = 0; x < tableLength; x++) {
			if (table[x] != NULL) {
				cout << "Name: " << table[x]->weaponName << "   Damage:" << table[x]->damage << "    Cost:" << table[x]->cost << endl;
			}
		}
	}
};
*/

template<typename T>
class BinaryTree;

/* 
 * We decided to adapt the node class - to separate the key (string) from the data that is 
 * being stored. Using this solution enable us to create more generic solutions using the 
 * binary tree to potentially store anything that can be indexed by a string
 */
template<typename T>
class Node {
	friend class BinaryTree<T>;
public:
	Node(T* value) : m_left(NULL), m_right(NULL), m_value(value) {

	}
	~Node() {
		if (m_left != NULL) {
			delete m_left;
			m_left = NULL;
		}
		if (m_right != NULL) {
			delete m_right;
			m_right = NULL;
		}
	}
	string getKey() {
		return m_value->getKey();
	}
private:
	Node<T> *m_left, *m_right;
	T *m_value;
};

/*
 * This binary tree uses the T only to guide the way the node should be built 
 * and relies on a string to be the key that will guide the correct placement
 * of nodes
 */
template<typename T>
class BinaryTree {
public:
	BinaryTree():m_root(NULL) {}
	~BinaryTree() {
		if (m_root != NULL) {
			delete m_root;
			m_root = NULL;
		}
	}

	/*
	 * Since we want the weapons in alphabetical order, we are going to print them
	 * in order (I would use pre or post order only if I wanted to confuse my players)
	 */
	void printTable() {
		printInOrder(m_root);
	}

	/*
	 * Inserts items on the binary tree
	 * Returns:
	 * true when it successfully inserts a new item on the tree
	 * false when the given item already exists on the tree - this doesn't update 
	 */
	bool put(T* item) {
		Node<T> *newNode = new Node<T>(item);

		/* 
		 * When there is nothing - this is going to be the first node
		 */
		if (m_root == NULL) {
			m_root = newNode;
			return true;
		}

		Node<T> *parentNode = NULL;
		Node<T> *currentNode = m_root;
		/*
		 * Let's start the saga of looking for the correct place to insert this new node
		 */
		while (!DOOMSDAY) {
			parentNode = currentNode;
			int compareResult = item->getKey().compare(currentNode->getKey());
			if (compareResult == 0) {
				/*
				 * Nothing to insert here - just move around
				 */
				delete newNode;
				return false;
			}

			/*
			 * The given key is less than the node being evaluated 
			 */
			if (compareResult < 0) {
				currentNode = currentNode->m_left;
				// the spot is free
				if (currentNode == NULL) {
					parentNode->m_left = newNode;
					return true;
				}
			}

			/*
			 * The given key is more than the node being evaluated
			 */
			if (compareResult > 0) {
				currentNode = currentNode->m_right;
				// the spot is free
				if (currentNode == NULL) {
					parentNode->m_right = newNode;
					return true;
				}
			}
		}
	}

	/*
	 * Removes a node given a certain key
	 */
	void remove(string key) {

		if(m_root == NULL)
			return;

		Node<T> *parentNode = NULL;
		Node<T> *currentNode = m_root;
		bool isLeftNode = false;
		int comparison = key.compare(currentNode->getKey());

		/*
		 * First we need to find whatever we need to remove
		 */
		while (comparison != 0) {
			parentNode = currentNode;
			if (comparison < 0) {
				currentNode = currentNode->m_left;
				isLeftNode = true;
			}
			if (comparison > 0) {
				currentNode = currentNode->m_right;
				isLeftNode = false;
			}
			/*
			 * when the item is not on the tree, there is nothing to remove
			 */
			if (currentNode == NULL)
				return;
			/* for the next comparison round */
			comparison = key.compare(currentNode->getKey());
		}

		/*
		 * Time to roll up our sleeves and go to work - let's remove this
		 */
		if (currentNode->m_left == NULL && currentNode->m_right == NULL) {
			/*
			 * This is a leaf - we just have to make it fall gracefully detatching it from its parent 
			 */
			if (currentNode == m_root) 
				m_root = NULL; // and sometimes the parent can be the root node
			else if (isLeftNode) 
				parentNode->m_left = NULL;
			else 
				parentNode->m_right = NULL;
		}
		else if (currentNode->m_left == NULL) {
			if (currentNode == m_root)
				m_root = currentNode->m_right; // replacing the root with the non-null member
			else if (isLeftNode)
				parentNode->m_left = currentNode->m_right; // just replacing the node in the correct position will suffice
			else
				parentNode->m_right = currentNode->m_right;
		}
		else if (currentNode->m_right == NULL) {
			if (currentNode == m_root)
				m_root = currentNode->m_left; // replacing the root with the non-null member
			else if (isLeftNode)
				parentNode->m_left = currentNode->m_left; // just replacing the node in the correct position will suffice
			else
				parentNode->m_right = currentNode->m_left;
		}
		else {
			/*
			 * Now for the most interesting case - when we have both nodes and 
			 * we have to navigate and reposition nodes carefully in order not to lose the 
			 * correct ordering of nodes
			 * Therefore, first we need to get the next superior value going all the way to the left
			 * from the first to the right
			 */
			Node<T> *tempNode = currentNode->m_right;
			Node<T> *successor = currentNode;
			Node<T> *successorParent = currentNode;

			while (tempNode != NULL) {
				successorParent = successor;
				successor = tempNode;
				tempNode = tempNode->m_left;
			}

			/*
			 * If the successor is not the first node to the right (who knows?) 
			 * we have to position it correctly
			 */
			if (successor != currentNode->m_right) {
				/*
				 * makes the parent take the continuation for the successor that is 
				 * going to replace the node to be removed
				 */
				successorParent->m_left = successor->m_right;
				/*
				 * makes the successor->right point to the right of the node to be removed
				 */
				successor->m_right = currentNode->m_right;
				//
			}
			/*
			 * And now the usual trio
			 */
			if (currentNode == m_root) {
				m_root = successor;
			}
			else if(isLeftNode){
				currentNode = parentNode->m_left; /* recovers the original node to be removed just for safety? */
				parentNode->m_left = successor;
			}
			else {
				currentNode = parentNode->m_right; /* recovers the original node to be removed just for safety? */
				parentNode->m_right = successor;
			}
			/* 
			 * And finally recovering the original left member
			 */
			successor->m_left = currentNode->m_left;
		}

		/*
		 * Remove all the references that this node used to have
		 */
		currentNode->m_left = NULL;
		currentNode->m_right = NULL;
		/*
		 * Removes the node from the memory
		 */
		delete currentNode;
	}

	T* get(string key) {
		Node<T> *currentNode = m_root;
		while (!DOOMSDAY) {
			if (currentNode == NULL)
				return NULL;
			/*
			 * The saga returns (but now we are just looking for the last jedi)
			 */
			int compareResult = key.compare(currentNode->getKey());
			if (compareResult == 0) {
				return currentNode->m_value;
			}

			if (compareResult < 0) {
				currentNode = currentNode->m_left;
			}

			if (compareResult > 0) {
				currentNode = currentNode->m_right;
			}
		}
	}
private:
	Node<T> *m_root;
	void printInOrder(Node<T> *currentNode) {
		if (currentNode == NULL) return;
		printInOrder(currentNode->m_left);
		currentNode->m_value->print();
		printInOrder(currentNode->m_right);
	}
};

class Player {
public:
	string name;
	Weapon ** backpack;
	int numItems;
	float money;

	Player(string n, float m) {
		name = n;
		money = m;
		numItems = 0;
		backpack = new Weapon*[10];
	}

	void buy(Weapon * w) {
		cout << w->weaponName << " bought..." << endl;
		backpack[numItems] = w;
		numItems++;
		cout << " You now have " << numItems << " weapons " << endl;
		if (numItems > 10) cout << " Wow! Walking arsenal Much guns. " << endl;
	}
	void withdraw(float amt) {
		money = money - amt;
	}

	bool inventoryFull() {
		bool full = false;
		if (numItems == 10)full = true;
		return full;
	}


	void printCharacter() {
		cout << " Name:" << name << endl << " Money:" << money << endl;
		printBackpack();
	}

	void printBackpack() {
		cout << " " << name << ", you own " << numItems << " Weapons:" << endl;
		for (int x = 0; x < numItems; x++) {
			cout << " " << backpack[x]->weaponName << endl;
		}
		cout << endl;
	}

};

void addWeapons(BinaryTree<Weapon> *h) {
	cout << "***********WELCOME TO THE WEAPON ADDING MENU*********" << endl;
	string weaponName; int weaponRange; int weaponDamage; float weaponWeight; float weaponCost;
	cout << "Please enter the NAME of the Weapon ('end' to quit):"; cin >> weaponName;
	while (weaponName.compare("end") != 0) {
		cout << "Please enter the Range of the Weapon (0-10):"; cin >> weaponRange;
		cout << "Please enter the Damage of the Weapon:"; cin >> weaponDamage;
		cout << "Please enter the Weight of the Weapon (in pounds):"; cin >> weaponWeight;
		cout << "Please enter the Cost of the Weapon:"; cin >> weaponCost;
		Weapon *w = new Weapon(weaponName, weaponRange, weaponDamage, weaponWeight, weaponCost);
		h->put(w);
		cout << "Please enter the NAME of another Weapon ('end' to quit):"; cin >> weaponName;
	}
}

void showRoom(BinaryTree<Weapon> *ht, Player *p) {
	string choice = "go speed racer";
	cout << "WELCOME TO THE SHOWROOM!!!!" << endl;
	cout << "Guns at your disposal: " << endl;
	ht->printTable();
	cout << " You have " << p->money << " money." << endl;
	cout << "Please select a weapon to buy('end' to quit):"; cin >> choice;
	while (choice.compare("end") != 0 && !p->inventoryFull()) {
		Weapon *w = ht->get(choice);
		if (w != NULL) {
			if (w->cost > p->money) {
				cout << "Insufficient funds to buy " << w->weaponName << endl;
			}
			else {
				p->buy(w);
				p->withdraw(w->cost);
				/* If you want to test removal */
				//ht->remove(w->weaponName);
			}
		}
		else {
			cout << " ** " << choice << " not found!! **" << endl;
		}
		//ht->printTable();
		cout << "Please select another weapon to buy('end' to quit):"; cin >> choice;
	}
	cout << endl;
}


int main() {
	string pname;
	cout << "Please enter Player name:" << endl;
	cin >> pname;
	Player pl(pname, 100);
	BinaryTree<Weapon> bt;
	addWeapons(&bt);
	showRoom(&bt, &pl);
	pl.printCharacter();

	return 0;
}
