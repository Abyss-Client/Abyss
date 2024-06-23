// class by sleepyfish for abyss recode
// February 2024 Friday 3:25 AM

#pragma once

#include <vector>

// To do like: ArrayList<object> objectArray;
template <typename T>
class ArrayList {

private:
    // the vector variable
    std::vector<T> internalVector;

public:

    // gets the vector
    std::vector<T> getVector() const noexcept {
        return internalVector;
    }

    // get the size of the vector
    int getSize() const noexcept {
        return internalVector.size();
    }

    // add a object to the vector
    void add(const T& object) noexcept {
        internalVector.push_back(object);
    }

    // remove a object from the vector
    void remove(const T& object) noexcept {
        auto it = std::find(internalVector.begin(), internalVector.end(), object);

        if (it != internalVector.end())
            internalVector.erase(it);
    }

    // check if a elemetnt is inside of the vector
    bool contains(const T& object) const noexcept {
        return std::find(internalVector.begin(), internalVector.end(), object) != internalVector.end();
    }

    // clears the vector
    void clear() noexcept {
        internalVector.clear();
    }

    // checks if the vector is empty
    bool isEmpty() const noexcept {
        return internalVector.empty();
    }

};