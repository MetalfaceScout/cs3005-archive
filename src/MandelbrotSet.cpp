#include "MandelbrotSet.h"
#include <cmath>

MandelbrotSet::MandelbrotSet() : ComplexFractal() {

}

MandelbrotSet::MandelbrotSet(const int& height, const int& width, const double& minX, const double& maxX, const double& minY, const double& maxY) : ComplexFractal(height, width, minX, maxX, minY, maxY) {}

MandelbrotSet::~MandelbrotSet() {}

//Calculate the next point in the set, where a = x coordinate in the plane from the grid and b is the y coordinate of the same plane value from the grid.
void MandelbrotSet::calculateNextPoint(const double x0, const double y0, const double &a, const double &b, double &x1, double &y1) const {
    x1 = (x0*x0) - (y0*y0) + a;
    y1 = (2*x0*y0) + b;
}

int MandelbrotSet::calculatePlaneEscapeCount(const double &a, const double &b) const {
    double x1;
    double y1;
    double x = 0;
    double y = 0;
    bool escaped;
    unsigned int escapeCount;
    calculateNextPoint(x, y, a, b, x1, y1);
    x = x1, y = y1;
    for (escapeCount = 0; (int) escapeCount < mMaxNumber; ++escapeCount, x = x1, y = y1) { 
        calculateNextPoint(x, y, a, b, x1, y1);
        escaped = ifEscapedSet(x, y);
        if (escaped)
            return escapeCount;
    }
    return escapeCount;
}

int MandelbrotSet::calculateNumber(const int& row, const int& column) const {
    if (checkRowAndColumnValid(row, column)) {
        double x, y;
        calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
        return calculatePlaneEscapeCount(x, y);
    }
    return -1;
}

//Begin power definition

MandelbrotPower::MandelbrotPower() : MandelbrotSet(), mPower(2.0) {} ;

MandelbrotPower::~MandelbrotPower() {}

void MandelbrotPower::calculateNextPoint(const double x0, const double y0, const double &a, const double &b, double &x1, double &y1) const {
    double r = std::sqrt(((x0*x0) + (y0*y0)));
    double theta = std::atan2(y0, x0);
    x1 = ((std::pow(r, mPower)) * (std::cos(mPower * theta))+a);
    y1 = ((std::pow(r, mPower)) * (std::sin(mPower * theta))+b);
}
