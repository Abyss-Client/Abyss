// class by sleepyfish for abyss recode
// March 2024 Sunday 4:52 PM

#include "AutoTool.h"
#include "../../../utils/Utils.h"

AutoTool::AutoTool() : Module("Auto Tool", Category::Other, "Switches to the best tool") {
}

jint oldSlot;
jboolean allowSave;
// TimerUtils timer;

void AutoTool::onToggleTail() {
    allowSave = true;

    if (this->isEnabled()) {
        Abyss::notify.notify(this->getName() + " does not work in this version");
        this->toggle();
    }
}

void AutoTool::onTick() {

    if (Utils::holdingLeft()) {
        if (Abyss::minecraft->getObjectMouseOver().isNull()) {
            if (!allowSave) {
                Abyss::minecraft->thePlayer->getInventory().setCurrentItem(oldSlot);
                allowSave = true;
            }

            return;
        }

        if (!Abyss::minecraft->getObjectMouseOver().isTypeOfBlock())
            return;

        BlockPos pos = Abyss::minecraft->getObjectMouseOver().getBlockPos();
        if (pos.isNull())
            return;

        Block posBlock = pos.getBlock();
        if (posBlock.isNull()) {
            Abyss::logger.log("NIBBA");
            return;
        }

        if (allowSave) {
            oldSlot = Abyss::minecraft->thePlayer->getInventory().getCurrentItemInt();
            allowSave = false;
        }

        //if (timer.delay(400L)) {

            String itemName = posBlock.getLocalizedName().toLowercase();
            Abyss::logger.log(itemName);

             for (const String name : pickaxeBlocks) {
                if (itemName.contains(name.toString()))
                    Utils::switchTo("Pickaxe");
            }

            for (const String name : axeBlocks) {
                if (itemName.contains(name.toString()))
                    Utils::switchTo("Axe");
            }

            for (const String name : shearBlocks) {
                if (itemName.contains(name.toString()))
                    Utils::switchTo("Shears");
            }
        //}
    } else {
        if (oldSlot != -1) {
            Abyss::minecraft->thePlayer->getInventory().setCurrentItem(oldSlot);
            allowSave = true;
            oldSlot = -1;
            //timer.reset();
        }
    }

}