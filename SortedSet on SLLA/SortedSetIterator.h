#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	SortedSetIterator(const SortedSet& m);

	int currentIndex;

public:
	void first();
	void next();
	TComp getCurrent();
	bool valid() const;
};

