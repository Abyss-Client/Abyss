// class by sleepyfish for abyss recode
// February 2024 Friday 3:25 AM

#include "Java.h"

#include "../client/Abyss.h"

JavaVM* vm;
jobject classLoader;
jmethodID mid_findClass;

jclass c_system;
jmethodID c_gc;

void Java::inject() {
    if (Java::isNull) {
        Abyss::logger.log("/ Java - Info: Inject");

        Java::injectJavaEnv();
        Java::setupClassLoader();
        Java::checkForMappings();

        Abyss::logger.log("\\ Java - Info: Inject Done");
        Abyss::logger.nextLine();

        Java::isNull = false;
    }
}

void Java::unInject() {
    if (!Java::isNull) {
        Abyss::logger.log("| Java - Info: UnInject");

        Java::callGarbageCollector();
        EnvUtils::Env->DeleteLocalRef(classLoader);
        EnvUtils::Env->DeleteLocalRef(c_system);
        vm->DetachCurrentThread();

        Abyss::logger.log("| Java - Info: Detached current thread");
        Abyss::logger.nextLine();

        Java::isNull = true;
    }
}

void Java::injectJavaEnv() {

    jsize count;
    if (JNI_GetCreatedJavaVMs(&vm, 1, &count) != JNI_OK || count == 0) {
        Abyss::logger.log("| Java - Err: Could not get Created Java VM");
        return;
    } else {
        Abyss::logger.log("| Java - Info: Got created Java VM");
    }

    jint res = vm->GetEnv((void**) &EnvUtils::Env, JNI_VERSION_1_8);

    if (res == JNI_EDETACHED) {
        res = vm->AttachCurrentThreadAsDaemon((void**) &EnvUtils::Env, nullptr);
        Abyss::logger.log("| Java - Info: Attach Current Thread");
    }

    if (res == JNI_ENOMEM) {
        Abyss::logger.log("| Java - Err: Not enough memory");
        return;
    }

    if (res == JNI_EVERSION) {
        Abyss::logger.log("| Java - Err: JNI Version error");
        return;
    }

    if (res == JNI_EEXIST) {
        Abyss::logger.log("| Java - Err: VM already created");
        return;
    }

    if (res == JNI_EINVAL) {
        Abyss::logger.log("| Java - Err: Invalid arguments");
        return;
    }

    if (EnvUtils::Env == nullptr) {
        Abyss::logger.log("| Java - Err: JNI Environment is null");
        vm->DestroyJavaVM();
        return;
    }
}

void Java::setupClassLoader() {
    c_system = EnvUtils::Env->FindClass("java/lang/System");
    c_gc = EnvUtils::Env->GetStaticMethodID(c_system, "gc", Mapper::Descriptors::void_);

    if (c_gc != nullptr) {
        Abyss::logger.log("| Java - Info: Got Garbage Collector");
    } else {
        Abyss::logger.log("| Java - Err: getting Garbage Collector");
    }

    jclass c_Map = EnvUtils::Env->FindClass("java/util/Map");
    jclass c_Set = EnvUtils::Env->FindClass("java/util/Set");
    jclass c_Thread = EnvUtils::Env->FindClass("java/lang/Thread");
    jclass c_ClassLoader = EnvUtils::Env->FindClass("java/lang/ClassLoader");

    /*
    if (Abyss::mapper.useLunarMappings()) {
        // CIIIOIIRIHIOHORCOICIIRHCO ?
        c_ClassLoader = EnvUtils::Env->FindClass("com/moonsworth/lunar/genesis/Genesis");
    }
    */

    jmethodID mid_getAllStackTraces = EnvUtils::Env->GetStaticMethodID(c_Thread, "getAllStackTraces", "()Ljava/util/Map;");
    jmethodID mid_keySet = EnvUtils::Env->GetMethodID(c_Map, "keySet", "()Ljava/util/Set;");
    jmethodID mid_toArray = EnvUtils::Env->GetMethodID(c_Set, "toArray", "()[Ljava/lang/Object;");
    jmethodID mid_getContextClassLoader = EnvUtils::Env->GetMethodID(c_Thread, "getContextClassLoader", "()Ljava/lang/ClassLoader;");

    jobject obj_stackTracesMap = EnvUtils::Env->CallStaticObjectMethod(c_Thread, mid_getAllStackTraces);
    jobject obj_threadsSet = EnvUtils::Env->CallObjectMethod(obj_stackTracesMap, mid_keySet);

    auto threads = (jobjectArray) EnvUtils::Env->CallObjectMethod(obj_threadsSet, mid_toArray);
    jint szThreads = EnvUtils::Env->GetArrayLength(threads);

    mid_findClass = EnvUtils::Env->GetMethodID(c_ClassLoader, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
    jstring className = EnvUtils::Env->NewStringUTF("net.minecraft.client.Minecraft");

    for (int i = 0; i < szThreads; i++) {
        jobject thread = EnvUtils::Env->GetObjectArrayElement(threads, i);
        jobject classLoaderObj = EnvUtils::Env->CallObjectMethod(thread, mid_getContextClassLoader);

        if (classLoaderObj != nullptr) {
            jobject minecraftClass = EnvUtils::Env->CallObjectMethod(classLoaderObj, mid_findClass, className);

            if (minecraftClass != nullptr) {
                classLoader = classLoaderObj;
                Abyss::logger.log("| Java - Info: Got Minecraft classloader");
                EnvUtils::Env->DeleteLocalRef(minecraftClass);
                break;
            }
        }

        EnvUtils::Env->DeleteLocalRef(classLoaderObj);
        EnvUtils::Env->DeleteLocalRef(thread);
    }

    EnvUtils::Env->DeleteLocalRef(threads);
    EnvUtils::Env->DeleteLocalRef(obj_stackTracesMap);
    EnvUtils::Env->DeleteLocalRef(obj_threadsSet);
    EnvUtils::Env->DeleteLocalRef(c_Thread);
    EnvUtils::Env->DeleteLocalRef(c_Map);
    EnvUtils::Env->DeleteLocalRef(c_Set);
    EnvUtils::Env->DeleteLocalRef(c_ClassLoader);

    Abyss::logger.log("| Java - Info: Classloader ready");
}

/**
 * @param name Class path name / package name
 * @param out Assigned class
 * @Info LUNAR FUNCTION CRASHES
 * @return if class got assigned
 */
bool Java::assignClass(String name, jclass& out) {
    if (name.startsWith("java/")) {
        out = EnvUtils::Env->FindClass(name.toChar());
        return true;
    } else {
        if (Abyss::mapper.useVanillaMappings()) {
            out = EnvUtils::Env->FindClass(name.toChar());
            return true;
        }

        if (Abyss::mapper.useForgeMappings()) {
            out = Mapper::findForgeClass(name);
            return true;
        }

        if (Abyss::mapper.useLunarMappings()) {
            jstring className = EnvUtils::Env->NewStringUTF(name.toChar());
            jobject findClass = EnvUtils::Env->CallObjectMethod(classLoader, mid_findClass, className);

            if (findClass)
                out = (jclass) findClass;

            return out != nullptr;
        }

        // this is crashing
        if (Abyss::mapper.useLunarMappings()) {
            jstring className = EnvUtils::Env->NewStringUTF( (String("net.minecraft.")+ name).toChar() );
            if (className == nullptr)
                return false;

            auto findClass = (jclass) EnvUtils::Env->CallObjectMethod(classLoader, mid_findClass, className);
            out = findClass;

            EnvUtils::Env->DeleteLocalRef(findClass);
            EnvUtils::Env->DeleteLocalRef(className);

            return out != nullptr;
        }
    }

    return false;
}

void Java::checkForMappings() {

    if (vm->GetEnv((void**) &EnvUtils::JVMti, JVMTI_VERSION_1_2) != JNI_OK) {
        Abyss::logger.log("| Java - Err: Could not get Created Java JVMTI");
        return;
    }

    jclass javaClassClass = EnvUtils::Env->FindClass("java/lang/Class");
    jmethodID javaGetClassName = EnvUtils::Env->GetMethodID(javaClassClass, "getName", "()Ljava/lang/String;");

    jclass* classPtr;
    jint amount;
    EnvUtils::JVMti->GetLoadedClasses(&amount, &classPtr);
    int finalAmount = 0;

    for (int i = 0; amount > i; i++) {
        const auto name = (jstring) EnvUtils::Env->CallObjectMethod(classPtr[i], javaGetClassName);
        const char* className = EnvUtils::Env->GetStringUTFChars(name, 0);
        const String stringClassName = String(className);
        EnvUtils::Env->ReleaseStringUTFChars(name, className);

        // Mapping checks
        const bool lunar = stringClassName.startsWith("com.moonsworth.lunar.genesis.");
        const bool forge = stringClassName.equals("net.minecraftforge.client.MinecraftForgeClient");
        const bool minec = stringClassName.equals("ave");

        // Weave clients
        const bool smok = stringClassName.equals("me.sleepyfish.smok.Smok");
        const bool legitish = stringClassName.equals("legitish.main.Legitish");
        const bool ravenweave = stringClassName.equals("ravenweave.client.main.Raven");
        const bool stormy = stringClassName.equals("dev.stormy.client.main.Stormy");

        // Forge clients
        const bool snow = stringClassName.equals("org.nextbyte.sleepyfish.snow.client.Snow");
        const bool cloud = stringClassName.equals("dev.cloudmc.Cloud");
        const bool patcher = stringClassName.equals("club.sk1er.patcher.Patcher");
        const bool rat = stringClassName.equals("me.sleepyfish.rat.Rat");
        const bool raven = stringClassName.equals("keystrokesmod.client.main.Raven");

        // Other clients
        const bool optifine = stringClassName.equals("net.optifine.VersionCheckThread");
        const bool rand = stringClassName.equals("fff");

        if (Mapper::currentMapping == Mapper::Mappings::None) {
            if (lunar) {
                Mapper::currentMapping = Mapper::Mappings::Lunar;
                Abyss::logger.log("| Java - Info: Found class: Genesis");
            } else
            if (forge) {
                Mapper::currentMapping = Mapper::Mappings::Forge;
                Abyss::logger.log("| Java - Info: Found class: MinecraftForgeClient");
            } else
            if (minec) {
                Mapper::currentMapping = Mapper::Mappings::Vanilla;
                Abyss::logger.log("| Java - Info: Found class: ave");
            }
        }

        {
            // Crazy ahh clients
            if (snow) loadedClients.emplace_back("snow");
            if (smok) loadedClients.emplace_back("smok");
            if (rat) loadedClients.emplace_back("rat");

            if (optifine) loadedClients.emplace_back("optifine");
            if (cloud) loadedClients.emplace_back("cloud");
            if (stormy) loadedClients.emplace_back("stormy");
            if (legitish) loadedClients.emplace_back("legitish");
            if (patcher) loadedClients.emplace_back("patcher");
            if (raven) loadedClients.emplace_back("ravenforge");
            if (ravenweave) loadedClients.emplace_back("ravenweave");
        }

        finalAmount++;
    }

    Abyss::logger.log("| Java - Info: Found", finalAmount, "classes");
    for (const String name : loadedClients) {
        Abyss::logger.log((String) "| Java - Info: Found " + name + " client");
    }

    classPtr = nullptr;
    javaGetClassName = nullptr;
    EnvUtils::Env->DeleteLocalRef(javaClassClass);
    amount = 0;

    Abyss::logger.log("| Java - Info: Version", EnvUtils::Env->GetVersion());
}

void Java::callGarbageCollector() {
    if (c_gc != nullptr) {
        EnvUtils::Env->CallStaticVoidMethod(c_system, c_gc);
        Abyss::logger.log("| Java - Info: Called Garbage Collector");
    } else {
        Abyss::logger.log("| Java - Err: Garbage Collector is null");
    }
}