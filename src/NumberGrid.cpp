#include <sched.h>
#include <vector>
#include <map>
#include "PPM.h"
#include "NumberGrid.h"
#include <cmath>

NumberGrid::NumberGrid(const int& height, const int& width) : mWidth(width), mHeight(height), mMaxNumber(255) {
    mNumbers.resize(mHeight * mWidth);
    for (int i = 0; i < (mHeight * mWidth); i++) {
        mNumbers[i] = 0;
    }
    configuremNumberMap();
};

NumberGrid::NumberGrid() : mWidth(400), mHeight(300), mMaxNumber(255) {
    mNumbers.resize(mWidth * mHeight);
    for (int i = 0; i < (mWidth * mHeight); i++) {
        mNumbers[i] = 0;
    }
    configuremNumberMap();
}

void NumberGrid::configuremNumberMap() { //Looking back, this was likely the worst way to do this
    unsigned char i;
    for (i = 0; i < 8; i++) {
        switch (i) {
            case 0:
                mNumberMap[0] = {63, 63, 63};
                break;
            case 1:
                mNumberMap[1] = {63, 31, 31};
                break;
            case 2:
                mNumberMap[2] = {63, 63, 31};
                break;
            case 3:
                mNumberMap[3] = {31, 63, 31};
                break;
            case 4:
                mNumberMap[4] = {0, 0, 0}; 
                break;
            case 5:
                mNumberMap[5] = {31, 63, 63};
                break;
            case 6:
                mNumberMap[6] = {31, 31, 63};
                break;
            case 7:
                mNumberMap[7] = {63, 31, 63};
                break;
        }
    }
}

NumberGrid::~NumberGrid() {}

int NumberGrid::getHeight() const {
    return mHeight;
}

int NumberGrid::getWidth() const {
    return mWidth;
}

int NumberGrid::getMaxNumber() const {  
    return mMaxNumber;
}

void NumberGrid::setGridSize(const int& height, const int& width) { 
    if (height >= 2 && width >= 2) {
        mHeight = height;
        mWidth = width;
        mNumbers.resize(mHeight * mWidth);
    }
}

void NumberGrid::setMaxNumber(const int& maxNumber) {
    if (maxNumber >= 0) {
        mMaxNumber = maxNumber;
    }
}

const std::vector<int>& NumberGrid::getNumbers() const {
    return mNumbers;
}

int NumberGrid::index(const int& row, const int& column) const {
    return ((row * mWidth) + column);
}

bool NumberGrid::indexValid(const int& row, const int& column) const {
    if (row < 0 || column < 0) {
        return false;
    }
    if (row >= mHeight || column >= mWidth) {
        return false;
    }
    int ind = index(row, column);
    if (ind < (int) mNumbers.size() && ind >= 0) { 
        return true;
    }
    return false;
}

bool NumberGrid::numberValid(const int& number) const {
    if (number <= mMaxNumber && number >= 0) {
        return true;
    }
    return false;
}

int NumberGrid::getNumber(const int& row, const int& column) const {
    if (indexValid(row, column)) {
        return mNumbers[index(row, column)];
    }
    return -1;
}

int* NumberGrid::getNumberRef(const int& row, const int& column) {
    if (indexValid(row, column)) {
        return &mNumbers[index(row, column)];
    }
    return 0;
}

void NumberGrid::setNumber(const int& row, const int& column, const int& number) {
    if (indexValid(row, column)) {
        if (numberValid(number)) {
            mNumbers[index(row, column)] = number;
        }
    }
}

void NumberGrid::setPPM(PPM& ppm) const {
    ppm.setWidth(this->mWidth);
    ppm.setHeight(this->mHeight);
    ppm.setMaxColorValue(63);
    unsigned int row;
    unsigned int col;
    for (row = 0; row < (unsigned int) this->mHeight; row++) {
        for (col = 0; col < (unsigned int) this->mWidth; col++) {
            int number = this->getNumber(row, col);
            std::tuple<unsigned int, unsigned int, unsigned int> value;

            if (number == 0) {
                value = {0, 0, 0};
            } else if (number == mMaxNumber) {
                value = {63, 31, 31};
            } else {
                value = mNumberMap.at(((unsigned char) number % 8));
            }

            ppm.setPixel(row, col, std::get<0>(value), std::get<1>(value), std::get<2>(value));
        }
    }
}

void NumberGrid::setPPM(PPM& ppm, const ColorTable& colors) const {
    if (colors.getNumberOfColors() <= 1) {
        return;
    }
    ppm.setWidth(this->mWidth);
    ppm.setHeight(this->mHeight);
    ppm.setMaxColorValue(colors.getMaxChannelValue());
    unsigned int row;
    unsigned int col;
    for (row = 0; row < (unsigned int) this->mHeight; row++) {
        for (col = 0; col < (unsigned int) this->mWidth; col++) {
            int number = this->getNumber(row, col);

            if (number == this->getMaxNumber()) {
                int highestIndex = colors.getNumberOfColors()-1;
                ppm.setChannel(row, col, 0, colors[highestIndex].getRed());
                ppm.setChannel(row, col, 1, colors[highestIndex].getGreen());
                ppm.setChannel(row, col, 2, colors[highestIndex].getBlue());
            } else {
                int ind = (this->getNumber(row, col) % colors.getNumberOfColors());
                ppm.setChannel(row, col, 0, colors[ind].getRed());
                ppm.setChannel(row, col, 1, colors[ind].getGreen());
                ppm.setChannel(row, col, 2, colors[ind].getBlue());
            }
        }
    }
}

void NumberGrid::calculateAllNumbers() {
    int col;
    int row;
    for (col = 0; col < getWidth(); ++col) {
        for (row = 0; row < getHeight(); ++row) {
           setNumber(row, col, calculateNumber(row, col));
        }
    }
}

//begin exam 3

ManhattanNumbers::ManhattanNumbers() : NumberGrid() {
    setGridSize(600, 800);
}

ManhattanNumbers::ManhattanNumbers(const int& height, const int& width) : NumberGrid(height, width) {
};

ManhattanNumbers::~ManhattanNumbers() {}

int ManhattanNumbers::calculateNumber(const int& row, const int& column) const {
    return (std::abs((column - mWidth/2))) + std::abs((row - mHeight/2));
}