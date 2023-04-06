/*
 * RBTree.h
 *
 *  Created on: Dec 3, 2019
 *      Author: Luke H
 */

#ifndef RBTREE_H_
#define RBTREE_H_


#include <iostream>
#include <iomanip>
#include <cstddef>
#include <string>
#include <cassert>
#include <math.h>
#include "linkedList.h"

//forward class declaration
template<class Type>
class RBTree;

//treenode class
template <class Type>
class treeNode
{
    friend class RBTree<Type>;

public:
    //constructors
    treeNode(): dataType(), pR(nullptr), pL(nullptr), pP(nullptr), color(""){}
    treeNode(const Type &data): dataType(data), pR(nullptr), pL(nullptr), pP(nullptr), color("") {}
    treeNode(const Type &data, std::string c): dataType(data), pR(nullptr), pL(nullptr), pP(nullptr), color(c) {}
    treeNode(const Type &data, treeNode<Type>* parent, std::string c): dataType(data), pR(nullptr), pL(nullptr), pP(parent), color(c) {}
    ~treeNode() {pR = nullptr; pL = nullptr; pP = nullptr;}

protected:
    void right(treeNode<Type> *add) {pR = add;}
    void left(treeNode<Type> *add) {pL = add;}
    void parent(treeNode<Type> *add) {pP = add;}
    void Color(std::string c) {if(c == "R" || c == "B") {this->color = c;}}

    bool isRed() {return color == "R";}
    bool isBlack() {return color == "B";}
    treeNode<Type>* right() const {return pR;}
    treeNode<Type>* left() const {return pL;}
    treeNode<Type>* parent() const {return pL;}

    int isRightChild() {if(pP == nullptr) {return -1;} else if(pP->pR == this) {return 1;} else {return 0;}}
    const Type& data() const {return dataType;}
    Type& data() {return dataType;}
    const std::string Color() const {return color;}
	std::string Color() {return color;}

private:
    Type dataType;
    treeNode<Type>* pR;
    treeNode<Type>* pL;
    treeNode<Type>* pP;
    std::string color;
};

template<class Type> void printData(const Type& foundItem, std::ostream& out) {out << foundItem;}




template <class Type>
class RBTree
{
public:
	RBTree(): root(nullptr), size(0) {}
	RBTree(const RBTree<Type> &other);
	virtual ~RBTree();

	bool empty() const;
	int Size() const;
	void print() const;
	void print(std::ostream &out) const;

	void traversePreOrder(std::ostream& out, void (*itemFound)(const Type& foundItem, std::ostream& out)) const;
	bool find(const Type &searchItem, void (*foundNode)(const Type&));
	treeNode<Type>* find(const Type &searchItem);
	bool erase(const Type &deleteItem);
	void insert(const Type &newItem);
	void insert(const Type &newItem, void (*duplicateItemFound)(Type &existingItem, const Type &newItem));
	void traverse(std::ostream& out, void (*itemFound)(const Type& foundItem, std::ostream& out)) const;

	const RBTree<Type>& operator=(const RBTree<Type> &other);
	bool operator==(const RBTree<Type> &other) const;
	bool operator!=(const RBTree<Type> &other) const;

	bool checkBlackNodes();
	int checkHeightDiff();

	void superBalancer(int s, linkedList<Type> dat);

private:
	treeNode<Type>* root;
	int size;

	void cleanTree();
	void recDelete(treeNode<Type> * curr);
	void inOrder(treeNode<Type> *current, std::ostream& out, void (*itemFound)(const Type& foundItem, std::ostream& out)) const;
	void preOrder(treeNode<Type> *current, std::ostream& out, void (*itemFound)(const Type& foundItem, std::ostream& out)) const;

	void simplePreOrderCopy(treeNode<Type>* copyTo, treeNode<Type>* copyFrom);
	bool equivCheckRec(treeNode<Type>* node1, treeNode<Type>* node2);

	void setChild(treeNode<Type>* parent, int dir, treeNode<Type>* child);
	void replChild(treeNode<Type>* parent, treeNode<Type>* curr, treeNode<Type>* succ);
	void rotLeft(treeNode<Type>* curr);
	void rotRight(treeNode<Type>* curr);

	void fullRepl(treeNode<Type>* toRepl, treeNode<Type>* replWith);
	treeNode<Type>* simpleIns(const Type &newItem);
	treeNode<Type>* simpleIns(const Type &newItem, void (*duplicateItemFound)(Type &existingItem, const Type &newItem));

	void balance(treeNode<Type>* curr);
	treeNode<Type>* getGP(treeNode<Type>* curr);
	treeNode<Type>* getUnc(treeNode<Type>* curr);

	void removal(treeNode<Type>* curr);
	treeNode<Type>* getPred(treeNode<Type>* curr);
	treeNode<Type>* getSib(treeNode<Type>* curr);
	bool NNR(treeNode<Type>* curr);
	bool NB(treeNode<Type>* curr);
	bool ABCB(treeNode<Type>* curr);

	void prepRem(treeNode<Type>* curr);
	bool case1(treeNode<Type>* curr);
	bool case2(treeNode<Type>* curr, treeNode<Type>* pSib);
	bool case3(treeNode<Type>* curr, treeNode<Type>* pSib);
	bool case4(treeNode<Type>* curr, treeNode<Type>* pSib);
	bool case5(treeNode<Type>* curr, treeNode<Type>* pSib);
	bool case6(treeNode<Type>* curr, treeNode<Type>* pSib);

	void simpleRem(treeNode<Type>* curr);

	int getPathNodes(treeNode<Type>* curr);
	int getLeastHeight(treeNode<Type>* curr);
	int getGreatestHeight(treeNode<Type>* curr);

	treeNode<Type>* goLeft(treeNode<Type>* curr);
	treeNode<Type>* onceRight(treeNode<Type>* curr);
	bool ifRight(treeNode<Type>* curr);
	void indexHelper(int * oldA, int * newA, int start, int end, int level, int max);
};


template <class Type>
void RBTree<Type>::cleanTree()
{
	recDelete(root);
	root = nullptr;
}

template <class Type>
void RBTree<Type>::recDelete(treeNode<Type>* curr)
{
	if(curr != nullptr)
	{
		recDelete(curr->pL);
		recDelete(curr->pR);
		delete curr;
	}
}

template <class Type>
RBTree<Type>::RBTree(const RBTree<Type> &other)
{
	root = new treeNode<Type>(other.root->data(), other.root->color);
	size = 1;

	simplePreOrderCopy(root, other.root);
}

template <class Type>
void RBTree<Type>::simplePreOrderCopy(treeNode<Type>* copyTo, treeNode<Type>* copyFrom)
{
	if(copyFrom->pL != nullptr)
	{
		copyTo->pL = new treeNode<Type>(copyFrom->pL->data(), copyTo, copyFrom->pL->color);
		size++;
		simplePreOrderCopy(copyTo->pL, copyFrom->pL);
	}
	if(copyFrom->pR != nullptr)
	{
		copyTo->pR = new treeNode<Type>(copyFrom->pR->data(), copyTo, copyFrom->pR->color);
		size++;
		simplePreOrderCopy(copyTo->pR, copyFrom->pR);
	}
}

template <class Type>
RBTree<Type>::~RBTree()
{
	cleanTree();
}


template <class Type>
bool RBTree<Type>::empty() const
{
	return size == 0;
}

template <class Type>
int RBTree<Type>::Size() const
{
	return size;
}

template <class Type>
void RBTree<Type>::print() const
{
	this->print(std::cout);
}

template <class Type>
void RBTree<Type>::print(std::ostream &out) const
{
	inOrder(root, out, &printData);
}

template <class Type>
void RBTree<Type>::inOrder(treeNode<Type> *current, std::ostream& out, void (*itemFound)(const Type& foundItem, std::ostream& out)) const
{
	if(current != nullptr)
	{
		inOrder(current->pL, out, itemFound);
		(*itemFound)(current->data(), out);
		inOrder(current->pR, out, itemFound);
	}
}

template <class Type>
void RBTree<Type>::preOrder(treeNode<Type> *current, std::ostream& out, void (*itemFound)(const Type& foundItem, std::ostream& out)) const
{
	if(current != nullptr)
	{
		(*itemFound)(current->data(), out);
		preOrder(current->pL, out, itemFound);
		preOrder(current->pR, out, itemFound);
	}
}

template <class Type>
void RBTree<Type>::traversePreOrder(std::ostream& out, void (*itemFound)(const Type& foundItem, std::ostream& out)) const
{
	preOrder(root, out, itemFound);
}


template <class Type>
bool RBTree<Type>::find(const Type &searchItem, void (*foundNode)(const Type&))
{
	treeNode<Type> *sNode = root;
	while(sNode != nullptr)
	{
		if(sNode->data() == searchItem)
		{
			(*foundNode)(sNode->data());
			return true;
		}
		else if(searchItem < sNode->data())
		{
			sNode = sNode->left();
		}
		else
		{
			sNode = sNode->right();
		}
	}
	return false;
}



template <class Type>
bool RBTree<Type>::erase(const Type &deleteItem)
{
	treeNode<Type>* toErase = find(deleteItem);
	if(toErase != nullptr)
	{
		removal(toErase);
		return true;
	}
	return false;
}

template <class Type>
treeNode<Type>* RBTree<Type>::find(const Type &searchItem)
{
	treeNode<Type> *sNode = root;
	while(sNode != nullptr)
	{
		if(sNode->data() == searchItem)
		{
			return sNode;
		}
		else if(searchItem < sNode->data())
		{
			sNode = sNode->left();
		}
		else
		{
			sNode = sNode->right();
		}
	}
	return sNode;
}

template <class Type>
void RBTree<Type>::removal(treeNode<Type>* curr)
{
	Type checkData= curr->data();

	if (curr->pL != nullptr && curr->pR != nullptr)
	{
	  treeNode<Type>* pPred = getPred(curr);
	  Type predData = pPred->data();
	  removal(pPred);
	  curr->dataType = predData;
	  return;
	}
	if (curr->color == "B")
	{
		prepRem(curr);
	}
	assert(checkData == curr->data());
	simpleRem(curr);
}

template<class Type>
treeNode<Type>* RBTree<Type>::getPred(treeNode<Type>* curr)
{
	curr = curr->pL;
	while(curr->pR != nullptr)
	{
		curr = curr->pR;
	}
	return curr;
}

template<class Type>
treeNode<Type>* RBTree<Type>::getSib(treeNode<Type>* curr)
{
	if(curr != nullptr)
	{
		if(curr->isRightChild() == 1)
		{
			return curr->pP->pL;
		}
		else if(curr->isRightChild() == 0)
		{
			return curr->pP->pR;
		}
	}
	return nullptr;
}

template<class Type>
bool RBTree<Type>::NNR(treeNode<Type>* curr)
{
	if(curr != nullptr)
	{
		return curr->isRed();
	}
	return false;
}

template<class Type>
bool RBTree<Type>::NB(treeNode<Type>* curr)
{
	if(curr != nullptr)
	{
		return curr->isBlack();
	}
	return true;
}

template<class Type>
bool RBTree<Type>::ABCB(treeNode<Type>* curr)
{
	return NB(curr->pL) && NB(curr->pR);
}

template<class Type>
void RBTree<Type>::prepRem(treeNode<Type>* curr)
{
	if(case1(curr))
	{
		return;
	}

	treeNode<Type>* pS = getSib(curr);
	if(case2(curr, pS))
	{
		pS = getSib(curr);
	}
	if(case3(curr, pS))
	{
		return;
	}

	if(case4(curr, pS))
	{
		return;
	}

	if(case5(curr, pS))
	{
		pS = getSib(curr);
	}
	if(case6(curr, pS))
	{
		pS = getSib(curr);
	}

	pS->color = curr->pP->color;
	curr->pP->color = "B";

	if(curr->isRightChild() == 0)
	{
		pS->pR->color = "B";
		rotLeft(curr->pP);
	}
	else
	{
		pS->pL->color = "B";
		rotRight(curr->pP);
	}
}

template<class Type>
bool RBTree<Type>::case1(treeNode<Type>* curr)
{
	return curr->isRed() || curr->pP == nullptr;
}

template<class Type>
bool RBTree<Type>::case2(treeNode<Type>* curr, treeNode<Type>* pSib)
{
	if(NNR(pSib))
	{
		curr->pP->color = "R";
		pSib->color = "B";

		if(curr->isRightChild() == 0)
		{
			rotLeft(curr->pP);
		}
		else
		{
			rotRight(curr->pP);
		}
		return true;
	}
	return false;
}

template<class Type>
bool RBTree<Type>::case3(treeNode<Type>* curr, treeNode<Type>* pSib)
{
	if(curr->pP->isBlack() && ABCB(pSib))
	{
		pSib->color = "R";
		prepRem(curr->pP);
		return true;
	}
	return false;
}

template<class Type>
bool RBTree<Type>::case4(treeNode<Type>* curr, treeNode<Type>* pSib)
{
	if(curr->pP->isRed() && ABCB(pSib))
	{
		curr->pP->color = "B";
		pSib->color = "R";
		return true;
	}
	return false;
}

template<class Type>
bool RBTree<Type>::case5(treeNode<Type>* curr, treeNode<Type>* pSib)
{
	if(NNR(pSib->pL) && NB(pSib->pR) && curr->isRightChild() == 0)
	{
		pSib->color = "R";
		pSib->pL->color = "B";
		rotRight(pSib);
		return true;
	}
	return false;
}

template<class Type>
bool RBTree<Type>::case6(treeNode<Type>* curr, treeNode<Type>* pSib)
{
	if(NNR(pSib->pR) && NB(pSib->pL) && curr->isRightChild() == 1)
	{
		pSib->color = "R";
		pSib->pR->color = "B";
		rotLeft(pSib);
		return true;
	}
	return false;
}

template<class Type>
void RBTree<Type>::simpleRem(treeNode<Type>* curr)
{
	if(curr != nullptr)
	{
		bool L = (curr->pL != nullptr);
		bool R = (curr->pR != nullptr);

		if(L && R)
		{
			treeNode<Type>* pPred = getPred(curr);
			treeNode<Type>* copyPred = new treeNode<Type>(pPred->data(), pPred->color);
			simpleRem(pPred);
			fullRepl(curr, copyPred);
		}
		else if(L || R)
		{
			treeNode<Type>* child = nullptr;
			if(L)
			{
				child = curr->pL;
			}
			else
			{
				child = curr->pR;
			}

			if(curr->pP == nullptr)
			{
				root = child;
			}
			else if(curr->isRightChild() == 0)
			{
				curr->pP->pL = child;
			}
			else
			{
				curr->pP->pR = child;
			}
			child->pP = curr->pP;

			delete curr;
			size--;
		}
		else
		{
			if(curr->isRightChild() == 0)
			{
				curr->pP->pL = nullptr;
			}
			else if(curr->isRightChild() == 1)
			{
				curr->pP->pR = nullptr;
			}
			else
			{
				root = nullptr;
			}
			delete curr;
			size--;
		}
	}
}



template <class Type>
void RBTree<Type>::setChild(treeNode<Type>* parent, int dir, treeNode<Type>* child)
{
	assert(dir == 1 || dir == 0);
	if(dir == 1)
	{
		if(parent != nullptr)
			parent->pR = child;
	}
	else
	{
		if(parent != nullptr)
			parent->pL = child;
	}

	if(child != nullptr)
	{
		child->pP = parent;
	}
}

template <class Type>
void RBTree<Type>::replChild(treeNode<Type>* parent, treeNode<Type>* curr, treeNode<Type>* succ)
{
	if(curr != nullptr)
	{
		assert(curr->pP == parent);
		setChild(parent, curr->isRightChild(), succ);
	}
}

template <class Type>
void RBTree<Type>::rotLeft(treeNode<Type>* curr)
{
	assert(curr->pR != nullptr);
	treeNode<Type>* RLC = curr->pR->pL;

	if(curr == root)
	{
		root = curr->pR;
		root->pP = nullptr;
	}
	else
	{
		replChild(curr->pP, curr, curr->pR);
	}
	setChild(curr->pR, 0, curr);
	setChild(curr, 1, RLC);
}

template <class Type>
void RBTree<Type>::rotRight(treeNode<Type>* curr)
{
	assert(curr->pL != nullptr);
	treeNode<Type>* LRC = curr->pL->pR;

	if(curr == root)
	{
		root = curr->pL;
		root->pP = nullptr;
	}
	else
	{
		replChild(curr->pP, curr, curr->pL);
	}
	setChild(curr->pL, 1, curr);
	setChild(curr, 0, LRC);
}



template <class Type>
void RBTree<Type>::fullRepl(treeNode<Type>* toRepl, treeNode<Type>* replWith)
{
	if(toRepl->isRightChild() == 0)
	{
		toRepl->pP->pL = replWith;
	}
	else if(toRepl->isRightChild() == 1)
	{
		toRepl->pP->pR = replWith;
	}
	else
	{
		root = replWith;
	}
	replWith->pP = toRepl->pP;
	if(toRepl->pR != nullptr)
	{
		toRepl->pR->pP = replWith;
	}
	replWith->pR = toRepl->pR;
	if(toRepl->pL != nullptr)
	{
		toRepl->pL->pP = replWith;
	}
	replWith->pL = toRepl->pL;
	delete toRepl;
}

template <class Type>
treeNode<Type>* RBTree<Type>::simpleIns(const Type &newItem)
{
	treeNode<Type> *newNode = new treeNode<Type>(newItem, "R");
	if(empty())
	{
		root = newNode;
		size++;
	}
	else
	{
		treeNode<Type> *curr = root;
		bool loop = true;
		while(loop)
		{
			if(curr->data() == newItem)
			{
				fullRepl(curr, newNode);
				loop = false;
			}
			else if(newItem < curr->data())
			{
				if(curr->pL == nullptr)
				{
					curr->pL = newNode;
					newNode->pP = curr;
					size++;
					loop = false;
				}
				else
				{
					curr = curr->pL;
				}
			}
			else
			{
				if(curr->pR== nullptr)
				{
					curr->pR = newNode;
					newNode->pP = curr;
					size++;
					loop = false;
				}
				else
				{
					curr = curr->pR;
				}
			}
		}
	}
	return newNode;
}

template <class Type>
treeNode<Type>* RBTree<Type>::simpleIns(const Type &newItem, void (*duplicateItemFound)(Type &existingItem, const Type &newItem))
{
	treeNode<Type> *newNode = new treeNode<Type>(newItem, "R");
		if(empty())
		{
			root = newNode;
			size++;
		}
		else
		{
			treeNode<Type> *curr = root;
			bool loop = true;
			while(loop)
			{
				if(curr->data() == newItem)
				{
					(*duplicateItemFound)(curr->data(), newItem);
					treeNode<Type>* temp = newNode;
					newNode = curr;
					delete temp;

					loop = false;
				}
				else if(newItem < curr->data())
				{
					if(curr->pL == nullptr)
					{
						curr->pL = newNode;
						newNode->pP = curr;
						size++;
						loop = false;
					}
					else
					{
						curr = curr->pL;
					}
				}
				else
				{
					if(curr->pR== nullptr)
					{
						curr->pR = newNode;
						newNode->pP = curr;
						size++;
						loop = false;
					}
					else
					{
						curr = curr->pR;
					}
				}
			}
		}
		return newNode;
}




template <class Type>
void RBTree<Type>::insert(const Type &newItem)
{
	treeNode<Type>* curr = simpleIns(newItem);
	balance(curr);
}

template <class Type>
void RBTree<Type>::insert(const Type &newItem, void (*duplicateItemFound)(Type &existingItem, const Type &newItem))
{
	treeNode<Type>* curr = simpleIns(newItem, duplicateItemFound);
	balance(curr);
}


template<class Type>
treeNode<Type>* RBTree<Type>::getGP(treeNode<Type>* curr)
{
	if(curr != root)
	{
		return curr->pP->pP;
	}
	return nullptr;
}

template<class Type>
treeNode<Type>* RBTree<Type>::getUnc(treeNode<Type>* curr)
{
	treeNode<Type>* pGP = getGP(curr);
	if(pGP == nullptr)
	{
		return nullptr;
	}
	else if(curr->pP->isRightChild() == 1)
	{
		return pGP->pL;
	}
	else
	{
		return pGP->pR;
	}
}

template<class Type>
void RBTree<Type>::balance(treeNode<Type>* curr)
{
	if(curr == root)
	{
		root->color = "B";
		return;
	}
	else if(curr->pP->color == "B")
	{
		return;
	}

	treeNode<Type>* pP = curr->pP;
	treeNode<Type>* pGP = getGP(curr);
	treeNode<Type>* pU = getUnc(curr);

	if(pU != nullptr)
	{
		if(pU->color == "R")
		{
			pU->color = "B";
			pP->color = "B";
			pGP->color = "R";
			balance(pGP);
			return;
		}
	}

	assert(pGP != nullptr);
	if(curr->isRightChild() == 1 && pP->isRightChild() == 0)
	{
		rotLeft(pP);
		curr = pP;
		pP = curr->pP;
	}
	else if(curr->isRightChild() == 0 && pP->isRightChild() == 1)
	{
		rotRight(pP);
		curr = pP;
		pP = curr->pP;
	}

	pP->color = "B";
	pGP->color = "R";

	if(curr->isRightChild() == 0)
	{
		rotRight(pGP);
	}
	else
	{
		rotLeft(pGP);
	}
}



template <class Type>
void RBTree<Type>::traverse(std::ostream& out, void (*itemFound)(const Type& foundItem, std::ostream& out)) const
{
	inOrder(root, out, itemFound);
}


template <class Type>
const RBTree<Type>& RBTree<Type>::operator=(const RBTree<Type> &other)
{
	if(other != *this)
	{
		cleanTree();

		root = new treeNode<Type>(other.root->data(), other.root->color);
		size = 1;

		simplePreOrderCopy(root, other.root);
	}
	return *this;
}

template <class Type>
bool RBTree<Type>::operator==(const RBTree<Type> &other) const
{
	return equivCheckRec(root, other.root);
}

template <class Type>
bool RBTree<Type>::operator!=(const RBTree<Type> &other) const
{
	return !(*this == other);
}

template <class Type>
bool RBTree<Type>::equivCheckRec(treeNode<Type>* node1, treeNode<Type>* node2)
{
	if(node1 == nullptr && node2 == nullptr)
	{
		return true;
	}
	else if(node1 == nullptr || node2 == nullptr)
	{
		return false;
	}
	else if(node1->data() != node2->data())
	{
		return false;
	}
	else
	{
		return equivCheckRec(node1->pL, node2->pL) && equivCheckRec(node1->pR, node2->pR);
	}
}


template<class Type>
bool RBTree<Type>::checkBlackNodes()
{
	if(empty())
	{
		return true;
	}
	int left = getPathNodes(root->pL);
	int right = getPathNodes(root->pR);

	return right != 0 && left != 0 && right == left;
}

template<class Type>
int RBTree<Type>::getPathNodes(treeNode<Type>* curr)
{
	if(curr == nullptr)
	{
		return 1;
	}
	else
	{
		int add = 0;
		if(curr->isBlack())
		{
			add = 1;
		}

		int left = getPathNodes(curr->pL);
		int right = getPathNodes(curr->pR);
		if(right == left && right != 0)
		{
			return add + right;
		}
		else
		{
			return 0;
		}
	}
}

template<class Type>
int RBTree<Type>::checkHeightDiff()
{
	int diff = getGreatestHeight(root) - getLeastHeight(root);
	return diff;
}

template<class Type>
int RBTree<Type>::getLeastHeight(treeNode<Type>* curr)
{
	if(curr == nullptr)
	{
		return 0;
	}
	else
	{
		int left = getLeastHeight(curr->pL);
		int right = getLeastHeight(curr->pR);
		if(left < right)
		{
			return 1 + left;
		}
		else
		{
			return 1 + right;
		}
	}
}

template<class Type>
int RBTree<Type>::getGreatestHeight(treeNode<Type>* curr)
{
	if(curr == nullptr)
	{
		return 0;
	}
	else
	{
		int left = getGreatestHeight(curr->pL);
		int right = getGreatestHeight(curr->pR);
		if(left < right)
		{
			return 1 + right;
		}
		else
		{
			return 1 + left;
		}
	}
}





//This function is designed to input data into the tree in the most balanced way possible
//It takes the max elements and a linkedList of the elements in proper order as input
//taking into account the creation of the linked list, runs roughly in O(.5n^2 + 3n) time
template<class Type>
void RBTree<Type>::superBalancer(int s, linkedList<Type> dat)
{
	const int l = s;
	int * inOrder = new int[l];
	int * newOrder = new int[l];

	//makes inOrder array have nums in order, fill newOrder with -1
	for(int i = 0; i < l; i++) {
		inOrder[i] = i;
		newOrder[i] = -1;
	}

	//call recursive helpter function; inserts nums into newOrder array
	//newOrder should contain a BST order of indexes to properly insert elements breadth first
	indexHelper(inOrder, newOrder, 0, l - 1, 0, l);

	//cleans any possible elements in the tree
	this->cleanTree();

	//loops through newOrder array, accesses element at specified index of linkedlist and inserts into tree
	listNode<Type>* curr;
	for(int k = 0; k < l; k++){
		curr = dat.gethead();

		for(int r = 0; r < newOrder[k]; r++) {
			curr = curr->next();
		}
		this->insert(curr->data());
	}

	//deletes the arrays
	delete inOrder;
	delete newOrder;
	//should result in a tree with max height difference of 1 across the whole tree
}



template<class Type>
void RBTree<Type>::indexHelper(int * oldA, int * newA, int start, int end, int level, int max) {
	if(!(start > end)) {
		int mid, s1, s2, e1, e2;

		mid = (start + end)/2;
		s1 = start;
		e1 = mid - 1;
		s2 = mid + 1;
		e2 = end;

		int startIndex = (int)pow(2.0, level) - 1;
		while(newA[startIndex] != -1 && startIndex < max) {
			startIndex++;
		}
		if(startIndex < max) {
			newA[startIndex] = oldA[mid];
			indexHelper(oldA, newA, s1, e1, level + 1, max);
			indexHelper(oldA, newA, s2, e2, level + 1, max);
		}
		else
		{
			std::cout << "ERROR - out of bounds when making new BST indexer" << std::endl;
		}
	}
}





template<class Type>
treeNode<Type>* RBTree<Type>::goLeft(treeNode<Type>* curr)
{
	while(curr->left() != nullptr){
		curr = curr->left();
	}
	return curr;
}


template<class Type>
treeNode<Type>* RBTree<Type>::onceRight(treeNode<Type>* curr)
{
	curr = curr->right();
	return curr;
}

template<class Type>
bool RBTree<Type>::ifRight(treeNode<Type>* curr)
{
	if(curr != root){
		return (curr->parent()->right() == curr);
	}
	return false;
}

#endif /* RBTREE_H_ */
