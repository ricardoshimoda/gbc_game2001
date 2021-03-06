// GAME2001_EXTRA_Nakasako_Ricardo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "BasicQueue.h"
#include "Bug.h"
using namespace std;

int main()
{
	BasicQueue<int> iQ;
	iQ.enQueue(4, 'B');
	iQ.enQueue(8, 'C');
	iQ.enQueue(1, 'A');
	iQ.enQueue(2, 'A');
	iQ.enQueue(7, 'B');
	iQ.enQueue(9, 'C');
	iQ.enQueue(3, 'A');
	iQ.enQueue(5, 'B');
	iQ.enQueue(10, 'C');
	iQ.enQueue(6, 'B');
	iQ.print();
	/* Bugs Bunny!  */
	/* Bugs Galore! */

	BasicQueue<Bug> bugsQ;
	bugsQ.enQueue(Bug('A', "First"), 'A');
	bugsQ.enQueue(Bug('A', "Second"), 'A');
	bugsQ.enQueue(Bug('A', "Third"), 'A');
	bugsQ.enQueue(Bug('B', "Fourth"), 'B');
	bugsQ.enQueue(Bug('B', "Fifth"), 'B');
	bugsQ.enQueue(Bug('B', "Sixth"), 'B');
	bugsQ.enQueue(Bug('B', "Seventh"), 'B');
	bugsQ.enQueue(Bug('B', "Eigth"), 'B');
	bugsQ.enQueue(Bug('C', "Ninth"), 'C');
	bugsQ.enQueue(Bug('C', "Tenth"), 'C');
	bugsQ.enQueue(Bug('C', "Eleventh"), 'C');
	bugsQ.enQueue(Bug('C', "Twelfth"), 'C');
	bugsQ.enQueue(Bug('C', "Thirteenth"), 'C');
	bugsQ.print();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
