#include <fstream>
#include <string>
#include "Library.h"
#include "StringTokenizer.h"
#include "HelperFunctions.h"
using namespace std;


void Library::ReturnToLibrary(Periodical& p, Employee& e, Date currentDate)
{//Jordan
	p.setCheckedOut(false);
	e.removeBookFromList(p.getBarcode());
	e.updateReliability(currentDate, p.getReturnDate());

	if (p.morePeopleInQueue())
	{
		p.passToNextEmployee(currentDate);
	}
    else
    {
        ArchivePeriodical(p);
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
			Periodical per;
			Employee emp;

			for (vector<Periodical>::iterator itr = circulatingPeriodicals.begin(); itr != circulatingPeriodicals.end(); itr++){
				if (itr->getBarcode() == aBarcode){
					per = *itr;
					break;
				}
			}

			for (vector<Employee>::iterator itr = employees.begin(); itr != employees.end(); itr++){
				if (itr->getEmpname() == name){
					emp = *itr;
					break;
				}
			}

			if (action == "RETURN"){
				ReturnToLibrary(per, emp, currentDate);
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


void Library::ArchivePeriodical(Periodical& p) // Evan
{
	for (vector<Periodical>::iterator itr = circulatingPeriodicals.begin(); itr != circulatingPeriodicals.end(); itr++){
		if (*itr == p){
			circulatingPeriodicals.erase(itr);
		}
		else {
			throw::exception("The periodical was not circulating");
		}
	}

	archivedPeriodicals.push_back(p);
}

/*
void Library::removeArchivedPeriodical(Periodical& p) // Evan
{
	archivedPeriodicals.erase(p.getBarcode());
}

void Library::removeCirculatingPeriodical(Periodical& p) // Evan
{
    circulatingPeriodicals.erase(p.getBarcode());
}
*/