/*
Andrew Mashhadi
ID: 905092387
PIC 10C
Programming Homework #1

Honor Pledge:

I pledge that I have neither given nor received
unauthorized assistance on this assignment.
*/

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <iostream>
#include <string>


class BinarySearchTree;

class TreeNode
{

private:
	std::string data;
	TreeNode* left;
	TreeNode* right;

public:
	/* Constructor with parameters for TreeNode class. This initializes the data to a value and the left and right
	pointers to nullptr.
	@param d is the integer value that data will be set to.
	*/
	TreeNode(const std::string& d);

	/* This is the TreeNode member function that helps insert a new node into a BinarySearchTree object using
	recursion. Called usually from a BinarySearchTree object, this function finds the proper location for a new TreeNode
	in the BinarySearchTree object (using the BinarySearchTree properties). It deletes the node if a node with the same
	data already exists.
	@param newNode is the newly created TreeNode that we want to insert into the BinarySearchTree object that called this
	funciton from its own insert function.
	@return void
	*/
	void insert_node(TreeNode* newNode);

	/* This TreeNode member function is called on by the BinarySearchTree's print function. It recursively displays data
	in each attached TreeNode in ascending order.
	@return void
	*/
	void print_nodes() const;

	friend class BinarySearchTree;

};

class BinarySearchTree
{

private:
	TreeNode* root;

	/* This function will help perform deep copies for the copy constructor and the overloaded assignment operator. It 
	recursively copies the data and structure of another BinarySearchTree when the nodeptr paramater is pointing to the 
	top of the other BinarySearchTree. It uses a preorder copy to preserve the structure of the other BinarySearchTree.
	@param nodeptr is pointer to a TreeNode that should orginally point to the root of the other BinarySearchTree that 
	we would like to copy.
	@return a TreeNode pointer that is pointing to the new copied root.
	*/
	TreeNode* copy(const TreeNode* nodeptr);

	/* This function will help the destructor perform the task of deleting all of the dynamically allocated TreeNodes
	associated with this BinarySearchTree by using recursion.
	@param nodeptr is a TreeNode pointer pointing to the root of this BinarySearchTree.
	@return void
	*/
	void kill_tree(TreeNode* nodeptr);

public:
	/* Default constructor for BinarySearchTree class. This intializes the root to nullptr. 
	*/
	BinarySearchTree();

	/* Copy constructor for the BinarySearchTree class. If the right BinarySearchTree isn't empty, we make a 
	deep copy of it by calling the copy member function.
	@param right is the BinarySearchTree we would like to make a deep copy of.
	*/
	BinarySearchTree(const BinarySearchTree& right);

	/* Creates a new TreeNode with new data, then either inserts the first TreeNode into the tree or calls the
	insert_node function to recursively find the correct location in the tree for the new TreeNode to be inserted.
	@param new_dat is the data that the newly created TreeNode will contain.
	@return void.
	*/
	void insert(const std::string& new_dat);

	/* This function properly erases (and therefore deletes) a TreeNode from this BinarySearchTree object without
	altering the correct BinarySearchTree structure.
	@param r_dat is the data in the TreeNode that we want to erase (and delete) properly.
	@return void.
	*/
	void erase(const std::string& r_dat);

	/* This member function is meant to display all of the data held in this BinarySearchTree structure by 
	calling the root's print_nodes recursive function. Displays in order.
	@return void
	*/
	void print() const;

	/* This member function overloads the assignment operator between two BinarySearchTrees. We first destruct
	our current BinarySearchTree properly by calling the recusive kill_tree function, then if the right 
	BinarySearchTree has data, we make a deep copy of it by calling copy. 
	@param the BinarySearchTree we would like to make a deep copy of.
	@return reference to this BinarySearchTree incase we have a chain of assignments (i.e. bst1 = bst2 = bst3)
	*/
	BinarySearchTree& operator=(const BinarySearchTree& right);

	/* Destructor for BinarySearchTree class. Properly deletes all of the dynamically allocated TreeNodes by calling
	the kill_tree function with the root as the argument. That call will cause the BinarySearchTree object to be
	properly destructed so we have no memory leaks.
	*/
	~BinarySearchTree();

};

#endif