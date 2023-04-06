/*
 * mainRunner.cpp
 *
 *  Created on: Nov 28, 2019
 *      Author: Luke H
 */

#include <fstream>
#include "RBTree.h"
#include "jWord.h"

int main() {
	//currently only opened for the proper number of elements
	std::ifstream ifs ("jPreOrderFile.txt");
	if(!(ifs.is_open()))
	{
		std::cout << "Open failed (PreOrder input)" << std::endl;
		return 1;
	}

	//opened to retrieve all elements in order
	std::ifstream ifs2 ("jOrderedWords.txt");
	if(!(ifs2.is_open()))
	{
		std::cout << "Open failed (Ordered input)" << std::endl;
		return 10;
	}

	RBTree<jWord> tree;
	linkedList<jWord> inOrder;

	//get size of tree from preorder
	int treeInitSize;
	ifs >> treeInitSize;

	int wordCount;
	std::string k;
	std::string w;
	std::string d;

	//read in words from Ordered, add them to linkedList
	for(int i = 0; i < treeInitSize; i++)
	{
		ifs2 >> wordCount;
		ifs2 >> k;
		jWord newWord(k);

		for(int j = 0; j < wordCount; j++)
		{
			ifs2 >> w;
			ifs2 >> d;
			newWord.add(w,d);
		}
		inOrder.push_back(newWord);

		//tree.insert(newWord, &update);
	}
	ifs.close();
	ifs2.close();
	//pass num of elements and linkedList to superBalancer; creates tree in most balanced form
	tree.superBalancer(treeInitSize, inOrder);

	std::cout << "Tree has " << tree.Size() << " initialized pronounciations\n" << std::endl;


	bool quit = false;
	while(!quit)
	{
		std::cout << "Add a word pronounciation (quit-now to stop):" << std::endl;
		std::cin >> w;
		if(w == "quit-now") //checks if user end loop
		{
			quit = !quit;
		}
		else
		{
			jWord newW(w);
			std::cout << "Kanji? If not write いい" << std::endl;
			std::cin >> w;

			if(w != "いい")
			{
				std::cout << "Definition? if not write いい" << std::endl;
				std::cin >> d;
				std::cout << "Kanji added" << std::endl;
				if(d != "いい")
				{
					newW.add(w,d);
					std::cout << "Def added" << std::endl;

				}
				else
				{
					newW.add(w);
					std::cout << "Def not added" << std::endl;
				}
			}
			else
			{
				std::cout << "Kanji not added" << std::endl;
			}
			tree.insert(newW, &update);
			std::cout << std::endl;
		}
	}

	std::cout << "Checking RB Tree Black nodes...";
	if(tree.checkBlackNodes())
	{
		std::cout << "  check success." << std::endl;
		std::cout << "Currently a max path difference of " << tree.checkHeightDiff() << " nodes." << std::endl;
		std::cout << std::endl;
	}
	else
	{
		std::cout << "  check failed.\nClosing without file alterations." << std::endl;
		return 2;
	}


	std::ofstream ofs1("jPreOrderFile.txt", std::ofstream::out | std::ofstream::trunc);
	if(!(ofs1.is_open()))
	{
		std::cout << "Open failed (PreOrder output)" << std::endl;
		return 2;
	}
	ofs1 << tree.Size() << std::endl;
	tree.traversePreOrder(ofs1, &addToFile);
	ofs1.close();


	std::ofstream ofs2("jOrderedWords.txt", std::ofstream::out | std::ofstream::trunc);
	if(!(ofs2.is_open()))
	{
		std::cout << "Open failed (Ordered Output)" << std::endl;
		return 3;
	}
	tree.traverse(ofs2, &addToFile);
	ofs2.close();

	std::cout << "All files closed successfully." << std::endl;

	return 0;
}


