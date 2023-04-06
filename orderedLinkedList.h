/*
 * orderedLinkedList.h
 *
 *  Created on: Nov 29, 2019
 *      Author: Luke H
 */

#ifndef ORDEREDLINKEDLIST_H_
#define ORDEREDLINKEDLIST_H_

#include <cstddef>

#include "linkedList.h"

template<class DataType>
class orderedLinkedList
{
	public:
		typedef linkedList<DataType>              		unorderedLinkedList;
		typedef std::bidirectional_iterator_tag			iterator_category;
		typedef std::ptrdiff_t 					      	difference_type;
		typedef std::size_t						      	size_type;
		typedef typename unorderedLinkedList::iterator  iterator;
		typedef const iterator	  	               		const_iterator;
	private:
		unorderedLinkedList list;
	public:
		orderedLinkedList(): list() {}

		orderedLinkedList(const orderedLinkedList &other): list(other.list) {}

		const orderedLinkedList& operator=(const orderedLinkedList &other)
		{
			list = other.list;
			return *this;
		}

		virtual ~orderedLinkedList() {}

		listNode<DataType>* getHead()
		{
			return list.gethead();
		}


		iterator begin()
		{
			return list.begin();
		}

		iterator end()
		{
			return list.end();
		}

		const_iterator begin() const
		{
			return list.begin();
		}

		const_iterator end() const
		{
			return list.end();
		}


		virtual std::size_t size() const
		{
			return list.size();
		}

		virtual bool empty() const
		{
			return list.empty();
		}

		virtual void print() const
		{
			print(std::cout);
		}

		virtual void print(std::ostream &out) const
		{
			list.print(out);
		}

		virtual void debug(std::ostream &out) const
		{
			list.debug(out);
		}

		virtual iterator find(const DataType &existingItem)
		{
			return list.find(existingItem);
		}

		virtual bool erase(const DataType &currentItem)
		{
			return list.erase(currentItem);
		}

		virtual iterator erase(iterator iter)
		{
			return list.erase(iter);
		}


		virtual void insert(const DataType &newItem);

		iterator back()
		{
		   return list.back();
		}

		const_iterator back() const
		{
		   return list.back();
		}
};



//insert node in proper position to keep list ordered
template<class DataType>
void orderedLinkedList<DataType>::insert(const DataType &newItem)
{
	if(find(newItem) == end()) //only true when node is not in list
	{
		iterator mainSearch = begin(); //create iterator at beginning, set insert flag
		bool inserted = false;

		while(mainSearch != end()) //loop iterator through whole list unless broken
		{
			if(newItem < *mainSearch) //check if node is lower than current iterator node
			{
				//if yes, insert before iterator, set flag to true, end loop
				list.insert_before(mainSearch, newItem);
				inserted = true;
				mainSearch = end();
			}
			else //increment iterator if not lower
			{
				mainSearch++;
			}
		}
		if(!inserted) //if not yet inserted, add to end of list
		{
			list.push_back(newItem);
		}
	}
}

#endif /* ORDEREDLINKEDLIST_H_ */
