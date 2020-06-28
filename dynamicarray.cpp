#include "dynamicarray.h"
#include "DragonActionLine.h"
#include <ostream>
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
	list[counter]=value;
	counter++;
	if(counter>=max)
	{
		DragonActionLine *added_array = new DragonActionLine[added];
		DragonActionLine *temp=new DragonActionLine[max+added];
		memcpy(temp,list,max*sizeof(int));
		memcpy(temp + counter, added_array, added * sizeof(int));
		delete(list);
		list=temp;
		max=max+added;
	}
}


DragonActionLine dynamicarray::getElm(int pos)
{
	return list[pos];
}
