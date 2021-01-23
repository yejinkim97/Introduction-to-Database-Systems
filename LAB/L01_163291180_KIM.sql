-- ------------------------
-- Name: Ye Jin Kim
-- Date: January 10, 2020
-- Student ID: 163291180
-- Purpose: Lab 01
-- ------------------------

-- Q1 --
/* 8 tables: customers, employees, offices, orderdetails, orders, payments, productlines, products */

-- Q2 --
/* 122 rows */

-- Q3 --
SELECT * FROM db_yjkim33.customers;
/* Results are the same */

-- Q4 --
/* 13 columns: customerNumber, customerName, contactLastName, contactFirstName,
phone, addressLine1, addressLine2, city, state, postalCode, country, salesRepEmployeeNumber, creditLimit
*/

-- Q5 --
/*  customerNumber- 103, customerName- Atelier graphique, contactLastName- Schmitt, contactFirstName- Carine ,
phone- 40.32.2555, addressLine1- 54, rue Royale, addressLine2- null, city- Nantes, state- null, 
postalCode- 44000, country- France, salesRepEmployeeNumber- 1370, creditLimit- 21000.00
*/

-- Q6 --
/* Table Name	Rows	Columns
	employees	23		8
    offices 	7		9
    orderdetails 1000	5
    orders		326		7
    payments 	273		4
    productlines 7		4
    products	110		9
    */
    
    -- Q7 --
    /* Column Name			Column Type
		employeeNumber		INT(11)
        lastName			VARCHAR(50)
		firstName			VARCHAR(50)
        extension           VARCHAR(10)
        email               VARCHAR(100)
        officeCode          VARCHAR(10)
        reportsTo           INT(11)
        jobTitle            VARCHAR(50)
    */
    
    -- Q8 --
    /*
    officeCode	varchar(10)	NO	PRI		
	city	varchar(50)	NO			
	phone	varchar(50)	NO			
	addressLine1	varchar(50)	NO			
	addressLine2	varchar(50)	YES			
	state	varchar(50)	YES			
	country	varchar(50)	NO			
	postalCode	varchar(15)	NO			
	territory	varchar(10)	NO			
	*/
    
    -- Q9 --
    /* It is showing the two results which are employees information and customer information which is 
    sorted by contactlastname in an alphabetical order.
    */

