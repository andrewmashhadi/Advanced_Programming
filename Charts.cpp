#include "Charts.h"

Chart::Iterator::Iterator() : position(0), in_chart(nullptr) { };

Chart::Iterator::Iterator(size_t p, const Chart* c) : position(p), in_chart(c) { };

Chart::Iterator& Chart::Iterator::operator++()		
{
	++position;
	return *this;
}

Chart::Iterator Chart::Iterator::operator++(int dummy)		
{
	Iterator temp = *this;
	++position;
	return temp;
}

bool Chart::Iterator::operator==(const Iterator& right) const
{
	return position == right.position;
}

bool Chart::Iterator::operator!=(const Iterator& right) const
{
	return position != right.position;
}

int Chart::Iterator::operator*() const
{
	return (in_chart->data)[position];
}

void Chart::add(int input_val)
{
	data.push_back(input_val);
}

Chart::Iterator Chart::begin() const
{
	return Iterator(0, this);
}

Chart::Iterator Chart::end() const
{
	return Iterator(data.size(), this);
}

void Chart::draw() const
{
	std::cout << "cannot draw base chart";
}

Chart::~Chart() {}

void BarChart::draw() const
{
	/* Derived classes inherit the nested classes from the base class. No 
	scope resolution operators needed here.
	*/

	/* Loop to display each integer (and a corresponding bar) in the base class's member variable, data. */
	for (Iterator it = begin(); it != end(); ++it)
	{
		std::cout << *it << " ";
		int i = 0;
		/* Displays the corresponding bar for the integer recently displayed by the deferenced Iterator object above.*/
		while (i < *it)
		{
			std::cout << "*";
			++i;
		}
		std::cout << std::endl;
	}

}
