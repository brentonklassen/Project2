#include "Library.h"
#include "HelperFunctions.h"
#include <iostream>

int main()
{
	Library myLib(Date("8/31/2014"));
	myLib.ReadPeriodicalsFromFile();
	myLib.ReadEmployeesFromFile();
	myLib.buildPriorityQueues(); 
    myLib.ExecuteSimulator();
	
	system("pause");

    return 0;
}
