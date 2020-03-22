#include <iostream>
#include <string>
#include "Less_More_BinarySearch.h"

int main()
{
	std::vector<int> vi = { 1, 3, 5,10,19 };
	std::vector<double> vd = { 3.14,2.7,2.54, 0.19 };
	more<double> dd;
	std::vector<std::string> vs = { "one", "two","zero" };
	std::string two = "two";
	std::cout << binary_search(vi, 0, vi.size(), 10);
	std::cout << binary_search(vd, 0, vd.size(), 2.7, dd);
	std::cout << binary_search(vs, 0, vs.size(), two);

	//this code should output: 311
	return 0;
}

