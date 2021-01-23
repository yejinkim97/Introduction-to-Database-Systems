-- ------------------------------
-- Name: Ye Jin Kim
-- Date: January 24,2020
-- StudID: 163291180
-- Purpose: Week 03 Lab
-- ------------------------------

-- Q1. Display the information of all offices.
SELECT * FROM offices;

-- Q2. Display the employee number for all employees whose office code is 1. 
SELECT employeeNumber
	FROM employees
    WHERE officeCode = 1;
    
-- Q3. Display customer number, customer name, contact first name and contact last name, and phone for all customers in Paris.
SELECT customerNumber, customerName, contactFirstName, contactLastname, phone
	FROM customers
    WHERE city = 'Paris';
    
-- Q4. Display customer number for customers who have payments.
SELECT DISTINCT customerNumber
	FROM payments;

-- Q5. List customer numbers, check number, and amount for customers whose payment amount is not in the range of $30,000 to $65,000. Sort the output by top payments amount first.
SELECT customerNumber, checkNumber, amount
	 FROM payments
     WHERE amount < 30000 OR amount >65000
     ORDER BY amount;
    
-- Q6. Display the order information for all orders that are cancelled. 
SELECT * FROM orders
	WHERE status ='Disputed';

-- Q7. Display the information of all products with string ‘co’ in their product name. (c and o can be lower or upper case).
SELECT * FROM products
	WHERE productName LIKE '%co%';

-- Q8. Display all customers whose contact first name starts with letter s (both lowercase and uppercase) and includes letter e (both lowercase and uppercase).
SELECT * FROM customers
	WHERE contactFirstName LIKE 's%' AND contactFirstName LIKE '%e%';