/*
 * linkedList.h
 *
 *  Created on: Nov 29, 2019
 *      Author: Luke H
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_


#include <cassert>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>


template<class DataType>
class linkedList;

template<class DataType>
class linkedListIterator;


template<class DataType>
class listNode
{
	// make DoubleLinkedList<DataType> a friend class
	friend class linkedList<DataType>;
	friend class linkedListIterator<DataType>;
	private:
		// contains the actual data
		DataType dataType;
		// pointer to the next item in the list or nullptr
		// if at the end
		listNode<DataType>* pNext;
		// pointer to the previous item in the list or nullptr
		// if at the start
		listNode<DataType>* pPrevious;
	public:
		// default constructor
		listNode();
		// constructor with data
		listNode(const DataType &newItem);
	public:
		// get the next node
		listNode* next() const
		{
			return pNext;
		}

		// get the previous node
		listNode* previous() const
		{
			return pPrevious;
		}

		// return the data stored in the node as a const
		const DataType& data() const
		{
			return dataType;
		}
		// return the data stored in the node
		DataType& data()
		{
			return dataType;
		}
		// update the next node
		void next(listNode<DataType> *nextNode)
		{
			pNext = nextNode;
		}
		// update the previous node
		void previous(listNode<DataType> *previousNode)
		{
			pPrevious = previousNode;
		}
};

// the linkedListIterator is the iterator for class linkedList.
//
// most of this code has been provided for you.
// the exceptions are the operator--() operator--(int) member fuctions and
// and the operator== and operator!= member functions.
template<class DataType>
class linkedListIterator
{
	typedef DataType 								value_type;
	typedef DataType& 								reference;
	typedef const DataType& 						const_reference;
	typedef DataType* 								pointer;
	typedef const DataType* 						const_pointer;
	typedef std::bidirectional_iterator_tag			iterator_category;
	typedef std::ptrdiff_t 							difference_type;
	typedef std::size_t								size_type;
	typedef linkedListIterator						iterator;
	typedef const linkedListIterator	  			const_iterator;

	friend class linkedList<DataType>;
	private:
		//listNode pointer
		listNode<DataType> *current;
	public:
		//constructor
		linkedListIterator(listNode<DataType>* current): current(current) {}

		//destructor
		virtual ~linkedListIterator() {}

		reference operator*()
		{
		   assert(current != nullptr);
			return current->data();
		}

		const_reference operator*() const
		{
		   assert(current != nullptr);
			return current->data();
		}

		pointer operator->()
		{
		   assert(current != nullptr);
			return &(current->data());
		}

		const_pointer operator->() const
		{
		   assert(current != nullptr);
			return &(current->data());
		}

		iterator operator++()
		{
			if (current != nullptr)
			{
				current = current->next();
			}
			return *this;
		}

		iterator operator++(int)
		{
			iterator it = *this;
			if (current != nullptr)
			{
				current = current->next();
			}
			return it;
		}

      // you need to implement the following - they can be inlined if you want
		iterator operator--()
		{
			if(current != nullptr)
			{
				current = current->previous(); //moves to previous node if not null
			}
			return *this;
		}

		iterator operator--(int)
		{
			iterator iter = *this; //store previous pointer
			if(current != nullptr)
			{
				current = current->previous(); //change pointer node
			}
			return iter; //return previous pointer
		}

		bool operator==(const_iterator &other) const
		{
			if(this->current == other.current) //compares pointer addresses
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool operator!=(const_iterator &other) const
		{
			return !(this->current == other.current); //return opposite of ==
		}

};

// linkedList class
template<class DataType>
class linkedList
{
	public:
// 		typedef DataType 								   value_type;
// 		typedef DataType& 								reference;
// 		typedef const DataType& 						const_reference;
// 		typedef DataType* 								pointer;
// 		typedef const DataType* 						const_pointer;
// 		typedef std::bidirectional_iterator_tag	iterator_category;
// 		typedef std::ptrdiff_t 							difference_type;
// 		typedef std::size_t								size_type;
		typedef linkedListIterator<DataType>		iterator;
		typedef const linkedListIterator<DataType> const_iterator;

	private:
		listNode<DataType>* head;
		listNode<DataType>* tail;
		std::size_t nodeCount;
	public:
		linkedList(): head(nullptr), tail(nullptr), nodeCount(0) {}

		linkedList(const linkedList &other)
		{
			head = nullptr; //set base values
			tail = nullptr;
			nodeCount = 0;
			//loop through other list and add each individual new node
			iterator otherList = other.begin();
			for(; otherList != other.end(); otherList++)
			{
				this->push_back(*otherList);
			}
		}

		const linkedList& operator=(const linkedList &other)
		{
			while(!empty())
			{
				pop_front();
			}

			listNode<DataType> *curr = other.head;
			while(curr != nullptr)
			{
				push_back(curr->data());
				curr = curr->next();
			}

			return *this;
		}

		virtual ~linkedList()
		{
			while(!(empty()))
			{
				pop_front();
			}
		}



		std::size_t size() const
		{
			return nodeCount;
		}

		bool empty() const
		{
			return (nodeCount == 0);
		}

		void print() const
		{
			print(std::cout);
		}

		void print(std::ostream &out) const;


		listNode<DataType>* gethead()
		{
			return head;
		}


		iterator begin()
		{
			return iterator(head);
		}

		const_iterator begin() const
		{
			return iterator(head);
		}

		iterator end()
		{
			return iterator(nullptr);
		}

		const_iterator end() const
		{
			return iterator(nullptr);
		}


		void debug(std::ostream &out) const;

	public:

		virtual void push_front(const DataType &newItem);

		virtual void push_back(const DataType &newItem);

		virtual void pop_front();

		virtual void pop_back();

		virtual void insert_before (iterator iter, const DataType &newItem);

		virtual void insert_after (iterator iter, const DataType &newItem);

		virtual iterator find(const DataType &existingItem);

		virtual bool erase(const DataType &currentItem);

		virtual iterator erase(iterator iter);

		virtual iterator back()
		{
			return iterator(tail);
		}
		virtual const_iterator back() const
		{
			return iterator(tail);
		}
};


//add node to front
template<class DataType>
void linkedList<DataType>::push_front(const DataType &newItem)
{
	//create new node with pointer
	listNode<DataType> *newNode = new listNode<DataType>(newItem);
	newNode->next(head);

	if(empty()) //check if empty --> update tail
	{
		tail = newNode;
	}
	else //update node pointers if size!=0
	{
		head->previous(newNode);
	}
	head = newNode; //update head, increase count

	nodeCount++;
}

//add to end
template<class DataType>
void linkedList<DataType>::push_back(const DataType &newItem)
{
	listNode<DataType> *newNode = new listNode<DataType>(newItem);
	newNode->next(nullptr);
	newNode->previous(tail);
	if(empty()) //check if empty
	{
		head = newNode; //update front
	}
	else //otherwise update end nodes
	{
		tail->next(newNode);
	}
	tail = newNode; //update tail, increase count

	nodeCount++;
}

//get rid of first element
template<class DataType>
void linkedList<DataType>::pop_front()
{
	if(!empty()) //only execute if not empty
	{
		listNode<DataType>* toDel = head;

		head = head->next(); //decrease count, delete node
		delete toDel;
		nodeCount--;
		if(empty())
		{
			tail = nullptr;
		}
		else //change adjacent pointers
		{
			head->previous(nullptr);
		}
	}
}

//remove from end
template<class DataType>
void linkedList<DataType>::pop_back()
{
	if(!empty()) //only execute if not empty
	{
		listNode<DataType>* toDel = tail;

		tail = tail->previous(); //decrease count, delete node
		delete toDel;
		nodeCount--;
		if(empty())
		{
			head = nullptr;
		}
		else //otherwise set adjacent pointers
		{
			tail->next(nullptr);
		}
	}
}

//iterator add node before
template<class DataType>
void linkedList<DataType>::insert_before (linkedList<DataType>::iterator iter, const DataType &newItem)
{
	if(iter == end() || iter == begin()) //check if iter node is null or beginning
	{
		push_front(newItem); //CHECK LATER
	}
	else
	{
		//change all adjacent pointers, increase count
		listNode<DataType> *newNode = new listNode<DataType>(newItem);

		newNode->previous(iter.current->previous());
		newNode->previous()->next(newNode);
		newNode->next(iter.current);
		iter.current->previous(newNode);

		nodeCount++;
	}
}

//iterator add after location
template<class DataType>
void linkedList<DataType>::insert_after (linkedList<DataType>::iterator iter, const DataType &newItem)
{
	if(iter == end() || iter == back()) //check if iter node is null or tail
	{
		push_back(newItem); //CHECK LATER
	}
	else
	{
		listNode<DataType> *newNode = new listNode<DataType>(newItem);

		//update adjacent pointers otherwise and inc count
		newNode->previous(iter.current);
		newNode->next(iter.current->next());
		newNode->next()->previous(newNode);
		iter.current->next(newNode);

		nodeCount++;
	}
}

//scan list with iterator for data value
template<class DataType>
typename linkedList<DataType>::iterator linkedList<DataType>::find(const DataType &existingItem)
{
	linkedList<DataType>::iterator searchNode = begin();
	while(searchNode != end()) //continue loop until found or end
	{
		if(searchNode.current->data() == existingItem) //check value
		{
			return searchNode;
		}
		else //move to next
		{
			searchNode++;
		}
	}
	return end(); //return null node if no match
}

//erase a node given only its data
template<class DataType>
bool linkedList<DataType>::erase(const DataType &currentItem)
{
	linkedList<DataType>::iterator iterNode = find(currentItem);
	//scan list with iterator for given data
	if(iterNode != end())
	{
		erase(iterNode); //call iterator erase if found
		return true;
	}
	else //false if nothing erased
	{
		return false;
	}
}

//erase a node given by iterator
template<class DataType>
typename linkedList<DataType>::iterator linkedList<DataType>::erase(linkedList<DataType>::iterator iter)
{
	if(iter != end()) //only execute if not null node
	{
		nodeCount--;
		if(empty()) //check if last element, set nullptr
		{
			head = nullptr;
			tail = nullptr;
		}
		else if(iter == begin()) //check if head in list with >1 nodes
		{
			 //update front
			head = iter.current->next();
			head->previous(nullptr);
			delete iter.current;
			return begin(); //return new head
		}
		else if(iter == back()) //check if tail in list >1 nodes
		{
			 // update new tail
			tail = iter.current->previous();
			tail->next(nullptr);
		}
		else //if in middle if array of >2 nodes
		{
			linkedList<DataType>::iterator nextIter(iter.current);

			nextIter++; //store next node, update adjacent pointers
			iter.current->previous()->next(nextIter.current);
			nextIter.current->previous(iter.current->previous());
			delete iter.current; //delete node, return next
			return nextIter;
		}
		delete iter.current; //delete node if not already (only deleted on paths with a return statement
	}
	return end(); //return null node if no next
}

//prints list data, one node per line
template<class DataType>
void linkedList<DataType>::print(std::ostream &out) const
{
	linkedList<DataType>::iterator curr(head); //loop with iterator
	for(; curr != end(); curr++)
	{
		out << *curr << std::endl;
	}
}



// the constructors for the listNode class are included here
// default constructor
template <class DataType>
listNode<DataType>::listNode()
	: dataType(), pNext(nullptr), pPrevious(nullptr)
{
}

// constructor with data
template <class DataType>
listNode<DataType>::listNode(const DataType &newItem)
	: dataType(newItem), pNext(nullptr), pPrevious(nullptr)
{
}

// note the code for the debug() function is included
// display a debug version of the list
template<class DataType>
void linkedList<DataType>::debug(std::ostream &out) const
{
	const unsigned int ADDRWIDTH = 10;
	out << "START DEBUG" << std::endl;
	out << "first  =" << std::setw(ADDRWIDTH) << head;
	out << ", last=" << std::setw(ADDRWIDTH) << tail;
	out << ", # nodes=" << size() << std::endl;
	unsigned int count = 1;

	for (auto current=head; current!= nullptr; current=current->next())
	{
		out << "node " << std::setw(2) << count;
		out << "=" << std::setw(ADDRWIDTH) << current;
		out << ", next=" << std::setw(ADDRWIDTH)
			<< current->next();
		out << ", previous=" << std::setw(ADDRWIDTH)
			<< current->previous();
		out << ", value=" << current->data() << std::endl;
		count++;
	}
	out << "END DEBUG" << std::endl;
}

// I have included a few function headers and bodies here where the syntax is odd
// Your implementation of non-inlined member funcctions needs to go there.
// default constructor


// this is one where the C++ stynax gets very odd. Since we are returning back an interator we
// need to qualify it with the class it is in (linkedList<DataType>::iterator and we
// have ot include the typename so the C++ comiler knows this is a typename and not some other
// template class usage.
// find the node and return the address to the node. Return
// nullptr if not found

// all of your member function need to be before the #endif
#endif /* DOUBLELINKEDLIST_H_ */
