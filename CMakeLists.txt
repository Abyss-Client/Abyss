# Set the minimum required cmake version
cmake_minimum_required(VERSION 3.27)

# Declare project
project(NewAbyss)

# Find package
find_package(JNI REQUIRED)
find_package(OpenGL REQUIRED)

# Set your c++ version here
set(CMAKE_CXX_STANDARD 20)

# This will be containing all of your files
add_library(NewAbyss SHARED
        src/me/sleepyfish/abyss/Inject.cpp
        src/me/sleepyfish/abyss/client/Abyss.cpp
        src/me/sleepyfish/abyss/java/mapper/Mapper.cpp
        src/me/sleepyfish/abyss/java/sdk/SdkClass.h
        src/me/sleepyfish/abyss/java/sdk/Sdk.cpp
        src/me/sleepyfish/abyss/java/Java.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/Minecraft.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/entity/EntityPlayerSP.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/entity/EntityPlayer.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/entity/EntityLivingBase.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/entity/Entity.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/world/World.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/world/WorldClient.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/settings/GameSettings.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/item/Item.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/item/ItemStack.cpp
        src/me/sleepyfish/abyss/java/sdk/java/JavaString.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/item/InventoryPlayer.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/settings/Session.cpp
        src/me/sleepyfish/abyss/java/sdk/java/JavaUUID.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/world/Team.cpp
        src/me/sleepyfish/abyss/java/sdk/java/JavaList.cpp

        src/me/sleepyfish/abyss/modules/settings/impl/ModeSetting.h
        src/me/sleepyfish/abyss/modules/settings/impl/SpaceSetting.h
        src/me/sleepyfish/abyss/modules/settings/impl/BoolSetting.h
        src/me/sleepyfish/abyss/modules/settings/impl/SliderSetting.h
        src/me/sleepyfish/abyss/modules/settings/impl/TextSetting.h
        src/me/sleepyfish/abyss/modules/settings/impl/InfoSetting.h
        src/me/sleepyfish/abyss/modules/settings/impl/ColorSetting.h
        src/me/sleepyfish/abyss/modules/settings/Setting.h
        src/me/sleepyfish/abyss/modules/Module.h
        src/me/sleepyfish/abyss/modules/ModuleManager.cpp
        src/me/sleepyfish/abyss/modules/Category.h
        src/me/sleepyfish/abyss/modules/impl/visual/TextGui.cpp
        src/me/sleepyfish/abyss/modules/impl/visual/Overlay.cpp
        src/me/sleepyfish/abyss/modules/impl/legit/AutoClickerL.cpp
        src/me/sleepyfish/abyss/modules/impl/legit/AutoClickerR.cpp
        src/me/sleepyfish/abyss/modules/impl/visual/Fullbright.cpp
        src/me/sleepyfish/abyss/modules/impl/useless/Headache.cpp
        src/me/sleepyfish/abyss/modules/impl/legit/JumpReset.cpp
        src/me/sleepyfish/abyss/modules/impl/other/AutoMove.cpp
        src/me/sleepyfish/abyss/modules/impl/legit/TriggerBot.cpp
        src/me/sleepyfish/abyss/modules/impl/legit/LegitScaffold.cpp
        src/me/sleepyfish/abyss/modules/impl/other/CustomScript.cpp
        src/me/sleepyfish/abyss/modules/impl/useless/Spin.cpp
        src/me/sleepyfish/abyss/modules/impl/useless/Disabler.cpp

        src/me/sleepyfish/abyss/utils/Logger.h
        src/me/sleepyfish/abyss/utils/type/Class.h
        src/me/sleepyfish/abyss/utils/type/ArrayList.h
        src/me/sleepyfish/abyss/utils/type/String.h
        src/me/sleepyfish/abyss/utils/type/Set.h
        src/me/sleepyfish/abyss/utils/ColorUtils.h
        src/me/sleepyfish/abyss/utils/Utils.h
        src/me/sleepyfish/abyss/utils/ClientUtils.h
        src/me/sleepyfish/abyss/utils/MathUtils.h
        src/me/sleepyfish/abyss/utils/type/Vector2.h
        src/me/sleepyfish/abyss/utils/type/Vector3.h
        src/me/sleepyfish/abyss/utils/type/Vector4.h
        src/me/sleepyfish/abyss/utils/ClickGuiUtils.h
        src/me/sleepyfish/abyss/utils/opengl/TextureUtils.cpp
        src/me/sleepyfish/abyss/utils/notification/Notification.h
        src/me/sleepyfish/abyss/utils/notification/NotificationUtils.h
        src/me/sleepyfish/abyss/utils/ClickUtils.h
        src/me/sleepyfish/abyss/utils/EnvUtils.h

        src/me/sleepyfish/abyss/gui/ClickGui.cpp
        src/me/sleepyfish/abyss/gui/ClickGui.h
        src/me/sleepyfish/abyss/gui/hooks/SwapBuffers.cpp
        src/me/sleepyfish/abyss/gui/hooks/KeyEvent.cpp
        src/me/sleepyfish/abyss/gui/hooks/KeyEvent.cpp
        src/me/sleepyfish/abyss/gui/hooks/RenderHook.cpp
        src/me/sleepyfish/abyss/gui/hooks/PacketHook.cpp
        src/me/sleepyfish/abyss/gui/hooks/DoRenderEntityHook.cpp

        # libraries/glew/include/GL/glew.h
        # libraries/glew/include/GL/wglew.h
        # libraries/glew/include/GL/glxew.h

        libraries/imgui/imgui.cpp
        libraries/imgui/imgui_demo.cpp
        libraries/imgui/imgui_draw.cpp
        libraries/imgui/imgui_impl_opengl2.cpp
        libraries/imgui/imgui_impl_win32.cpp
        libraries/imgui/imgui_tables.cpp
        libraries/imgui/imgui_widgets.cpp
        libraries/minhook/buffer.cpp
        libraries/minhook/hook.cpp
        libraries/minhook/trampoline.cpp
        libraries/minhook/hde/hde32.cpp
        libraries/minhook/hde/hde64.cpp
        libraries/stb/stb_image.h

        assets/fonts/quicksand.h
        assets/fonts/quicksandMedium.h
        assets/fonts/quicksandBold.h
        src/me/sleepyfish/abyss/modules/impl/other/AutoTool.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/utils/MovingObjectPosition.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/utils/BlockPos.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/utils/Block.cpp
        src/me/sleepyfish/abyss/modules/impl/other/AutoPearl.cpp
        src/me/sleepyfish/abyss/modules/impl/other/AutoLow.cpp
        src/me/sleepyfish/abyss/modules/impl/visual/TimeChanger.cpp
        src/me/sleepyfish/abyss/modules/impl/legit/AimAssist.cpp
        src/me/sleepyfish/abyss/modules/impl/hud/Coordinates.cpp
        src/me/sleepyfish/abyss/modules/HudModule.h
        src/me/sleepyfish/abyss/modules/impl/blatant/Hitbox.cpp
        src/me/sleepyfish/abyss/modules/impl/hud/Fps.cpp
        src/me/sleepyfish/abyss/modules/impl/hud/Keystrokes.cpp
        src/me/sleepyfish/abyss/utils/opengl/animation/normal/Animation.h
        src/me/sleepyfish/abyss/utils/opengl/animation/normal/DecelerateAnimation.h
        src/me/sleepyfish/abyss/utils/opengl/animation/simple/AnimationUtils.h
        src/me/sleepyfish/abyss/utils/opengl/animation/simple/SimpleAnimation.h
        src/me/sleepyfish/abyss/modules/impl/hud/ServerIp.cpp
        src/me/sleepyfish/abyss/java/sdk/minecraft/world/ServerData.cpp
        src/me/sleepyfish/abyss/modules/impl/hud/ServerName.cpp
        src/me/sleepyfish/abyss/modules/impl/hud/RamUsed.cpp
        src/me/sleepyfish/abyss/utils/MemoryStats.h
        src/me/sleepyfish/abyss/modules/impl/other/Remover.cpp
        src/me/sleepyfish/abyss/modules/impl/blatant/Hitbox.cpp
        src/me/sleepyfish/abyss/modules/impl/blatant/Hitbox.cpp
        src/me/sleepyfish/abyss/modules/impl/blatant/Hitbox.cpp
        src/me/sleepyfish/abyss/modules/impl/blatant/Hitbox.cpp
        src/me/sleepyfish/abyss/modules/impl/blatant/Hitbox.cpp
        src/me/sleepyfish/abyss/modules/impl/blatant/Hitbox.cpp
        src/me/sleepyfish/abyss/modules/impl/blatant/Hitbox.cpp
        src/me/sleepyfish/abyss/modules/impl/visual/PlayerOverlay.cpp
)

# Add glew library
# include_directories(${CMAKE_SOURCE_DIR}/libraries/glew/include)

# Add glew dll
# add_library(glew32dll SHARED IMPORTED)
# set_target_properties(glew32dll PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libraries/glew/bin/glew32.dll)
# set_target_properties(glew32dll PROPERTIES IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/libraries/glew/lib/glew32.lib) # Adjust the path if necessary

# Link against GLEW DLL
target_link_libraries(NewAbyss PRIVATE
        winmm
        ${JNI_LIBRARIES}
        opengl32
        # glew32dll
)