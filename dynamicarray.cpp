#include "dynamicarray.h"
#include "DragonActionLine.h"
#include <ostream>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


dynamicarray::dynamicarray() {


}

dynamicarray::~dynamicarray() {
	// TODO Auto-generated destructor stub
}


void dynamicarray::pop(DragonActionLine value)
{
	list[counter] = value;
	counter++;
	if(counter >= max)
	{
		std::cerr<<" add new chunk\n";
		DragonActionLine *added_array = new DragonActionLine[numberOfNewElementsToAdd];
		DragonActionLine *temp = new DragonActionLine[max+numberOfNewElementsToAdd];
		memcpy(temp,list,max*sizeof(DragonActionLine));
		memcpy(temp + counter, added_array, numberOfNewElementsToAdd * sizeof(DragonActionLine));
		//free(list);
		list = temp;
		max = max+numberOfNewElementsToAdd;
	}
}


DragonActionLine dynamicarray::getElm(int pos)
{
	return list[pos];
}

int dynamicarray::size()
{
	return counter;
}


void dynamicarray::clear()
{
	counter = 0;
}
