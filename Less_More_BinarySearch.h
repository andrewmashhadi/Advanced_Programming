/*
Andrew Mashhadi
ID: 905092387
PIC 10C
Programming Homework #4

Honor Pledge:

I pledge that I have neither given nor received
unauthorized assistance on this assignment.
*/

#ifndef LESS_MORE_BINARYSEARCH_H
#define LESS_MORE_BINARYSEARCH_H
#include <vector>


/* A class to make comparisons between two type T objects/variables. The following class
assumes that type T has a properly defined less than operator, <.
*/
template <typename T>
class less
{
public:
	/* Overloading the function call operator. Used to compare the two parameters by using the less than 
	operator.
	@param x is of type T, meant to be compared to parameter y
	@param y is of type T, meant to be compared to parameter x
	@return true if x is "less than" y according to the defined less than operator, <, and false otherwise
	*/
	bool operator()(const T& x, const T& y) const
	{
		return x < y;
	}
};


/* A class to make comparisons between two type T objects/variables. The following class
assumes that type T has a properly defined greater than operator, >.
*/
template <typename T>
class more
{
public:
	/* Overloading the function call operator. Used to compare the two parametersby using the greater than
	operator.
	@param x is of type T, meant to be compared to parameter y
	@param y is of type T, meant to be compared to parameter x
	@return true if x is "greater than" y according to the defined greater than operator, >, and false otherwise
	*/
	bool operator()(const T& x, const T& y) const
	{
		return x > y;
	}
};

/* A binary search function that searches a vector contianing elements of type T. Searches the vector using 
the type of the last argument, where the default type is set to less<T>.
@param v is the vector we are searching
@param from is the index we begin searching from in our vector
@param to is the ending index we finish searching at in our vector
@param value is the value we are searching for in our vector
@param cmp is the function object defining our method of comparison in its overloaded function call
@return the index of the vector corresponding to the element that is equivalent to value and returns -1 if not found
*/
template <typename T, typename CMP = less<T>>	 
int binary_search(const std::vector<T>& v, int from, int to, T value, const CMP& cmp = CMP())
{
	// If we have finished searching the vector v for value, return -1.
	if (from > to)	
		return -1;

	int mid = (to + from) / 2;

	/* If the comparison method defined in type CMP returns true with the first argument of v[mid] and the 
	second argument of value, search the top half the interval we are in, in vector v. Otherwise if the 
	comparison method defined in type CMP returns true with the first argument of value and the 
	second argument of v[mid], search the bottom half the interval we are in, in vector v. Otherwise we found 
	the element of v that corresponds to value, so we return its index.
	*/
	if (cmp(v[mid], value))
	{
		return binary_search(v, mid + 1, to, value, cmp);
	}
	else if (cmp(value, v[mid]))
	{
		return binary_search(v, from, mid - 1, value, cmp);
	}
	else
		return mid;					
}

#endif
