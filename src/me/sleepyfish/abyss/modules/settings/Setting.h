// class by sleepyfish for abyss recode
// February 2024 Saturday 10:32 PM

#ifndef NEWABYSS_SETTING_H
#define NEWABYSS_SETTING_H

#include "../../utils/type/String.h"

class SettingBase {
public:
    virtual ~SettingBase() = default;
};

class Setting : public SettingBase {

private:
    String name;
    short type;
    String desc;

public:

    Setting(String name, short type) :
            name(name),
            type(type),
            desc("")
    {}

    Setting(String name, String desc, short type) :
        name(name),
        type(type),
        desc(desc)
    {}

    String getName() const {
        return this->name;
    }

    short getType() const {
        return this->type;
    }

    String getDesc() const {
        return this->desc;
    }

    String getTypeAsName() const {
        switch (this->getType()) {
            case 0:
                return "space";

            case 1:
                return "bool";

            case 2:
                return "slider";

            case 3:
                return "mode";

            case 4:
                return "color";

            case 5:
                return "text";

            case 6:
                return "info";

            default: return "";
        }
    }

};

#endif //NEWABYSS_SETTING_H