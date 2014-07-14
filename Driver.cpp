#include "Library.h"
#include "HelperFunctions.h"
#include <iostream>

int main()
{
	Library myLib;
	myLib.ReadPeriodicalsFromFile();
	myLib.ReadEmployeesFromFile();
	myLib.buildPriorityQueues(Date("7/13/2014"));
	//myLib.ReadActionsFromFile();

	system("pause");

    return 0;
}
