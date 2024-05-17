#ifndef _MANDELBROTSET_H_
#define _MANDELBROTSET_H_

#include "ComplexFractal.h"
#include <math.h>

class MandelbrotSet : public ComplexFractal {

public:
    MandelbrotSet();
    MandelbrotSet(const int& height, const int& width, const double& minX, const double& maxX, const double& minY, const double& maxY);
    virtual ~MandelbrotSet();
    virtual void calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double& y1) const;
    int calculatePlaneEscapeCount(const double& a, const double& b) const;
    virtual int calculateNumber(const int& row, const int& column) const;

private:
    bool ifEscapedSet(const double& x, const double& y) const {
        if (std::sqrt(((x)*(x) + (y)*(y))) > 2) {
            return true;
        }
        return false;
    }


};

class MandelbrotPower : public MandelbrotSet {
public:
    MandelbrotPower();
    virtual ~MandelbrotPower();
    double getPower() const { return mPower;}
    void setPower(const double& power) { mPower = power; }
    virtual void calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double &y1) const;

private:
    double mPower;
    
};
#endif