#include "image_menu.h"
#include "ActionData.h"
#include <iostream>

std::string getString(ActionData &action_data, const std::string &prompt)
{
    std::string st;
    action_data.getOS() << prompt;
    action_data.getIS() >> st;
    return st;
}

int getInteger(ActionData &action_data, const std::string &prompt)
{
    int in;
    action_data.getOS() << prompt;
    action_data.getIS() >> in;
    return in;
}

double getDouble(ActionData &action_data, const std::string &prompt)
{
    double db;
    action_data.getOS() << prompt;
    action_data.getIS() >> db;
    return db;
}

int askQuestions3(ActionData &action_data)
{
    std::string color = getString(action_data, "What is your favorite color? ");
    int integer = getInteger(action_data, "What is your favorite integer? ");
    double number = getDouble(action_data, "What is your favorite number? ");
    for (int i = 0; i < integer; i++)
    {
        action_data.getOS() << i + 1 << " " << color << " " << number << std::endl;
    }
    return integer;
}

std::string getChoice(ActionData &action_data)
{
    std::string userString;
    userString = getString(action_data, "Choice? ");
    return userString;
}

void commentLine(ActionData& action_data) {
    long c;
    unsigned char newline = 0x0a;
    while (action_data.getIS().good() && (unsigned char) c != newline) {
        action_data.getIS().read((char *) &c, 1);
    }
    return;
}

void quit(ActionData& action_data) {
    action_data.setDone();
}