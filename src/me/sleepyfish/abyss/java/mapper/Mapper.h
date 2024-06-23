// class by sleepyfish for abyss recode
// February 2024 Friday 6:22 AM

#ifndef NEWABYSS_MAPPER_H
#define NEWABYSS_MAPPER_H

#include "../../utils/type/String.h"
#include "../../utils/type/Class.h"
#include "../../../../../../libraries/jni/jni.h"
#include <map>

class Mapper : public Class {
public:

    class Descriptors {
    public:

        // Java
        static inline const char* class_uuid = "()Ljava/util/UUID;";
        static inline const char* class_string = "()Ljava/lang/String;";

        // Minecraft
        static inline const char* class_item = "()Lnet/minecraft/item/Item;";
        static inline const char* class_itemStack = "()Lnet/minecraft/item/ItemStack;";
        static inline const char* class_itemStack_array = "[Lnet/minecraft/item/ItemStack;";

        // Basic
        static inline const char* void_ = "()V";

        static inline const char* void_with_boolean = "(Z)V";
        static inline const char* void_with_long = "(J)V";
        static inline const char* void_with_double = "(D)V";
        static inline const char* void_with_float = "(F)V";
        static inline const char* void_with_int = "(I)V";

        static inline const char* void_boolean = "()Z";
        static inline const char* void_double = "()D";
        static inline const char* void_float = "()F";
        static inline const char* void_int = "()I";

        static inline const char* field_string = "Ljava/lang/String;";
        static inline const char* field_boolean = "Z";
        static inline const char* field_long = "J";
        static inline const char* field_double = "D";
        static inline const char* field_float = "F";
        static inline const char* field_int = "I";
    };

    enum class Mappings {
        None, Vanilla, Forge, Lunar
    };

    static inline Mappings currentMapping = Mappings::None;

    static std::map<std::string, jclass>    mapper_classes;
    static std::map<std::string, jfieldID>  mapper_fields;
    static std::map<std::string, jmethodID> mapper_voids;

    void inject() override;
    void unInject() override;

    bool useVanillaMappings();
    bool useForgeMappings();
    bool useLunarMappings();

    void applyMappings();

    static void injectForgeClass();
    static jclass findForgeClass(String clazz);

private:
    inline static jclass LaunchWrapperClassLoaderClass;
    inline static jmethodID FindClassMethodID;
    inline static jclass LaunchClass;
    inline static jfieldID ClassLoaderFieldID;
    inline static jobject ClassLoaderObject;

    void assignClasses();
    void applyVanillaMappings();
    void applyForgeMappings();
    void applyLunarMappings();
    void checkMappings();

    void assignJavaClasses();
};

#endif //NEWABYSS_MAPPER_H