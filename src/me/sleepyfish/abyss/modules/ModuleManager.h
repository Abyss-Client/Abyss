// class by sleepyfish for abyss recode
// February 2024 Saturday 8:35 PM

#ifndef NEWABYSS_MODULEMANAGER_H
#define NEWABYSS_MODULEMANAGER_H

#include "Module.h"
#include "../utils/type/Class.h"
#include "../utils/type/ArrayList.h"
#include "Category.h"

class ModuleManager : Class {
private:

    ArrayList<Module*> modules;

    // Modules in category ArrayList's to save performance later
    ArrayList<Module*> modulesInCategoryLegit;
    ArrayList<Module*> modulesInCategoryBlatant;
    ArrayList<Module*> modulesInCategoryOther;
    ArrayList<Module*> modulesInCategoryUseless;
    ArrayList<Module*> modulesInCategoryHud;
    ArrayList<Module*> modulesInCategoryVisual;

    // Categories because c++ does not have a .valueOf in enum
    ArrayList<Category> categories;

public:
    void inject() override;
    void unInject() override;

    void onModuleTick();

    ArrayList<Module*> getModules();
    const ArrayList<Module*> getModulesByCategory(const Category category);
    ArrayList<Category> getCategories();

    static String getCategoryName(const Category category);

    Module* getModuleByName(const String name);
};

#endif //NEWABYSS_MODULEMANAGER_H