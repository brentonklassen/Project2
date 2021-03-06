#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include "Library.h"
#include "StringTokenizer.h"
#include "HelperFunctions.h"
using namespace std;

Library::Library(Date current) :currentDate(current){}

// if the periodical was passed to another employee, that employee is returned
void Library::ReturnToLibraryandPassOn(Periodical& p, Employee& e, Date currentDate, int daysLate)
{//Jordan
	e.removeBookFromList(p.getBarcode());
    e.updateReliability(currentDate, p.getCheckOutDate(), p.getMaxCheckoutDuration());
	if (p.morePeopleInQueue() && p.passToNextEmployee(currentDate, daysLate, employees)) return;
    else {
        p.setCheckedOut(false);
        p.setArchiveDate(currentDate);
        ArchivePeriodical(p);
    }
}

void Library::SimulateEmployeeAction(ostream& outputStream)
{
	int randDaysToAdd;
	for (map<string, Employee>::iterator iter = employees.begin(); iter != employees.end(); iter++)
    {
		if (iter->second.hasNoBooks()) continue;
		if (iter->second.isLazy()) randDaysToAdd = rand() % 6;
        else randDaysToAdd = rand() % 2;

        string barcode = iter->second.getTopBookFromList();

		outputStream << iter->second.getName() << " returned " << circulatingPeriodicals[barcode].getName() << " after " << randDaysToAdd << " days." << endl;

		ReturnToLibraryandPassOn(circulatingPeriodicals[barcode], iter->second, currentDate, randDaysToAdd);
    }
}

void Library::ExecuteSimulator() // Jordan's function
{
    ofstream simulatorFile("SimulatorData.txt");
    while (!circulatingPeriodicals.empty())
    {
		currentDate.add_days(7);
        SimulateEmployeeAction(simulatorFile);
    }
    employees.begin()->second.PrintEmployeeDataBeforeNextSim(simulatorFile, employees);
	simulatorFile.close();
}




void Library::ReadPeriodicalsFromFile()
{//Evan w/ Brenton debug

	ifstream fin("Periodicals.txt");
	if (fin)
	{
		string line, aName, barcode;


		while (getline(fin, line))
		{
			String_Tokenizer st(line, ",");
			aName = trim(st.next_token());
			barcode = trim(st.next_token());
            circulatingPeriodicals[barcode] = Periodical(aName, barcode);
		}
	}
	fin.close();
}

void Library::ReadEmployeesFromFile()
{//Evan w/ Brenton debug
	ifstream fin("Employees.txt");
	if (fin)
	{
		string line, empName, startVacation, endVacation, lazyString;
		int lateDays, theWaitingTime;
		bool lazyBool;

		while (getline(fin, line))
		{
			String_Tokenizer st(line, ",");
			empName = trim(st.next_token());
			lateDays = stoi(trim(st.next_token()));
			theWaitingTime = stoi(trim(st.next_token()));
			startVacation = trim(st.next_token());
			endVacation = trim(st.next_token());
			lazyString = trim(st.next_token());
			transform(lazyString.begin(), lazyString.end(), lazyString.begin(), ::toupper); // convert to all uppercase
				if (lazyString == "LAZY")
					lazyBool = true;
				else if (lazyString == "NOT LAZY")
					lazyBool = false;
				else
					throw::exception("Invalid lazy input from employees.txt file");
			employees[empName] = Employee(lateDays, empName, Date(startVacation, DateFormat::US), Date(endVacation, DateFormat::US), theWaitingTime, lazyBool);
		}
	}
	fin.close();
}


void Library::buildPriorityQueues(){
	//Brenton
	for (map<string,Periodical>::iterator itr = circulatingPeriodicals.begin(); itr != circulatingPeriodicals.end(); itr++){
		itr->second.generateEmpQueue(employees);
		itr->second.passToNextEmployee(currentDate, 0, employees);
	}
}


void Library::ArchivePeriodical(Periodical p) // Evan
{
	if (circulatingPeriodicals.empty())
		throw::exception("All periodicals have been archived");
	circulatingPeriodicals.erase(p.getBarcode());
	archivedPeriodicals[p.getBarcode()] = p;
}
