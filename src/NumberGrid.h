#ifndef _NUMBER_GRID_H_
#define _NUMBER_GRID_H_

#include <tuple>
#include <vector>
#include <map>
#include "ColorTable.h"
#include "PPM.h"


class NumberGrid { 
public:

NumberGrid();
NumberGrid(const int& height, const int& width);
public:

    virtual ~NumberGrid();
    int getWidth() const;
    int getHeight() const;
    int getMaxNumber() const;
    virtual void setGridSize(const int& height, const int& width);
    void setMaxNumber(const int& number);
    const std::vector<int>& getNumbers() const;
    int index(const int& row, const int& column) const;
    bool indexValid(const int& row, const int& column) const;
    bool numberValid(const int& number) const;
    int getNumber(const int& row, const int& column) const;
    int* getNumberRef(const int& row, const int& column);
    void setNumber(const int& row, const int& column, const int& number);
    void setPPM(PPM& ppm) const;
    void setPPM(PPM& ppm, const ColorTable& colors) const;
    virtual int calculateNumber(const int& row, const int& column) const = 0;
    virtual void calculateAllNumbers();

protected:

int mWidth;
int mHeight;
int mMaxNumber;
std::vector<int> mNumbers;
std::map<unsigned char, std::tuple<unsigned char, unsigned char, unsigned char>> mNumberMap;

void configuremNumberMap();

};

class ManhattanNumbers : public NumberGrid {
public:
    ManhattanNumbers();
    ManhattanNumbers(const int& height, const int& width);
    virtual ~ManhattanNumbers();
    int calculateNumber(const int& row, const int& column) const;
};
#endif