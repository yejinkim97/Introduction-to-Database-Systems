// DBS_Milestone2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/* Name: Yuvraj Parmar, Ye Jin Kim, Huyen Phan
Student ID : 121391171, 163291180, 1284407194
Class : DBS211
Group# : 5
Final Milestone
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <mysql.h>
using namespace std;
struct Employee
{
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
int menu(void)
{
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
	do
	{
		cin >> option;
		if (cin.fail())
		{
			cout << " Invalid Integer, try again: ";
			cin.clear();
			checkinput = false;
		}
		else
		{
			if (option >= 0 && option < 6)
			{
				checkinput = true;
			}
			else
			{
				cout << "Invalid selection, try again: ";
				cin.clear();
				checkinput = false;
			}
		}
		cin.ignore(1000, '\n');
	} while (!checkinput);
	return option;
};
int findEmployee(MYSQL* conn, int employeeNumber, struct Employee* emp)
{
	int result = 0;
	string query = "SELECT e.employeeNumber, e.lastName, e.firstName, e.email, o.phone, e.extension, concat(e.firstName, ' ', e.lastName) 'reportsTo', e.jobTitle, o.city from employees e LEFT JOIN employees e2 ON e.reportsTo = e2.employeeNumber LEFT JOIN offices o ON e.officeCode = o.officeCode WHERE e.employeeNumber= " + to_string(employeeNumber) + ";";
	const char* q = query.c_str();
	int exequery;
	exequery = mysql_query(conn, q);
	mysql_query(conn, q);
	if (!exequery)
	{
		//query execution is successful
		cout << "The query executed successfully with no error." << endl;
	}
	else
	{
		//query execution is not successful
		cout << "Error message: " << mysql_error(conn) << ": " << mysql_errno(conn) << endl;
	}
	MYSQL_RES* res;
	res = mysql_store_result(conn);
	MYSQL_ROW row;
	row = mysql_fetch_row(res);
	if (row != nullptr)
	{
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
	else
	{
		result = 0;
	}
	return result;
};
void displayEmployee(MYSQL* conn, struct Employee emp)
{
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
void displayAllEmployees(MYSQL* conn)
{
	string query = "select  e.employeeNumber, concat(e.firstName, ' ', e.lastName) 'EmployeeName', e.email, o.phone, e.extension, concat(e2.firstName,' ' ,e2.lastName) 'Manager' from employees e LEFT JOIN employees e2 ON e.reportsTo=e2.employeeNumber LEFT JOIN offices o ON e.officeCode = o.officeCode;";
	const char* q = query.c_str();
	int exequery;
	exequery = mysql_query(conn, q);
	mysql_query(conn, q);
	if (!exequery)
	{
		//query execution is successful
		cout << "The query executed successfully with no error." << endl;
	}
	else
	{
		//query execution is not successful
		cout << "Error message: " << mysql_error(conn) << ": " << mysql_errno(conn) << endl;
	}
	MYSQL_RES* res;
	res = mysql_store_result(conn);
	MYSQL_ROW row;
	row = mysql_fetch_row(res);
	if (row == nullptr)
	{
		cout << "There is no employees information to be displayed" << endl;
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
	for (int i = 0; i < 107; i++)
	{
		cout << "-";
	}
	cout << endl << endl;
	while (row != nullptr)
	{

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
		if (row[5] == nullptr)
		{
			cout << " " << endl << endl;
		}
		else
		{
			cout << row[5] << endl << endl;
		}

		row = mysql_fetch_row(res);
	}
	cout << endl;
}


// #3 Add Employee 
void insertEmployee(MYSQL* conn, struct Employee emp)
{
	int employeeNumber;
	bool checkinput = false;
	cout << "Please enter employee number: ";
	do
	{
		cin >> employeeNumber;
		if (cin.fail())
		{
			cin.clear();
			
			cout << "Invalid interger, please enter again: ";
		}
		else
		{
			checkinput = true;
		}
		cin.ignore(100, '\n');
	} while (!checkinput);
	int found = findEmployee(conn, employeeNumber, &emp);
	if (found == 1)
	{
		cout << "An employee with the same employee number exists." << endl;
	}
	else
	{
		emp.employeeNumber = employeeNumber;
		cout << "Last Name = ";
		cin.ignore();
		cin.getline(emp.lastName, 50);
		cout << "First Name = ";
		cin.getline(emp.firstName, 50);
		cout << "Email = ";
		cin.getline(emp.email, 100);
		cout << "extension = ";
		cin.getline(emp.extension, 10);
		cout << "Job Title = ";
		cin.getline(emp.jobTitle, 50);
		cout << "City = ";
		cin.getline(emp.city, 50);
		strcpy(emp.reportsTo, "102");
		string query =
			"INSERT INTO employees (employeeNumber, lastName, firstName, email, extension, jobTitle, officeCode) VALUES ('" + to_string(emp.employeeNumber) + "', '" + emp.lastName + "', '" + emp.firstName + "', '" + emp.email + "', '" + emp.extension + "', '" + emp.jobTitle + "', '1');";
		const char* q = query.c_str();
		int exequery;
		exequery = mysql_query(conn, q);
		mysql_query(conn, q);
		if (!exequery)
		{
			//query execution is successful
			cout << "The new employee is added successfully." << endl;
		}
		else
		{
			//query execution is not successful
			cout << "Error message: " << mysql_error(conn) << ": " << mysql_errno(conn) << endl;
		}
	}
}
// #4 Update Employee
void updateEmployee(MYSQL* conn, int employeeNumber)
{
	Employee emp = {};
	int found = findEmployee(conn, employeeNumber, &emp);
	if (found == 1)
	{
		cout << "New Extension: ";
		cin.ignore();
		cin.getline(emp.extension, 10);
		int exequery;
		string query = "UPDATE employees SET extension = '";
		query.append(emp.extension);
		query.append("' WHERE employeeNumber = " + to_string(employeeNumber) + ";");
		const char* q = query.c_str();
		exequery = mysql_query(conn, q);
		if (!exequery)
		{
			cout << "Employee " << employeeNumber << " Extension updated." << endl;
		}
		else
		{
			cout << "Error message: " << mysql_error(conn) << ":" << mysql_errno(conn) << endl;
		}
	}
	else
	{
		cout << "Employee " << employeeNumber << " dose not exit." << endl;
	}
}

// #5 Remove Employee
// Set FK field in table reportsto = null then Delete the row with employeeNumbers
void deleteEmployee(MYSQL* conn, int employeeNumber)
{
	Employee emp = {};
	if (findEmployee(conn, employeeNumber, &emp))
	{
		int exequery;
		string query1 = "update employees set reportsTo = null where reportsTo =" + to_string(employeeNumber) + "; ";
		const char* q1 = query1.c_str();
		exequery = mysql_query(conn, q1);
		if (exequery)
		{
			cout << "Error message: " << mysql_error(conn) << ":" << mysql_errno(conn) << endl;
		}
		string query2 = "DELETE FROM employees WHERE employeeNumber = " + to_string(employeeNumber) + ";";
		const char* q2 = query2.c_str();
		exequery = mysql_query(conn, q2);
		if (!exequery)
		{
			cout << " The employee " << employeeNumber << " is deleted." << endl;
		}
		else
		{
			cout << "Error message: " << mysql_error(conn) << ":" << mysql_errno(conn) << endl;
		}
	}
	else
	{
		cout << "Employee " << employeeNumber << " does not exit." << endl;
	}
}

int main()
{

	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "mymysql.senecacollege.ca", "db_hphan9", "Xtwv]7v6+R", "db_hphan9", 3306, nullptr, 0);
	if (conn)
	{
		cout << "Successful connection to database" << endl;
	}
	else
	{
		cout << "Connection Failed" << mysql_error(conn) << endl;
	}

	int option;
	Employee emp = { { 0} };
	do
	{
		option = menu();
		switch (option)
		{
		case 1: {
			int employeeNumber;
			bool checkinput = false;
			cout << "Please enter employee number: ";
			do
			{
				cin >> employeeNumber;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "Invalid interger, please enter again: ";
				}
				else
				{
					checkinput = true;
				}
			} while (!checkinput);
			int found = findEmployee(conn, employeeNumber, &emp);
			if (found == 0)
			{
				cout << "Employee " << employeeNumber << " does not exist." << endl;
			}
			else
			{
				displayEmployee(conn, emp);
			}
			break;
		}
		case 2:
		{
			displayAllEmployees(conn);
			break;
		}
		case 3:
		{
			insertEmployee(conn, emp);
			break;
		}

		case 4:
		{
			int employeeNumber;
			bool checkinput = false;
			cout << "Please enter employee number: ";
			do
			{
				cin >> employeeNumber;
				if (cin.fail())
				{
					cin.clear();
					cout << "Invalid interger, please enter again: ";
				}
				else
				{
					checkinput = true;
				}
			} while (!checkinput);
			int found = findEmployee(conn, employeeNumber, &emp);
			if (found == 0)
			{
				cout << "Employee " << employeeNumber << " does not exist." << endl;
			}
			else
			{
				updateEmployee(conn, employeeNumber);
			}
			break;
		}
		case 5:
		{
			int employeeNumber;
			bool checkinput = false;
			cout << "Please enter employee number: ";
			do
			{
				cin >> employeeNumber;
				if (cin.fail())
				{
					cin.clear();
					cout << "Invalid interger, please enter again: ";
				}
				else
				{
					checkinput = true;
				}
			} while (!checkinput);
			int found = findEmployee(conn, employeeNumber, &emp);
			if (found == 0)
			{
				cout << "Employee " << employeeNumber << " does not exist." << endl;
			}
			else
			{
				deleteEmployee(conn, employeeNumber);
			}
			break;
		}
		case 0:
			break;
		}
	} while (option != 0);

	mysql_close(conn);
	return 0;
}
