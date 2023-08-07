#pragma once

#include <iostream>
#include <queue>

namespace ft{

using namespace std;

enum COLOR { RED, BLACK };

template<class T>
class Node {
public:
T data;
COLOR color;
Node *left, *right, *parent;
int scam;

Node(T data) : data(data) {
	parent = left = right = NULL;

	// Node is created during insertion
	// Node is red at insertion
	color = RED;
	scam = 0;
}

// returns pointer to uncle
Node<T> *uncle() {
	// If no parent or grandparent, then no uncle
	if (parent == NULL or parent->parent == NULL)
	return NULL;

	if (parent->isOnLeft())
	// uncle on right
	return parent->parent->right;
	else
	// uncle on left
	return parent->parent->left;
}

// check if node is left child of parent
bool isOnLeft() { return this == parent->left; }

// returns pointer to sibling
Node<T> *sibling() {
	// sibling null if no parent
	if (parent == NULL)
	return NULL;

	if (isOnLeft())
	return parent->right;

	return parent->left;
}

// moves node down and moves given node in its place
void moveDown(Node<T> *nParent) {
	if (parent != NULL) {
	if (isOnLeft()) {
		parent->left = nParent;
	} else {
		parent->right = nParent;
	}
	}
	nParent->parent = parent;
	parent = nParent;
}

bool hasRedChild() {
	return (left != NULL and left->color == RED) or
		(right != NULL and right->color == RED);
}
};

template<class T>
class RedBTree {
typedef Node<T>	Node;
Node *root;
size_t _size;

// left rotates the given node
void leftRotate(Node *x) {
	// new parent will be node's right child
	Node *nParent = x->right;

	// update root if current node is root
	if (x == root)
	root = nParent;

	x->moveDown(nParent);

	// connect x with new parent's left element
	x->right = nParent->left;
	// connect new parent's left element with node
	// if it is not null
	if (nParent->left != NULL)
	nParent->left->parent = x;

	// connect new parent with x
	nParent->left = x;
}

void rightRotate(Node *x) {
	// new parent will be node's left child
	Node *nParent = x->left;

	// update root if current node is root
	if (x == root)
	root = nParent;

	x->moveDown(nParent);

	// connect x with new parent's right element
	x->left = nParent->right;
	// connect new parent's right element with node
	// if it is not null
	if (nParent->right != NULL)
	nParent->right->parent = x;

	// connect new parent with x
	nParent->right = x;
}

void swapColors(Node *x1, Node *x2) {
	COLOR temp;
	temp = x1->color;
	x1->color = x2->color;
	x2->color = temp;
}

void swapdataues(Node *u, Node *v) {
	T temp;
	temp = u->data;
	u->data = v->data;
	v->data = temp;
}

// fix red red at given node
void fixRedRed(Node *x) {
	// if x is root color it black and return
	if (x == root) {
	x->color = BLACK;
	return;
	}

	// initialize parent, grandparent, uncle
	Node *parent = x->parent, *grandparent = parent->parent,
		*uncle = x->uncle();

	if (parent->color != BLACK) {
	if (uncle != NULL && uncle->color == RED) {
		// uncle red, perform recoloring and recurse
		parent->color = BLACK;
		uncle->color = BLACK;
		grandparent->color = RED;
		fixRedRed(grandparent);
	} else {
		// Else perform LR, LL, RL, RR
		if (parent->isOnLeft()) {
		if (x->isOnLeft()) {
			// for left right
			swapColors(parent, grandparent);
		} else {
			leftRotate(parent);
			swapColors(x, grandparent);
		}
		// for left left and left right
		rightRotate(grandparent);
		} else {
		if (x->isOnLeft()) {
			// for right left
			rightRotate(parent);
			swapColors(x, grandparent);
		} else {
			swapColors(parent, grandparent);
		}

		// for right right and right left
		leftRotate(grandparent);
		}
	}
	}
}

// find node that do not have a left child
// in the subtree of the given node
Node *successor(Node *x) {
	Node *temp = x;

	while (temp->left != NULL)
	temp = temp->left;

	return temp;
}

// find node that replaces a deleted node in BST
Node *BSTreplace(Node *x) {
	// when node have 2 children
	if (x->left != NULL and x->right != NULL)
	return successor(x->right);

	// when leaf
	if (x->left == NULL and x->right == NULL)
	return NULL;

	// when single child
	if (x->left != NULL)
	return x->left;
	else
	return x->right;
}

// deletes the given node
void deleteNode(Node *v) {
	Node *u = BSTreplace(v);

	// True when u and v are both black
	bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
	Node *parent = v->parent;

	if (u == NULL) {
	// u is NULL therefore v is leaf
	if (v == root) {
		// v is root, making root null
		root = NULL;
	} else {
		if (uvBlack) {
		// u and v both black
		// v is leaf, fix double black at v
		fixDoubleBlack(v);
		} else {
		// u or v is red
		if (v->sibling() != NULL)
			// sibling is not null, make it red"
			v->sibling()->color = RED;
		}

		// delete v from the tree
		if (v->isOnLeft()) {
		parent->left = NULL;
		} else {
		parent->right = NULL;
		}
	}
	delete v;
	return;
	}

	if (v->left == NULL or v->right == NULL) {
	// v has 1 child
	if (v == root) {
		// v is root, assign the dataue of u to v, and delete u
		v->data = u->data;
		v->left = v->right = NULL;
		delete u;
	} else {
		// Detach v from tree and move u up
		if (v->isOnLeft()) {
		parent->left = u;
		} else {
		parent->right = u;
		}
		delete v;
		u->parent = parent;
		if (uvBlack) {
		// u and v both black, fix double black at u
		fixDoubleBlack(u);
		} else {
		// u or v red, color u black
		u->color = BLACK;
		}
	}
	return;
	}

	// v has 2 children, swap dataues with successor and recurse
	swapdataues(u, v);
	deleteNode(u);
}

void fixDoubleBlack(Node *x) {
	if (x == root)
	// Reached root
	return;

	Node *sibling = x->sibling(), *parent = x->parent;
	if (sibling == NULL) {
	// No sibiling, double black pushed up
	fixDoubleBlack(parent);
	} else {
	if (sibling->color == RED) {
		// Sibling red
		parent->color = RED;
		sibling->color = BLACK;
		if (sibling->isOnLeft()) {
		// left case
		rightRotate(parent);
		} else {
		// right case
		leftRotate(parent);
		}
		fixDoubleBlack(x);
	} else {
		// Sibling black
		if (sibling->hasRedChild()) {
		// at least 1 red children
		if (sibling->left != NULL and sibling->left->color == RED) {
			if (sibling->isOnLeft()) {
			// left left
			sibling->left->color = sibling->color;
			sibling->color = parent->color;
			rightRotate(parent);
			} else {
			// right left
			sibling->left->color = parent->color;
			rightRotate(sibling);
			leftRotate(parent);
			}
		} else {
			if (sibling->isOnLeft()) {
			// left right
			sibling->right->color = parent->color;
			leftRotate(sibling);
			rightRotate(parent);
			} else {
			// right right
			sibling->right->color = sibling->color;
			sibling->color = parent->color;
			leftRotate(parent);
			}
		}
		parent->color = BLACK;
		} else {
		// 2 black children
		sibling->color = RED;
		if (parent->color == BLACK)
			fixDoubleBlack(parent);
		else
			parent->color = BLACK;
		}
	}
	}
}

// prints level order for given node
void levelOrder(Node *x) {
	if (x == NULL)
	// return if node is null
	return;

	// queue for level order
	queue<Node *> q;
	Node *curr;

	// push x
	q.push(x);

	while (!q.empty()) {
	// while q is not empty
	// dequeue
	curr = q.front();
	q.pop();

	// print node dataue
	cout << curr->data << " ";

	// push children to queue
	if (curr->left != NULL)
		q.push(curr->left);
	if (curr->right != NULL)
		q.push(curr->right);
	}
}

// prints inorder recursively
void inorder(Node *x) {
	if (x == NULL)
	return;
	inorder(x->left);
	cout << x->data << " ";
	inorder(x->right);
}

public:
// constructor
// initialize root
RedBTree() { 
	root = NULL; 
	_size = 0;
	}

Node *getRoot() { return root; }

// searches for given dataue
// if found returns the node (used for delete)
// else returns the last node while traversing (used in insert)


Node *search(T n) {
	Node *temp = root;
	while (temp != NULL) {
	if (n.first < temp->data.first) {
		if (temp->left == NULL)
		break;
		else
		temp = temp->left;
	} else if (n.first == temp->data.first) {
		break;
	} else {
		if (temp->right == NULL)
		break;
		else
		temp = temp->right;
	}
	}
	if (temp->data.first != n.first)
		root->scam = 1;
	return temp;
}

int	checkScam(void)
{return root->scam;}

void	endScam(void)
{
	root->scam = 0;
}


// inserts the given dataue to tree
void insert(T n) {
	_size++;
	Node *newNode = new Node(n);
	if (root == NULL) {
	// when root is null
	// simply insert dataue at root
	newNode->color = BLACK;
	root = newNode;
	} else {
	Node *temp = search(n);

	if (temp->data.first == n.first) {
		// return if dataue already exists
		return;
	}

	// if dataue is not found, search returns the node
	// where the dataue is to be inserted

	// connect new node to correct node
	newNode->parent = temp;

	if (n.first < temp->data.first)
		temp->left = newNode;
	else
		temp->right = newNode;

	// fix red red voilaton if exists
	fixRedRed(newNode);
	}
}

// utility function that deletes the node with given dataue
void deleteBydata(T n) {
	if (root == NULL)
	// Tree is empty
	return;

	Node *v = search(n), *u;

	if (v->data.first != n.first) {
	cout << "No node found to delete with dataue:" << n.first << endl;
	return;
	}

	_size--;
	deleteNode(v);
}

// prints inorder of the tree
void printInOrder() {
	cout << "Inorder: " << endl;
	if (root == NULL)
	cout << "Tree is empty" << endl;
	else
	inorder(root);
	cout << endl;
}

// prints level order of the tree
void printLevelOrder() {
	cout << "Level order: " << endl;
	if (root == NULL)
	cout << "Tree is empty" << endl;
	else
	levelOrder(root);
	cout << endl;
}
Node *min(void) const
{
	Node *tmp = root;
	while (tmp != NULL && tmp->left)
		tmp = tmp->left;
	return tmp;
}

Node *max(void)
{
	Node *tmp = root;
	while (tmp != NULL && tmp->right)
		tmp = tmp->right;
	return tmp;
}


size_t	getSize(void) const
{return _size;}

};
}