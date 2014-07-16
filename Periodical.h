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
    Periodical() : CheckedOut(false), name(""), barcode(), checkOutDate(Date()), archiveDate(Date()), maxCheckoutDuration(7) {}

    //two-argument constructor
    Periodical(string aName, string aBarCode)
        : CheckedOut(false), name(aName), barcode(aBarCode), checkOutDate(Date()), archiveDate(Date()), maxCheckoutDuration(7) {}

    //full-argument constructor
    Periodical(bool checkedOut, std::string aName, string aBarcode, Date theOutDate, Date theArchiveDate, int theMaxDur)
        : CheckedOut(checkedOut), name(aName), barcode(aBarcode), checkOutDate(theOutDate), maxCheckoutDuration(theMaxDur)
    {
    }

    //copy constructor
    Periodical(const Periodical& p) : CheckedOut(p.CheckedOut), name(p.name), barcode(p.barcode), checkOutDate(p.checkOutDate),
        archiveDate(p.archiveDate), maxCheckoutDuration(p.maxCheckoutDuration) {}

    //setters
    void setCheckedOut(bool isItChecked) { CheckedOut = isItChecked; }
    void setCheckOutDate(Date& aDate) { checkOutDate = aDate; }
    void setArchiveDate(Date& aDate) { archiveDate = aDate; }
    void setMaxCheckoutDur(int& dur) { maxCheckoutDuration = dur; }

    //getters
    Date getCheckOutDate() const { return checkOutDate; }
    Date getReturnDate() const { return archiveDate; }
    string getName() const { return name; }
    bool isCheckedOut() { return CheckedOut; }
    string getBarcode() const { return barcode; }
    int getMaxCheckoutDuration() const { return maxCheckoutDuration; }


    bool operator ==(const Periodical& other){
        return barcode == other.barcode;
    }

    bool morePeopleInQueue(){ return !empQueue.empty(); }

	// returns bool indicating whether or not it could pass to another person
    bool passToNextEmployee(Date currentDate, map<string,Employee>& empMap){

        stack<Employee> vacationingEmployees;
        Employee nextEmployee;

        if (empQueue.empty()){
            throw::exception("Employee queue is empty.");
        }
        else {

            while (!empQueue.empty() && empQueue.top().isVacationing(currentDate)){
                vacationingEmployees.push(empQueue.top());
                empQueue.pop();
            }
            checkOutDate = currentDate;
            if (!empQueue.empty()){
                cout << empQueue.top().getName() << " got " << name << endl;
                nextEmployee = empQueue.top();
                empQueue.pop();
            }
            else {
                //all employees in queue are on vacation
				while (!vacationingEmployees.empty()){
					empMap[vacationingEmployees.top().getName()].removeBookFromList(barcode); // since they were on vacation the whole time the book was circulating, they don't get a chance to read it
					vacationingEmployees.pop();
				}
				return false;
            }

            while (!vacationingEmployees.empty()){
                empQueue.push(vacationingEmployees.top());
                vacationingEmployees.pop();
            }
            empMap[nextEmployee.getName()].addBookToList(barcode);
        }
		return true;
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
    bool CheckedOut;
    Date checkOutDate;
    Date archiveDate;
    int maxCheckoutDuration;
    priority_queue<Employee, vector<const Employee>, EmployeeComparer> empQueue;
};

#endif