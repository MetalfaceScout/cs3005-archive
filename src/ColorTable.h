#ifndef _COLORTABLE_H_
#define _COLORTABLE_H_
#include <iostream>
#include <vector>

class Color {

public:
    Color();
    Color(const int& red, const int& green, const int& blue);
    int getRed() const {return mColorData[0];}
    int getGreen() const {return mColorData[1];}
    int getBlue() const {return mColorData[2];}
    int getChannel(const int& channel) const;
    void setRed(const int& value);
    void setBlue(const int& value);
    void setGreen(const int& value);
    void setChannel(const int& channel, const int& value);
    void invert(const int& max_color_value);
    bool operator==(const Color& rhs) const;
    Color& operator=(const std::tuple<int, int, int>& colors);
    Color& operator+=(const std::tuple<int, int, int>& colors);
    void setFromHSV(const double& hue, const double& saturation, const double& value);
    void getHSV(double& hue, double& saturation, double& value) const;
    

private:
    std::vector<int> mColorData;
};

std::ostream& operator<<(std::ostream& os, const Color& color);

class ColorTable {

public:
    ColorTable(const int& num_color);
    int getNumberOfColors() const;
    void setNumberOfColors(const int& num_color);
    const Color& operator[](const int& i) const;
    Color& operator[](const int& i);
    void setRandomColor(const int& max_color_value, const int& position);
    double gradientSlope(const double y1, const double y2, const double x1, const double x2) const;
    double gradientValue(const double y1, const double x1, const double slope, const double x) const;
    void insertGradient(const Color& color1, const Color& color2, const int& position1, const int& position2);
    void insertHueSaturationValueGradient(const Color& color1, const Color& color2, const int& position1, const int& position2);
    int getMaxChannelValue() const;

private:
    std::vector<Color> mColorData;
    bool indexValid(const int& index) const {
        if (index >= (int) mColorData.size() || index < 0) {
            return false;
        }
        return true;
    }

    Color& returnStaticColor() const {
        static Color c1(-1, -1, -1);
        static Color c2(-1, -1, -1);
        c1 = c2;
        return c1;
    }

};

void HSV_to_RGB(const double& hue, const double& saturation, const double& value, double& red, double &green, double& blue);
void RGB_to_HSV(const double& red, const double &green, const double& blue, double& hue, double& saturation, double& value);

#endif