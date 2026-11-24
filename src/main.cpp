#include <iostream>
#include <vector>

#include "project/set.h"

int main() {
    Set a;
    Set b;

    for (int value : {1, 2, 3, 4, 5}) {
        a.insert(value);
    }
    for (int value : {3, 4, 5, 6, 7}) {
        b.insert(value);
    }

    std::cout << "A: ";
    for (int value : a.toVector()) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    std::cout << "Union: ";
    for (int value : a.unionWith(b).toVector()) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    std::cout << "Intersection size: " << a.intersectionWith(b).size() << "\n";
    return 0;
}
