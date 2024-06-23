// class by sleepyfish for abyss recode
// February 2024 Friday 6:22 AM

#include "Mapper.h"
#include "../../client/Abyss.h"

// Init Maps
std::map<std::string, jclass> Mapper::mapper_classes;
std::map<std::string, jfieldID> Mapper::mapper_fields;
std::map<std::string, jmethodID> Mapper::mapper_voids;

void Mapper::inject() {
    if (Mapper::isNull) {
        Abyss::logger.log("/ Mapper - Info: Inject");

        Mapper::injectForgeClass();
        Mapper::assignClasses();
        Mapper::applyMappings();
        Mapper::checkMappings();

        Mapper::isNull = false;
        Abyss::logger.log("\\ Mapper - Info: Inject Done");
    }
}

void Mapper::unInject() {
    if (!Mapper::isNull) {
        Abyss::logger.log("/ Mapper - Info: UnInject");

        for (auto& pair : Mapper::mapper_classes)
            EnvUtils::Env->DeleteLocalRef(pair.second);

        Abyss::logger.log("| Mapper - Info: cleared classes");

        for (auto& pair : Mapper::mapper_voids)
            pair.second = nullptr;

        Abyss::logger.log("| Mapper - Info: cleared voids");

        for (auto& pair : Mapper::mapper_fields)
            pair.second = nullptr;

        Abyss::logger.log("| Mapper - Info: cleared fields");

        EnvUtils::Env->DeleteLocalRef(LaunchWrapperClassLoaderClass);
        FindClassMethodID  = nullptr;
        EnvUtils::Env->DeleteLocalRef(LaunchClass);
        ClassLoaderFieldID = nullptr;
        EnvUtils::Env->DeleteLocalRef(ClassLoaderObject);

        Abyss::logger.log("\\ Mapper - Info: UnInject Done");
        Abyss::logger.nextLine();
        Mapper::isNull = true;
    }
}

void Mapper::assignClasses() {
    Abyss::logger.log("| Mapper - Info: Classes");

    Mapper::assignJavaClasses();

    if (Mapper::useVanillaMappings()) {
        Abyss::java.assignClass("ave", Mapper::mapper_classes["Minecraft"]);
        Abyss::java.assignClass("avm", Mapper::mapper_classes["Session"]);
        Abyss::java.assignClass("pk",  Mapper::mapper_classes["Entity"]);
        Abyss::java.assignClass("pr",  Mapper::mapper_classes["EntityLivingBase"]);
        Abyss::java.assignClass("auq", Mapper::mapper_classes["Team"]);
        Abyss::java.assignClass("wn",  Mapper::mapper_classes["EntityPlayer"]);
        Abyss::java.assignClass("bew", Mapper::mapper_classes["EntityPlayerSP"]);
        Abyss::java.assignClass("avh", Mapper::mapper_classes["GameSettings"]);
        Abyss::java.assignClass("avb", Mapper::mapper_classes["KeyBinding"]);
        Abyss::java.assignClass("bdb", Mapper::mapper_classes["WorldClient"]);
        Abyss::java.assignClass("biu", Mapper::mapper_classes["RenderManager"]);
        Abyss::java.assignClass("auz", Mapper::mapper_classes["ActiveRenderInfo"]);
        Abyss::java.assignClass("avl", Mapper::mapper_classes["Timer"]);
        Abyss::java.assignClass("adm", Mapper::mapper_classes["World"]);
        Abyss::java.assignClass("ato", Mapper::mapper_classes["WorldInfo"]);
        Abyss::java.assignClass("amy", Mapper::mapper_classes["Chunk"]);
        Abyss::java.assignClass("aug", Mapper::mapper_classes["AxisAlignedBB"]);
        Abyss::java.assignClass("auh", Mapper::mapper_classes["MovingObjectPosition"]);
        Abyss::java.assignClass("aui", Mapper::mapper_classes["Vec3"]);
        Abyss::java.assignClass("wm",  Mapper::mapper_classes["InventoryPlayer"]);
        Abyss::java.assignClass("yg",  Mapper::mapper_classes["Slot"]);
        Abyss::java.assignClass("xi",  Mapper::mapper_classes["Container"]);
        Abyss::java.assignClass("cj",  Mapper::mapper_classes["BlockPos"]);
        Abyss::java.assignClass("afh", Mapper::mapper_classes["Block"]);
        Abyss::java.assignClass("azc", Mapper::mapper_classes["GuiInventory"]);
        Abyss::java.assignClass("alz", Mapper::mapper_classes["IBlockState"]);
        Abyss::java.assignClass("aey", Mapper::mapper_classes["BlockAir"]);
        Abyss::java.assignClass("zw",  Mapper::mapper_classes["Item"]);
        Abyss::java.assignClass("zx",  Mapper::mapper_classes["ItemStack"]);
        Abyss::java.assignClass("yj",  Mapper::mapper_classes["ItemArmor"]);
        Abyss::java.assignClass("aaw", Mapper::mapper_classes["ItemEnderPearl"]);
        Abyss::java.assignClass("aag", Mapper::mapper_classes["ItemPickaxe"]);
        Abyss::java.assignClass("yl",  Mapper::mapper_classes["ItemAxe"]);
        Abyss::java.assignClass("aap", Mapper::mapper_classes["ItemShears"]);
        Abyss::java.assignClass("aay", Mapper::mapper_classes["ItemSword"]);
        Abyss::java.assignClass("yo",  Mapper::mapper_classes["ItemBlock"]);
        Abyss::java.assignClass("zs",  Mapper::mapper_classes["ItemFood"]);
        Abyss::java.assignClass("bde", Mapper::mapper_classes["ServerData"]);
    }

    if (Mapper::useForgeMappings() || Mapper::useLunarMappings()) {
        Abyss::java.assignClass("net.minecraft.client.Minecraft", Mapper::mapper_classes["Minecraft"]);
        Abyss::java.assignClass("net.minecraft.util.Session", Mapper::mapper_classes["Session"]);
        Abyss::java.assignClass("net.minecraft.entity.Entity", Mapper::mapper_classes["Entity"]);
        Abyss::java.assignClass("net.minecraft.entity.EntityLivingBase", Mapper::mapper_classes["EntityLivingBase"]);
        Abyss::java.assignClass("net.minecraft.scoreboard.Team", Mapper::mapper_classes["Team"]);
        Abyss::java.assignClass("net.minecraft.entity.player.EntityPlayer", Mapper::mapper_classes["EntityPlayer"]);
        Abyss::java.assignClass("net.minecraft.client.entity.EntityPlayerSP", Mapper::mapper_classes["EntityPlayerSP"]);
        Abyss::java.assignClass("net.minecraft.client.settings.GameSettings", Mapper::mapper_classes["GameSettings"]);
        Abyss::java.assignClass("net.minecraft.client.settings.KeyBinding", Mapper::mapper_classes["KeyBinding"]);
        Abyss::java.assignClass("net.minecraft.client.multiplayer.WorldClient", Mapper::mapper_classes["WorldClient"]);
        Abyss::java.assignClass("net.minecraft.client.renderer.entity.RenderManager", Mapper::mapper_classes["RenderManager"]);
        Abyss::java.assignClass("net.minecraft.client.renderer.ActiveRenderInfo", Mapper::mapper_classes["ActiveRenderInfo"]);
        Abyss::java.assignClass("net.minecraft.util.Timer", Mapper::mapper_classes["Timer"]);
        Abyss::java.assignClass("net.minecraft.world.World", Mapper::mapper_classes["World"]);
        Abyss::java.assignClass("net.minecraft.world.storage.WorldInfo", Mapper::mapper_classes["WorldInfo"]);
        Abyss::java.assignClass("net.minecraft.world.chunk.Chunk", Mapper::mapper_classes["Chunk"]);
        Abyss::java.assignClass("net.minecraft.util.AxisAlignedBB", Mapper::mapper_classes["AxisAlignedBB"]);
        Abyss::java.assignClass("net.minecraft.util.MovingObjectPosition", Mapper::mapper_classes["MovingObjectPosition"]);
        Abyss::java.assignClass("net.minecraft.util.Vec3", Mapper::mapper_classes["Vec3"]);
        Abyss::java.assignClass("net.minecraft.entity.player.InventoryPlayer", Mapper::mapper_classes["InventoryPlayer"]);
        Abyss::java.assignClass("net.minecraft.inventory.Slot", Mapper::mapper_classes["Slot"]);
        Abyss::java.assignClass("net.minecraft.inventory.Container", Mapper::mapper_classes["Container"]);
        Abyss::java.assignClass("net.minecraft.util.BlockPos", Mapper::mapper_classes["BlockPos"]);
        Abyss::java.assignClass("net.minecraft.block.Block", Mapper::mapper_classes["Block"]);
        Abyss::java.assignClass("net.minecraft.client.gui.inventory.GuiInventory", Mapper::mapper_classes["GuiInventory"]);
        Abyss::java.assignClass("net.minecraft.block.state.IBlockState", Mapper::mapper_classes["IBlockState"]);
        Abyss::java.assignClass("net.minecraft.block.BlockAir", Mapper::mapper_classes["BlockAir"]);
        Abyss::java.assignClass("net.minecraft.item.Item", Mapper::mapper_classes["Item"]);
        Abyss::java.assignClass("net.minecraft.item.ItemStack", Mapper::mapper_classes["ItemStack"]);
        Abyss::java.assignClass("net.minecraft.item.ItemArmor", Mapper::mapper_classes["ItemArmor"]);
        Abyss::java.assignClass("net.minecraft.item.ItemEnderPearl", Mapper::mapper_classes["ItemEnderPearl"]);
        Abyss::java.assignClass("net.minecraft.item.ItemPickaxe", Mapper::mapper_classes["ItemPickaxe"]);
        Abyss::java.assignClass("net.minecraft.item.ItemAxe", Mapper::mapper_classes["ItemAxe"]);
        Abyss::java.assignClass("net.minecraft.item.ItemShears", Mapper::mapper_classes["ItemShears"]);
        Abyss::java.assignClass("net.minecraft.item.ItemSword", Mapper::mapper_classes["ItemSword"]);
        Abyss::java.assignClass("net.minecraft.item.ItemBlock", Mapper::mapper_classes["ItemBlock"]);
        Abyss::java.assignClass("net.minecraft.item.ItemFood", Mapper::mapper_classes["ItemFood"]);
        Abyss::java.assignClass("net.minecraft.client.multiplayer.ServerData", Mapper::mapper_classes["ServerData"]);
    }

    Abyss::logger.log("| Mapper - Info: Classes Done");
}

void Mapper::assignJavaClasses() {
    // Set.class
    Abyss::java.assignClass("java/util/Set", Mapper::mapper_classes["JavaSet"]);

    // List.class
    Abyss::java.assignClass("java/util/List", Mapper::mapper_classes["JavaList"]);
    Mapper::mapper_voids["list_toArray"] = EnvUtils::Env->GetMethodID(Mapper::mapper_classes["JavaList"], "toArray", "()[Ljava/lang/Object;");

    // UUID.class
    Abyss::java.assignClass("java/util/UUID", Mapper::mapper_classes["JavaUUID"]);
    Mapper::mapper_voids["uuid_getVersion"] = EnvUtils::Env->GetMethodID(Mapper::mapper_classes["JavaUUID"], "version", "()I");

    // String.class
    Abyss::java.assignClass("java/lang/String", Mapper::mapper_classes["JavaString"]);
}

void Mapper::applyMappings() {
    switch (Mapper::currentMapping) {
        case Mappings::Vanilla:
            Mapper::applyVanillaMappings();
        break;

        case Mappings::Forge:
            Mapper::applyForgeMappings();
        break;

        case Mappings::Lunar:
            Mapper::applyLunarMappings();
        break;

        case Mappings::None:
            Abyss::logger.log("| Mapper - Err: There is no mapping");
        break;
    }
}

void Mapper::applyVanillaMappings() {
    Abyss::logger.log("| Mapper - Info: Applying Vanilla");

    // Minecraft.class ---
    jclass mcClass = Mapper::mapper_classes["Minecraft"];
        Mapper::mapper_voids["minecraft_getMinecraft"] = EnvUtils::Env->GetStaticMethodID(mcClass, "A", "()Lave;");
        Mapper::mapper_voids["minecraft_isSinglePlayer"] = EnvUtils::Env->GetMethodID(mcClass, "F", Descriptors::void_boolean);
        Mapper::mapper_fields["minecraft_thePlayer"] = EnvUtils::Env->GetFieldID(mcClass, "h", "Lbew;");
        Mapper::mapper_fields["minecraft_theWorld"] = EnvUtils::Env->GetFieldID(mcClass, "f", "Lbdb;");
        Mapper::mapper_fields["minecraft_session"] = EnvUtils::Env->GetFieldID(mcClass, "ae", "Lavm;");
        Mapper::mapper_fields["minecraft_pointedEntity"] = EnvUtils::Env->GetFieldID(mcClass, "i", "Lpk;");
        Mapper::mapper_fields["minecraft_objectMouseOver"] = EnvUtils::Env->GetFieldID(mcClass, "s", "Lauh;");
        Mapper::mapper_fields["minecraft_gameSettings"] = EnvUtils::Env->GetFieldID(mcClass, "t", "Lavh;");
        Mapper::mapper_fields["minecraft_currentScreen"] = EnvUtils::Env->GetFieldID(mcClass, "m", "Laxu;");
        Mapper::mapper_fields["minecraft_renderManager"] = EnvUtils::Env->GetFieldID(mcClass, "aa", "Lbiu;");
        Mapper::mapper_fields["minecraft_debugFPS"] = EnvUtils::Env->GetStaticFieldID(mcClass, "ao", Descriptors::field_int);
        Mapper::mapper_fields["minecraft_rightClickDelayTimer"] = EnvUtils::Env->GetFieldID(mcClass, "ap", Descriptors::field_int);
        Mapper::mapper_fields["minecraft_leftClickCounter"] = EnvUtils::Env->GetFieldID(mcClass, "ag",Descriptors::field_int);
        Mapper::mapper_fields["minecraft_currentServerData"] = EnvUtils::Env->GetFieldID(mcClass, "Q", "Lbde;");
    EnvUtils::Env->DeleteLocalRef(mcClass);

    // Session.class ---
    jclass sessionClass = Mapper::mapper_classes["Session"];
        Mapper::mapper_voids["session_getName"] = EnvUtils::Env->GetMethodID(sessionClass, "c", Descriptors::class_string);
        Mapper::mapper_voids["session_getType"] = EnvUtils::Env->GetMethodID(sessionClass, "f", "()Lavm$a;");
    EnvUtils::Env->DeleteLocalRef(sessionClass);

    // World.class ---
    jclass worldClass = Mapper::mapper_classes["World"];
        Mapper::mapper_voids["world_isAirBlock"] = EnvUtils::Env->GetMethodID(worldClass, "d", "(Lcj;)Z");
        Mapper::mapper_voids["world_getBlockState"] = EnvUtils::Env->GetMethodID(worldClass, "p", "(Lcj;)Lalz;");
        Mapper::mapper_voids["world_setWorldTime"] = EnvUtils::Env->GetMethodID(worldClass, "b", Descriptors::void_with_long);
        Mapper::mapper_fields["world_playerEntities"] = EnvUtils::Env->GetFieldID(worldClass, "j", "Ljava/util/List;");
    EnvUtils::Env->DeleteLocalRef(worldClass);

    // Entity.class ---
    jclass entityClass = Mapper::mapper_classes["Entity"];
        Mapper::mapper_voids["entity_getName"] = EnvUtils::Env->GetMethodID(entityClass, "e_", Descriptors::class_string);
        Mapper::mapper_voids["entity_isSneaking"] = EnvUtils::Env->GetMethodID(entityClass, "av", Descriptors::void_boolean);
        Mapper::mapper_voids["entity_setSneaking"] = EnvUtils::Env->GetMethodID(entityClass, "c", Descriptors::void_with_boolean);
        Mapper::mapper_voids["entity_inWater"] = EnvUtils::Env->GetMethodID(entityClass, "V", Descriptors::void_boolean);
        Mapper::mapper_voids["entity_isInvisible"] = EnvUtils::Env->GetMethodID(entityClass, "ax", Descriptors::void_boolean);
        Mapper::mapper_voids["entity_getUUID"] = EnvUtils::Env->GetMethodID(entityClass, "aK", Descriptors::class_uuid);
        Mapper::mapper_voids["entity_getEntityWorld"] = EnvUtils::Env->GetMethodID(entityClass, "e", "adm");
        Mapper::mapper_fields["entity_motionX"] = EnvUtils::Env->GetFieldID(entityClass, "v", Descriptors::field_double);
        Mapper::mapper_fields["entity_motionY"] = EnvUtils::Env->GetFieldID(entityClass, "w", Descriptors::field_double);
        Mapper::mapper_fields["entity_motionZ"] = EnvUtils::Env->GetFieldID(entityClass, "x", Descriptors::field_double);
        Mapper::mapper_fields["entity_posX"] = EnvUtils::Env->GetFieldID(entityClass, "s", Descriptors::field_double);
        Mapper::mapper_fields["entity_posY"] = EnvUtils::Env->GetFieldID(entityClass, "t", Descriptors::field_double);
        Mapper::mapper_fields["entity_posZ"] = EnvUtils::Env->GetFieldID(entityClass, "u", Descriptors::field_double);
        Mapper::mapper_fields["entity_lastTickPosX"] = EnvUtils::Env->GetFieldID(entityClass, "p", Descriptors::field_double);
        Mapper::mapper_fields["entity_lastTickPosY"] = EnvUtils::Env->GetFieldID(entityClass, "Q", Descriptors::field_double);
        Mapper::mapper_fields["entity_lastTickPosZ"] = EnvUtils::Env->GetFieldID(entityClass, "R", Descriptors::field_double);
        Mapper::mapper_fields["entity_width"] = EnvUtils::Env->GetFieldID(entityClass, "J", Descriptors::field_float);
        Mapper::mapper_fields["entity_height"] = EnvUtils::Env->GetFieldID(entityClass, "K", Descriptors::field_float);
        Mapper::mapper_fields["entity_hurtResistantTime"] = EnvUtils::Env->GetFieldID(entityClass, "Z", Descriptors::field_int);
        Mapper::mapper_fields["entity_rotationYaw"] = EnvUtils::Env->GetFieldID(entityClass, "y", Descriptors::field_float);
        Mapper::mapper_fields["entity_rotationPitch"] = EnvUtils::Env->GetFieldID(entityClass, "z", Descriptors::field_float);
        Mapper::mapper_fields["entity_boundingBox"] = EnvUtils::Env->GetFieldID(entityClass, "f", "Laug;");
        Mapper::mapper_fields["entity_onGround"] = EnvUtils::Env->GetFieldID(entityClass, "C", Descriptors::field_boolean);
        Mapper::mapper_fields["entity_fallDistance"] = EnvUtils::Env->GetFieldID(entityClass, "O", Descriptors::field_float);
        Mapper::mapper_fields["entity_ticksExisted"] = EnvUtils::Env->GetFieldID(entityClass, "W", Descriptors::field_int);
        Mapper::mapper_fields["entity_isDead"] = EnvUtils::Env->GetFieldID(entityClass, "I", Descriptors::field_boolean);
    EnvUtils::Env->DeleteLocalRef(entityClass);

    // EntityLivingBase.class ---
    jclass entityLivingBaseClass = Mapper::mapper_classes["EntityLivingBase"];
        Mapper::mapper_voids["entityLivingBase_jump"]  = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "bF", Descriptors::void_);
        Mapper::mapper_voids["entityLivingBase_swingItem"]  = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "bw", Descriptors::void_);
        Mapper::mapper_voids["entityPlayerBase_isPlayerSleeping"]  = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "bJ", Descriptors::void_boolean);
        Mapper::mapper_voids["entityPlayerBase_canEntityBeSeen"]  = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "t", "(Lpk;)Z");
        Mapper::mapper_voids["entityLivingBase_getHealth"] = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "bn", Descriptors::void_float);
        Mapper::mapper_voids["entityLivingBase_getMaxHealth"] = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "bu", Descriptors::void_float);
        Mapper::mapper_fields["entityLivingBase_maxHurtResistantTime"]  = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "aD", Descriptors::field_int);
        Mapper::mapper_fields["entityLivingBase_hurtTime"]  = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "au", Descriptors::field_int);
        Mapper::mapper_fields["entityLivingBase_moveForward"] = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "ba", Descriptors::field_float);
        Mapper::mapper_fields["entityLivingBase_moveStrafe"] = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "aZ", Descriptors::field_float);
        Mapper::mapper_fields["entityLivingBase_rotationYawHead"] = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "aK", Descriptors::field_float);
        Mapper::mapper_fields["entityLivingBase_prevRotationYawHead"] = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "aL", Descriptors::field_float);
        Mapper::mapper_fields["entityLivingBase_renderYawOffset"] = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "aI", Descriptors::field_float);
        Mapper::mapper_voids["entityLivingBase_getTeam"] = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "bO", "()Lauq;");
    EnvUtils::Env->DeleteLocalRef(entityLivingBaseClass);

    // EntityPlayer.class ---
    jclass entityPlayerClass = Mapper::mapper_classes["EntityPlayer"];
        Mapper::mapper_voids["entityPlayer_isSpectator"]  = EnvUtils::Env->GetMethodID(entityPlayerClass, "v", Descriptors::void_boolean);
        Mapper::mapper_voids["entityPlayer_isBlocking"] = EnvUtils::Env->GetMethodID(entityPlayerClass, "bW", Descriptors::void_boolean);
        Mapper::mapper_voids["entityPlayer_closeScreen"] = EnvUtils::Env->GetMethodID(entityPlayerClass, "n", Descriptors::void_);
        Mapper::mapper_voids["entityPlayer_dropItem"] = EnvUtils::Env->GetMethodID(entityPlayerClass, "a", "(Z)Luz;");
        Mapper::mapper_fields["entityPlayer_openContainer"] = EnvUtils::Env->GetFieldID(entityPlayerClass, "bk", "Lxi;");
        Mapper::mapper_fields["entityPlayer_inventory"] = EnvUtils::Env->GetFieldID(entityPlayerClass, "bi", "Lwm;");
    EnvUtils::Env->DeleteLocalRef(entityPlayerClass);

    // WorldClient.class ---
    jclass worldClientClass = Mapper::mapper_classes["WorldClient"];
        Mapper::mapper_fields["worldClient_entityList"] = EnvUtils::Env->GetFieldID(worldClientClass, "c", "Ljava/util/Set;");
        Mapper::mapper_voids["worldClient_sendQuittingDisconnectingPacket"] = EnvUtils::Env->GetMethodID(worldClientClass, "H", Descriptors::void_);
    EnvUtils::Env->DeleteLocalRef(worldClientClass);

    // RenderManager.class ---
    jclass renderManagerClass = Mapper::mapper_classes["RenderManager"];
        Mapper::mapper_voids["renderManager_doRenderEntity"] = EnvUtils::Env->GetMethodID(renderManagerClass, "a", "(Lpk;DDDFFZ)Z");
    EnvUtils::Env->DeleteLocalRef(renderManagerClass);

    // InventoryPlayer.class ---
    jclass inventoryPlayerClass = Mapper::mapper_classes["InventoryPlayer"];
        Mapper::mapper_voids["inventoryPlayer_getCurrentItem"] = EnvUtils::Env->GetMethodID(inventoryPlayerClass, "h", "()Lzx;");
        Mapper::mapper_fields["inventoryPlayer_mainInv"] = EnvUtils::Env->GetFieldID(inventoryPlayerClass, "a", "[Lzx;");
        Mapper::mapper_fields["inventoryPlayer_armorInv"] = EnvUtils::Env->GetFieldID(inventoryPlayerClass, "b", "[Lzx;");
        Mapper::mapper_fields["inventoryPlayer_currentItem"] = EnvUtils::Env->GetFieldID(inventoryPlayerClass, "c", Descriptors::field_int);
    EnvUtils::Env->DeleteLocalRef(inventoryPlayerClass);

    // ItemStack.class ---
    jclass itemStackClass = Mapper::mapper_classes["ItemStack"];
        Mapper::mapper_voids["itemStack_getItem"] = EnvUtils::Env->GetMethodID(itemStackClass, "b", "()Lzw;");
        Mapper::mapper_voids["itemStack_getName"] = EnvUtils::Env->GetMethodID(itemStackClass, "q", Descriptors::class_string);
    EnvUtils::Env->DeleteLocalRef(itemStackClass);

    // KeyBinding.class ---
    jclass keybindingClass = Mapper::mapper_classes["KeyBinding"];
        Mapper::mapper_fields["keybinding_pressed"] = EnvUtils::Env->GetFieldID(keybindingClass, "h", Descriptors::field_boolean);
    EnvUtils::Env->DeleteLocalRef(keybindingClass);

    // GameSettings.class ---
    jclass gameSettingClass = Mapper::mapper_classes["GameSettings"];
        Mapper::mapper_fields["gameSetting_keyBindRight"] = EnvUtils::Env->GetFieldID(gameSettingClass, "ab", "Lavb;");
        Mapper::mapper_fields["gameSetting_keyBindLeft"] = EnvUtils::Env->GetFieldID(gameSettingClass, "Z", "Lavb;");
        Mapper::mapper_fields["gameSetting_keyBindBack"] = EnvUtils::Env->GetFieldID(gameSettingClass, "aa", "Lavb;");
        Mapper::mapper_fields["gameSetting_keyBindForward"] = EnvUtils::Env->GetFieldID(gameSettingClass, "Y", "Lavb;");
        Mapper::mapper_fields["gameSetting_keyBindSneak"] = EnvUtils::Env->GetFieldID(gameSettingClass, "ad", "Lavb;");
        Mapper::mapper_fields["gameSetting_keyBindJump"] = EnvUtils::Env->GetFieldID(gameSettingClass, "ac", "Lavb;");
        Mapper::mapper_fields["gameSetting_fovSetting"] = EnvUtils::Env->GetFieldID(gameSettingClass, "aI", Descriptors::field_float);
        Mapper::mapper_fields["gameSetting_gammaSetting"] = EnvUtils::Env->GetFieldID(gameSettingClass, "aJ", Descriptors::field_float);
        Mapper::mapper_fields["gameSetting_thirdPersonView"] = EnvUtils::Env->GetFieldID(gameSettingClass, "aB", Descriptors::field_int);
    EnvUtils::Env->DeleteLocalRef(gameSettingClass);

    // MovingObjectPosition.class
    jclass movingObjectPositionClass = Mapper::mapper_classes["MovingObjectPosition"];
        Mapper::mapper_fields["movingObjectPosition_hitVec"] = EnvUtils::Env->GetFieldID(movingObjectPositionClass, "c", "Laui;");
        Mapper::mapper_fields["movingObjectPosition_typeOfHit"] = EnvUtils::Env->GetFieldID(movingObjectPositionClass, "a", "Lauh$a;");
        Mapper::mapper_fields["movingObjectPosition_blockPos"] = EnvUtils::Env->GetFieldID(movingObjectPositionClass, "e", "Lcj;");
    EnvUtils::Env->DeleteLocalRef(movingObjectPositionClass);

    // Block.class
    jclass blockClass = Mapper::mapper_classes["Block"];
        Mapper::mapper_voids["getLocalizedName"] = EnvUtils::Env->GetMethodID(blockClass, "f", Descriptors::class_string);
    EnvUtils::Env->DeleteLocalRef(blockClass);

    // BlockPos.class
    jclass blockPosClass = Mapper::mapper_classes["BlockPos"];
        Mapper::mapper_fields["blockPos_x"] = EnvUtils::Env->GetFieldID(blockPosClass, "a", Descriptors::field_int);
        Mapper::mapper_fields["blockPos_y"] = EnvUtils::Env->GetFieldID(blockPosClass, "c", Descriptors::field_int);
        Mapper::mapper_fields["blockPos_z"] = EnvUtils::Env->GetFieldID(blockPosClass, "d", Descriptors::field_int);
    EnvUtils::Env->DeleteLocalRef(blockPosClass);

    // IBlockState.class
    jclass iblockStateClass = Mapper::mapper_classes["IBlockState"];
        Mapper::mapper_voids["iBlockState_getBlock"] = EnvUtils::Env->GetMethodID(iblockStateClass, "c", "()Lafh;");
    EnvUtils::Env->DeleteLocalRef(iblockStateClass);

    // ServerData.class
    jclass serverDataClass = Mapper::mapper_classes["ServerData"];
        Mapper::mapper_fields["serverData_serverName"] = EnvUtils::Env->GetFieldID(serverDataClass, "a", Descriptors::field_string);
        Mapper::mapper_fields["serverData_serverIP"] = EnvUtils::Env->GetFieldID(serverDataClass, "b", Descriptors::field_string);
        Mapper::mapper_fields["serverData_pingToServer"] = EnvUtils::Env->GetFieldID(serverDataClass, "e", Descriptors::field_long);
    EnvUtils::Env->DeleteLocalRef(serverDataClass);

    Abyss::logger.log("| Mapper - Info: Applying Vanilla Done");
}

jmethodID minecraftObj = nullptr;
void Mapper::applyForgeMappings() {
    Abyss::logger.log("| Mapper - Info: Applying Forge Mappings");

    // Minecraft.class ---
    jclass mcClass = Mapper::mapper_classes["Minecraft"];
        Mapper::mapper_voids["minecraft_getMinecraft"] = EnvUtils::Env->GetStaticMethodID(mcClass, "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
        Mapper::mapper_voids["minecraft_isSinglePlayer"] = EnvUtils::Env->GetMethodID(mcClass, "func_71356_B", Descriptors::void_boolean);
        Mapper::mapper_fields["minecraft_thePlayer"]    = EnvUtils::Env->GetFieldID(mcClass, "field_71439_g", "Lnet/minecraft/client/entity/EntityPlayerSP;");
        Mapper::mapper_fields["minecraft_theWorld"] = EnvUtils::Env->GetFieldID(mcClass, "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
        Mapper::mapper_fields["minecraft_session"] = EnvUtils::Env->GetFieldID(mcClass, "field_71449_j", "Lnet/minecraft/util/Session;");
        Mapper::mapper_fields["minecraft_pointedEntity"] = EnvUtils::Env->GetFieldID(mcClass, "field_147125_j", "Lnet/minecraft/entity/Entity;");
        Mapper::mapper_fields["minecraft_objectMouseOver"] = EnvUtils::Env->GetFieldID(mcClass, "field_71476_x", "Lnet/minecraft/util/MovingObjectPosition;");
        Mapper::mapper_fields["minecraft_gameSettings"] = EnvUtils::Env->GetFieldID(mcClass, "field_71474_y", "Lnet/minecraft/client/settings/GameSettings;");
        Mapper::mapper_fields["minecraft_currentScreen"] = EnvUtils::Env->GetFieldID(mcClass, "field_71462_r", "Lnet/minecraft/client/gui/GuiScreen;");
        Mapper::mapper_fields["minecraft_renderManager"] = EnvUtils::Env->GetFieldID(mcClass, "field_175616_W", "Lnet/minecraft/client/renderer/entity/RenderManager;");
        Mapper::mapper_fields["minecraft_debugFPS"] = EnvUtils::Env->GetStaticFieldID(mcClass, "field_71470_ab", Descriptors::field_int);
        Mapper::mapper_fields["minecraft_rightClickDelayTimer"] = EnvUtils::Env->GetFieldID(mcClass, "field_71467_ac", Descriptors::field_int);
        Mapper::mapper_fields["minecraft_leftClickCounter"] = EnvUtils::Env->GetFieldID(mcClass, "field_71429_W", Descriptors::field_int);
        Mapper::mapper_fields["minecraft_currentServerData"] = EnvUtils::Env->GetFieldID(mcClass, "field_71422_O", "Lnet/minecraft/client/multiplayer/ServerData;");
    EnvUtils::Env->DeleteLocalRef(mcClass);

    // Session.class ---
    jclass sessionClass = Mapper::mapper_classes["Session"];
        Mapper::mapper_voids["session_getName"] = EnvUtils::Env->GetMethodID(sessionClass, "func_111285_a", Descriptors::class_string);
        Mapper::mapper_voids["session_getType"] = EnvUtils::Env->GetMethodID(sessionClass, "func_152428_f", "()Lnet/minecraft/util/Session$Type;");
    EnvUtils::Env->DeleteLocalRef(sessionClass);

    // World.class ---
    jclass worldClass = Mapper::mapper_classes["World"];
        Mapper::mapper_voids["world_isAirBlock"] = EnvUtils::Env->GetMethodID(worldClass, "func_175623_d", "(Lnet/minecraft/util/BlockPos;)Z");
        Mapper::mapper_voids["world_getBlockState"] = EnvUtils::Env->GetMethodID(worldClass, "func_180495_p", "(Lnet/minecraft/util/BlockPos;)Lnet/minecraft/block/state/IBlockState;");
        Mapper::mapper_voids["world_setWorldTime"] = EnvUtils::Env->GetMethodID(worldClass, "func_72877_b", Descriptors::void_with_long);
        Mapper::mapper_fields["world_playerEntities"] = EnvUtils::Env->GetFieldID(worldClass, "field_73010_i", "Ljava/util/List;");
    EnvUtils::Env->DeleteLocalRef(worldClass);

    // Entity.class ---
    jclass entityClass = Mapper::mapper_classes["Entity"];
        Mapper::mapper_voids["entity_getName"] = EnvUtils::Env->GetMethodID(entityClass, "func_70005_c_", Descriptors::class_string);
        Mapper::mapper_voids["entity_isSneaking"] = EnvUtils::Env->GetMethodID(entityClass, "func_70093_af", Descriptors::void_boolean);
        Mapper::mapper_voids["entity_setSneaking"] = EnvUtils::Env->GetMethodID(entityClass, "func_70095_a", Descriptors::void_with_boolean);
        Mapper::mapper_voids["entity_inWater"] = EnvUtils::Env->GetMethodID(entityClass, "func_70090_H", Descriptors::void_boolean);
        Mapper::mapper_voids["entity_isInvisible"] = EnvUtils::Env->GetMethodID(entityClass, "func_82150_aj", Descriptors::void_boolean);
        Mapper::mapper_voids["entity_getUUID"] = EnvUtils::Env->GetMethodID(entityClass, "func_110124_au", Descriptors::class_uuid);
        Mapper::mapper_voids["entity_getEntityWorld"] = EnvUtils::Env->GetMethodID(entityClass, "func_130014_f_", "()Lnet/minecraft/world/World;");
        Mapper::mapper_fields["entity_motionX"] = EnvUtils::Env->GetFieldID(entityClass, "field_70159_w", Descriptors::field_double);
        Mapper::mapper_fields["entity_motionY"] = EnvUtils::Env->GetFieldID(entityClass, "field_70181_x", Descriptors::field_double);
        Mapper::mapper_fields["entity_motionZ"] = EnvUtils::Env->GetFieldID(entityClass, "field_70179_y", Descriptors::field_double);
        Mapper::mapper_fields["entity_posX"] = EnvUtils::Env->GetFieldID(entityClass, "field_70165_t", Descriptors::field_double);
        Mapper::mapper_fields["entity_posY"] = EnvUtils::Env->GetFieldID(entityClass, "field_70163_u", Descriptors::field_double);
        Mapper::mapper_fields["entity_posZ"] = EnvUtils::Env->GetFieldID(entityClass, "field_70161_v", Descriptors::field_double);
        Mapper::mapper_fields["entity_lastTickPosX"] = EnvUtils::Env->GetFieldID(entityClass, "field_70142_S", Descriptors::field_double);
        Mapper::mapper_fields["entity_lastTickPosY"] = EnvUtils::Env->GetFieldID(entityClass, "field_70137_T", Descriptors::field_double);
        Mapper::mapper_fields["entity_lastTickPosZ"] = EnvUtils::Env->GetFieldID(entityClass, "field_70136_U", Descriptors::field_double);
        Mapper::mapper_fields["entity_width"] = EnvUtils::Env->GetFieldID(entityClass, "field_70130_N", Descriptors::field_float);
        Mapper::mapper_fields["entity_height"] = EnvUtils::Env->GetFieldID(entityClass, "field_70131_O", Descriptors::field_float);
        Mapper::mapper_fields["entity_hurtResistantTime"] = EnvUtils::Env->GetFieldID(entityClass, "field_70172_ad", Descriptors::field_int);
        Mapper::mapper_fields["entity_rotationYaw"] = EnvUtils::Env->GetFieldID(entityClass, "field_70177_z", Descriptors::field_float);
        Mapper::mapper_fields["entity_rotationPitch"] = EnvUtils::Env->GetFieldID(entityClass, "field_70125_A", Descriptors::field_float);
        Mapper::mapper_fields["entity_boundingBox"] = EnvUtils::Env->GetFieldID(entityClass, "field_70121_D", "Lnet/minecraft/util/AxisAlignedBB;");
        Mapper::mapper_fields["entity_onGround"] = EnvUtils::Env->GetFieldID(entityClass, "field_70122_E", Descriptors::field_boolean);
        Mapper::mapper_fields["entity_fallDistance"] = EnvUtils::Env->GetFieldID(entityClass, "field_70143_R", Descriptors::field_float);
        Mapper::mapper_fields["entity_ticksExisted"] = EnvUtils::Env->GetFieldID(entityClass, "field_70173_aa", Descriptors::field_int);
        Mapper::mapper_fields["entity_isDead"] = EnvUtils::Env->GetFieldID(entityClass, "field_70128_L", Descriptors::field_boolean);
    EnvUtils::Env->DeleteLocalRef(entityClass);

    // EntityLivingBase.class ---
    jclass entityLivingBaseClass = Mapper::mapper_classes["EntityLivingBase"];
        Mapper::mapper_voids["entityLivingBase_jump"] = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "func_70664_aZ", Descriptors::void_);
        Mapper::mapper_voids["entityLivingBase_swingItem"]  = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "func_71038_i", Descriptors::void_);
        Mapper::mapper_voids["entityPlayerBase_isPlayerSleeping"]  = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "func_70608_bn", Descriptors::void_boolean);
        Mapper::mapper_voids["entityPlayerBase_canEntityBeSeen"]  = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "func_70685_l", "(Lnet/minecraft/entity/Entity;)Z");
        Mapper::mapper_voids["entityLivingBase_getHealth"] = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "func_110143_aJ", Descriptors::void_float);
        Mapper::mapper_voids["entityLivingBase_getMaxHealth"] = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "func_110138_aP", Descriptors::void_float);
        Mapper::mapper_fields["entityLivingBase_maxHurtResistantTime"]  = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "field_70771_an", Descriptors::field_int);
        Mapper::mapper_fields["entityLivingBase_hurtTime"]  = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "field_70737_aN", Descriptors::field_int);
        Mapper::mapper_fields["entityLivingBase_moveForward"] = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "field_70701_bs", Descriptors::field_float);
        Mapper::mapper_fields["entityLivingBase_moveStrafe"] = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "field_70702_br", Descriptors::field_float);
        Mapper::mapper_fields["entityLivingBase_rotationYawHead"] = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "field_70759_as", Descriptors::field_float);
        Mapper::mapper_fields["entityLivingBase_prevRotationYawHead"] = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "field_70758_at", Descriptors::field_float);
        Mapper::mapper_fields["entityLivingBase_renderYawOffset"] = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "field_70761_aq", Descriptors::field_float);
        Mapper::mapper_voids["entityLivingBase_getTeam"] = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "func_96124_cp", "()Lnet/minecraft/scoreboard/Team;");
    EnvUtils::Env->DeleteLocalRef(entityLivingBaseClass);

    // EntityPlayer.class ---
    jclass entityPlayerClass = Mapper::mapper_classes["EntityPlayer"];
        Mapper::mapper_voids["entityPlayer_isSpectator"]  = EnvUtils::Env->GetMethodID(entityPlayerClass, "func_175149_v", Descriptors::void_boolean);
        Mapper::mapper_voids["entityPlayer_isBlocking"] = EnvUtils::Env->GetMethodID(entityPlayerClass, "func_70632_aY", Descriptors::void_boolean);
        Mapper::mapper_voids["entityPlayer_closeScreen"] = EnvUtils::Env->GetMethodID(entityPlayerClass, "func_71053_j", Descriptors::void_);
        Mapper::mapper_voids["entityPlayer_dropItem"] = EnvUtils::Env->GetMethodID(entityPlayerClass, "func_71040_bB", "(Z)Lnet/minecraft/entity/item/EntityItem;");
        Mapper::mapper_fields["entityPlayer_openContainer"] = EnvUtils::Env->GetFieldID(entityPlayerClass, "field_71070_bA", "Lnet/minecraft/inventory/Container;");
        Mapper::mapper_fields["entityPlayer_inventory"] = EnvUtils::Env->GetFieldID(entityPlayerClass, "field_71071_by", "Lnet/minecraft/entity/player/InventoryPlayer;");
    EnvUtils::Env->DeleteLocalRef(entityPlayerClass);

    // WorldClient.class ---
    jclass worldClientClass = Mapper::mapper_classes["WorldClient"];
        Mapper::mapper_fields["worldClient_entityList"] = EnvUtils::Env->GetFieldID(worldClientClass, "field_73032_d", "Ljava/util/Set;");
        Mapper::mapper_voids["worldClient_sendQuittingDisconnectingPacket"] = EnvUtils::Env->GetMethodID(worldClientClass, "func_72882_A", Descriptors::void_);
    EnvUtils::Env->DeleteLocalRef(worldClientClass);

    // RenderManager.class ---
    jclass renderManagerClass = Mapper::mapper_classes["RenderManager"];
        Mapper::mapper_voids["renderManager_doRenderEntity"] = EnvUtils::Env->GetMethodID(renderManagerClass, "func_147939_a", "(Lnet/minecraft/entity/Entity;DDDFFZ)Z");
    EnvUtils::Env->DeleteLocalRef(renderManagerClass);

    // InventoryPlayer.class ---
    jclass inventoryPlayerClass = Mapper::mapper_classes["InventoryPlayer"];
        Mapper::mapper_voids["inventoryPlayer_getCurrentItem"] = EnvUtils::Env->GetMethodID(inventoryPlayerClass, "func_70448_g", Descriptors::class_itemStack);
        Mapper::mapper_fields["inventoryPlayer_mainInv"] = EnvUtils::Env->GetFieldID(inventoryPlayerClass, "field_70462_a", Descriptors::class_itemStack_array);
        Mapper::mapper_fields["inventoryPlayer_armorInv"] = EnvUtils::Env->GetFieldID(inventoryPlayerClass, "field_70460_b", Descriptors::class_itemStack_array);
        Mapper::mapper_fields["inventoryPlayer_currentItem"] = EnvUtils::Env->GetFieldID(inventoryPlayerClass, "field_70461_c", Descriptors::field_int);
    EnvUtils::Env->DeleteLocalRef(inventoryPlayerClass);

    // ItemStack.class ---
    jclass itemStackClass = Mapper::mapper_classes["ItemStack"];
        Mapper::mapper_voids["itemStack_getItem"] = EnvUtils::Env->GetMethodID(itemStackClass, "func_77973_b" , Descriptors::class_item);
        Mapper::mapper_voids["itemStack_getName"] = EnvUtils::Env->GetMethodID(itemStackClass, "func_82833_r", Descriptors::class_string);
    EnvUtils::Env->DeleteLocalRef(itemStackClass);

    // KeyBinding.class ---
    jclass keybindingClass = Mapper::mapper_classes["KeyBinding"];
        Mapper::mapper_fields["keybinding_pressed"] = EnvUtils::Env->GetFieldID(keybindingClass, "field_74513_e", Descriptors::field_boolean);
    EnvUtils::Env->DeleteLocalRef(keybindingClass);

    // GameSettings.class ---
    jclass gameSettingClass = Mapper::mapper_classes["GameSettings"];
        Mapper::mapper_fields["gameSetting_keyBindRight"] = EnvUtils::Env->GetFieldID(gameSettingClass, "field_74366_z", "Lnet/minecraft/client/settings/KeyBinding;");
        Mapper::mapper_fields["gameSetting_keyBindLeft"] = EnvUtils::Env->GetFieldID(gameSettingClass, "field_74370_x", "Lnet/minecraft/client/settings/KeyBinding;");
        Mapper::mapper_fields["gameSetting_keyBindBack"] = EnvUtils::Env->GetFieldID(gameSettingClass, "field_74368_y", "Lnet/minecraft/client/settings/KeyBinding;");
        Mapper::mapper_fields["gameSetting_keyBindForward"] = EnvUtils::Env->GetFieldID(gameSettingClass, "field_74351_w", "Lnet/minecraft/client/settings/KeyBinding;");
        Mapper::mapper_fields["gameSetting_keyBindSneak"] = EnvUtils::Env->GetFieldID(gameSettingClass, "field_74311_E", "Lnet/minecraft/client/settings/KeyBinding;");
        Mapper::mapper_fields["gameSetting_keyBindJump"] = EnvUtils::Env->GetFieldID(gameSettingClass, "field_74314_A", "Lnet/minecraft/client/settings/KeyBinding;");
        Mapper::mapper_fields["gameSetting_fovSetting"] = EnvUtils::Env->GetFieldID(gameSettingClass, "field_74334_X", Descriptors::field_float);
        Mapper::mapper_fields["gameSetting_gammaSetting"] = EnvUtils::Env->GetFieldID(gameSettingClass, "field_74333_Y", Descriptors::field_float);
        Mapper::mapper_fields["gameSetting_thirdPersonView"] = EnvUtils::Env->GetFieldID(gameSettingClass, "field_74320_O", Descriptors::field_int);
    EnvUtils::Env->DeleteLocalRef(gameSettingClass);

    // MovingObjectPosition.class
    jclass movingObjectPositionClass = Mapper::mapper_classes["MovingObjectPosition"];
        Mapper::mapper_fields["movingObjectPosition_hitVec"] = EnvUtils::Env->GetFieldID(movingObjectPositionClass, "field_72307_f", "Lnet/minecraft/util/Vec3;");
        Mapper::mapper_fields["movingObjectPosition_typeOfHit"] = EnvUtils::Env->GetFieldID(movingObjectPositionClass, "field_72313_a", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
        Mapper::mapper_fields["movingObjectPosition_blockPos"] = EnvUtils::Env->GetFieldID(movingObjectPositionClass, "field_178783_e", "Lnet/minecraft/util/BlockPos;");
    EnvUtils::Env->DeleteLocalRef(movingObjectPositionClass);

    // Block.class
    jclass blockClass = Mapper::mapper_classes["Block"];
        Mapper::mapper_voids["getLocalizedName"] = EnvUtils::Env->GetMethodID(blockClass, "func_149732_F", Descriptors::class_string);
    EnvUtils::Env->DeleteLocalRef(blockClass);

    // BlockPos.class
    jclass blockPosClass = Mapper::mapper_classes["BlockPos"];
        Mapper::mapper_fields["blockPos_x"] = EnvUtils::Env->GetFieldID(blockPosClass, "field_177962_a", Descriptors::field_int);
        Mapper::mapper_fields["blockPos_y"] = EnvUtils::Env->GetFieldID(blockPosClass, "field_177960_b", Descriptors::field_int);
        Mapper::mapper_fields["blockPos_z"] = EnvUtils::Env->GetFieldID(blockPosClass, "field_177961_c", Descriptors::field_int);
    EnvUtils::Env->DeleteLocalRef(blockPosClass);

    // IBlockState.class
    jclass iblockStateClass = Mapper::mapper_classes["IBlockState"];
        Mapper::mapper_voids["iBlockState_getBlock"] = EnvUtils::Env->GetMethodID(iblockStateClass, "func_177230_c", "()Lnet/minecraft/block/Block;");
    EnvUtils::Env->DeleteLocalRef(iblockStateClass);

    // ServerData.class
    jclass serverDataClass = Mapper::mapper_classes["ServerData"];
        Mapper::mapper_fields["serverData_serverName"] = EnvUtils::Env->GetFieldID(serverDataClass, "field_78847_a", Descriptors::field_string);
        Mapper::mapper_fields["serverData_serverIP"] = EnvUtils::Env->GetFieldID(serverDataClass, "field_78845_b", Descriptors::field_string);
        Mapper::mapper_fields["serverData_pingToServer"] = EnvUtils::Env->GetFieldID(serverDataClass, "field_78844_e", Descriptors::field_long);
    EnvUtils::Env->DeleteLocalRef(serverDataClass);

    Abyss::logger.log("| Mapper - Info: Applying Forge Done");
}

void Mapper::applyLunarMappings() {
    if (Mapper::currentMapping != Mappings::Lunar)
        return;

    Abyss::logger.log("| Mapper - Info: Applying Lunar Mappings");
    // Minecraft.class ---
    jclass mcClass = Mapper::mapper_classes["Minecraft"];
        Mapper::mapper_voids["minecraft_getMinecraft"] = EnvUtils::Env->GetStaticMethodID(mcClass, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
        Mapper::mapper_voids["minecraft_isSinglePlayer"] = EnvUtils::Env->GetMethodID(mcClass, "isSingleplayer", Descriptors::void_boolean);

        Mapper::mapper_fields["minecraft_theMinecraft"] = EnvUtils::Env->GetStaticFieldID(mcClass, "theMinecraft", "Lnet/minecraft/client/Minecraft;");
        Mapper::mapper_fields["minecraft_thePlayer"] = EnvUtils::Env->GetFieldID(mcClass, "thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;");
        Mapper::mapper_fields["minecraft_theWorld"] = EnvUtils::Env->GetFieldID(mcClass, "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");
        Mapper::mapper_fields["minecraft_session"] = EnvUtils::Env->GetFieldID(mcClass, "session", "Lnet/minecraft/util/Session;");
        Mapper::mapper_fields["minecraft_pointedEntity"] = EnvUtils::Env->GetFieldID(mcClass, "pointedEntity", "Lnet/minecraft/entity/Entity;");
        Mapper::mapper_fields["minecraft_objectMouseOver"] = EnvUtils::Env->GetFieldID(mcClass, "objectMouseOver", "Lnet/minecraft/util/MovingObjectPosition;");
        Mapper::mapper_fields["minecraft_gameSettings"] = EnvUtils::Env->GetFieldID(mcClass, "gameSettings", "Lnet/minecraft/client/settings/GameSettings;");
        Mapper::mapper_fields["minecraft_currentScreen"] = EnvUtils::Env->GetFieldID(mcClass, "currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");
        Mapper::mapper_fields["minecraft_renderManager"] = EnvUtils::Env->GetFieldID(mcClass, "renderManager", "Lnet/minecraft/client/renderer/entity/RenderManager;");
        Mapper::mapper_fields["minecraft_debugFPS"] = EnvUtils::Env->GetStaticFieldID(mcClass, "debugFPS", Descriptors::field_int);
        Mapper::mapper_fields["minecraft_rightClickDelayTimer"] = EnvUtils::Env->GetFieldID(mcClass, "rightClickDelayTimer", Descriptors::field_int);
        Mapper::mapper_fields["minecraft_leftClickCounter"] = EnvUtils::Env->GetFieldID(mcClass, "leftClickCounter", Descriptors::field_int);
        Mapper::mapper_fields["minecraft_currentServerData"] = EnvUtils::Env->GetFieldID(mcClass, "currentServerData", "Lnet/minecraft/client/multiplayer/ServerData;");
    EnvUtils::Env->DeleteLocalRef(mcClass);

    // Session.class ---
    jclass sessionClass = Mapper::mapper_classes["Session"];
        Mapper::mapper_voids["session_getName"] = EnvUtils::Env->GetMethodID(sessionClass, "getUsername", Descriptors::class_string);
        Mapper::mapper_voids["session_getType"] = EnvUtils::Env->GetMethodID(sessionClass, "getSessionType", "()Lnet/minecraft/util/Session$Type;");
    EnvUtils::Env->DeleteLocalRef(sessionClass);

    // World.class ---
    jclass worldClass = Mapper::mapper_classes["World"];
        Mapper::mapper_voids["world_isAirBlock"] = EnvUtils::Env->GetMethodID(worldClass, "isAirBlock", "(Lnet/minecraft/util/BlockPos;)Z");
        Mapper::mapper_voids["world_getBlockState"] = EnvUtils::Env->GetMethodID(worldClass, "getBlockState", "(Lnet/minecraft/util/BlockPos;)Lnet/minecraft/block/state/IBlockState;");
        Mapper::mapper_voids["world_setWorldTime"] = EnvUtils::Env->GetMethodID(worldClass, "setWorldTime", Descriptors::void_with_long);
        Mapper::mapper_fields["world_playerEntities"] = EnvUtils::Env->GetFieldID(worldClass, "playerEntities", "Ljava/util/List;");
    EnvUtils::Env->DeleteLocalRef(worldClass);

    // Entity.class ---
    jclass entityClass = Mapper::mapper_classes["Entity"];
        Mapper::mapper_voids["entity_getName"] = EnvUtils::Env->GetMethodID(entityClass, "getName", Descriptors::class_string);
        Mapper::mapper_voids["entity_isSneaking"] = EnvUtils::Env->GetMethodID(entityClass, "isSneaking", Descriptors::void_boolean);
        Mapper::mapper_voids["entity_setSneaking"] = EnvUtils::Env->GetMethodID(entityClass, "setSneaking", Descriptors::void_with_boolean);
        Mapper::mapper_voids["entity_inWater"] = EnvUtils::Env->GetMethodID(entityClass, "isInWater", Descriptors::void_boolean);
        Mapper::mapper_voids["entity_isInvisible"] = EnvUtils::Env->GetMethodID(entityClass, "isInvisible", Descriptors::void_boolean);
        Mapper::mapper_voids["entity_getUUID"] = EnvUtils::Env->GetMethodID(entityClass, "getUniqueID", Descriptors::class_uuid);
        Mapper::mapper_voids["entity_getEntityWorld"] = EnvUtils::Env->GetMethodID(entityClass, "getEntityWorld", "()Lnet/minecraft/world/World;");
        Mapper::mapper_fields["entity_motionX"] = EnvUtils::Env->GetFieldID(entityClass,  "motionX", Descriptors::field_double);
        Mapper::mapper_fields["entity_motionY"] = EnvUtils::Env->GetFieldID(entityClass,  "motionY", Descriptors::field_double);
        Mapper::mapper_fields["entity_motionZ"] = EnvUtils::Env->GetFieldID(entityClass,  "motionZ", Descriptors::field_double);
        Mapper::mapper_fields["entity_posX"] = EnvUtils::Env->GetFieldID(entityClass, "posX", Descriptors::field_double);
        Mapper::mapper_fields["entity_posY"] = EnvUtils::Env->GetFieldID(entityClass, "posY", Descriptors::field_double);
        Mapper::mapper_fields["entity_posZ"] = EnvUtils::Env->GetFieldID(entityClass, "posZ", Descriptors::field_double);
        Mapper::mapper_fields["entity_lastTickPosX"] = EnvUtils::Env->GetFieldID(entityClass, "lastTickPosX", Descriptors::field_double);
        Mapper::mapper_fields["entity_lastTickPosY"] = EnvUtils::Env->GetFieldID(entityClass, "lastTickPosY", Descriptors::field_double);
        Mapper::mapper_fields["entity_lastTickPosZ"] = EnvUtils::Env->GetFieldID(entityClass, "lastTickPosZ", Descriptors::field_double);
        Mapper::mapper_fields["entity_width"] = EnvUtils::Env->GetFieldID(entityClass, "width", Descriptors::field_float);
        Mapper::mapper_fields["entity_height"] = EnvUtils::Env->GetFieldID(entityClass, "height", Descriptors::field_float);
        Mapper::mapper_fields["entity_hurtResistantTime"] = EnvUtils::Env->GetFieldID(entityClass, "hurtResistantTime", Descriptors::field_int);
        Mapper::mapper_fields["entity_rotationYaw"] = EnvUtils::Env->GetFieldID(entityClass, "rotationYaw", Descriptors::field_float);
        Mapper::mapper_fields["entity_rotationPitch"] = EnvUtils::Env->GetFieldID(entityClass, "rotationPitch", Descriptors::field_float);
        Mapper::mapper_fields["entity_boundingBox"] = EnvUtils::Env->GetFieldID(entityClass, "boundingBox", "Lnet/minecraft/util/AxisAlignedBB;");
        Mapper::mapper_fields["entity_onGround"] = EnvUtils::Env->GetFieldID(entityClass, "onGround", Descriptors::field_boolean);
        Mapper::mapper_fields["entity_fallDistance"] = EnvUtils::Env->GetFieldID(entityClass, "fallDistance", Descriptors::field_float);
        Mapper::mapper_fields["entity_ticksExisted"] = EnvUtils::Env->GetFieldID(entityClass, "ticksExisted", Descriptors::field_int);
        Mapper::mapper_fields["entity_isDead"] = EnvUtils::Env->GetFieldID(entityClass, "isDead", Descriptors::field_boolean);
    EnvUtils::Env->DeleteLocalRef(entityClass);

    // EntityLivingBase.class ---
    jclass entityLivingBaseClass = Mapper::mapper_classes["EntityLivingBase"];
        Mapper::mapper_voids["entityLivingBase_jump"] = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "jump", Descriptors::void_);
        Mapper::mapper_voids["entityLivingBase_swingItem"]  = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "swingItem", Descriptors::void_);
        Mapper::mapper_voids["entityPlayerBase_isPlayerSleeping"]  = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "isPlayerSleeping", Descriptors::void_boolean);
        Mapper::mapper_voids["entityPlayerBase_canEntityBeSeen"]  = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "canEntityBeSeen", "(Lnet/minecraft/entity/Entity;)Z");
        Mapper::mapper_voids["entityLivingBase_getHealth"] = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "getHealth", Descriptors::void_float);
        Mapper::mapper_voids["entityLivingBase_getMaxHealth"] = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "getMaxHealth", Descriptors::void_float);
        Mapper::mapper_fields["entityLivingBase_maxHurtResistantTime"]  = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "maxHurtResistantTime", Descriptors::field_int);
        Mapper::mapper_fields["entityLivingBase_hurtTime"]  = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "hurtTime", Descriptors::field_int);
        Mapper::mapper_fields["entityLivingBase_moveForward"] = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "moveForward", Descriptors::field_float);
        Mapper::mapper_fields["entityLivingBase_moveStrafe"] = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "moveStrafing", Descriptors::field_float);
        Mapper::mapper_fields["entityLivingBase_rotationYawHead"] = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "rotationYawHead", Descriptors::field_float);
        Mapper::mapper_fields["entityLivingBase_prevRotationYawHead"] = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "prevRotationYawHead", Descriptors::field_float);
        Mapper::mapper_fields["entityLivingBase_renderYawOffset"] = EnvUtils::Env->GetFieldID(entityLivingBaseClass, "renderYawOffset", Descriptors::field_float);
        Mapper::mapper_voids["entityLivingBase_getTeam"] = EnvUtils::Env->GetMethodID(entityLivingBaseClass, "getTeam", "()Lnet/minecraft/scoreboard/Team;");
    EnvUtils::Env->DeleteLocalRef(entityLivingBaseClass);

    // EntityPlayer.class ---
    jclass entityPlayerClass = Mapper::mapper_classes["EntityPlayer"];
        Mapper::mapper_voids["entityPlayer_isSpectator"]  = EnvUtils::Env->GetMethodID(entityPlayerClass, "isSpectator", Descriptors::void_boolean);
        Mapper::mapper_voids["entityPlayer_isBlocking"] = EnvUtils::Env->GetMethodID(entityPlayerClass, "isBlocking", Descriptors::void_boolean);
        Mapper::mapper_voids["entityPlayer_closeScreen"] = EnvUtils::Env->GetMethodID(entityPlayerClass, "closeScreen", Descriptors::void_);
        Mapper::mapper_voids["entityPlayer_dropItem"] = EnvUtils::Env->GetMethodID(entityPlayerClass, "dropOneItem", "(Z)Lnet/minecraft/entity/item/EntityItem;");
        Mapper::mapper_fields["entityPlayer_openContainer"] = EnvUtils::Env->GetFieldID(entityPlayerClass, "openContainer", "Lnet/minecraft/inventory/Container;");
        Mapper::mapper_fields["entityPlayer_inventory"] = EnvUtils::Env->GetFieldID(entityPlayerClass, "inventory", "Lnet/minecraft/entity/player/InventoryPlayer;");
    EnvUtils::Env->DeleteLocalRef(entityPlayerClass);

    // WorldClient.class ---
    jclass worldClientClass = Mapper::mapper_classes["WorldClient"];
        Mapper::mapper_fields["worldClient_entityList"] = EnvUtils::Env->GetFieldID(worldClientClass, "entityList", "Ljava/util/Set;");
        Mapper::mapper_voids["worldClient_sendQuittingDisconnectingPacket"] = EnvUtils::Env->GetMethodID(worldClientClass, "sendQuittingDisconnectingPacket", Descriptors::void_);
    EnvUtils::Env->DeleteLocalRef(worldClientClass);

    // RenderManager.class ---
    jclass renderManagerClass = Mapper::mapper_classes["RenderManager"];
        Mapper::mapper_voids["renderManager_doRenderEntity"] = EnvUtils::Env->GetMethodID(renderManagerClass, "doRenderEntity", "(Lnet/minecraft/entity/EntityPlayerSP;DDDFF)Z");
    EnvUtils::Env->DeleteLocalRef(renderManagerClass);

    // InventoryPlayer.class ---
    jclass inventoryPlayerClass = Mapper::mapper_classes["InventoryPlayer"];
        Mapper::mapper_voids["inventoryPlayer_getCurrentItem"] = EnvUtils::Env->GetMethodID(inventoryPlayerClass, "getCurrentItem", Descriptors::class_itemStack);
        Mapper::mapper_fields["inventoryPlayer_mainInv"] = EnvUtils::Env->GetFieldID(inventoryPlayerClass, "mainInventory", Descriptors::class_itemStack_array);
        Mapper::mapper_fields["inventoryPlayer_armorInv"] = EnvUtils::Env->GetFieldID(inventoryPlayerClass, "armorInventory", Descriptors::class_itemStack_array);
        Mapper::mapper_fields["inventoryPlayer_currentItem"] = EnvUtils::Env->GetFieldID(inventoryPlayerClass, "currentItem", Descriptors::field_int);
    EnvUtils::Env->DeleteLocalRef(inventoryPlayerClass);

    // ItemStack.class ---
    jclass itemStackClass = Mapper::mapper_classes["ItemStack"];
        Mapper::mapper_voids["itemStack_getItem"] = EnvUtils::Env->GetMethodID(itemStackClass, "getItem" , Descriptors::class_item);
        Mapper::mapper_voids["itemStack_getName"] = EnvUtils::Env->GetMethodID(itemStackClass, "getDisplayName", Descriptors::class_string);
    EnvUtils::Env->DeleteLocalRef(itemStackClass);

    // KeyBinding.class ---
    jclass keybindingClass = Mapper::mapper_classes["KeyBinding"];
        Mapper::mapper_fields["keybinding_pressed"] = EnvUtils::Env->GetFieldID(keybindingClass, "pressed", Descriptors::field_boolean);
    EnvUtils::Env->DeleteLocalRef(keybindingClass);

    // GameSettings.class ---
    jclass gameSettingClass = Mapper::mapper_classes["GameSettings"];
        Mapper::mapper_fields["gameSetting_keyBindRight"] = EnvUtils::Env->GetFieldID(gameSettingClass, "keyBindRight", "Lnet/minecraft/client/settings/KeyBinding;");
        Mapper::mapper_fields["gameSetting_keyBindLeft"] = EnvUtils::Env->GetFieldID(gameSettingClass, "keyBindLeft", "Lnet/minecraft/client/settings/KeyBinding;");
        Mapper::mapper_fields["gameSetting_keyBindBack"] = EnvUtils::Env->GetFieldID(gameSettingClass, "keyBindBack", "Lnet/minecraft/client/settings/KeyBinding;");
        Mapper::mapper_fields["gameSetting_keyBindForward"] = EnvUtils::Env->GetFieldID(gameSettingClass, "keyBindForward", "Lnet/minecraft/client/settings/KeyBinding;");
        Mapper::mapper_fields["gameSetting_keyBindSneak"] = EnvUtils::Env->GetFieldID(gameSettingClass, "keyBindSneak", "Lnet/minecraft/client/settings/KeyBinding;");
        Mapper::mapper_fields["gameSetting_keyBindJump"] = EnvUtils::Env->GetFieldID(gameSettingClass, "keyBindJump", "Lnet/minecraft/client/settings/KeyBinding;");
        Mapper::mapper_fields["gameSetting_fovSetting"] = EnvUtils::Env->GetFieldID(gameSettingClass, "fovSetting", Descriptors::field_float);
        Mapper::mapper_fields["gameSetting_gammaSetting"] = EnvUtils::Env->GetFieldID(gameSettingClass, "gammaSetting", Descriptors::field_float);
        Mapper::mapper_fields["gameSetting_thirdPersonView"] = EnvUtils::Env->GetFieldID(gameSettingClass, "thirdPersonView", Descriptors::field_int);
    EnvUtils::Env->DeleteLocalRef(gameSettingClass);

    // MovingObjectPosition.class
    jclass movingObjectPositionClass = Mapper::mapper_classes["MovingObjectPosition"];
        Mapper::mapper_fields["movingObjectPosition_hitVec"] = EnvUtils::Env->GetFieldID(movingObjectPositionClass, "hitVec", "Lnet/minecraft/util/Vec3;");
        Mapper::mapper_fields["movingObjectPosition_typeOfHit"] = EnvUtils::Env->GetFieldID(movingObjectPositionClass, "typeOfHit", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
        Mapper::mapper_fields["movingObjectPosition_blockPos"] = EnvUtils::Env->GetFieldID(movingObjectPositionClass, "blockPos", "Lnet/minecraft/util/BlockPos;");
    EnvUtils::Env->DeleteLocalRef(movingObjectPositionClass);

    // Block.class
    jclass blockClass = Mapper::mapper_classes["Block"];
        Mapper::mapper_voids["getLocalizedName"] = EnvUtils::Env->GetMethodID(blockClass, "getLocalizedName", Descriptors::class_string);
    EnvUtils::Env->DeleteLocalRef(blockClass);

    // BlockPos.class
    jclass blockPosClass = Mapper::mapper_classes["BlockPos"];
        Mapper::mapper_fields["blockPos_x"] = EnvUtils::Env->GetFieldID(blockPosClass, "x", Descriptors::field_int);
        Mapper::mapper_fields["blockPos_y"] = EnvUtils::Env->GetFieldID(blockPosClass, "y", Descriptors::field_int);
        Mapper::mapper_fields["blockPos_z"] = EnvUtils::Env->GetFieldID(blockPosClass, "z", Descriptors::field_int);
    EnvUtils::Env->DeleteLocalRef(blockPosClass);

    // IBlockState.class
    jclass iblockStateClass = Mapper::mapper_classes["IBlockState"];
        Mapper::mapper_voids["iBlockState_getBlock"] = EnvUtils::Env->GetMethodID(iblockStateClass, "getBlock", "()Lnet/minecraft/block/Block;");
    EnvUtils::Env->DeleteLocalRef(iblockStateClass);

    // ServerData.class
    jclass serverDataClass = Mapper::mapper_classes["ServerData"];
        Mapper::mapper_fields["serverData_serverName"] = EnvUtils::Env->GetFieldID(serverDataClass, "serverName", Descriptors::field_string);
        Mapper::mapper_fields["serverData_serverIP"] = EnvUtils::Env->GetFieldID(serverDataClass, "serverIP", Descriptors::field_string);
        Mapper::mapper_fields["serverData_pingToServer"] = EnvUtils::Env->GetFieldID(serverDataClass, "pingToServer", Descriptors::field_long);
    EnvUtils::Env->DeleteLocalRef(serverDataClass);

    Abyss::logger.log("| Mapper - Info: Applying Lunar Done");
}

void Mapper::checkMappings() {
    Abyss::logger.log("| Mapper - Info: Checking Mappings");

    for (const auto& pair : Mapper::mapper_classes) {
        const std::string& name = pair.first;

        if (pair.second == nullptr)
            Abyss::logger.log("| Mapper - Err: (Class) " + name);
    }

    for (const auto& pair : Mapper::mapper_voids) {
        const std::string& name = pair.first;

        if (pair.second == nullptr)
            Abyss::logger.log("| Mapper - Err: (Void) " + name);
    }

    for (const auto& pair : Mapper::mapper_fields) {
        const std::string& name = pair.first;

        if (pair.second == nullptr)
            Abyss::logger.log("| Mapper - Err: (Field) " + name);
    }

    Abyss::logger.log("| Mapper - Info: Checking Mappings Done");
}

void Mapper::injectForgeClass() {
    LaunchWrapperClassLoaderClass = EnvUtils::Env->FindClass("net/minecraft/launchwrapper/LaunchClassLoader");
    if (LaunchWrapperClassLoaderClass == nullptr)
        return;

    FindClassMethodID = EnvUtils::Env->GetMethodID(LaunchWrapperClassLoaderClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
    if (FindClassMethodID == nullptr)
        return;

    LaunchClass = EnvUtils::Env->FindClass("net/minecraft/launchwrapper/Launch");
    if (LaunchClass == nullptr)
        return;

    ClassLoaderFieldID = EnvUtils::Env->GetStaticFieldID(LaunchClass, "classLoader", "Lnet/minecraft/launchwrapper/LaunchClassLoader;");
    if (ClassLoaderFieldID == nullptr)
        return;

    ClassLoaderObject = EnvUtils::Env->GetStaticObjectField(LaunchClass, ClassLoaderFieldID);
    if (ClassLoaderObject == nullptr) {
        Abyss::logger.log("===========================================================");
        Abyss::logger.log("| Mapper - Err: Didnt Got Classloader");
        Abyss::logger.log("===========================================================");
        return;
    }

    Abyss::logger.log("| Mapper - Info: Got Forge Classloader");
}

jclass Mapper::findForgeClass(String clazz) {
    if (ClassLoaderObject == nullptr)
        return nullptr;

    if (FindClassMethodID == nullptr)
        return nullptr;

    jstring jClassName = EnvUtils::Env->NewStringUTF(clazz.toChar());

    {
        std::string prefix = "net.minecraft.";
        std::string className;
        std::string clazzz = clazz.toString();

        if (clazzz.compare(0, prefix.length(), prefix) == 0)
            className = clazzz.substr(prefix.length());
    }

    auto cls = (jclass) EnvUtils::Env->CallObjectMethod(ClassLoaderObject, FindClassMethodID, jClassName);
    EnvUtils::Env->DeleteLocalRef(jClassName);

    return cls;
}

bool Mapper::useVanillaMappings() {
    return Mapper::currentMapping == Mappings::Vanilla;
}

bool Mapper::useForgeMappings() {
    return Mapper::currentMapping == Mappings::Forge;
}

bool Mapper::useLunarMappings() {
    return Mapper::currentMapping == Mappings::Lunar;
}