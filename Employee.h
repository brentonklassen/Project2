/*
Employee class header
*/

#ifndef __EMPLOYEE_H__
#define __EMPLOYEE_H__
#include <string>
#include <iostream>
#include <queue>
#include <set>
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

	//argument constructor
	Employee(int lateDays, string aName, Date aVacStart, Date aVacEnd, int aWaitTime, set<string> bookSet)
		: lateDays(lateDays), empname(aName), vacationStart(aVacStart), vacationEnd(aVacEnd), waiting_time(aWaitTime), books(bookSet){}

	//copy constructor
	Employee(const Employee& e) : lateDays(e.lateDays), empname(e.empname),
		vacationStart(e.vacationStart), vacationEnd(e.vacationEnd), waiting_time(e.waiting_time), books(e.books) {}


	void setVacationStart(const Date& d) { vacationStart = d; }
	void setVacationEnd(const Date& d) { vacationEnd = d; }
	void setWaitingTime(const int& t) { waiting_time = t; }
	void addBookToList(string& b) { books.insert(b); }
	string getTopBookFromList() { return *books.begin(); }
	void removeBookFromList(string& b) {
		books.erase(b);
	}

	//getters
	Date getVacationStart() const { return vacationStart; }
	Date getVacationEnd() const { return vacationEnd; }
	string getName() const { return empname; }
	int getWaitingTime() const { return waiting_time; }
	int getLateDays() const { return lateDays; }
	int getNumberOfBooks() const { return books.size(); }
    bool isLazy() const { return isALazyGuyorGal; }
    bool hasNoBooks() const { return books.empty(); }

	set<string> getBooks(){ return books; }

	bool isVacationing(Date currentDate) const{
		return currentDate > getVacationStart() && currentDate < getVacationEnd();
	}

	void updateReliability(Date currentDate, const Date& checkOutDate, const int maxCheckoutDur){
        int daysCheckedOut = currentDate - checkOutDate;
        lateDays += (daysCheckedOut - maxCheckoutDur);
	}

	bool operator ==(const Employee& other){
		return empname == other.empname;
	}

private:
	string empname;
	int lateDays;
    bool isALazyGuyorGal;
	Date vacationStart;
	Date vacationEnd;
	set<string> books;
	int waiting_time; // # of days
};

#endif