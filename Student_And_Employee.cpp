#include "Student_And_ Employee.h"


Student::Student(const std::string& i_id) : id(i_id) {}

std::string Student::get_id() const
{
	return id;
}

Student::~Student() {}

Employee::Employee(const std::string& i_id) : id(i_id) {}

std::string Employee::get_id() const
{
	return id;
}

Employee::~Employee() {}
