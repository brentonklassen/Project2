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
	void ReturnToLibrary(Periodical&, Employee&, Date);
	void ReadPeriodicalsFromFile();
	void ReadEmployeesFromFile();
    void SimulateEmployeeAction(ofstream&);
    void SaveSimulatorData(ofstream&);
    void ExecuteSimulator();
	void ReadActionsFromFile();
	void buildPriorityQueues(Date);
	void ArchivePeriodical(Periodical& p);

private:
	map<string,Periodical> archivedPeriodicals;
	map<string,Periodical> circulatingPeriodicals;
	map<string,Employee> employees;

};

#endif