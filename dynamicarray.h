#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

#include "DragonActionLine.h"

class dynamicarray {
public:
	dynamicarray();
	virtual ~dynamicarray();
	void clear();
	void pop(DragonActionLine elm);
	DragonActionLine getElm(int pos);
	int size();

private:
	int counter = 0;
	int max = 1000;
	DragonActionLine *list = new DragonActionLine[10];
	int numberOfNewElementsToAdd = 100;
};

#endif /* DYNAMICARRAY_H_ */
