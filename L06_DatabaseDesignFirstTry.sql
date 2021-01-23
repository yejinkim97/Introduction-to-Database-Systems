-- ------------------------------
-- Name: Ye Jin Kim
-- Date: Febuary 14th, 2020
-- StudID: 163291180
-- Purpose: Week 06 Lab
-- ------------------------------

/*
In this lab you are going to design and create a mini database.  This will not be a full database,
but a small part of a larger database.  You will be creating a data base to help the professor keep track 
of your marks in this class.  

You will need to tracks students (Just basic information for the class only).  You will need to track the 
markable items (tests, labs, quizzes, assignments) and their percentage of the final mark, then record each students mark 
for each markable item.  

Tasks
1) Create the appropriate tables, fields, field types and sizes, and required constraints (your choice)
2) Insert your student information and that of 3 of your classmates. (Fake data is okay)
3) Insert marks for all markable items for those 4 students
4) BONUS ONLY: Create a Query (Select) that calculates the final mark for each student
5) BONUS ONLY: Create a View that stores the above query.

HINTS: 
1) Use the course outline for the mark breakdown
2) draw the tables with circles and lines on paper to determine their relationships
3) Use your experience so far as to what fields are required.
4) ASK QUESTIONS 
*/

 CREATE TABLE students (
	stdId INT PRIMARY KEY,
    firstName varchar(20) NOT NULL,
    lastName varchar(30) NOT NULL,
	email varchar(50)
    );
    
INSERT INTO students VALUES
---------------------------------------------


CREATE TABLE mark(
madeup char primary key,
markId	tinyint NOT NULL,
stdId INT NOT NULL,	
grade	DEC(5,3),
CONSTRAINT mrk_fk FOREIGN KEY(markId) REFERENCES juncT(markId),
CONSTRAINT std_fk FOREIGN KEY(stdId) REFERENCES juncT(stdId)
);
INSERT INTO mark VALUES
('a',1, 163291180, 2.5),
('b',2, 163291180, 2.5),
('c',1, 100897281, 2.5),
('d',2, 100897281, 3.0),
('e',1, 286138492, 3.0),
('f',2, 286138492, 3.0),
('g',1, 187329362, 3.5),
('h',2, 187329362, 3.5);

CREATE TABLE juncT(
madeup char primary key,
markId tinyint NOT NULL,
stdId INT NOT NULL,
CONSTRAINT id_fk FOREIGN KEY(stdId) REFERENCES students(stdId),
CONSTRAINT mrk_fk FOREIGN KEY(markId) REFERENCES test(markId)
);
INSERT INTO juncT VALUES
('a',1,163291180),
('b',1,163291180),
('c',1,100897281);

CREATE TABLE test(
markId tinyint NOT NULL,
markName varchar(10) NOT NULL );

INSERT INTO test VALUES
(1,'quiz1'),
(2,'midterm'),
(3,'assignment1');

