// class by sleepyfish for abyss recode
// February 2024 Saturday 8:40 PM

#ifndef NEWABYSS_MODULE_H
#define NEWABYSS_MODULE_H

#include "Category.h"
#include "settings/Setting.h"

#include "../java/sdk/Sdk.h"
#include "../java/sdk/minecraft/Minecraft.h"

#include "../utils/type/String.h"
#include "../utils/type/ArrayList.h"
#include "settings/impl/TextSetting.h"
#include "settings/impl/BoolSetting.h"

// Module class
class Module {

private:
    // Module variables
    const String oldModName;
    Category   category;
    String     descript;
    bool       enabled;
    int        keybind;

    // Settings
    ArrayList<Setting*> settings;

public:
    String modName;

    bool showWindow = false;

    bool hideModule = false;
    bool ignoreGuiState;
    bool settingsExpanded;

    // Module without keybind constructor
    Module(const String n, const Category c, const String d) :
        modName(n),
        oldModName(n),
        category(c),
        descript(d),
        enabled(false),
        keybind(0),
        ignoreGuiState(false),
        settingsExpanded(false)
    {
        this->onInit();
    }

    // Module with keybind constructor
    Module(const String n, const Category c, const String d, int k) :
        modName(n),
        oldModName(n),
        category(c),
        descript(d),
        enabled(false),
        keybind(k),
        ignoreGuiState(false),
        settingsExpanded(false)
    {
        this->onInit();
    }

    // Void that is called on init
    virtual void onInit() {
        // Override this method if needed
    }

    // Module enable void
    void onEnable() {
        this->enabled = true;
        this->onEnableEvent();
    }

    // Module on enable event void
    virtual void onEnableEvent() {
        // Override this method if needed
    }

    // Module disable void
    void onDisable() {
        this->enabled = false;
        this->onDisableEvent();
    }

    // Module on disable event void
    virtual void onDisableEvent() {
        // Override this method if needed
    }

    // Module toggle void
    void toggle() {
        this->onToggleHead();

        if (this->isEnabled()) {
            this->onDisable();
        } else {
            this->onEnable();
        }

        this->onToggleTail();
    }

    void setToggle(bool toggle) {
        if (toggle != this->isEnabled())
            this->toggle();
    }

    // Module onTick void
    virtual void onTick() {
        // Override this method if needed
    }

    // Module onTick when in gui
    virtual void onGuiRenderTick() {
        // Override this method if needed
    }

    // Module onRenderTick void
    virtual void onRenderTick() {
        // Override this method if needed
    }

    // Void that is called before toggle is called
    virtual void onToggleHead() {
        // Override this method if needed
    }

    // Void that is called after toggle is called
    virtual void onToggleTail() {
        // Override this method if needed
    }

    void expandSettingToggle() {
        this->onExpandToggleHead();
        this->settingsExpanded = !this->settingsExpanded;
        this->onExpandToggleTail();
    }

    // Void that is called before setting expand is called
    virtual void onExpandToggleHead() {
        // Override this method if needed
    }

    // Void that is called after setting expand is called
    virtual void onExpandToggleTail() {
        // Override this method if needed
    }

    // Function to add settings to the module
    void addSetting(Setting* setting) {
        this->settings.add(setting);
    }

    // Set the keybind for the module
    void setKeybind(const int keybind) {
        this->keybind = keybind;
        this->onKeybindChange();
    }

    // Void that is called after changing the keybind
    virtual void onKeybindChange() {
        // Override this method if needed
    }

    const String getOldName() {
        return this->oldModName;
    }

    // Returns the enable state
    bool isEnabled() const {
        return this->enabled;
    }

    // Returns the modName of the Module
    String getName() const {
        return this->modName;
    }

    // Returns the category of the Module
    Category getCategory() const {
        return this->category;
    }

    // Returns the description of the Module
    String getDesc() {
        return this->descript;
    }

    // Returns all settings of the Module as ArrayList
    ArrayList<Setting*> getSettings() {
        return this->settings;
    }

    // Returns the keybind of the Module
    int getKeybind() const {
        return this->keybind;
    }

    // Function to clear all settings
    void clearSettings() {
        this->settings.clear();
    }

    // Basically kills the Module
    void reset() {
        this->onDisable();
        this->modName = "";
        this->category = Category::Null;
        this->descript = "";
        this->keybind = 0;
        this->ignoreGuiState = false;
        this->settingsExpanded = false;
        this->clearSettings();
    }

};

#endif //NEWABYSS_MODULE_H