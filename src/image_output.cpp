//#include <iostream>
#include <string>
#include <fstream>
#include "Image.h"
#include "image_menu.h"
#include "ActionData.h"

std::string getCharacter(double charvalue) {
    if (charvalue >= 1.0) {
        return "@";
    } else if (charvalue >= 0.9) {
        return "#";
    } else if (charvalue >= 0.8) {
        return "%";
    } else if (charvalue >= 0.7) {
        return "*";
    } else if (charvalue >= 0.6) {
        return "|";
    } else if (charvalue >= 0.5) {
        return "+";
    } else if (charvalue >= 0.4) {
        return ";";
    } else if (charvalue >= 0.3) {
        return "~";
    } else if (charvalue >= 0.2) {
        return "-";
    } else if (charvalue >= 0.1) {
        return ".";
    } else {
        return " ";
    }
}

void drawAsciiImage(ActionData& action_data) {
    PPM& image = action_data.getOutputImage();
    double value = 0.0;
    int i;
    int j;
    for (i = 0; i < image.getHeight(); i++) {
        for (j = 0; j < image.getWidth(); j++) {
            value = image.getChannel(i, j, 0) + image.getChannel(i, j, 1) + image.getChannel(i, j, 2);
            action_data.getOS() << getCharacter(value/765.0);
        }
    action_data.getOS() << std::endl;
    }
}

void writeUserImage(ActionData& action_data) {
    PPM& p = action_data.getOutputImage();
    std::string filename = getString(action_data, "Output filename? ");
    std::fstream file;
    file.open(filename, std::ios::out);
    p.writeStream(file);
    file.close();
}

void copyImage(ActionData& action_data) {
    action_data.getOutputImage() = action_data.getInputImage1();
}

void readUserImage1(ActionData& action_data) {
    std::string filename = getString(action_data, "Input filename? ");
    std::ifstream file = std::ifstream(filename, std::ios::in);

    if (!file.good()) {
        action_data.getOS() << "'" << filename << "' could not be opened." << std::endl;
        return;
    }

    PPM& inputImage1 = action_data.getInputImage1();
    inputImage1.readStream(file);
}

void readUserImage2(ActionData& action_data) {
    std::string filename = getString(action_data, "Input filename? ");
    std::ifstream file = std::ifstream(filename, std::ios::in);

    if (!file.good()) {
        action_data.getOS() << "'" << filename << "' could not be opened." << std::endl;
        return;
    }

    PPM& inputImage2 = action_data.getInputImage2();
    inputImage2.readStream(file);
}