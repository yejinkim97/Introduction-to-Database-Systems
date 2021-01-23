-- ------------------------------
-- Name: Ye Jin Kim
-- Date: Febuary 7th, 2020
-- StudID: 163291180
-- Purpose: Week 05 Lab
-- ------------------------------

-- #1
CREATE TABLE l5_movies(
	id INT PRIMARY KEY,
	title varchar(35) NOT NULL,
	year INT NOT NULL,
    director INT NOT NULL,
    score  DECIMAL(3,2),
    CONSTRAINT l5_movies_score_chk CHECK (score BETWEEN 0 AND 5)
    );
    
    CREATE TABLE l5_actors (
	id INT PRIMARY KEY,
    firstName varchar(20) NOT NULL,
    lastName varchar(30) NOT NULL
    );
    
    CREATE TABLE l5_castings (
	movieid INT PRIMARY KEY,
    actorid INT PRIMARY KEY,
    CONSTRAINT l5_castings FOREIGN KEY (movieid) REFERENCES l5_movies(id),
	CONSTRAINT l5_castings FOREIGN KEY (actorid) REFERENCES l5_actors(id)
    );
    
	CREATE TABLE l5_directors (
	id INT PRIMARY KEY,
    name varchar(20) NOT NULL,
    lastName varchar(30) NOT NULL
    );
    
-- #2
  ALTER TABLE l5_movies
		ADD CONSTRAINT l5_movies_director_fk FOREIGN KEY (director) REFERENCES l5_directors(id);
        
-- #3
 ALTER TABLE l5_movies
		ADD CONSTRAINT l5_movies_title UNIQUE (title);
        
-- #4
INSERT INTO l5_director 
	VALUES (1010,'Rob','Minkoff'),
		(1020, 'Bill','Condon'),
        (1050, 'Josh','Cooley'),
        (2010,'Brad','Bird'),
        (3020,'Lake','Bell');
  
INSERT INTO l5_movies
	VALUES(100,'The Lion King',	2019,3020,3.50),
		  (200,'Beauty and the Beast',2017,1050,4.20),
		  (300,'Toy Story',4,2019,1020,4.50),
          (400,'Mission Impossible',2018,2010,5.00),
          (500,'The Secret Life of Pets',2016,1010,3.90);

-- #5
DROP table  l5_movies, l5_actors, l5_castings, l5_directors;
-- Yes, because we should not delete the parent table first

-- #6
CREATE TABLE employee2(
employeeNumber int(11) PRiMARY KEY,
lastName varchar(50),
firstName varchar(50), 
extension varchar(10),
email varchar(100), 
officeCode varchar(10), 
reportsTo int(11),
jobTitle varchar(50),
CONSTRAINT EMPLLOYEE_OFFICECODE_FK FOREIGN KEY (officeCode) REFERENCES offices(officeCode),
CONSTRAINT EMPLLOYEE_REPORT_FK FOREIGN KEY (reportsTo) REFERENCES employees(employeeNumber)
);
        
-- #7
 ALTER TABLE employee2
ADD COLUMN username  varchar(50) ;

-- #8
INSERT INTO employee2 (employeeNumber, lastName, firstName, extension, email, officeCode, reportsTo, jobTitle)
SELECT * FROM employees; 

-- #9
UPDATE employee2 SET firstName = 'YeJin',lastName = 'Kim'
WHERE employeeNumber = 1002;

-- #10
UPDATE employee2 SET username = LOWER(CONCAT(lEFT(firstName,1),lastName))
WHERE firstName is not null 
AND lastName is not null;

-- #11
DELETE FROM employee2 WHERE officeCode = 4;

-- #12
DROP TABLE employee2;