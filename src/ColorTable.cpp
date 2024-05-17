#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
#include "ColorTable.h"

Color::Color() : mColorData(3) {
    mColorData.resize(3);
    mColorData[0] = 0;
    mColorData[1] = 0;
    mColorData[2] = 0;
}

Color::Color(const int& red, const int& green, const int& blue) :
    mColorData(3)
{
    mColorData.resize(3);
    mColorData[0] = red;
    mColorData[1] = green;
    mColorData[2] = blue;
}

void Color::setRed(const int &value) {
    if (value >= 0) {
        mColorData[0] = value;
    }
}

void Color::setBlue(const int &value) {
    if (value >= 0) {
        mColorData[2] = value;
    }
}

void Color::setGreen(const int& value) {
    if (value >= 0) {
        mColorData[1] = value;
    }
}

int Color::getChannel(const int& channel) const {
    if (channel >= 0 && channel < 3) {
        return mColorData[channel];
    }
    return -1;
}

void Color::setChannel(const int &channel, const int &value) {
    if (channel >= 0 && channel < 3 && value >= 0) {
        mColorData[channel] = value;
        
        for (int i = 0; i < 3; i++) {
            if (mColorData[i] < 0) {
                mColorData[i] = 0;
            }
            if (mColorData[i] > 255) {
                mColorData[i] = 255;
            }
        }
    }
}

void Color::invert(const int &max_color_value) {
    int maxValue = std::max(std::max(mColorData[0], mColorData[1]), mColorData[2]);
    if (maxValue > max_color_value) {
        return;
    }
    mColorData[0] = max_color_value - mColorData[0];
    mColorData[1] = max_color_value - mColorData[1];
    mColorData[2] = max_color_value - mColorData[2];
}

bool Color::operator==(const Color &rhs) const {
    if (rhs.getRed() == this->getRed() &&
        rhs.getGreen() == this->getGreen() &&
        rhs.getBlue() == this->getBlue()) {
            return true;
        }
    return false;
}

Color& Color::operator=(const std::tuple<int, int, int>& colors) {
    mColorData[0] = std::get<0>(colors);
    mColorData[1] = std::get<1>(colors);
    mColorData[2] = std::get<2>(colors);
    return *this;
}

Color& Color::operator+=(const std::tuple<int, int, int>& colors) {
    mColorData[0] = std::get<0>(colors);
    mColorData[1] = std::get<1>(colors);
    mColorData[2] = std::get<2>(colors);

    for (int i = 0; i < 3; i++) {
        if (mColorData[i] > 255){
            mColorData[i] = 255;
        }
    }

    return *this;
}


std::ostream& operator<<(std::ostream& os, const Color& color) {
    return os << color.getRed() << ":" << color.getGreen() << ":" << color.getBlue();
}

void Color::setFromHSV(const double &hue, const double &saturation, const double &value) {
    double r, g, b;
    HSV_to_RGB(hue, saturation, value, r, g, b);
    setRed(r);
    setGreen(g);
    setBlue(b);
}

void Color::getHSV(double &hue, double &saturation, double &value) const {
    RGB_to_HSV(getRed(), getGreen(), getBlue(), hue, saturation, value);
}

//Copy Paste :)
//////////////////////////////////////////////////////////////////////////
///
void HSV_to_RGB(const double& hue, const double& saturation, const double& value, double& red, double &green, double& blue) {
  /* Convert Hue, Saturation, Value to Red, Green, Blue
   * Implementation of algorithm from:
   * https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
   *
   * Inputs and ranges:
   * 0.0 <= hue <= 360.0
   * 0.0 <= saturation <= 1.0
   * 0.0 <= value <= 1.0
   *
   * Outputs and ranges:
   * 0.0 <= red <= 255.0
   * 0.0 <= green <= 255.0
   * 0.0 <= blue <= 255.0
   */
  if(hue < 0.0 || hue > 360.0 || saturation < 0.0 || saturation > 1.0 || value < 0.0 || value > 1.0) {
    red = green = blue = 0.0;
    std::cerr << "HSV_to_RGB() input parameters out of range." << std::endl
              << " hue: " << hue  << std::endl
              << " saturation: " << saturation << std::endl
              << " value: " << value << std::endl;
    return;
  }

  // chroma selects the strength of the "primary" color of the current area of the wheel
  double chroma = value * saturation;
  // hue2 selects which 60-degree wedge of the color wheel we are in
  double hue2 = hue / 60.0;
  // x selects the strength of the "secondary" color of the current area of the wheel
  double x = chroma * ( 1 - std::abs( std::fmod( hue2, 2 ) - 1 ) );
  if( hue2 >= 0 && hue2 < 1 ) {
    red = chroma;
    green = x;
    blue = 0.0;
  } else if( hue2 >= 1 && hue2 < 2 ) {
    red = x;
    green = chroma;
    blue = 0.0;
  } else if( hue2 >= 2 && hue2 < 3 ) {
    red = 0.0;
    green = chroma;
    blue = x;
  } else if( hue2 >= 3 && hue2 < 4 ) {
    red = 0.0;
    green = x;
    blue = chroma;
  } else if( hue2 >= 4 && hue2 < 5 ) {
    red = x;
    green = 0.0;
    blue = chroma;
  } else if( hue2 >= 5 && hue2 <= 6 ) {
    red = chroma;
    green = 0.0;
    blue = x;
  } else {
    red = 0;
    green = 0;
    blue = 0;
  }

  // m scales all color channels to obtain the overall brightness.
  double m = value - chroma;
  red = 255.0*( red + m );
  green = 255.0*( green + m );
  blue = 255.0*( blue + m );
}
void RGB_to_HSV(const double& red0, const double &green0, const double& blue0, double& hue, double& saturation, double& value) {
  /* Red, Green, Blue to Convert Hue, Saturation, Value
   * Implementation of algorithm from:
   * https://en.wikipedia.org/wiki/HSL_and_HSV#From_RGB
   *
   * Inputs and ranges:
   * 0.0 <= red <= 255.0
   * 0.0 <= green <= 255.0
   * 0.0 <= blue <= 255.0
   *
   * Outputs and ranges:
   * 0.0 <= hue <= 360.0
   * 0.0 <= saturation <= 1.0
   * 0.0 <= value <= 1.0
   */
  if(red0 < 0.0 || red0 > 255.0 || green0 < 0.0 || green0 > 255.0 || blue0 < 0.0 || blue0 > 255.0) {
    hue = saturation = value = 0.0;
    std::cerr << "RGB_to_HSV() input parameters out of range." << std::endl
              << " red: " << red0  << std::endl
              << " green: " << green0 << std::endl
              << " blue: " << blue0 << std::endl;
    return;
  }

  double red   = red0 / 255.0;
  double green = green0 / 255.0;
  double blue  = blue0 / 255.0;

  // x_max helps identify the primary hue
  double x_max = red;
  if(green > x_max) { x_max = green; }
  if(blue > x_max) { x_max = blue; }
  value = x_max;

  double x_min = red;
  if(green < x_min) { x_min = green; }
  if(blue < x_min) { x_min = blue; }

  double chroma = x_max - x_min;

  if(chroma == 0) {
    hue = 0;
  } else if(value == red) {
    hue = 60.0 * (0 + (green - blue)/chroma);
  } else if(value == green) {
    hue = 60.0 * (2 + (blue - red)/chroma);
  } else if(value == blue) {
    hue = 60.0 * (4 + (red - green)/chroma);
  } else {
    hue = -720.0;
  }
  if(hue < 0.0) {
    hue += 360.0;
  }

  if(value == 0.0) {
    saturation = 0.0;
  } else {
    saturation = chroma/value;
  }

}
///
//////////////////////////////////////////////////////////////////////////



ColorTable::ColorTable( const int& num_color ) {
    mColorData.resize( num_color );
}

int ColorTable::getNumberOfColors() const { return mColorData.size(); }

void ColorTable::setNumberOfColors(const int& num_color ) { mColorData.resize( num_color ); }

const Color& ColorTable::operator[](const int& index) const {
    if (indexValid(index)) {
       return mColorData[index];  
    } else {
        return returnStaticColor();
    }
}

Color& ColorTable::operator[](const int& index) {
    if (indexValid(index)) {
        return mColorData[index];
    } else {
        return returnStaticColor();
    }
}

void ColorTable::setRandomColor(const int& max_color_value, const int& position) {
    if (indexValid(position) && max_color_value >= 0) {
        Color& c = mColorData[position];
        if (max_color_value == 0) {
            c.setRed(0);
            c.setGreen(0);
            c.setBlue(0);
            return;
        }
        
        c.setRed(int(std::rand() % max_color_value));
        c.setGreen(int(std::rand() % max_color_value));
        c.setBlue(int(std::rand() % max_color_value));
    }
}

double ColorTable::gradientSlope(const double y1, const double y2, const double x1, const double x2) const {
    return (((y1-y2))/((x1-x2)));
}

double ColorTable::gradientValue(const double y1, const double x1, const double slope, const double x) const {
    double yVal = (slope * (x - x1)) + y1;
    return yVal;
}

void ColorTable::insertGradient(const Color &color1, const Color &color2, const int &position1, const int &position2) {
    if (position1 < position2 && position2 < (int) mColorData.size()) {
        double slopeRed = gradientSlope(color1.getRed(), color2.getRed(), position1, position2);
        double slopeGreen = gradientSlope(color1.getGreen(), color2.getGreen(), position1, position2);
        double slopeBlue = gradientSlope(color1.getBlue(), color2.getBlue(), position1, position2);
        unsigned int i;
        for (i = (unsigned int) position1; i <= (unsigned int) position2; i++) {
            Color& color = mColorData[i];
            color.setRed(gradientValue(color1.getRed(), position1, slopeRed, i));
            color.setGreen(gradientValue(color1.getGreen(), position1, slopeGreen, i));
            color.setBlue(gradientValue(color1.getBlue(), position1, slopeBlue, i));
        }
    }
}

void ColorTable::insertHueSaturationValueGradient(const Color &color1, const Color &color2, const int &position1, const int &position2) {
    if (position1 < position2 && position2 < (int) mColorData.size()) {
        //std::cout << "Incoming position: " << position1 << " " << position2 << std::endl;
        double h1,s1,v1;
        double h2,s2,v2; //Could have used getHSV
        color1.getHSV(h1, s1, v1);
        color2.getHSV(h2, s2, v2);
        double slopeHue = gradientSlope(h1, h2, position1, position2);
        double slopeSaturation = gradientSlope(s1, s2, position1, position2);
        double slopeValue = gradientSlope(v1, v2, position1, position2);
        //std::cout << h1 << " " << s1 << " " << v1 << std::endl;
        unsigned int i;
        for (i = (unsigned int) position1; i <= (unsigned int) position2; i++) {
            Color& color = mColorData[i];
            color.setFromHSV(
                gradientValue(h1, position1, slopeHue, i),
                gradientValue(s1, position1, slopeSaturation, i),
                gradientValue(v1, position1, slopeValue, i)
            );
        }
    }
}

int ColorTable::getMaxChannelValue() const { //Challenge: code something in the wackiest way possible
    unsigned int i;
    int biggestColor = 0;
    int red;
    int green;
    int blue;
    for (i = 0; i < mColorData.size(); i++) {
        red = mColorData[i].getRed();
        green = mColorData[i].getGreen();
        blue = mColorData[i].getBlue();
        //Returns the biggest color
        biggestColor = (std::max(std::max(std::max(red,biggestColor), std::max(green, biggestColor)), std::max(blue, biggestColor)));
    }
    return biggestColor;
}
