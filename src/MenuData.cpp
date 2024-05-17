#include "MenuData.h"
#include <map>
#include <vector>

MenuData::MenuData() : mCommandNames(), mCommandMap(), mCommandDescriptions() {}

/*
Uncondtionally adds the menu item described by name, func, and desc.
*/
void MenuData::addAction(const std::string& name, ActionFunctionType func, const std::string& desc) {
    MenuData::mCommandMap.insert({name, func});
    MenuData::mCommandNames.push_back(name);
    MenuData::mCommandDescriptions.insert({name, desc});
}

const std::vector<std::string>& MenuData::getNames() const {
    return mCommandNames;
}

/*
Gets the ActionFunctionType related to the "name" passed in. Uses MenuData map. Returns 0 if fail.
*/
ActionFunctionType MenuData::getFunction(const std::string& name) {
    if (MenuData::mCommandMap.find(name) == MenuData::mCommandMap.end()) {
        return 0;
    }
    return MenuData::mCommandMap[name];
}

const std::string& MenuData::getDescription(const std::string& name) {
    if (MenuData::mCommandDescriptions.find(name) == MenuData::mCommandDescriptions.end()) {
        
        return MenuData::empty;
    }
    return MenuData::mCommandDescriptions[name];
}
