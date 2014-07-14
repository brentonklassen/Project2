/*
Periodical class header
*/

#ifndef __PERIODICAL_H__
#define __PERIODICAL_H__
#include <map>
#include <queue>
#include <stack>
#include <iostream>
#include "Date.h"
#include "Employee.h"

class Periodical { //implemented by Jordan
public:
	//default constructor
	Periodical() : isCheckedOut(false), name(""), barcode(), checkOutDate(Date()), archiveDate(Date()), maxCheckoutDuration(7) {}

	//two-argument constructor
	Periodical(string aName, string aBarCode)
		: isCheckedOut(false), name(aName), barcode(aBarCode), checkOutDate(Date()), archiveDate(Date()), maxCheckoutDuration(7) {}

	//full-argument constructor
	Periodical(bool checkedOut, std::string aName, string aBarcode, Date theOutDate, Date theArchiveDate, int theMaxDur)
		: isCheckedOut(checkedOut), name(aName), barcode(aBarcode), checkOutDate(theOutDate), maxCheckoutDuration(theMaxDur)
	{
	}

	//copy constructor
	Periodical(const Periodical& p) : isCheckedOut(p.isCheckedOut), name(p.name), barcode(p.barcode), checkOutDate(p.checkOutDate),
		archiveDate(p.archiveDate), maxCheckoutDuration(p.maxCheckoutDuration) {}

	//setters
	void setCheckedOut(bool isItChecked) { isCheckedOut = isItChecked; }
	void setCheckOutDate(Date& aDate) { checkOutDate = aDate; }
    void setArchiveDate(Date& aDate) { archiveDate = aDate; }
	void setMaxCheckoutDur(int& dur) { maxCheckoutDuration = dur; }

	//getters
	Date getCheckOutDate() const { return checkOutDate; }
	Date getReturnDate() const { return archiveDate; }
	string getName() const { return name; }
	bool getCheckOutStatus() { return isCheckedOut; }
	string getBarcode() const { return barcode; }
    int getMaxCheckoutDuration() const { return maxCheckoutDuration; }


	bool operator ==(const Periodical& other){
		return barcode == other.barcode;
	}

	bool morePeopleInQueue(){ return !empQueue.empty(); }

	Employee passToNextEmployee(Date currentDate){

		stack<Employee> vacationingEmployees;
		Employee nextEmployee;

		if (empQueue.empty()){
			throw::exception("Employee queue is empty.");
		}
		else {
			while (empQueue.top().isVacationing(currentDate)){
				vacationingEmployees.push(empQueue.top());
				empQueue.pop();
			}

			if (empQueue.empty()){
				throw::exception("All employees were on vacation");
			}
			else {
				checkOutDate = currentDate;
				// should we record who currently has the book?

				cout << empQueue.top().getName() << " got " << name << endl;
				nextEmployee = empQueue.top();
				empQueue.pop();
			}

			while (!vacationingEmployees.empty()){
				empQueue.push(vacationingEmployees.top());
				vacationingEmployees.pop();
			}
			nextEmployee.addBookToList(barcode);
			return nextEmployee;
		}
	}


	struct EmployeeComparer{ //Brenton
		bool operator()(const Employee emp1, const Employee emp2){
			int emp1priority = emp1.getWaitingTime() - emp1.getLateDays() - emp1.getNumberOfBooks();
			int emp2priority = emp2.getWaitingTime() - emp2.getLateDays() - emp2.getNumberOfBooks();
			return emp1priority < emp2priority;
		}
	};

	void Periodical::generateEmpQueue(map<string,Employee>& employeeMap)
	{
		for (map<string, Employee>::iterator itr = employeeMap.begin(); itr != employeeMap.end(); itr++){
			empQueue.push(itr->second);
		}
	}


private:
	string name;
	string barcode;
	bool isCheckedOut;
	Date checkOutDate;
    Date archiveDate;
	int maxCheckoutDuration;
	priority_queue<Employee, vector<const Employee>, EmployeeComparer> empQueue;
};

#endif