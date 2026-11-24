#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

class Set {
public:
    Set();

    bool empty() const noexcept;
    std::size_t size() const noexcept;
    bool contains(int value) const;
    bool insert(int value);
    bool erase(int value);
    void clear();
    std::vector<int> toVector() const;
    bool isSubsetOf(const Set& other) const;
    bool equals(const Set& other) const;
    Set unionWith(const Set& other) const;
    Set intersectionWith(const Set& other) const;
    Set difference(const Set& other) const;

private:
    std::vector<int> elements_;
    bool containsInternal(int value) const;
};
