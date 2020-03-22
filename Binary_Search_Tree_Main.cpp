#include "Binary_Search_Tree.h"

int main()
{
	//check default constructor:
	BinarySearchTree mybst;

	//create a BST with data:
	mybst.insert("Hi");
	mybst.insert("Hello");
	mybst.insert("Hey");
	mybst.insert("Hola");
	

	//check copy constructor:
	BinarySearchTree mybst2(mybst);

	//check assignment operator:
	mybst = mybst2;	
	
	return 0;
}