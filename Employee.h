/*
Employee class header
*/

#ifndef __EMPLOYEE_H__
#define __EMPLOYEE_H__
#include <string>
#include <iostream>
#include <vector>
#include "Periodical.h"
#include "Date.h"
using namespace std;

class Employee { //implemented by Jordan
public:
	//default constructor
	Employee() : lateDays(), empname(), vacationStart(Date()), vacationEnd(Date()), waiting_time() {}

	//argument constructor
	Employee(int lateDays, string aName, Date aVacStart, Date aVacEnd, int aWaitTime)
		: lateDays(lateDays), empname(aName), vacationStart(aVacStart), vacationEnd(aVacEnd), waiting_time(aWaitTime){}

	//copy constructor
	Employee(const Employee& e) : lateDays(e.lateDays), empname(e.empname),
		vacationStart(e.vacationStart), vacationEnd(e.vacationEnd), waiting_time(e.waiting_time), books(e.books) {}


	void setVacationStart(const Date& d) { vacationStart = d; }
	void setVacationEnd(const Date& d) { vacationEnd = d; }
	void setWaitingTime(const int& t) { waiting_time = t; }
	void addBookToList(string& b) { books.push_back(b); }
	void removeBookFromList(string& b) {
		//Jordan
		vector<string>::iterator iter;
		for (iter = books.begin(); iter != books.end(); iter++)
		{
			if (*iter == b)
			{
				books.erase(iter);
				return;
			}
		}
		throw::exception("The periodical is not in this employees periodical list.\n");
	}

	//getters
	Date getVacationStart() const { return vacationStart; }
	Date getVacationEnd() const { return vacationEnd; }
	string getName() const { return empname; }
	int getWaitingTime() const { return waiting_time; }
	int getLateDays() const { return lateDays; }
	int getNumberOfBooks() const { return books.size(); }

	bool isVacationing(Date currentDate) const{
		return currentDate > getVacationStart() && currentDate < getVacationEnd();
	}

	void updateReliability(Date currentDate, Date dueDate){
		lateDays += dueDate - currentDate;
	}

private:
	string empname;
	int lateDays;
	Date vacationStart;
	Date vacationEnd;
	vector<string> books;
	int waiting_time; // # of days
};

#endif