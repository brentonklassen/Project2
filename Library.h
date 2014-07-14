/*
Library class header
*/

#ifndef __LIBRARY_H__
#define __LIBRARY_H__
#include "Periodical.h"
#include "Employee.h"
#include <vector>

class Library { //implemented by Jordan
public:
	void ReturnToLibrary(Periodical&, Employee&, Date);
	void checkoutPeriodical(Periodical& p, Employee& e, Date currentDate);
	void ExchangePeriodical(Periodical& p, Employee& e1, Date currentDate);
	void ReadPeriodicalsFromFile();
	void ReadEmployeesFromFile();
	void ReadActionsFromFile();
	void buildPriorityQueues(Date);
	void ArchivePeriodical(Periodical& p);
	void removeArchivedPeriodical(Periodical& p);
	void CirculatePeriodical(Periodical& p);

	void removeCirculatingPeriodical(Periodical& p);
    map <int,Employee> UpdateQueue(Periodical& p, Date currentDate);


private:
	vector<Periodical> archivedPeriodicals;
	vector<Periodical> circulatingPeriodicals;
	vector<Employee> employees;

};

#endif