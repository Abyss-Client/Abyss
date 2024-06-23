// class by sleepyfish for abyss recode
// February 2024 Friday 9:12 AM

#ifndef NEWABYSS_SDKCLASS_H
#define NEWABYSS_SDKCLASS_H

#include "Sdk.h"
#include "../../utils/EnvUtils.h"

struct SdkClass {

public:
    jclass instanceClass{};
    jobject instanceObject{};

    virtual jclass getInstanceClass() = 0;
    virtual jobject getInstanceObject() = 0;

    bool isNull() const {
        return (this->instanceObject == nullptr || this->instanceClass == nullptr);
    }
    
// Mapper checks
protected:

    jfieldID getField(jclass clazz, const char* name, const char* sig) const {
        return EnvUtils::Env->GetFieldID(clazz, name, sig);
    }

    jfieldID getStaticField(jclass clazz, const char* name, const char* sig) const {
        return EnvUtils::Env->GetStaticFieldID(clazz, name, sig);
    }

    jmethodID getVoid(jclass clazz, const char* name, const char* sig) const {
        return EnvUtils::Env->GetMethodID(clazz, name, sig);
    }

    jmethodID getStaticVoid(jclass clazz, const char* name, const char* sig) const {
        return EnvUtils::Env->GetStaticMethodID(clazz, name, sig);
    }

    jobject getObjectField(jclass clazz, const char* name, const jobject instance = nullptr) const {
        if (instance == nullptr)
            return EnvUtils::Env->GetObjectField(this->instanceObject, getMappingField(clazz, name));
        else
            return EnvUtils::Env->GetObjectField(instance, getMappingField(clazz, name));
    }

    jobject getObjectFieldNormal(jobject instance, jfieldID field) const {
        return EnvUtils::Env->GetObjectField(instance, field);
    }

    jobject getStaticObjectFieldNormal(jclass clazz, jfieldID field) const {
        return EnvUtils::Env->GetStaticObjectField(clazz, field);
    }

    jobject getObjectMethod(const jobject instance, jmethodID method) const {
        return EnvUtils::Env->CallObjectMethod(instance, method);
    }

    jobject getObjectMethodArgs(const jobject instance, jmethodID method, ...) const {
        va_list args;
        va_start(args, method);
        jobject objMethod = EnvUtils::Env->CallObjectMethod(instance, method, args);
        va_end(args);
        return objMethod;
    }

    jobject getStaticMethodObject(jclass clazz, jmethodID method) const {
        return EnvUtils::Env->CallStaticObjectMethod(clazz, method);
    }

    jfieldID getMappingField(jclass clazz, const char* name, const char* sig = "") const {
        jfieldID fieldFound = getField(clazz, name, sig);

        for (const auto& pair : Mapper::mapper_fields) {
            std::string foundString = pair.first;

            if (name == foundString) {
                fieldFound = pair.second;
                break;
            }
        }

        return fieldFound;
    }

    jmethodID getMappingVoid(jclass clazz, const char* name, const char* sig) const {
        jmethodID methodFound = getVoid(clazz, name, sig);

        for (auto pair : Mapper::mapper_voids) {
            std::string foundString = pair.first;

            if (name == foundString) {
                methodFound = pair.second;
                break;
            }
        }

        return methodFound;
    }

    /**
     * @param value 1 - Integer
     * @param value 2 - Double
     * @param value 3 - Float
     */
    void callArgumentVoid(jclass clazz, const char* name, short sig, const auto value = nullptr) const {
        jmethodID method;

        switch (sig) {

            // Integer
            case 1: {
                method = getMappingVoid(clazz, name, "(I)V");
                EnvUtils::Env->CallIntMethod(clazz, method, (jint) value);
                break;
            }

            // Double
            case 2: {
                method = getMappingVoid(clazz, name, "(D)V");
                EnvUtils::Env->CallDoubleMethod(clazz, method, (jdouble) value);
                break;
            }

            // Float
            case 3: {
                method = getMappingVoid(clazz, name, "(F)V");
                EnvUtils::Env->CallFloatMethod(clazz, method, (jfloat) value);
                break;
            }

            default: break;
        }
    }

    void callVoid(jobject instance, jmethodID method) const {
        EnvUtils::Env->CallVoidMethod(instance, method);
    }

    void callVoidArg(jobject instance, jmethodID method, ...) const {
        va_list args;
        va_start(args, method);
        EnvUtils::Env->CallVoidMethod(instance, method, args);
        va_end(args);
    }

    jstring getString(std::string text) const {
        return EnvUtils::Env->NewStringUTF(text.c_str());
    }

    const char* getChars(jstring text) const {
        return EnvUtils::Env->GetStringUTFChars(text, 0);
    }

    void releaseString(jstring text, const char* chars) const {
        EnvUtils::Env->ReleaseStringUTFChars(text, chars);
    }

    void setIntField(jobject instance, jfieldID field, jint value) const {
        EnvUtils::Env->SetIntField(instance, field, value);
    }

    jint getIntField(jobject instance, jfieldID field) const {
        return EnvUtils::Env->GetIntField(instance, field);
    }

    jint getIntMethod(jobject instance, jmethodID method) const {
        return EnvUtils::Env->CallIntMethod(instance, method);
    }

    jdouble getDoubleField(jobject instance, jfieldID field) const {
        return EnvUtils::Env->GetDoubleField(instance, field);
    }

    jfloat getFloatField(jobject instance, jfieldID field) const {
        return EnvUtils::Env->GetFloatField(instance, field);
    }

    void setFloatField(jobject instance, jfieldID field, jfloat value) const {
        EnvUtils::Env->SetFloatField(instance, field, value);
    }

    jfloat getFloatMethod(jobject instance, jmethodID method) const {
        return EnvUtils::Env->CallFloatMethod(instance, method);
    }

    jobject getItemInArray(jobjectArray array, jsize index) const {
        return EnvUtils::Env->GetObjectArrayElement(array, index);
    }

    jboolean getBooleanField(jobject instance, jfieldID field) const {
        return EnvUtils::Env->GetBooleanField(instance, field);
    }

    void setBooleanField(jobject instance, jfieldID field, jboolean state) const {
        EnvUtils::Env->SetBooleanField(instance, field, state);
    }

    jboolean getBooleanMethod(jobject instance, jmethodID method) const {
        return EnvUtils::Env->CallBooleanMethod(instance, method);
    }

    void callLongMethod(jobject instance, jmethodID method, jlong value) const {
        EnvUtils::Env->CallLongMethod(instance, method, value);
    }

    jboolean getBooleanMethod(jobject instance, jmethodID method, jboolean state) const {
        return EnvUtils::Env->CallBooleanMethod(instance, method, state);
    }

    jboolean getBooleanMethodArgs(jobject instance, jmethodID method, ...) const {
        va_list args;
        va_start(args, method);
        jboolean boolMethod = EnvUtils::Env->CallBooleanMethod(instance, method, args);
        va_end(args);
        return boolMethod;
    }

    void deleteRef(jobject obj) {
        EnvUtils::Env->DeleteLocalRef(obj);
    }

    jobject newObject(jclass clazz, jmethodID method, ...) const {
        va_list args;
        va_start(args, method);
        jobject boolMethod = EnvUtils::Env->NewObject(clazz, method, args);
        va_end(args);
        return boolMethod;
    }

};

#endif //NEWABYSS_SDKCLASS_H