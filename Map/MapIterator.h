#pragma once
#include "Map.h"
class MapIterator
{
	//DO NOT CHANGE THIS PART
	friend class Map;
private:
	const Map& map;
	HT HashTable;
	int currentPosition;

	HNode* currentNode;

	MapIterator(const Map& m);

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};


