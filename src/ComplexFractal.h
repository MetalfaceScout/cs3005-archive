#ifndef _COMPLEXFRACTAL_H_
#define _COMPLEXFRACTAL_H_
#include "NumberGrid.h"
#include "ThreadedGrid.h"

class ComplexFractal : public ThreadedGrid {
public:
    ComplexFractal();
    ComplexFractal(const int& height, const int& width, const double& minX, const double& maxX, const double& minY, const double& maxY);
    virtual ~ComplexFractal();
    double getMinX() const;
    double getMinY() const;
    double getMaxX() const;
    double getMaxY() const;
    virtual void setGridSize(const int& height, const int& width);
    void setPlaneSize(const double& min_X, const double& max_X, const double& min_Y, const double& max_Y);
    double getDeltaX() const;
    double getDeltaY() const;
    void setDeltas(const double& delta_X, const double& delta_Y);
    double calculateDeltaX() const;
    double calculateDeltaY() const;
    double calculatePlaneXFromPixelColumn(const int& column) const;
    double calculatePlaneYFromPixelRow(const int& row) const;
    void calculatePlaneCoordinatesFromPixelCoordinates(const int& row, const int& column, double& x, double& y) const;
    virtual int calculateNumber(const int& row, const int& column) const;

protected:
    double mMinX;
    double mMaxX;
    double mMinY;
    double mMaxY;
    double mDeltaX;
    double mDeltaY;

    /*
    Check if the given row and column exceed the object's height and witdth respectively.
    */
    bool checkRowAndColumnValid(const int& row, const int& column) const {
        if (row >= 0 && row < mHeight && column >= 0 && column < mWidth) {
            return true;
        }
        return false;
    }
};

#endif