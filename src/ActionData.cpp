/*

input_image_1 <- scratch drawing, reading, editing
input_image_2 
output_image <- now is a copy of input_image_1

we'll be filtering PPM images to greyscale

var& <- ampersand means BY REFERENCE, do not forget
you can return a reference

void readStream()
readstream reverses the write stream, essentially taking a ppm file and putting it into a ppm object
the read operator stops when it sees whitespace, but stays in the same place


std::string p6;
is >> p6;
int newWidth;
is >> newWidth;
... So on for the next ASCII values

is.read((char *) &c, 1); advance input stream pointer one byte (newline) (10)
now.... we read
my vector is special so I likely could just read with one line, and calculate my readsize with my width and height

*/

#include "ActionData.h"
#include "image_menu.h"
#include <iostream>

ActionData::ActionData(std::istream& is, std::ostream& os) :
    mInputStream(is), mOutputStream(os), mNumberGrid(0), mColorTable(16), mDone(false) {
        mColorTable.insertGradient(Color(0,255,0), Color(255,0,255), 0, 15);
}

std::istream& ActionData::getIS() {
    return mInputStream;
}

std::ostream& ActionData::getOS() {
    return mOutputStream;
}

PPM& ActionData::getInputImage1() {
    return mInputImage1;
}

PPM& ActionData::getInputImage2() {
    return mInputImage2;
}

PPM& ActionData::getOutputImage() {
    return mOutputImage;
}

bool ActionData::getDone() const {
    return mDone;
}

void ActionData::setDone() {
    mDone = true;
    return;
}

NumberGrid& ActionData::getGrid() {
    return *mNumberGrid;
}

void ActionData::setGrid(NumberGrid *grid) {
    if (mNumberGrid) {
        delete mNumberGrid;        
    }
    mNumberGrid = grid;
}

ActionData::~ActionData() {
    if (mNumberGrid) {
        delete mNumberGrid;
    }
}