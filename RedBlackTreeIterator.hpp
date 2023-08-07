#pragma once
#include "utils.hpp"
#include "Redb.hpp"

namespace ft{

template<class T>
struct RBTreeIterator : public ft::iterator<ft::bidirectional_iterator_tag, T>{
public:
	typedef Node<T> Node;
	typedef RBTreeIterator<T> Self;
	RBTreeIterator(Node* n=nullptr) 
		:_pNode(n), _root(n)// Constructors 
	{
		if (_root == nullptr)
			return;
		while (_root->parent != nullptr)
			_root = _root->parent;
	}
	T& operator*() {
		return _pNode->data;
	}
	T* operator->() {
		return &(_pNode->data);
	}

	Self& operator++() {
		if (max()->data.first == _pNode->data.first || _pNode == nullptr)
		{
			_pNode = nullptr;
			return *this;
		}
		Increment();
		return *this;
	}
	Self operator++(int) {
		if (max()->data.first == _pNode->data.first || _pNode == nullptr)
		{
			_pNode = nullptr;
			return *this;
		}
		Self tmp = *this;
		Increment();
		return tmp;
	}
	Self& operator--() {
		Decrement();
		return *this;
	}
	Self operator--(int) {
		Self tmp = *this;
		Decrement();
		return tmp;
	}
	bool operator==(const Self& s) {
		return _pNode == s._pNode;
	}
	bool operator!=(const Self& s) {
		return _pNode != s._pNode;
	}
private:
void findPreSuc(Node* root, Node*& pre, Node*& suc, T key)
{
    // Base case
    if (root == NULL)  return ;
 
    // If key is present at root
    if (root->data.first == key.first)
    {
        // the maximum value in left subtree is predecessor
        if (root->left != NULL)
        {
            Node* tmp = root->left;
            while (tmp->right)
                tmp = tmp->right;
            pre = tmp ;
        }
 
        // the minimum value in right subtree is successor
        if (root->right != NULL)
        {
            Node* tmp = root->right ;
            while (tmp->left)
                tmp = tmp->left ;
            suc = tmp ;
        }
        return ;
    }
	    // If key is smaller than root's key, go to left subtree
    if (root->data.first > key.first)
    {
        suc = root ;
        findPreSuc(root->left, pre, suc, key) ;
    }
    else // go to right subtree
    {
        pre = root ;
        findPreSuc(root->right, pre, suc, key) ;
    }
}
	
	Node *max(void)
	{
		Node *x = _root;
		while (x != nullptr && x->right != nullptr)
			x = x->right;
		return x;
	}
	void Increment() {
		if (_pNode->right) {
			Node* temp = _pNode->right;
			while (temp->left) {
				temp = temp->left;
			}
			_pNode = temp;
		}
		else
		{
			Node* tmp = _pNode->parent;
			if (tmp->right==_pNode) {
				while (_pNode==tmp->right)
				{
					_pNode = tmp;
					tmp = tmp->parent;
				}
			}
			if (_pNode->right != tmp)
				_pNode = tmp;
		}
	}
	void Decrement() {
		Node *x;
		Node *y;
		findPreSuc(_root, x, y, _pNode->data);
		_pNode = x;
	}
private:
	Node* _pNode;
	Node* _root;
};


template<class T>
struct ConstRBTreeIterator : public ft::iterator<ft::bidirectional_iterator_tag, T>{
public:
	typedef Node<T> Node;
	typedef RBTreeIterator<T> Self;
	ConstRBTreeIterator(Node* n=nullptr) 
		:_pNode(n), _root(n)// Constructors 
	{
		while (_root->parent != nullptr)
			_root = _root->parent;
	}
	T& operator*() {
		return _pNode->data;
	}
	T* operator->() {
		return &(_pNode->data);
	}

	Self& operator++() {
		if (max()->data.first == _pNode->data.first || _pNode == nullptr)
		{
			_pNode = nullptr;
			return *this;
		}
		Increment();
		return *this;
	}
	Self operator++(int) {
		if (max()->data.first == _pNode->data.first || _pNode == nullptr)
		{
			_pNode = nullptr;
			return *this;
		}
		Self tmp = *this;
		Increment();
		return tmp;
	}
	Self& operator--() {
		Decrement();
		return *this;
	}
	Self operator--(int) {
		Self tmp = *this;
		Decrement();
		return tmp;
	}
	bool operator==(const Self& s) {
		return _pNode == s._pNode;
	}
	bool operator!=(const Self& s) {
		return _pNode != s._pNode;
	}
private:
void findPreSuc(Node* root, Node*& pre, Node*& suc, T key)
{
    // Base case
    if (root == NULL)  return ;
 
    // If key is present at root
    if (root->data.first == key.first)
    {
        // the maximum value in left subtree is predecessor
        if (root->left != NULL)
        {
            Node* tmp = root->left;
            while (tmp->right)
                tmp = tmp->right;
            pre = tmp ;
        }
 
        // the minimum value in right subtree is successor
        if (root->right != NULL)
        {
            Node* tmp = root->right ;
            while (tmp->left)
                tmp = tmp->left ;
            suc = tmp ;
        }
        return ;
    }
	    // If key is smaller than root's key, go to left subtree
    if (root->data.first > key.first)
    {
        suc = root ;
        findPreSuc(root->left, pre, suc, key) ;
    }
    else // go to right subtree
    {
        pre = root ;
        findPreSuc(root->right, pre, suc, key) ;
    }
}
	
	Node *max(void)
	{
		Node *x = _root;
		while (x != nullptr && x->right != nullptr)
			x = x->right;
		return x;
	}
	void Increment() {
		if (_pNode->right) {
			Node* temp = _pNode->right;
			while (temp->left) {
				temp = temp->left;
			}
			_pNode = temp;
		}
		else
		{
			Node* tmp = _pNode->parent;
			if (tmp->right==_pNode) {
				while (_pNode==tmp->right)
				{
					_pNode = tmp;
					tmp = tmp->parent;
				}
			}
			if (_pNode->right != tmp)
				_pNode = tmp;
		}
	}
	void Decrement() {
		Node *x;
		Node *y;
		findPreSuc(_root, x, y, _pNode->data);
		_pNode = x;
	}
private:
	Node* _pNode;
	Node* _root;
};

}