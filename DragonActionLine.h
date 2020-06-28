#ifndef DRAGONACTIONLINE_H_
#define DRAGONACTIONLINE_H_

#include <string>

class DragonActionLine {
public:
	DragonActionLine();
	virtual ~DragonActionLine();

    void fillFromString(std::string);
	void setValue(int pos, int value);
	int getValue(int pos);

private:
	int servovalues[16];
};

#endif /* DRAGONACTIONLINE_H_ */
