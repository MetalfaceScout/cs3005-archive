#include <vector>
#include "Image.h"

#include <iostream>

Image::Image() :
    mHeight(0), mWidth(0) {
}


Image::Image(const int& height, const int& width) :
    mHeight(height), mWidth(width) {
        imageData.resize(((mHeight)*(mWidth))*3);
}

int Image::getHeight() const {
    return mHeight;
}

int Image::getWidth() const {
    return mWidth;
}

int Image::index(const int& row, const int& column, const int& channel) const {
    return ((row * mWidth * 3) + (column * 3)) + channel;
}
    /* 
    Checks if row, column, and channel are all within the legal limits. Returns true if they all are, and false otherwise.
    */
bool Image::indexValid(const int& row, const int& column, const int& channel) const {
    if (row >= (int) getHeight() || column >= (int) getWidth() || channel > 2) {
        return false;
    } else if (row < 0 || column < 0 || channel < 0) {
        return false;
    }
    int validIndex = index(row, column, channel);
    if ((validIndex < (int) imageData.size()) && validIndex >= 0) {
        return true;
    }
    return false;
}

/*
Returns the value of the pixel specified by row, column, and channel.
If the pixel is invalid, this will return a -1.
*/
int Image::getChannel(const int& row, const int& column, const int& channel) const {
    if (indexValid(row, column, channel)) {
        return imageData[index(row, column, channel)];
    }
    return -1;
}

void Image::setHeight(const int& height) {
    if (height >= 0) {
        mHeight = height;
        imageData.resize((mHeight*mWidth)*3);
    }
    
}

void Image::setWidth(const int& width) {
    if (width >= 0) {
        mWidth = width;
        imageData.resize((mHeight*mWidth)*3);
    }
}

/*
Sets the "value" of the pixel specified by a row, column, channel.
Does nothing if row and column are invalid.
*/
void Image::setChannel(const int& row, const int& column, const int& channel, const int& value) {
    if (indexValid(row, column, channel) && value >= 0 && value < 256) {
        imageData[index(row, column, channel)] = (unsigned char) value;
    }
}