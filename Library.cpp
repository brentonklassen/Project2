#include <fstream>
#include <string>
#include "Library.h"
#include "StringTokenizer.h"
#include "HelperFunctions.h"
using namespace std;

/*
void Library::ReturnToLibrary(Periodical& p, Employee& e, Date currentDate)
{//Jordan
	p.setCheckedBool(false);
	e.removeBookFromList(p.getBarcode());
    UpdateEmployeeReliability(e, p, currentDate);

	if (p.morePeopleInQueue())
	{
		p.passToNextEmployee(currentDate);
	}
    else
    {
        ArchivePeriodical(p);
    }
	e.removeBookFromList(p.getBarcode());
	e.setReliability(0); //fix later

}
*/

void Library::UpdateEmployeeReliability(Employee& e, Periodical& p, Date& currentDate)
{//Jordan
    if (currentDate > p.getReturnDate())
	{
		e.setReliability(e.getReliability() + (currentDate - p.getReturnDate()));
	}
	else
	{
		e.setReliability(e.getReliability() - (currentDate - p.getReturnDate()));
        if (e.getReliability() < 0)
        {
            e.setReliability(0);
        }
	}
}


void Library::ReadPeriodicalsFromFile()
{//Evan w/ Brenton debug

	ifstream fin("Periodicals.txt");
	if (fin)
	{
		string line, aName;
		int aBarCode;


		while (getline(fin, line))
		{
			String_Tokenizer st(line, ",");
			aName = trim(st.next_token());
			aBarCode = stoi(trim(st.next_token()));
            circulatingPeriodicals.push_back(Periodical(aName, aBarCode));
		}
	}
	fin.close();
}

void Library::ReadEmployeesFromFile()
{//Evan w/ Brenton debug
	ifstream fin("Employees.txt");
	if (fin)
	{
		string line, empName, startVacation, endVacation;
		int theReliability, theWaitingTime;

		while (getline(fin, line))
		{
			String_Tokenizer st(line, ",");
			empName = trim(st.next_token());
			theReliability = stoi(trim(st.next_token()));
			theWaitingTime = stoi(trim(st.next_token()));
			startVacation = trim(st.next_token());
			endVacation = trim(st.next_token());
			employees.push_back(Employee(theReliability, empName, Date(startVacation, DateFormat::US), Date(endVacation, DateFormat::US), theWaitingTime));
		}
	}
	fin.close();
}
// Returns Date of next batch of actions
// if end of file has been reached return empty Date
void Library::ReadActionsFromFile() // Evan
{
	ifstream actionsFile("Actions.txt");
	if (actionsFile.fail()){
		cout << "Couldn't open actions.txt\n";
		system("pause");
		exit(1);
	}

	while (!actionsFile.eof())
	{
		string line, name, action;
		int aBarcode;
		Date currentDate;

		getline(actionsFile, line);

		if (line == ""){
			continue;
		}
		else if (isDate(line))
		{
			currentDate = Date(line);
		}
		else {
			String_Tokenizer st(line, ",");

			name = trim(st.next_token());
			action = trim(st.next_token());
			aBarcode = stoi(trim(st.next_token()));

			if (action == "RETURN"){
				//ReturnToLibrary(circulatingPeriodicals[aBarcode], employees[name], currentDate);
			}
			else {
				throw::exception("Invalid action call from file");
			}
		}
    }
}

void Library::buildPriorityQueues(Date currentDate){
	//Brenton
	for (vector<Periodical>::iterator itr = circulatingPeriodicals.begin(); itr != circulatingPeriodicals.end(); itr++){
		itr->generateEmpQueue(employees);
		itr->passToNextEmployee(currentDate);
	}
}

/*
void Library::ArchivePeriodical(Periodical& p) // Evan
{
	map<int, Periodical>::iterator iter = archivedPeriodicals.begin();
	archivedPeriodicals.insert(iter, pair <int, Periodical>(p.getBarcode(), p));
}

void Library::removeArchivedPeriodical(Periodical& p) // Evan
{
	archivedPeriodicals.erase(p.getBarcode());
}

void Library::removeCirculatingPeriodical(Periodical& p) // Evan
{
    circulatingPeriodicals.erase(p.getBarcode());
}
*/