#include <iostream>
#include "ActionData.h"
#include "image_menu.h"

int main() {
    std::srand(time(0));
    return imageMenu(std::cin, std::cout);
}