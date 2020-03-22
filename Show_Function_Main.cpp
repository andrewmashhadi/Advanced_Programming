/*
Andrew Mashhadi
ID: 905092387
PIC 10C
Programming Homework #5

Honor Pledge:

I pledge that I have neither given nor received
unauthorized assistance on this assignment.
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;		

/* 
Function that counts the number of times a word of a given size or larger occurs in a given vector. 
It also prints the words that are larger than or equal to this size to the console. 
@param v is a vector of strings containing the words we want to check the sizes of. Note, we cannot pass 
by const reference here because partition actually changes the ordering of the elements in v.
@param min_length is the minimum length of a word that we are examining the vector of strings for.
@return void.
*/
void show(vector<string>& v, size_t min_length)		
{
	auto f = [min_length](const string& a) {return a.length() >= min_length; };

	vector<string>::iterator partition_break = partition(v.begin(), v.end(), f);
	int num_words = count_if(v.begin(), v.end(), f);		

	cout << "\n" << num_words << " words found with size greater than/equal to " << min_length << " and they are:\n";

	/* Print the first part of the partitioned vector. This should print all of the words in v with length 
	greater than or equal to the value of min_length.
	*/
	for (vector<string>::iterator it = v.begin(); it != partition_break; ++it)
	{
		cout << *it << " ";
	}

}


int main()
{
	vector <string> words;
    string word;
	int word_length;

	cout << endl << "words = ";
	getline(cin, word);
	stringstream sentence(word);
	
	while (sentence >> word)
	{ words.push_back(word); }

	cout << endl << "word length = ";
	cin >> word_length;

	show(words, word_length);

	return 0;
}

