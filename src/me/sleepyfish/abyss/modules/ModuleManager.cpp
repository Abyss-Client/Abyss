// class by sleepyfish for abyss recode
// February 2024 Saturday 8:35 PM

#include <thread>
#include "ModuleManager.h"
#include "Module.h"

#include "../utils/Utils.h"

#include "impl/legit/AutoClickerL.h"
#include "impl/legit/AutoClickerR.h"
#include "impl/legit/AimAssist.h"
#include "impl/legit/TriggerBot.h"
#include "impl/legit/JumpReset.h"
#include "impl/legit/LegitScaffold.h"

#include "impl/visual/TextGui.h"
#include "impl/visual/Fullbright.h"
#include "impl/visual/Overlay.h"
#include "impl/visual/TimeChanger.h"
#include "impl/visual/PlayerOverlay.h"

#include "impl/other/AutoMove.h"
#include "impl/other/AutoTool.h"
#include "impl/other/AutoPearl.h"
#include "impl/other/AutoLow.h"
#include "impl/other/CustomScript.h"
#include "impl/other/Remover.h"

#include "impl/useless/Headache.h"
#include "impl/useless/Disabler.h"
#include "impl/useless/Spin.h"

#include "impl/blatant/Hitbox.h"

#include "impl/hud/Fps.h"
#include "impl/hud/ServerIP.h"
#include "impl/hud/ServerName.h"
#include "impl/hud/Keystrokes.h"
#include "impl/hud/Coordinates.h"
#include "impl/hud/RamUsed.h"

void ModuleManager::inject() {
    if (this->isNull) {
        Abyss::logger.log("/ Module - Info: Inject");

        // Add all categories here because c++ does not have a .valueOf in enum
        this->categories.add(Category::Legit);
        this->categories.add(Category::Visual);
        this->categories.add(Category::Other);
        this->categories.add(Category::Useless);
        this->categories.add(Category::Blatant);
        this->categories.add(Category::Hud);

        // Blatant
        this->modules.add(new Hitbox());

        // Legit
        this->modules.add(new AutoClickerL());
        this->modules.add(new AutoClickerR());
        this->modules.add(new AimAssist());
        this->modules.add(new TriggerBot());
        this->modules.add(new JumpReset());
        // this->modules.add(new LegitScaffold());

        // Other
        this->modules.add(new AutoMove());
        this->modules.add(new AutoTool());
        this->modules.add(new AutoPearl());
        this->modules.add(new AutoLow());
        this->modules.add(new CustomScript());
        this->modules.add(new Remover());

        // Useless
        this->modules.add(new Headache());
        this->modules.add(new Disabler());
        this->modules.add(new Spin());

        // Visual
        this->modules.add(new TextGui());
        this->modules.add(new Fullbright());
        this->modules.add(new Overlay());
        this->modules.add(new TimeChanger());
        // this->modules.add(new PlayerOverlay());

        // Hud
        this->modules.add(new Fps());
        this->modules.add(new ServerIP());
        this->modules.add(new ServerName());
        this->modules.add(new Keystrokes());
        this->modules.add(new Coordinates());
        this->modules.add(new RamUsed());

        // Add all modules in categories here to save performance later
        for (Module* mod: this->modules.getVector()) {
            if (mod->getCategory() == Category::Null)
                break;

            switch (mod->getCategory()) {
                case Category::Legit:
                    this->modulesInCategoryLegit.add(mod);
                break;

                case Category::Visual:
                    this->modulesInCategoryVisual.add(mod);
                    break;

                case Category::Other:
                    this->modulesInCategoryOther.add(mod);
                    break;

                case Category::Useless:
                    this->modulesInCategoryUseless.add(mod);
                    break;

                case Category::Hud:
                    this->modulesInCategoryHud.add(mod);
                    break;

                case Category::Blatant:
                    this->modulesInCategoryBlatant.add(mod);
                    break;
            }
        }

        this->isNull = false;
        Abyss::logger.log("\\ Module - Info: Inject Done");
        Abyss::logger.nextLine();
    }
}

void ModuleManager::unInject() {
    if (!this->isNull) {
        Abyss::logger.nextLine();
        Abyss::logger.log("/ Module - Info: UnInject");

        for (Module* mod: this->getModules().getVector())
            mod->reset();

        Abyss::logger.log("| Module - Info: Killed Modules");

        this->modules.clear();
        Abyss::logger.log("| Module - Info: Cleared modules");
        this->categories.clear();
        Abyss::logger.log("| Module - Info: Cleared categories");
        this->modulesInCategoryLegit.clear();
        this->modulesInCategoryBlatant.clear();
        this->modulesInCategoryVisual.clear();
        this->modulesInCategoryOther.clear();
        this->modulesInCategoryHud.clear();
        this->modulesInCategoryUseless.clear();
        Abyss::logger.log("| Module - Info: Cleared modules in categories");

        Abyss::logger.log("\\ Module - Info: UnInject Done");
        Abyss::logger.nextLine();
        this->isNull = true;
    }
}

const ArrayList<Module*> ModuleManager::getModulesByCategory(const Category category) {
    switch (category) {
        case Category::Null:
            return ArrayList<Module*>();

        case Category::Legit:
            return this->modulesInCategoryLegit;

        case Category::Blatant:
            return this->modulesInCategoryBlatant;

        case Category::Visual:
            return this->modulesInCategoryVisual;

        case Category::Other:
            return this->modulesInCategoryOther;

        case Category::Useless:
            return this->modulesInCategoryUseless;

        case Category::Hud:
            return this->modulesInCategoryHud;

        default: break;
    }
}

ArrayList<Module*> ModuleManager::getModules() {
    return this->modules;
}

ArrayList<Category> ModuleManager::getCategories() {
    return this->categories;
}

void ModuleManager::onModuleTick() {
    for (Module *mod: this->getModules().getVector()) {
        if (mod->isEnabled()) {
            if (!Utils::canLegitWork(mod->ignoreGuiState))
                mod->onTick();
        }
    }
}

String ModuleManager::getCategoryName(const Category category) {
    switch (category) {
        case Category::Legit:
            return "Legit";

        case Category::Blatant:
            return "Blatant";

        case Category::Visual:
            return "Visual";

        case Category::Other:
            return "Other";

        case Category::Hud:
            return "Hud";

        case Category::Useless:
            return "Useless";

        default: return "";
    }
}

Module* ModuleManager::getModuleByName(const String name) {
    for (Module* mod : getModules().getVector()) {
        if (name.equals(mod->getOldName()))
            return mod;
    }
}