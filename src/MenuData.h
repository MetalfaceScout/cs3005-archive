#ifndef _MENUDATA_H_
#define _MENUDATA_H_

#include "ActionData.h"
#include <map>
#include <vector>

typedef void (*ActionFunctionType)(ActionData& action_data);

class MenuData {
public:

    MenuData();
    void addAction(const std::string& name, ActionFunctionType func, const std::string& description);
    const std::vector<std::string>& getNames() const;
    ActionFunctionType getFunction(const std::string& name);
    const std::string& getDescription(const std::string& name);
    std::string empty;

private:
    std::vector<std::string> mCommandNames;
    std::map<std::string, ActionFunctionType> mCommandMap;
    std::map<std::string, std::string> mCommandDescriptions;

};

#endif