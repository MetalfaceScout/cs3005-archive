#include <iostream>
#include <cmath>
#include <tuple>

#include "ColorTable.h"
#include "ComplexFractal.h"
#include "Image.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"
#include "image_menu.h"
#include "PPM.h"
#include "ActionData.h"

void diagonalQuadPattern(ActionData &action_data)
{
    PPM &image = action_data.getInputImage1();
    image.setMaxColorValue(255);
    image.setHeight(getInteger(action_data, "Image height? "));
    image.setWidth(getInteger(action_data, "Image width? "));
    int i = 0;
    int j = 0;
    for (i = 0; i < image.getHeight(); i++)
    {
        for (j = 0; j < image.getWidth(); j++)
        {
            if (i < image.getHeight() / 2)
            {
                image.setChannel(i, j, 0, 0);
            }
            else
            {
                image.setChannel(i, j, 0, 255);
            }
        }
    }
    for (i = 0; i < image.getHeight(); i++)
    {
        for (j = 0; j < image.getWidth(); j++)
        {
            if (j < image.getWidth() / 2)
            {
                image.setChannel(i, j, 2, 0);
            }
            else
            {
                image.setChannel(i, j, 2, 255);
            }
        }
    }
    for (i = 0; i < image.getHeight(); i++)
    {
        for (j = 0; j < image.getWidth(); j++)
        {
            image.setChannel(i, j, 1, ((2 * i + 2 * j) % 256));
        }
    }
}

void realStripedDiagonalPatternFunction(ActionData &action_data)
{
    PPM &p = action_data.getInputImage1();
    p.setHeight(getInteger(action_data, "Image height? "));
    p.setWidth(getInteger(action_data, "Image width? "));
    int maxColor = (p.getHeight() + p.getWidth()) / 3;
    unsigned char maxColorChar;
    if (maxColor > 255)
    {
        maxColorChar = 255;
    }
    else
    {
        maxColorChar = (char)maxColor;
    }
    p.setMaxColorValue(maxColorChar);

    int i;
    for (i = 0; i < (int)p.getHeight(); i++)
    {
        int j;
        for (j = 0; j < (int)p.getWidth(); j++)
        {
            unsigned char red = 0;
            unsigned char green = 0;
            unsigned char blue = 0;
            // Set red
            if ((i >= (int)p.getHeight() / 2) && ((i % 3) != 0))
            {
                red = p.getMaxColorValue();
            }
            else
            {
                red = 0;
            }
            // Set green
            int greenint = ((i + (int)p.getWidth() - j - 1) % (p.getMaxColorValue() + 1));
            green = (unsigned char)greenint;
            // Set blue
            if (j < i)
            {
                blue = 0;
            }
            else
            {
                blue = p.getMaxColorValue();
            }
            // os << "Writing " << (unsigned int) red << " " << (unsigned int) green << " " << (unsigned int) blue << " to " << i << "," << j << std::endl;
            p.setPixel(i, j, (int)red, (int)green, (int)blue);
        }
    }
}

void stripedDiagonalPattern(ActionData &action_data)
{
    // Now there's a function with some chest hair
    realStripedDiagonalPatternFunction(action_data);
}

void flagRomaniaPattern(ActionData &action_data)
{
    PPM &p = action_data.getInputImage1();
    int height = getInteger(action_data, "Image height? ");
    p.setMaxColorValue(255);
    p.setHeight(height);
    int width = ((height * 3) / 2);
    p.setWidth(width);
    int colorColumnWidth = (p.getWidth() / 3);
    int row;
    for (row = 0; row < (int)p.getWidth(); row++)
    {
        int column;
        for (column = 0; column < (int)p.getWidth(); column++)
        {
            if (column < ((int)p.getWidth()) / 3)
            {
                p.setPixel(row, column, 0, 43, 127);
            }
            else if (column < colorColumnWidth * 2)
            {
                p.setPixel(row, column, 252, 209, 22);
            }
            else
            {
                p.setPixel(row, column, 206, 17, 38);
            }
        }
    }
}

void setSize(ActionData &action_data)
{
    PPM &inputImage1 = action_data.getInputImage1();
    inputImage1.setHeight(getInteger(action_data, "Height? "));
    inputImage1.setWidth(getInteger(action_data, "Width? "));
}

void setMaxColorValue(ActionData &action_data)
{
    PPM &inputImage1 = action_data.getInputImage1();
    inputImage1.setMaxColorValue(getInteger(action_data, "Max color value? "));
}

void setChannel(ActionData &action_data)
{
    int row;
    int column;
    int channel;
    int value;

    row = getInteger(action_data, "Row? ");
    column = getInteger(action_data, "Column? ");
    channel = getInteger(action_data, "Channel? ");
    value = getInteger(action_data, "Value? ");

    PPM &inputImage1 = action_data.getInputImage1();
    inputImage1.setChannel(row, column, channel, value);
}

void setPixel(ActionData &action_data)
{
    int row;
    int column;
    int red;
    int green;
    int blue;

    row = getInteger(action_data, "Row? ");
    column = getInteger(action_data, "Column? ");
    red = getInteger(action_data, "Red? ");
    green = getInteger(action_data, "Green? ");
    blue = getInteger(action_data, "Blue? ");

    PPM &inputImage1 = action_data.getInputImage1();
    inputImage1.setPixel(row, column, red, green, blue);
}

/*
Sets all pixels color to 0.
*/
void clearAll(ActionData &action_data)
{
    PPM &inputImage1 = action_data.getInputImage1();
    int height = inputImage1.getHeight();
    std::vector<unsigned char> &vector = inputImage1.getImageData();
    vector.clear();
    inputImage1.setHeight(height); //Very hacky way of resizing the vector quick
}

void drawCircle(ActionData &action_data) {
    PPM &inputImage1 = action_data.getInputImage1();
    int centerRow = getInteger(action_data, "Center Row? ");
    int centerColumn = getInteger(action_data, "Center Column? ");
    int radius = getInteger(action_data, "Radius? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    //I wrote this and I barely understand it
    for (
        int row = (centerRow - radius) - 1;
        row <= (centerRow + radius + 1) && row >= (centerRow - radius - 1);
        row++
        ) 
        { //Rows
        for (
        int column = (centerColumn - radius) - 1;
        column <= (centerColumn + radius + 1) && column >= (centerColumn - radius - 1); 
        column++
        ) 
        { //Columns
            double result = (std::sqrt(((column - centerColumn) * (column - centerColumn)) + ((row - centerRow) * (row - centerRow))));
            if (result <= (double) radius) {
                inputImage1.setPixel(row, column, red, green, blue);
            }
        }
    }
}

void drawBox(ActionData &action_data) {
    PPM &inputImage1 = action_data.getInputImage1();
    int topRow = getInteger(action_data, "Top Row? ");
    int leftColumn = getInteger(action_data, "Left Column? ");
    int bottomRow = getInteger(action_data, "Bottom Row? ");
    int rightColumn = getInteger(action_data, "Right Column? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    for (
            int row = topRow;
            row <= bottomRow && row >= topRow;
            row++
        ) 
        { //Rows
        for (
            int column = leftColumn;
            column <= rightColumn && column >= leftColumn;
            column++
        ) 
        { //Columns
            inputImage1.setPixel(row, column, red, green, blue);
        }
    }
}

//Exam calls for copy paste (not really but im lazy)
void drawSquare(ActionData &action_data) {
    PPM &inputImage1 = action_data.getInputImage1();
    int centerRow = getInteger(action_data, "Row? ");
    int centerColumn = getInteger(action_data, "Column? ");
    int size = getInteger(action_data, "Size? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    int radius = size / 2;
    for (
        int row = (centerRow - radius);
        row <= (centerRow + radius) && row >= (centerRow - radius);
        row++
        ) 
        {
        for (
        int column = (centerColumn - radius);
        column <= (centerColumn + radius) && column >= (centerColumn - radius); 
        column++
        ) 
        {
            inputImage1.setPixel(row, column, red, green, blue);
        }
    }
}

void configureGrid(ActionData &action_data) {
    int gHeight = getInteger(action_data, "Grid Height? ");
    int gWidth = getInteger(action_data, "Grid Width? ");
    int gMaxValue = getInteger(action_data, "Grid Max Value? ");
    NumberGrid& grid = action_data.getGrid();
    grid.setGridSize(gHeight, gWidth);
    grid.setMaxNumber(gMaxValue);
}

void setGrid(ActionData& action_data) {
    int gRow = getInteger(action_data, "Grid Row? ");
    int gColumn = getInteger(action_data, "Grid Column? ");
    int gValue = getInteger(action_data, "Grid Value? ");
    NumberGrid& grid = action_data.getGrid();
    grid.setNumber(gRow, gColumn, gValue);
}

void applyGrid(ActionData &action_data) {
    PPM& output = action_data.getOutputImage();
    action_data.getGrid().setPPM(output);
}

void setColorTableSize(ActionData &action_data) {
    int size = getInteger(action_data, "Size? ");
    action_data.getTable().setNumberOfColors(size);
}

void setColor(ActionData &action_data) {
    int position = getInteger(action_data, "Position? ");
    int red = getInteger(action_data, "Red? ");
    int green = getInteger(action_data, "Green? ");
    int blue = getInteger(action_data, "Blue? ");
    action_data.getTable()[position] = std::make_tuple(red, green, blue);
}

void setRandomColor(ActionData &action_data) {
    int position = getInteger(action_data, "Position? ");
    action_data.getTable().setRandomColor(255, position);
}

void setColorGradient(ActionData &action_data) {
    int firstPosition = getInteger(action_data, "First position? ");
    int firstRed = getInteger(action_data, "First red? ");
    int firstGreen = getInteger(action_data, "First green? ");
    int firstBlue = getInteger(action_data, "First blue? ");
    int secondPosition = getInteger(action_data, "Second position? ");
    int secondRed = getInteger(action_data, "Second red? ");
    int secondGreen = getInteger(action_data, "Second green? ");
    int secondBlue = getInteger(action_data, "Second blue? ");
    Color color1(firstRed, firstGreen, firstBlue);
    Color color2(secondRed, secondGreen, secondBlue);
    action_data.getTable().insertGradient(color1, color2, firstPosition, secondPosition);
}

void setHueSaturationValueGradient(ActionData &action_data) {
    int firstPosition = getInteger(action_data, "First position? ");
    double firstHue = getDouble(action_data, "First hue? ");
    double firstSat = getDouble(action_data, "First saturation? ");
    double firstVal = getDouble(action_data, "First value? ");
    int secondPosition = getInteger(action_data, "Second position? ");
    double secondHue = getDouble(action_data, "Second hue? ");
    double secondSat = getDouble(action_data, "Second saturation? ");
    double secondVal = getDouble(action_data, "Second value? ");
    Color color1 = Color();
    Color color2 = Color();
    color1.setFromHSV(firstHue, firstSat, firstVal);
    color2.setFromHSV(secondHue, secondSat, secondVal);
    action_data.getTable().insertHueSaturationValueGradient(color1, color2, firstPosition, secondPosition);
}       

void applyGridColorTable(ActionData &action_data) {
    PPM& output = action_data.getOutputImage();
    action_data.getGrid().setPPM(output, action_data.getTable());
}

void setFractalPlaneSize(ActionData &action_data) {
    NumberGrid* ptr_grid = &action_data.getGrid(); 
    ComplexFractal* ptr_complexFractal = dynamic_cast<ComplexFractal*>(ptr_grid);
    if (ptr_complexFractal == NULL) {
        action_data.getOS() << "Not a ComplexFractal object. Can't set plane size." << std::endl;
        return;
    }
    double minX = getDouble(action_data, "Min X? ");
    double maxX = getDouble(action_data, "Max X? ");
    double minY = getDouble(action_data, "Min Y? ");
    double maxY = getDouble(action_data, "Max Y? ");
    ptr_complexFractal->setPlaneSize(minX, maxX, minY, maxY);
    return;
}

void calculateFractal(ActionData &action_data) {
    action_data.getGrid().calculateAllNumbers();
}

void calculateFractalSingleThread(ActionData &action_data) {
    action_data.getGrid().NumberGrid::calculateAllNumbers();
}

void setJuliaParameters(ActionData &action_data) {
    NumberGrid* ptr_grid = &action_data.getGrid(); 
    JuliaSet* ptr_juliaSet = dynamic_cast<JuliaSet*>(ptr_grid);
    if (ptr_juliaSet == NULL) {
        action_data.getOS() << "Not a JuliaSet object. Can't set parameters." << std::endl;
        return;
    }
    double paramA = getDouble(action_data, "Parameter a? ");
    double paramB = getDouble(action_data, "Parameter b? ");
    ptr_juliaSet->setParameters(paramA, paramB);
}

void setMandelbrotPower(ActionData &action_data) {
    NumberGrid* ptr_grid = &action_data.getGrid(); 
    MandelbrotPower* ptr_mandelbrotPower = dynamic_cast<MandelbrotPower*>(ptr_grid);
    if (ptr_mandelbrotPower == NULL) {
        action_data.getOS() << "Not a MandelbrotPower object. Can't set power." << std::endl;
        return;
    }
    double power = getDouble(action_data, "Power? ");
    ptr_mandelbrotPower->setPower(power);
}