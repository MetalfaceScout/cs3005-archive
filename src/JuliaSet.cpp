#include "JuliaSet.h"
#include <cmath>

JuliaSet::JuliaSet() : ComplexFractal(), mParamA(-0.650492), mParamB(-0.478235) {
    mMaxNumber = 255;
}

JuliaSet::JuliaSet(const int& height, const int& width, const double& minX, const double& maxX, const double& minY, const double& maxY, const double& a, const double& b) : ComplexFractal(height, width, minX, maxX, minY, maxY), mParamA(a), mParamB(b) {
};

JuliaSet::~JuliaSet() {};

void JuliaSet::setParameters(const double &a, const double &b) {
    if (a <= 2.0 && a >= -2.0 && b <= 2.0 && b >= -2.0) {
        mParamA = a;
        mParamB = b;
    }
}

void JuliaSet::calculateNextPoint(const double& x0, const double& y0, double& x1, double& y1) const {
    x1 = (x0 * x0) - (y0 * y0) + mParamA;
    y1 = (2 * x0 * y0) + mParamB; 
}

int JuliaSet::calculatePlaneEscapeCount(const double& x0, const double& y0) const {
    unsigned int escapeCount;
    double x = x0;
    double y = y0;
    double xNext;
    double yNext;
    for (escapeCount = 0; (int) escapeCount < mMaxNumber; escapeCount++) {
        
        calculateNextPoint(x, y, xNext, yNext);
        bool escaped = ifEscapedSet(x, y);
        if (escaped) {
            return escapeCount;
        }
        x=xNext;
        y=yNext;
    }
    return escapeCount;
}

int JuliaSet::calculateNumber(const int& row, const int& column) const {
    if (checkRowAndColumnValid(row, column)) {
        double x, y;
        calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
        return calculatePlaneEscapeCount(x, y);
    }
    return -1;
}

