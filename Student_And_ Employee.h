/*
Andrew Mashhadi
ID: 905092387
PIC 10C
Programming Homework #3

Honor Pledge:

I pledge that I have neither given nor received
unauthorized assistance on this assignment.
*/

#ifndef STUDENT_AND_EMPLOYEE_H
#define STUDENT_AND_EMPLOYEE_H
#include <string>


class Student
{

private:
	std::string id;						

public:

	/* Constructor with parameters for Student class. Assigns the id member variable to the parameter.
	@param i_id is a string parameter meant to be assigned to the string member variable id. 
	*/
	Student(const std::string& i_id);	

	/* Accessor member function that returns a copy of the id member varible.
	@return the id member variable of this object.
	*/
	std::string get_id() const;		

	/* Student class destructor. We must declare it as virtual here because another class will inhereit from
	this Student class (this class will be made a base class). 
	*/
	virtual ~Student();						

};

class Employee
{

private:
	std::string id;							

public:

	/* Constructor with parameters for Employee class. Assigns the id member variable to the parameter.
	@param i_id is a string parameter meant to be assigned to the string member variable id.
	*/
	Employee(const std::string& i_id);

	/* Accessor member function that returns a copy of the id member varible.
	@return the id member variable of this object.
	*/
	std::string get_id() const;	

	/* Employee class destructor. We must declare it as virtual here because another class will inhereit from
	this Employee class (this class will be made a base class). 
	*/
	virtual ~Employee();				
};


#endif
