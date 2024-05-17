#ifndef _JULIASET_H_
#define _JULIASET_H_
#include "ComplexFractal.h"
#include <cmath>

class JuliaSet : public ComplexFractal {

public:
    JuliaSet();
    JuliaSet(const int& height, const int& width, const double& minX, const double& maxX, const double& minY, const double& maxY, const double& a, const double& b);
    virtual ~JuliaSet();
    double getA() const { return mParamA; }
    double getB() const { return mParamB; }
    void setParameters(const double& a, const double& b);
    virtual void calculateNextPoint(const double& x0, const double& y0, double& x1, double& y1) const;
    virtual int calculatePlaneEscapeCount(const double& x0, const double& y0) const;
    virtual int calculateNumber(const int& row, const int& column) const;

protected:
    double mParamA;
    double mParamB;

    bool ifEscapedSet(const double& x, const double& y) const {
        if (std::sqrt(((x)*(x) + (y)*(y))) > 2) {
            return true;
        }
        return false;
    }

};

#endif