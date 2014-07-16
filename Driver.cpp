#include "Library.h"
#include "HelperFunctions.h"
#include <iostream>

int main()
{
	Library myLib;
	myLib.ReadPeriodicalsFromFile();
	myLib.ReadEmployeesFromFile();
	// these dont work
	// myLib.buildPriorityQueues(Date("8/13/2014")); 
	// myLib.buildPriorityQueues(Date("8/25/2014"));
	// myLib.buildPriorityQueues(Date("7/25/2014"));
	myLib.buildPriorityQueues(Date("2/28/2014"));
	// myLib.buildPriorityQueues(Date("3/19/2014"));
	// myLib.buildPriorityQueues(Date("10/13/2014"));
    myLib.ExecuteSimulator();
	
	system("pause");

    return 0;
}
