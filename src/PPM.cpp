#include <functional>
#include <iostream>
#include "PPM.h"

PPM::PPM() :
   Image(), mMaxColor(1) {
}

PPM::PPM(const int& height, const int& width) :
    Image(height, width), mMaxColor(1) {
}

int PPM::getMaxColorValue() const {
    return mMaxColor;
}

bool PPM::valueValid(const int& value) const {
    if (value > (int) mMaxColor || value < 0) {
        return false;
    }
    return true;
}

void PPM::setMaxColorValue(const int& max_color_value) {
    if (max_color_value <= 255 && max_color_value >= 1) {
        mMaxColor = max_color_value;
    }
}  

void PPM::setPixel(const int& row, const int& column, const int& red, const int& green, const int& blue) {
    setChannel(row, column, 0, red);
    setChannel(row, column, 1, green);
    setChannel(row, column, 2, blue);
}

void PPM::writeStream(std::ostream &os) const {
    os << "P6 " << mWidth << " " << mHeight << " " << mMaxColor << "\n";
    os.write((char *) &PPM::imageData[0], PPM::imageData.size()); //rgbrgbrgb
}

void PPM::readStream(std::istream &is) {

    std::string fileIdentifier;
    is >> fileIdentifier;
    if (fileIdentifier != "P6") {
        throw std::exception();
    }
    int fileWidth;
    is >> fileWidth;
    setWidth(fileWidth);

    int fileHeight;
    is >> fileHeight;
    setHeight(fileHeight);

    int max_color_value;
    is >> max_color_value;
    setMaxColorValue(max_color_value);
  
    
    unsigned char c;

    is.read((char *) &c, 1);
    is.read((char *) &imageData[0], imageData.size());

}

std::vector<unsigned char>& PPM::getImageData() {
    return imageData;
}

void PPM::grayFromChannel(PPM &dst, const int &src_channel) const {
    dst.setHeight(this->getHeight());
    dst.setWidth(this->getWidth());
    dst.setMaxColorValue(this->getMaxColorValue());
    unsigned int i;
    for (i = 0; i < dst.getImageData().size(); i += 3) {
        unsigned char greyValue;
        if (src_channel == 0) {
            greyValue = imageData[i];
        } else if (src_channel == 1) {
            greyValue = imageData[i + 1];
        } else if (src_channel == 2) {
            greyValue = imageData[i + 2];
        }
        dst.getImageData()[i] = greyValue;
        dst.getImageData()[i+1] = greyValue;
        dst.getImageData()[i+2] = greyValue;
    }
}

void PPM::grayFromRed(PPM& dst) const {
    grayFromChannel(dst, 0);
}

void PPM::grayFromGreen(PPM &dst) const {
    grayFromChannel(dst, 1);
}

void PPM::grayFromBlue(PPM &dst) const {
    grayFromChannel(dst, 2);
}

/*
Calculates the linearColorMetric value of a pixel given row and column.
Returns -1.0 if the row and column were invalid.
*/
double PPM::linearColorimetricPixelValue(const int &row, const int &column) const {
    int pixelRed = getChannel(row, column, 0);
    int pixelGreen = getChannel(row, column, 1);
    int pixelBlue = getChannel(row, column, 2);
    if (pixelRed != -1 && pixelBlue != -1 && pixelGreen != -1) {
        return ((0.2126*pixelRed) + (0.7152*pixelGreen) + (0.0722*pixelBlue));
    }
    return -1.0;
}

/*
Sets the value of red, green, blue of every pixel of dst 
based on the linearColorMetric value of the pixel of this.
*/
void PPM::grayFromLinearColorimetric(PPM &dst) const {
    //Might as well use that function I had to make
    dst.setHeight(this->getHeight());
    dst.setWidth(this->getWidth());
    dst.setMaxColorValue(this->getMaxColorValue());
    unsigned int row;
    unsigned int column;
    for (row = 0; row < (unsigned int) dst.getHeight(); row++) {
        for (column = 0; column < (unsigned int) dst.getWidth(); column++) {
            int value = (int) linearColorimetricPixelValue(row, column);
            dst.setChannel(row, column, 0, value);
            dst.setChannel(row, column, 1, value);
            dst.setChannel(row, column, 2, value);
        }
    }
}

bool PPM::operator==(const PPM &rhs) const {
    if (rhs.imageData.size() == this->imageData.size()) {
        return true;
    }
    return false;
}

bool PPM::operator!=(const PPM& rhs) const {
    if (!PPM::operator==(rhs)) {
        return true;
    }
    return false;
}

bool PPM::operator<=(const PPM& rhs) const {
    if (this->imageData.size() <= rhs.imageData.size()) {
        return true;
    }
    return false;
}

bool PPM::operator>=(const PPM &rhs) const
{
    if (this->imageData.size() >= rhs.imageData.size())
    {
        return true;
    }
    return false;
}

bool PPM::operator<(const PPM &rhs) const
{
    if (this->imageData.size() < rhs.imageData.size())
    {
        return true;
    }
    return false;
}

bool PPM::operator>(const PPM &rhs) const
{
    if (this->imageData.size() > rhs.imageData.size())
    {
        return true;
    }
    return false;
}

PPM& PPM::operator+=(const PPM &rhs) {
    unsigned int i;
    for (i = 0; i < this->imageData.size(); i++) {
        int newValue = (int) this->imageData[i] + (int) rhs.imageData[i];
        if (valueValid(newValue)) {
            this->imageData[i] = (unsigned char) newValue;
        } else if (newValue < 0) {
            this->imageData[i] = (unsigned char) 0;
        } else {
            this->imageData[i] = (unsigned char) this->mMaxColor;
        }
    }
    return *this;
}

PPM& PPM::operator-=(const PPM &rhs) {
    unsigned int i;
    for (i = 0; i < this->imageData.size(); i++) {
        int newValue = this->imageData[i] - rhs.imageData[i];
        if (valueValid(newValue)) {
            this->imageData[i] = (unsigned char) newValue;
        } else if (newValue < 0) {
            this->imageData[i] = 0;
        } else {
            this->imageData[i] = this->mMaxColor;
        }
    }
    return *this;
}

PPM& PPM::operator*=(const double &rhs) {
    unsigned int i;
    for (i = 0; i < this->imageData.size(); i++) {
        int newValue = this->imageData[i] * rhs;
        if (valueValid(newValue)) {
            this->imageData[i] = (unsigned char) newValue;
        } else if (newValue < 0) {
            this->imageData[i] = 0;
        } else {
            this->imageData[i] = this->mMaxColor;
        }
    }

    return *this;
}

PPM& PPM::operator/=(const double &rhs) {
    unsigned int i;
    for (i = 0; i < this->imageData.size(); i++) {
        int newValue = this->imageData[i] / rhs;
        if (valueValid(newValue)) {
            this->imageData[i] = (unsigned char) newValue;
        } else if (newValue < 0) {
            this->imageData[i] = 0;
        } else {
            this->imageData[i] = this->mMaxColor;
        }
    }
    return *this;
}

PPM PPM::operator+(const PPM &rhs) const {
    PPM newPPM = PPM(this->mHeight, this->mWidth);
    newPPM.setMaxColorValue(this->mMaxColor);
    unsigned int i;
    for (i = 0; i < (unsigned int) rhs.imageData.size(); i++) {
        int newValue = this->imageData[i] + rhs.imageData[i];
        if (valueValid(newValue)) {
            newPPM.imageData[i] = (unsigned char) newValue;
        } else if (newValue < 0) {
            newPPM.imageData[i] = 0;
        } else {
            newPPM.imageData[i] = this->mMaxColor;
        }
    }
    return newPPM;
}

PPM PPM::operator-(const PPM &rhs) const {
    PPM newPPM = PPM(this->mHeight, this->mWidth);
    newPPM.setMaxColorValue(this->mMaxColor);
    unsigned int i;
    for (i = 0; i < this->imageData.size(); i++) {
        int newValue = this->imageData[i] - rhs.imageData[i];
        if (valueValid(newValue)) {
            newPPM.imageData[i] = (unsigned char) newValue;
        } else if (newValue < 0) {
            newPPM.imageData[i] = 0;
        } else {
            newPPM.imageData[i] = this->mMaxColor;
        }
    }
    return newPPM;
}

PPM PPM::operator*(const double &rhs) const {
    PPM newPPM = PPM(this->mHeight, this->mWidth);
    newPPM.setMaxColorValue(this->mMaxColor);
    unsigned int i;
    for (i = 0; i < this->imageData.size(); i++) {
        int newValue = this->imageData[i] * rhs;
        if (valueValid(newValue)) {
            newPPM.imageData[i] = (unsigned char) newValue;
        } else if (newValue < 0) {
            newPPM.imageData[i] = 0;
        } else {
            newPPM.imageData[i] = this->mMaxColor;
        }
    }
    return newPPM;
}

PPM PPM::operator/(const double &rhs) const {
    PPM newPPM = PPM(this->mHeight, this->mWidth);
    newPPM.setMaxColorValue(this->mMaxColor);
    unsigned int i;
    for (i = 0; i < this->imageData.size(); i++) {
        int newValue = this->imageData[i] / rhs;
        if (valueValid(newValue)) {
            newPPM.imageData[i] = (unsigned char) newValue;
        } else if (newValue < 0) {
            newPPM.imageData[i] = 0;
        } else {
            newPPM.imageData[i] = this->mMaxColor;
        }
    }
    return newPPM;
}

void PPM::orangeFilter(PPM& dst) const {
    dst.setHeight(this->mHeight);
    dst.setWidth(this->mWidth);
    dst.setMaxColorValue(this->mMaxColor);
    unsigned int i;
    for (i = 0; i < this->imageData.size(); i += 3) {
        int red = 2*(2*this->imageData[i]+imageData[i+1])/3;
        if (valueValid(red)) {
            dst.imageData[i] = (unsigned char) red;
        } else {
            dst.imageData[i] = this->mMaxColor;
        }
        int green = 2*(2*this->imageData[i]+imageData[i+1])/6;
        if (valueValid(green)) {
            dst.imageData[i+1] = (unsigned char) green;
        } else {
            dst.imageData[i+1] = this->mMaxColor;
        }
        int blue = (this->imageData[i+2]/2);
        if (valueValid(blue)) {
            dst.imageData[i+2] = (unsigned char) blue;
        } else {
            dst.imageData[i+2] = this->mMaxColor;
        }
    }
}