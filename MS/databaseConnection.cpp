/*
Name: Yuvraj Parmar, Ye Jin Kim, Huyen Phan
Student ID: 121391171, 163291180, 1284407194
Class: DBS211
Group#: 5
Milestone 1
*/

#include <mysql.h>
#include <iostream>
#include <cstring>

using namespace std;


void display(MYSQL_ROW row , MYSQL_RES* res) {

    while (row != nullptr) {

        cout << "ID: ";
        cout.width(14);
        cout.setf(ios::left);
        cout << row[0];
        cout << "Name:";
        cout.width(18);
        cout.setf(ios::left);
        cout << row[1];
        cout << " Phone: ";
        cout.width(17);
        cout.setf(ios::left);
        cout << row[2];
        cout << " Extention: " << row[3] << endl;
        row = mysql_fetch_row(res);
    }
}

int main() {
    
    MYSQL* conn;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "mymysql.senecacollege.ca", "db_yparmar", "w2kN%{^8^^", "db_yparmar", 3306, nullptr, 0);

    string query = "select employeeNumber, CONCAT(firstName, ' ', lastName), phone, extension from employees e left join offices o on e.officeCode = o.officecode where e.officeCode = 1;";
    const char* q = query.c_str();
    
    mysql_query(conn, q);
    
    MYSQL_RES* res;
    res = mysql_store_result(conn);
    
    MYSQL_ROW row = mysql_fetch_row(res);
 
    cout << "**************** Employee Report ****************" << endl;

    cout << "Employee Report:" << endl;
    
    display(row, res);

    query = "select distinct e.employeeNumber,CONCAT(e.firstName, ' ', e.lastName), o.phone, e.extension from employees e inner join employees c on e.employeeNumber = c.reportsTo left join offices o on e.officeCode = o.officeCode;";
    q = query.c_str();
    mysql_query(conn, q);
    res = mysql_store_result(conn);
    

    row = mysql_fetch_row(res);
    cout << "Manager Report:" << endl;
    
    display(row, res);


    mysql_close(conn);
    
    return 0;
}