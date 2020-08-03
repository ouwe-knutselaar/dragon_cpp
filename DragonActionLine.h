#ifndef DRAGONACTIONLINE_H_
#define DRAGONACTIONLINE_H_

#include <string>


class DragonActionLine {
public:
	DragonActionLine();
	virtual ~DragonActionLine();

    void fillFromString(std::string);
	unsigned int* getServoValues();

private:
	unsigned int servovalues[16];
};

#endif /* DRAGONACTIONLINE_H_ */
