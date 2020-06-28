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

private:
	int counter=0;
	int max=10;
	DragonActionLine *list=new DragonActionLine[10];
	int added=10;
};

#endif /* DYNAMICARRAY_H_ */
