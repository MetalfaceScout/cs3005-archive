#include "ComplexFractal.h"
#include "MandelbrotSet.h"
#include "NumberGrid.h"
#include "image_menu.h"
#include "Image.h"
#include "PPM.h"
#include "ActionData.h"
#include "MenuData.h"
#include "JuliaSet.h"
#include <iostream>

/*
gdb - debugging
next - step through the next instruction or statement
print <var> - can print objects
run - run program
break <function> - set breakpoint
continue - continue execution
step - low level next, goes line by line through methods
*/

/*
Syntax for inheritance
#include "ChildClass.h"

class ChildClass: public Point {

}

.cpp:

ChildClass::ChildClass()
    : Point(), mZ(0.0) {

}

ChildClass::ChildClass(parent param, child param) {

}

std::map<key, value>
std::map i = std::map<std::string, int>

Operator Overloading

bool Widget::operator==(const Widget)& <- method way of operator overloading
bool operator==(const Widget&, const Widget&)
Widget == Widget

CLASS& operator+=(const int& rhs); //Right hand side -> rhs
CLASS& operator-=(const int& rhs);

z = x += y <---- Is legal, WHY?
(x += y) += 1; <---- For this reason, we have to return a reference to the variable we modified

CLASS CLASS::operator+=(const int& rhs) {
    this->do stuff;
    return *this; <-- variable is a pointer, defererence it first
}

new keywork = heap
new returns a pointer to the place on the heap
*int returns the value of the address of whatever space we made

delete [] <space>;
[] means that because we allocated an array, we have to delete an array

pull unit test at start of exam

Complex fractals

DeltaY:
(Ymax - Ymin/ n - 1)

Yi = (Ymax - i*DeltaY(hopsize))

Ymax
|
|----------- Xmax
|
Ymin

Now DeltaY: (Ymax - Ymin/ n -1)

*/

int assignment1(std::istream& is, std::ostream& os) 
{
    ActionData action_data = ActionData(is, os);
    return askQuestions3(action_data);
}

int assignment2(std::istream &is, std::ostream &os)
{
    ActionData action_data = ActionData(is, os);
    diagonalQuadPattern(action_data);
    action_data.getOutputImage() = action_data.getInputImage1();
    drawAsciiImage(action_data);
    return 0;
}

int assignment3(std::istream &is, std::ostream &os)
{
    ActionData action_data = ActionData(is, os);
    stripedDiagonalPattern(action_data);
    action_data.getOutputImage() = action_data.getInputImage1();
    writeUserImage(action_data);
    return 0;
}

int flag_romania(std::istream& is, std::ostream& os)
{
    ActionData action_data = ActionData(is, os);
    flagRomaniaPattern(action_data);
    action_data.getOutputImage() = action_data.getInputImage1();
    writeUserImage(action_data);
    return 0;
}

void showMenu(MenuData &menu_data, ActionData &action_data)
{
    unsigned char item;
    std::vector<std::string> names = menu_data.getNames();
    for (item = 0; item < names.size(); item++)
    {
        action_data.getOS() << names[item] << ") " << menu_data.getDescription(names[item]) << std::endl;
    }
}

void takeAction(const std::string &choice, MenuData &menu_data, ActionData &action_data)
{
    ActionFunctionType callback;
    if (choice == "menu")
    {
        showMenu(menu_data, action_data);
        return;
    }
    else
    {
        callback = menu_data.getFunction(choice);
    }

    if (callback != 0)
    {
        callback(action_data);
    }
    else
    {
        action_data.getOS() << "Unknown action '" << choice << "'." << std::endl;
    }
}

void configureMenu(MenuData &menu_data)
{
    menu_data.addAction("draw-ascii", drawAsciiImage, "Write output image to terminal as ASCII art.");
    menu_data.addAction("write", writeUserImage, "Write output image to file.");
    menu_data.addAction("copy", copyImage, "Copy input image 1 to output image.");
    menu_data.addAction("read1", readUserImage1, "Read file into input image 1.");
    menu_data.addAction("#", commentLine, "Comment to end of line.");
    menu_data.addAction("size", setSize, "Set the size of input image 1.");
    menu_data.addAction("max-color-value", setMaxColorValue, "Set the max color value of input image 1.");
    menu_data.addAction("channel", setChannel, "Set a channel value in input image 1.");
    menu_data.addAction("pixel", setPixel, "Set a pixel's 3 values in input image 1.");
    menu_data.addAction("clear", clearAll, "Set all pixels to 0,0,0 in input image 1.");
    menu_data.addAction("read2", readUserImage2, "Read file into input image 2.");
    menu_data.addAction("+", plus, "Set output image from sum of input image 1 and input image 2.");
    menu_data.addAction("-", minus, "Set output image from difference of input image 1 and input image 2.");
    menu_data.addAction("*", times, "Set output image from input image 1 multiplied by a number.");
    menu_data.addAction("/", divide, "Set output image from input image 1 divided by a number.");
    menu_data.addAction("+=", plusEquals, "Set input image 1 by adding in input image 2.");
    menu_data.addAction("-=", minusEquals, "Set input image 1 by subtracting input image 2.");
    menu_data.addAction("*=", timesEquals, "Set input image 1 by multiplying by a number.");
    menu_data.addAction("/=", divideEquals, "Set input image 1 by dividing by a number.");
    menu_data.addAction("red-gray", grayFromRed, "Set output image by grayscale from red on input image 1.");
    menu_data.addAction("green-gray", grayFromGreen, "Set output image by grayscale from green on input image 1.");
    menu_data.addAction("blue-gray", grayFromBlue, "Set output image by grayscale from blue on input image 1.");
    menu_data.addAction("linear-gray", grayFromLinearColorimetric, "Set output image by linear colorimetric grayscale on input image 1.");
    menu_data.addAction("circle", drawCircle, "Draw a circle shape in input image 1.");
    menu_data.addAction("box", drawBox, "Draw a box shape in input image 1.");
    menu_data.addAction("square", drawSquare, "Draw a square shape in input image 1.");
    menu_data.addAction("orange", orangeFilter, "Set output image from orange filter on input image 1.");
    menu_data.addAction("grid", configureGrid, "Configure the grid.");
    menu_data.addAction("grid-set", setGrid, "Set a single value in the grid.");
    menu_data.addAction("grid-apply", applyGrid, "Use the grid values to set colors in the output image.");
    menu_data.addAction("set-color-table-size", setColorTableSize, "Change the number of slots in the color table.");
    menu_data.addAction("set-color", setColor, "Set the RGB values for one slot in the color table.");
    menu_data.addAction("set-random-color", setRandomColor, "Randomly set the RGB values for one slot in the color table.");
    menu_data.addAction("set-color-gradient", setColorGradient, "Smoothly set the RGB values for a range of slots in the color table.");
    menu_data.addAction("grid-apply-color-table", applyGridColorTable, "Use the grid values to set colors in the output image using the color table.");
    menu_data.addAction("fractal-plane-size", setFractalPlaneSize, "Set the dimensions of the grid in the complex plane.");
    menu_data.addAction("fractal-calculate", calculateFractal, "Calculate the escape values for the fractal.");
    menu_data.addAction("julia-parameters", setJuliaParameters, "Set the parameters of the Julia Set function.");
    menu_data.addAction("complex-fractal", setComplexFractal, "Choose to make a complex plane.");
    menu_data.addAction("julia", setJuliaFractal, "Choose to make a Julia set.");
    menu_data.addAction("mandelbrot", setMandelbrotFractal, "Choose to make a Mandelbrot set.");
    menu_data.addAction("mandelbrot-power", setMandelbrotPowerFractal, "Choose to make a Mandelbrot set with the power function.");
    menu_data.addAction("set-mandelbrot-power", setMandelbrotPower, "Choose a power for the Mandelbrot power function.");
    menu_data.addAction("manhattan", setManhattanNumbers, "Choose to make a Manhattan distance grid.");
    menu_data.addAction("fractal-calculate-single-thread", calculateFractalSingleThread, "Calculate the escape values for the fractal, single-thread.");
    menu_data.addAction("quit", quit, "Quit.");
    menu_data.addAction("set-hsv-gradient", setHueSaturationValueGradient, "Smoothly set colors for a range of slots in the color table, based on change of hue, saturation, and value.");
}

int imageMenu(std::istream &is, std::ostream& os)
{
    ActionData action_data = ActionData(is, os);
    NumberGrid* numberGrid = new ComplexFractal();
    action_data.setGrid(numberGrid);
    MenuData menu_data = MenuData();
    configureMenu(menu_data);
    while (action_data.getDone() == false && action_data.getIS().good() == true) {
        std::string choice = getChoice(action_data);
        takeAction(choice, menu_data, action_data);
    }
    return 0;
}

int guess_my_number(std::istream& is, std::ostream& os)
{
    ActionData action_data = ActionData(is, os);
    int magic_number = 34;
    int your_number = magic_number - 1;
    int attempt;

    for (attempt = 0; attempt < 10; attempt++)
    {
        your_number = getInteger(action_data, "Guess my number: ");
        if (your_number < magic_number)
        {
            action_data.getOS() << "Too low!" << std::endl;
        }
        else if (your_number > magic_number)
        {
            action_data.getOS() << "Too High!" << std::endl;
        }
        else if (your_number == magic_number)
        {
            action_data.getOS() << "Nice! You guessed right!" << std::endl;
            break;
        }
    }
    int end;
    if (attempt >= 9)
    {
        action_data.getOS() << "You lose...";
        end = 1;
    }
    else
    {
        action_data.getOS() << "You win!";
        end = 0;
    }
    return end;
}

void setComplexFractal(ActionData &action_data) {
    NumberGrid* ptr_complexFractal = new ComplexFractal();
    action_data.setGrid(ptr_complexFractal);
}

void setJuliaFractal(ActionData &action_data) {
    NumberGrid* ptr_JuliaFractal = new JuliaSet();
    action_data.setGrid(ptr_JuliaFractal);
}

void setMandelbrotFractal(ActionData &action_data) {
    NumberGrid* ptr_mandelbrotFractal = new MandelbrotSet();
    action_data.setGrid(ptr_mandelbrotFractal);
}

void setMandelbrotPowerFractal(ActionData &action_data) {
    NumberGrid* ptr_mandelbrotPowerFractal = new MandelbrotPower();
    action_data.setGrid(ptr_mandelbrotPowerFractal);
}

void setManhattanNumbers(ActionData& action_data) {
    NumberGrid* ptr_manhattanNumbers = new ManhattanNumbers();
    action_data.setGrid(ptr_manhattanNumbers);
}