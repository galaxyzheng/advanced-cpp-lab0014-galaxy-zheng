#include "project/set.h"

#include <algorithm>
#include <stdexcept>

Set::Set() = default;

bool Set::empty() const noexcept {
    return elements_.empty();
}

std::size_t Set::size() const noexcept {
    return elements_.size();
}

bool Set::contains(int value) const {
    (void)value;
    throw std::logic_error("Student implementation required: contains");
}

bool Set::insert(int value) {
    (void)value;
    throw std::logic_error("Student implementation required: insert");
}

bool Set::erase(int value) {
    (void)value;
    throw std::logic_error("Student implementation required: erase");
}

void Set::clear() {
    throw std::logic_error("Student implementation required: clear");
}

std::vector<int> Set::toVector() const {
    throw std::logic_error("Student implementation required: toVector");
}

bool Set::isSubsetOf(const Set& other) const {
    (void)other;
    throw std::logic_error("Student implementation required: isSubsetOf");
}

bool Set::equals(const Set& other) const {
    (void)other;
    throw std::logic_error("Student implementation required: equals");
}

Set Set::unionWith(const Set& other) const {
    (void)other;
    throw std::logic_error("Student implementation required: unionWith");
}

Set Set::intersectionWith(const Set& other) const {
    (void)other;
    throw std::logic_error("Student implementation required: intersectionWith");
}

Set Set::difference(const Set& other) const {
    (void)other;
    throw std::logic_error("Student implementation required: difference");
}

bool Set::containsInternal(int value) const {
    return std::find(elements_.begin(), elements_.end(), value) != elements_.end();
}
