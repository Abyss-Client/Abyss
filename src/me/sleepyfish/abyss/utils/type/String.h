// class by sleepyfish for abyss recode
// February 2024 Friday 3:25 AM

#ifndef NEWABYSS_STRING_H
#define NEWABYSS_STRING_H

#include <iostream>
#include <string>

class String {

private:
    char* data;
    int length;

public:

    // default constructor
    String() :
        length(0),
        data(nullptr)
    {}

    String(std::string str) {
        length = str.length();
        data = new char[length + 1];
        strcpy(data, str.data());
    }

    // char array constructor
    String(const char* str) {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

    // copy constructor
    String(const String& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    // assignment operator
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }

        return *this;
    }

    // add operator
    String operator+(const String& other) const {
        String result;
        result.length = length + other.length;
        result.data = new char[result.length + 1];
        strcpy(result.data, data);
        strcat(result.data, other.data);
        return result;
    }

    // -----------------------------------

    // destructor
    ~String() {
        length = 0;
        delete[] data;
    }

    // get char size
    int getLength() const {
        return length;
    }

    // get char data
    char* toChar() const {
        return data;
    }

    // get data changeable
    char& getData() {
        return *data;
    }

    // get as string
    const std::string toString() const {
        return std::string(data);
    }

    // get the string to lowercase
    String toLowercase() const {
        String result(*this);

        for (int i = 0; i < length; ++i)
            result.data[i] = std::tolower(result.data[i]);

        return result;
    }

    // checks if its the same object
    bool equals(const String text) const {
        return strcmp(data, text.data) == 0;
    }

    // stream insertion
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        os << str.data;
        return os;
    }

    // checks if str is contained in this*
    bool contains(const std::string& str) {
        return str.find(this->toString()) != std::string::npos;
    }

    std::string substring(int startIndex, int length) {
        return this->toString().substr(startIndex, length);
    }

    // checks if this* is starting with prefix
    bool startsWith(const char *prefix) const {
        const char* str = this->data;
        size_t strLen = strlen(str);
        size_t prefixLen = strlen(prefix);

        if (strLen < prefixLen)
            return false;

        return strncmp(str, prefix, prefixLen) == 0;
    }

    // checks if this* is ending with prefix
    bool endsWith(const char *suffix) const {
        const char* str = this->data;
        size_t strLen = strlen(str);
        size_t suffixLen = strlen(suffix);

        if (strLen < suffixLen)
            return false;

        return strncmp(str + strLen - suffixLen, suffix, suffixLen) == 0;
    }

    int indexOf(const std::string& substr, int startIndex = 0) {
        int n = this->length;
        int m = substr.length();

        for (int i = startIndex; i <= n - m; ++i) {
            int j;
            for (j = 0; j < m; ++j) {
                if (this->toString().at(i + j) != substr.at(j))
                    break;
            }

            if (j == m)
                return i;
        }

        return -1;
    }

    bool isNull() {
        return this->data == nullptr || this->length == -1;
    }

};

#endif //NEWABYSS_STRING_H