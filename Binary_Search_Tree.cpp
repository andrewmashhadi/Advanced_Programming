#include "Binary_Search_Tree.h"


TreeNode::TreeNode(const std::string& d) : data(d), left(nullptr), right(nullptr) { }

void TreeNode::insert_node(TreeNode* newNode)
{
	/* If the new TreeNode's data is less than this TreeNode's data, move to the left child.
	Otherwise if the new TreeNode's data is greater than this TreeNode's data, move to the right child.
	Otherwise the new TreeNode's data is exactly the same as the data from a previously inserted TreeNode.
	So we delete the new TreeNode.
	*/
	if (newNode->data < data)
	{
		if (this->left == nullptr)
			left = newNode;
		else
			left->insert_node(newNode);
	}
	else if (newNode->data > data)
	{
		if (this->right == nullptr)
			right = newNode;
		else
			right->insert_node(newNode);
	}
	else
	{
		delete newNode;
	}

}

void TreeNode::print_nodes() const
{
	// If there is a left TreeNode connected to this TreeNode, move to it before printing data.
	if (left != nullptr)
		left->print_nodes();
	std::cout << data << std::endl;
	// If there is a right TreeNode connected to this TreeNode, move to it to print its data eventually.
	if (right != nullptr)
		right->print_nodes();
}

BinarySearchTree::BinarySearchTree() : root(nullptr) { }

BinarySearchTree::BinarySearchTree(const BinarySearchTree& right):root(nullptr)	
{
	// If the right BinarySearchTree has a TreeNode with data in it, make a deep copy of it. 
	if (right.root != nullptr)
		root = copy(right.root);
}

TreeNode* BinarySearchTree::copy(const TreeNode* nodeptr)	
{
	TreeNode* newnode = new TreeNode(nodeptr->data);	
	/* If the TreeNode pointed to by this TreeNode's left TreeNode pointer exists and contains more 
	data, copy it too.
	*/
	if (nodeptr->left != nullptr)								
		newnode->left = copy(nodeptr->left);

	/* If the TreeNode pointed to by this TreeNode's right TreeNode pointer exists and contains more
	data, copy it too.
	*/
	if (nodeptr->right != nullptr)
		newnode->right = copy(nodeptr->right);

	return newnode;
}

void BinarySearchTree::insert(const std::string& new_dat)
{
	TreeNode* newNode = new TreeNode(new_dat);
	/* If the BinarySearchTree is empty, set the root to point to the first new TreeNode.
	Otherwise call insert_node function to find the new TreeNode's place in this BinarySearchTree.
	*/
	if (root == nullptr)
		root = newNode;
	else
		root->insert_node(newNode);
}

void BinarySearchTree::erase(const std::string& r_dat)
{
	TreeNode* remove = root;
	TreeNode* parent = nullptr;

	// While the remove pointer has not reached a nullptr in its search for the TreeNode with r_data.
	while (remove != nullptr)
	{
		/* If the remove TreeNode data is less than r_data, move to the right child.
		Otherwise if the remove TreeNode data is greater than the r_data, move to the left child.
		Otherwise the new TreeNode's data is exactly the same as the data from a previously inserted TreeNode.
		So we break from our while loop because remove and parent are at the proper location.
		*/
		if (remove->data < r_dat)
		{
			parent = remove;
			remove = remove->right;
		}
		else if (remove->data > r_dat)
		{
			parent = remove;
			remove = remove->left;
		}
		else
		{
			break;
		}
	}

	// If none of this BinarySearchTree's TreeNodes conatain r_data, we don't erase anything. So we return.
	if (remove == nullptr)
		return;

	// If remove only has at most a single child.
	if (remove->right == nullptr || remove->left == nullptr)
	{
		TreeNode* newChild = nullptr;

		// If remove only has a right child, set newChild to the right child. Otherwise set newChild to the left child.
		if (remove->left == nullptr)
			newChild = remove->right;
		else
			newChild = remove->left;

		/* If we are erasing the root TreeNode, set the root to the only child of remove.
		Otherwise if remove is the left child of parent, set remove's only child as the new left child of parent.
		Otherwise remove is the right child of parent, so set remove's only child as the new right child of parent.
		*/
		if (parent == nullptr)
			root = newChild;
		else if (parent->left == remove)
			parent->left = newChild;
		else
			parent->right = newChild;

		delete remove;
		remove = nullptr;
		return;
	}

	TreeNode* replace_parent = remove;
	TreeNode* replace_del = remove->right;

	// While we are not at the TreeNode with the next highest valued data from remove's data, keep moving to the left child.
	while (replace_del->left != nullptr)
	{
		replace_parent = replace_del;
		replace_del = replace_del->left;
	}

	remove->data = replace_del->data;

	/* If the TreeNode with the next highest valued data was immediately to the right of remove, set the orginal remove
	TreeNode's right child equal to the right child of the new TreeNode we are going to delete. Otherwise, set the
	replacement parent TreeNode's left child equal to the right child of the new TreeNode we are going to delete.
	*/
	if (replace_parent == remove)
		replace_parent->right = replace_del->right;
	else
		replace_parent->left = replace_del->right;

	delete replace_del;
	replace_del = nullptr;
}

void BinarySearchTree::print() const
{
	/* If this BinarySearchTree is not empty, call the recursive print_nodes function to display the data 
	in order.
	*/
	if (root != nullptr)
		root->print_nodes();
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& right)	
{
	/* If this BinarySearchTree is not being assigned to itself (i.e. bst1 = bst1), then we destroy this current 
	BinarySearchTree and make the deep copy of the right BinarySearchTree.
	*/
	if (this != &right)
	{
		kill_tree(root);
		// If the right BinarySearchTree has TreeNodes with data, make the deep copy. Otherwise set root to nullptr.
		if (right.root != nullptr)
			root = copy(right.root);
		else
			root = nullptr;
	}
	return *this;
}


void BinarySearchTree::kill_tree(TreeNode* nodeptr)
{
	/* If the nodeptr is not pointing to the nullptr (means the BinarySearchTree is not empty), we will have more
	TreeNodes to delete.
	*/
	if (nodeptr != nullptr)
	{
		// If the left child of nodeptr is not pointing to the nullptr, we destroy/delete the left subtree.
		if (nodeptr->left != nullptr)
			kill_tree(nodeptr->left);

		// If the right child of nodeptr is not pointing to the nullptr, we destroy/delete the right subtree.
		if (nodeptr->right != nullptr)
			kill_tree(nodeptr->right);

		delete nodeptr;
		nodeptr = nullptr;
	}

}

BinarySearchTree::~BinarySearchTree()
{
	kill_tree(root);
}
