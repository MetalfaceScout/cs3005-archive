#ifndef _ACTIONDATA_H_
#define _ACTIONDATA_H_
#include <iostream>
#include "ColorTable.h"
#include "PPM.h"
#include "NumberGrid.h"

class ActionData {

public:
    ActionData(std::istream& is, std::ostream& os);
    std::istream& getIS();
    std::ostream& getOS();
    PPM& getInputImage1();
    PPM& getInputImage2();
    PPM& getOutputImage();
    bool getDone() const;
    void setDone();
    ~ActionData();
    NumberGrid& getGrid();
    void setGrid(NumberGrid *grid);
    ColorTable& getTable() {return mColorTable;}

private:
    std::istream& mInputStream;
    std::ostream& mOutputStream;
    PPM mInputImage1;
    PPM mInputImage2;
    PPM mOutputImage;
    NumberGrid * mNumberGrid;
    ColorTable mColorTable;
    bool mDone;

};

#endif