#include "ComplexFractal.h"
#include "NumberGrid.h"
#include "math.h"

ComplexFractal::ComplexFractal() :
    ThreadedGrid(201, 301), mMinX(-1.5), mMaxX(1.5), mMinY(-1), mMaxY(1), mDeltaX(0.01), mDeltaY(0.01) {
}

ComplexFractal::ComplexFractal(const int& height, const int& width, const double& minX, const double& maxX, const double& minY, const double& maxY) :
    ThreadedGrid(height, width), mMinX(minX), mMaxX(maxX), mMinY(minY), mMaxY(maxY), mDeltaX(0), mDeltaY(0) {
        setDeltas(calculateDeltaX(), calculateDeltaY());
}

ComplexFractal::~ComplexFractal() {}

double ComplexFractal::getMinX() const { return mMinX; }
double ComplexFractal::getMinY() const { return mMinY; }
double ComplexFractal::getMaxX() const { return mMaxX; }
double ComplexFractal::getMaxY() const { return mMaxY; }
double ComplexFractal::getDeltaX() const { return mDeltaX; }
double ComplexFractal::getDeltaY() const { return mDeltaY; }

void ComplexFractal::setGridSize(const int &height, const int &width) {
    if (height >= 2 && width >= 2) {
        int oldData = mNumbers.size();
        NumberGrid::setGridSize(height, width);
        if (oldData != (int) mNumbers.size()) {
            double deltaX = calculateDeltaX();
            double deltaY = calculateDeltaY();
            setDeltas(deltaX, deltaY);
        }
    }
}

void ComplexFractal::setPlaneSize(const double &min_X, const double &max_X, const double &min_Y, const double &max_Y) {
    if (!(min_X > 2 || max_X > 2 || min_Y > 2 || max_Y > 2 || min_X < -2 || max_X < -2 || min_Y < -2 || max_Y < -2)) {
        if (min_X != max_X && min_Y != max_Y) { //Death to me...
            bool swapX = false;
            bool swapY = false;
            if (min_X > max_X) {
                swapX = true;
            } 
            if (min_Y > max_Y) {
                swapY = true;
            }
            if (swapX == true) {
                mMinX = max_X;
                mMaxX = min_X;
            } else {
                mMinX = min_X;
                mMaxX = max_X;
            }
            if (swapY == true) {
                mMinY = max_Y;
                mMaxY = min_Y;
            } else {
                mMinY = min_Y;
                mMaxY = max_Y;
            }
            double deltaX = calculateDeltaX();
            double deltaY = calculateDeltaY();
            setDeltas(deltaX, deltaY);
        }
    }
}

void ComplexFractal::setDeltas(const double &delta_X, const double &delta_Y) {
    if (delta_X > 0 && delta_Y > 0) {
        mDeltaX = delta_X;
        mDeltaY = delta_Y;
    }   
}

double ComplexFractal::calculateDeltaX() const {
    return ((mMaxX - mMinX) / (mWidth - 1));
}

double ComplexFractal::calculateDeltaY() const {
    return ((mMaxY - mMinY) / (mHeight - 1));
}

double ComplexFractal::calculatePlaneXFromPixelColumn(const int &column) const {
    if (column >= 0 && column < mWidth) {
        return (mMinX + (column * mDeltaX));
    }
    return 0;
}

double ComplexFractal::calculatePlaneYFromPixelRow(const int &row) const {
    if (row >= 0 && row < mHeight) {
        return (mMaxY - (row * mDeltaY));
    }
    return 0;
}

void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates(const int &row, const int &column, double& x, double& y) const {
    if (checkRowAndColumnValid(row, column)) {
        x = calculatePlaneXFromPixelColumn(column);
        y = calculatePlaneYFromPixelRow(row);
    } else {
        x = 0;
        y = 0;
    }
}

int ComplexFractal::calculateNumber(const int &row, const int &column) const {
    if (checkRowAndColumnValid(row, column)) {
        double x;
        double y;
        calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
        int number = std::abs(getMaxNumber() * std::sin(10*x) * std::cos(10*y));
        return number;
    }
    return -1;
}
