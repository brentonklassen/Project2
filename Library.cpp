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
		string line, empName, startVacation, endVacation;
		int lateDays, theWaitingTime;

		while (getline(fin, line))
		{
			String_Tokenizer st(line, ",");
			empName = trim(st.next_token());
			lateDays = stoi(trim(st.next_token()));
			theWaitingTime = stoi(trim(st.next_token()));
			startVacation = trim(st.next_token());
			endVacation = trim(st.next_token());
			employees[empName] = Employee(lateDays, empName, Date(startVacation, DateFormat::US), Date(endVacation, DateFormat::US), theWaitingTime);
		}
	}
	fin.close();
}

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
		string line, name, action, barcode;
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
			barcode = trim(st.next_token());
			Periodical per = circulatingPeriodicals[barcode];
			Employee emp = employees[name];

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
	for (map<string,Periodical>::iterator itr = circulatingPeriodicals.begin(); itr != circulatingPeriodicals.end(); itr++){
		itr->second.generateEmpQueue(employees);
		Employee firstEmployee = itr->second.passToNextEmployee(currentDate);
		employees[firstEmployee.getEmpname()] = firstEmployee;  // this updates the employee map with the new employee information
	}
}


void Library::ArchivePeriodical(Periodical& p) // Evan
{
	circulatingPeriodicals.erase(p.getBarcode());
	archivedPeriodicals[p.getBarcode()] = p;
}
