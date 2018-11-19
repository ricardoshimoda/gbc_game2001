#include <iostream>
#include <string>
#include "BasicQueue.h"
using namespace std;

int main()
{
	BasicQueue<int> iQ;
	iQ.enQueue(42);
	iQ.enQueue(117);
	iQ.print();
	Unit uOne("Infantry");
	Unit uTwo("Commando");
	BasicQueue<Unit> uQ;
	uQ.enQueue(uOne);
	uQ.enQueue(uTwo);
	uQ.print();
	uQ.deQueue();
	uQ.print();
	system("pause");
	return 0;
}
