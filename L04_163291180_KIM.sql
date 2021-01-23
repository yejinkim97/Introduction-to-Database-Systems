-- ------------------------------
-- Name: Ye Jin Kim
-- Date: January 31,2020
-- StudID: 163291180
-- Purpose: Week 05 Lab
-- ------------------------------

-- 1. For all employees in France, display employee number, 
-- first name, last name, city, phone number and postal code.  
SELECT employeeNumber, firstName, lastName, city, phone, postalCode
	FROM employees e JOIN offices o
    ON o.country = 'France';
    
-- 2. a) Create a view (vwCustomerOrder) to  list all orders 
-- with the following data for all customers:  
-- Customer Number, Order number, order date, product name, quantity ordered, 
-- and price for each product in every order. 
-- b) Write a statement to view the results of the view just created.

 CREATE VIEW vwCustomerOrder AS
	SELECT customerNumber, o.orderNumber, orderDate, p.productName, quantityOrdered, priceEach
    FROM orders o JOIN orderdetails od ON o.orderNumber=od.orderNumber
	JOIN products p ON od.productCode=p.productCode;
    
SELECT * FROM vwCustomerOrder ;

-- ! 3. Using the vwCustomerOrder  view, display the order information 
-- for customer number 124. Sort the output based on order number and then order line number. 
-- (Yes, I know orderLineNumber is not in the view)
SELECT * FROM vwCustomerOrder 
	WHERE(customerNumber = '124') 
	ORDER BY orderNumber, orderLineNumber;
	
-- 4. Display customer number, first name, last name, phone, and 
-- credit limits for all customers who do not have any orders.
SELECT customerNumber, contactFirstName, contactLastName, phone, creditLimit
	FROM customers 
	WHERE salesRepEmployeeNumber IS NULL;
    
-- !5. Create a view (vwEmployeeManager) to display all information of all employees and the name
--  and the last name of their managers if there is any manager that the employee reports to. 
--  Include All employees, include those whom do not report to anyone.
 CREATE VIEW vwEmployeeManager AS
	SELECT * FROM employees e JOIN employees s ON s.employeeNumber=e.reportsTo;
	-- WHERE reportsTo = ( SELECT lastName, firstName FROM employees WHERE reportsTo=employeeNumber);

      
-- 6. Modify the employee_manager view so the view returns only employee information for employees
--  who have a manager. Do not DROP and recreate the view – modify it. (Google is your friend).
SELECT * FROM vwEmployeeManager
	WHERE reportsTo IS NULL;
    
-- 7. Drop both customer_order and employee_manager views. 
DROP VIEW vwCustomerContacts, vwEmployeeManager;
