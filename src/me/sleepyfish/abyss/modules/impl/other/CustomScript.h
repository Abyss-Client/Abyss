// class by sleepyfish for abyss recode
// February 2024 Wednesday 3:41 PM

#ifndef NEWABYSS_CUSTOMSCRIPT_H
#define NEWABYSS_CUSTOMSCRIPT_H

#include "../../Module.h"

class CustomScript : public Module {

public:
    CustomScript();

    void onTick() override;
    void onRenderTick() override;

    std::vector<std::string> extractArguments(const std::string& argsString);

    std::string text = "#version 1.0\n#ignoreGui\n";
    std::vector<std::string> lines;
};

#endif //NEWABYSS_CUSTOMSCRIPT_H