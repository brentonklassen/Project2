#include "Library.h"
#include "HelperFunctions.h"
#include <iostream>

int main()
{
	Library myLib;
	myLib.ReadPeriodicalsFromFile();
	myLib.ReadEmployeesFromFile();
	myLib.buildPriorityQueues(Date("8/13/2014")); 
    myLib.ExecuteSimulator();
	
	system("pause");

    return 0;
}
