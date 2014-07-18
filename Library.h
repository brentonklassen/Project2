/*
Library class header
*/

#ifndef __LIBRARY_H__
#define __LIBRARY_H__
#include "Periodical.h"
#include "Employee.h"
#include <map>

class Library { //implemented by Jordan
public:
	Library(Date);
	void ReturnToLibraryandPassOn(Periodical&, Employee&, Date, int);
	void ReadPeriodicalsFromFile();
	void ReadEmployeesFromFile();
    void SimulateEmployeeAction(ostream&);
    void ExecuteSimulator();
	void buildPriorityQueues();
	void ArchivePeriodical(Periodical p);

private:
	map<string,Periodical> archivedPeriodicals;
	map<string,Periodical> circulatingPeriodicals;
	map<string,Employee> employees;
	Date currentDate;
};

#endif