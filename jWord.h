/*
 * jWord.h
 *
 *  Created on: Nov 28, 2019
 *      Author: Luke H
 */

#ifndef JWORD_H_
#define JWORD_H_

#include <iostream>
#include <iomanip>
#include <cstddef>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

class definer
{
	friend std::ostream& operator<<(std::ostream &out, const definer &curr);
public:
	definer(std::string w): kWord(w), wDef("X") {}
	definer(std::string w, std::string d): kWord(w), wDef(d) {}

	bool operator<(const definer &other) const
	{
		return kWord < other.kWord;
	}
	bool operator<=(const definer &other) const
	{
		return kWord <= other.kWord;
	}
	bool operator>(const definer &other) const
	{
		return kWord > other.kWord;
	}
	bool operator>=(const definer &other) const
	{
		return kWord >= other.kWord;
	}
	bool operator==(const definer &other) const
	{
		return kWord == other.kWord;
	}
	bool operator!=(const definer &other) const
	{
		return kWord != other.kWord;
	}

private:
	std::string kWord, wDef;
};

std::ostream& operator<<(std::ostream &out, const definer &curr)
{
	out << curr.kWord << "  " << curr.wDef;
	return out;
}


class jWord
{

	friend std::ostream& operator<<(std::ostream &out, const jWord &curr);
public:
	jWord(std::string k):proKey(k){}
	jWord(std::string k, std::string w):proKey(k)
	{
		definer r(w);
		wordList.push_back(r);
	}
	jWord(std::string k, std::string w, std::string d):proKey(k)
	{
		definer r(w, d);
		wordList.push_back(r);
	}

	std::string pronounciation() const
	{
		return proKey;
	}

	int size() const
	{
		return static_cast<int>(wordList.size());
	}

	void add(std::string w)
	{
		definer temp(w);
		if(std::find(wordList.begin(), wordList.end(), temp) == wordList.end())
		{
			wordList.push_back(temp);
		}
	}

	void add(std::string w, std::string d)
	{
		definer temp(w, d);
		if(std::find(wordList.begin(), wordList.end(), temp) == wordList.end())
		{
			wordList.push_back(temp);
		}
	}

	void add(jWord other)
	{
		if(proKey == other.proKey)
		{
			int j = other.size();

			for(int i = 0; i < j; i++)
			{
				if(std::find(wordList.begin(), wordList.end(),other.wordList[i]) == wordList.end())
				{
					wordList.push_back(other.wordList[i]);
				}
			}
		}
	}

	bool operator<(const jWord &other) const
	{
		return proKey < other.proKey;
	}
	bool operator<=(const jWord &other) const
	{
		return proKey <= other.proKey;
	}
	bool operator>(const jWord &other) const
	{
		return proKey > other.proKey;
	}
	bool operator>=(const jWord &other) const
	{
		return proKey >= other.proKey;
	}
	bool operator==(const jWord &other) const
	{
		return proKey == other.proKey;
	}
	bool operator!=(const jWord &other) const
	{
		return proKey != other.proKey;
	}

private:
	std::string proKey;
	std::vector<definer> wordList;
};

void update(jWord& exists, const jWord& newW)
{
	exists.add(newW);
}

void addToFile(const jWord& foundItem, std::ostream& out)
{
	out << foundItem;
}


std::ostream& operator<<(std::ostream &out, const jWord &curr)
{
	out << curr.size() << " " << curr.pronounciation() << std::endl;

	for(int i = 0; i < curr.size(); i++)
	{
		out << "\t" << curr.wordList[i] << std::endl;
	}
	out << std::endl;
	return out;
}

#endif /* JWORD_H_ */
