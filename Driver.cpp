#include "Library.h"
#include "HelperFunctions.h"
#include <iostream>

/*
Actions:::
could be evan returns a book at a date
           --outside actions.txt, automate decision to passtonext or return to archive

*/

int main()
{
	Library myLib;
	myLib.ReadPeriodicalsFromFile();
	myLib.ReadEmployeesFromFile();
	myLib.buildPriorityQueues(Date("7/13/2014"));
    myLib.ExecuteSimulator();

	system("pause");

    return 0;
}
