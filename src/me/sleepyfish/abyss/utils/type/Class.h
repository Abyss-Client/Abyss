// class by sleepyfish for abyss recode
// February 2024 Friday 3:21 AM

#ifndef NEWABYSS_CLASS_H
#define NEWABYSS_CLASS_H

struct Class {

public:
    bool isNull = true;
    virtual void inject() = 0;
    virtual void unInject() = 0;

};

#endif //NEWABYSS_CLASS_H