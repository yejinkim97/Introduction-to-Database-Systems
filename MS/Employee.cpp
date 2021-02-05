// DBS_Milestone2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/* Name: Yuvraj Parmar, Ye Jin Kim, Huyen Phan
Student ID : 121391171, 163291180, 1284407194
Class : DBS211
Group# : 5
Milestone 2
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <mysql.h>
using namespace std;
struct Employee {
	int employeeNumber;
	char lastName[50];
	char firstName[50];
	char email[100];
	char phone[50];
	char extension[10];
	char reportsTo[100];
	char jobTitle[50];
	char city[50];
};
int menu(void) {
	int option;
	bool checkinput = false;
	cout << "*********************HR Menu*********************" << endl;
	cout << "1)	Find Employee" << endl;
	cout << "2)	Employees Report" << endl;
	cout << "3)	Add Employee" << endl;
	cout << "4)	Update Employee" << endl;
	cout << "5)	Remove Employee" << endl;
	cout << "0)	Exit" << endl;
	cout << "Enter an option: ";
	do {
		cin >> option;
		if (cin.fail()) {
			cout << " Invalid Integer, try again: ";
			cin.clear();
			checkinput = false;
		}
		else {
			if (option >= 0 && option < 6) {
				checkinput = true;
			}
			else {
				cout << "Invalid selection, try again: ";
				cin.clear();
				checkinput = false;
			}
		}
		cin.ignore(1000, '\n');
	} while (!checkinput);
	return option;
};
 int findEmployee(MYSQL* conn, int employeeNumber, struct Employee* emp){
	 int result=0;
	 string query = "SELECT e.employeeNumber, e.lastName, e.firstName, e.email, o.phone, e.extension, concat(e.firstName, ' ', e.lastName) 'reportsTo', e.jobTitle, o.city from employees e LEFT JOIN employees e2 ON e.reportsTo = e2.employeeNumber LEFT JOIN offices o ON e.officeCode = o.officeCode WHERE e.employeeNumber= " + to_string(employeeNumber) + ";";
	 const char* q = query.c_str();
	 int exequery;
	 exequery = mysql_query(conn, q);
	 mysql_query(conn, q);
	 if (!exequery) {
		 //query execution is successful
		 cout << "The query executed successfully with no error." << endl;
	 }
	 else {
		 //query execution is not successful
		 cout << "Error message: " << mysql_error(conn) << ": " << mysql_errno(conn) << endl;
	 }
	 MYSQL_RES* res;
		 res = mysql_store_result(conn);
	 MYSQL_ROW row;
	 row = mysql_fetch_row(res);
	 if(row != nullptr) {
			 result = 1;
			 emp->employeeNumber = employeeNumber;
			 strcpy(emp->lastName, row[1]);
			 strcpy(emp->firstName, row[2]);
			 strcpy(emp->email, row[3]);
			 strcpy(emp->phone, row[4]);
			 strcpy(emp->extension, row[5]);
			 strcpy(emp->reportsTo, row[6]);
			 strcpy(emp->jobTitle, row[7]);
			 strcpy(emp->city, row[8]);
		 }
		 else {
			 result = 0;
		 }
	 return result;
};
 void displayEmployee(MYSQL* conn, struct Employee emp) {
	 cout << "employeeNumber = " << emp.employeeNumber << endl;
	 cout << "lastName = " << emp.lastName << endl;
	 cout << "firstName = " << emp.firstName << endl;
	 cout << "email = " << emp.email << endl;
	 cout << "phone = " << emp.phone << endl;
	 cout << "extension = " << emp.extension << endl;
	 cout << "reportsTo = " << emp.reportsTo << endl;
	 cout << "jobTitle = " << emp.jobTitle << endl;
	 cout << "city = " << emp.city << endl;
 }
 void displayAllEmployees(MYSQL* conn) {
	 string query = "select  e.employeeNumber, concat(e.firstName, ' ', e.lastName) 'EmployeeName', e.email, o.phone, e.extension, concat(e2.firstName,' ' ,e2.lastName) 'Manager' from employees e LEFT JOIN employees e2 ON e.reportsTo=e2.employeeNumber LEFT JOIN offices o ON e.officeCode = o.officeCode;";
	 const char* q = query.c_str();
	 int exequery;
	 exequery = mysql_query(conn, q);
	 mysql_query(conn, q);
	 if (!exequery) {
		 //query execution is successful
		 cout << "The query executed successfully with no error." << endl;
	 }
	 else {
		 //query execution is not successful
		 cout << "Error message: " << mysql_error(conn) << ": " << mysql_errno(conn) << endl;
	 }
	 MYSQL_RES* res;
	 res = mysql_store_result(conn);
	 MYSQL_ROW row;
	 row = mysql_fetch_row(res);
	 if (row == nullptr) {
		 cout << "There is no employees?information to be displayed" << endl;
	 }
	 cout << endl;
	 cout.width(6);
	 cout.setf(ios::left);
	 cout << "E ";
	 cout.width(19);
	 cout.setf(ios::left);
	 cout << "Employee Name";
	 cout.width(36);
	 cout.setf(ios::left);
	 cout << " Email ";
	 cout.width(20);
	 cout.setf(ios::left);
	 cout << " Phone";
	 cout.width(7);
	 cout.setf(ios::left);
	 cout << " Ext ";
	 cout.width(10);
	 cout.setf(ios::left);
	 cout << "Manager" << endl << endl;
	 for (int i = 0; i < 107; i++) {
		 cout << "-";
	 }
	 cout << endl << endl;
	 while (row != nullptr) {

		 cout.width(6);
		 cout.setf(ios::left);
		 cout << row[0];

		 cout.width(20);
		 cout.setf(ios::left);
		 cout << row[1];

		 cout.width(36);
		 cout.setf(ios::left);
		 cout << row[2];

		 cout.width(20);
		 cout.setf(ios::left);
		 cout << row[3];

		 cout.width(7);
		 cout.setf(ios::left);
		 cout << row[4];

		 cout.width(10);
		 cout.setf(ios::left);
		 if (row[5] == nullptr) {
			 cout << " " << endl << endl;
		 }
		 else {
			 cout << row[5] << endl << endl;
		 }

		 row = mysql_fetch_row(res);
	 }
	 cout << endl;
 }
int main()
{

MYSQL* conn;
conn = mysql_init(0);
conn = mysql_real_connect(conn, "mymysql.senecacollege.ca", "db_yjkim33", "r%L~X47ryx", "db_yjkim33", 3306, nullptr, 0);
if (conn) {
	cout << "Successful connection to database" << endl;
}
else {
	cout << "Connection Failed" << mysql_error(conn) << endl;
}

int option;
Employee emp;
do {
	option = menu();
	switch (option) {
	case 1: {
		int employeeNumber;
		bool checkinput = false;
		cout << "Please enter employee number: ";
		do {
			cin >> employeeNumber;
			if (cin.fail()) {
				cin.clear();
				cout << "Invalid interger, please enter again: ";
			}
			else {
				checkinput = true;
			}
		} while (!checkinput);
		int found = findEmployee(conn, employeeNumber, &emp);
		if (found == 0) {
			cout << "Employee " << employeeNumber << " does not exist." << endl;
		}
		else {
			displayEmployee(conn, emp);
		}
		break;
	}
	case 2:
	{displayAllEmployees(conn);
	break; }
	case 3: 
		break;
	case 4: 
		break;
	case 5: 
		break;
	case 0:
		break;
	}
} while (option != 0);

mysql_close(conn);
return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
