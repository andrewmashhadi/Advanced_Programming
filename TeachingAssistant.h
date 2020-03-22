#ifndef TEACHINGASSISTANT_H
#define TEACHINGASSISTANT_H
#include "Student_And_ Employee.h"

class TeachingAssistant: public Student, public Employee
{

public:

	/* Constuctor with parameters for this TeachingAssistant class. The parameters will be used as arguments 
	for constructing and assigning the inhereited class's members.
	@param s_id will be used as an argument in Student's constructor. This sets the id in Student to s_id.
	@param e_id will be used as an argument in Employee's constructor. This sets the id in Employee to e_id.*/
	TeachingAssistant(const std::string& s_id, const std::string& e_id);

	/* Redefining the get_id member funtion to eliminate ambiguity from the inherited get_id functions from 
	both the base class's Student and Employee.
	@return the employee id. That is, a copy of the id member variable from the Employee base class.
	*/
	std::string get_id() const;

	/* TeachingAssistant member function is placed to eliminate ambiguity from the inherited get_id functions from
	both the base class's, Student and Employee.
	@return the student id. That is, a copy of the id member variable from the Student base class.
	*/
	std::string student_id() const;

};

#endif
