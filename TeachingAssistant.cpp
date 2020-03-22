#include "TeachingAssistant.h"

TeachingAssistant::TeachingAssistant(const std::string& s_id, const std::string& e_id) : Student(s_id), 
Employee(e_id) {}

std::string TeachingAssistant::get_id() const
{
	return Employee::get_id();
}

std::string TeachingAssistant::student_id() const
{
	return Student::get_id();
}