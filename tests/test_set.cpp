#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "project/set.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

TEST_CASE("Set starts empty") {
    Set set;
    REQUIRE(set.empty());
    REQUIRE(set.size() == 0u);
    REQUIRE_FALSE(set.contains(42));
    REQUIRE(set.toVector().empty());
}

TEST_CASE("Set inserts unique values and rejects duplicates") {
    Set set;
    REQUIRE(set.insert(10));
    REQUIRE(set.insert(20));
    REQUIRE(set.insert(30));
    REQUIRE_FALSE(set.insert(10));
    REQUIRE(set.size() == 3u);
    REQUIRE(set.contains(10));
    REQUIRE(set.contains(20));
    REQUIRE_FALSE(set.contains(99));
}

TEST_CASE("Set erase removes values and updates size") {
    Set set;
    for (int v : {2, 4, 6, 8, 10}) {
        set.insert(v);
    }

    REQUIRE(set.erase(6));
    REQUIRE_FALSE(set.contains(6));
    REQUIRE(set.size() == 4u);
    REQUIRE_FALSE(set.erase(999));
}

TEST_CASE("Set clear empties the set") {
    Set set;
    for (int v : {1, 2, 3, 4, 5}) {
        set.insert(v);
    }

    set.clear();
    REQUIRE(set.empty());
    REQUIRE(set.size() == 0u);
    REQUIRE(set.toVector().empty());
}

TEST_CASE("Set toVector returns sorted unique values") {
    Set set;
    for (int v : {9, 1, 7, 1, 5, 3, 9, 7}) {
        set.insert(v);
    }

    auto values = set.toVector();
    REQUIRE(values == std::vector<int>({1, 3, 5, 7, 9}));
    REQUIRE(std::is_sorted(values.begin(), values.end()));
}

TEST_CASE("Set equality and subset checks work correctly") {
    Set a;
    Set b;
    Set c;

    for (int v : {1, 2, 3, 4}) {
        a.insert(v);
    }
    for (int v : {1, 2, 3}) {
        b.insert(v);
    }
    for (int v : {1, 2, 3, 4}) {
        c.insert(v);
    }

    REQUIRE(a.equals(c));
    REQUIRE(b.isSubsetOf(a));
    REQUIRE_FALSE(a.isSubsetOf(b));
    REQUIRE_FALSE(a.equals(b));
}

TEST_CASE("Set union includes all unique values") {
    Set a;
    Set b;
    for (int v : {1, 2, 3, 4}) {
        a.insert(v);
    }
    for (int v : {3, 4, 5, 6}) {
        b.insert(v);
    }

    Set result = a.unionWith(b);
    REQUIRE(result.size() == 6u);
    REQUIRE(result.contains(1));
    REQUIRE(result.contains(2));
    REQUIRE(result.contains(3));
    REQUIRE(result.contains(4));
    REQUIRE(result.contains(5));
    REQUIRE(result.contains(6));
}

TEST_CASE("Set intersection returns only shared values") {
    Set a;
    Set b;
    for (int v : {1, 2, 3, 4, 5}) {
        a.insert(v);
    }
    for (int v : {3, 4, 5, 6, 7}) {
        b.insert(v);
    }

    Set result = a.intersectionWith(b);
    REQUIRE(result.size() == 3u);
    REQUIRE(result.contains(3));
    REQUIRE(result.contains(4));
    REQUIRE(result.contains(5));
    REQUIRE_FALSE(result.contains(1));
}

TEST_CASE("Set difference removes values in the other set") {
    Set a;
    Set b;
    for (int v : {1, 2, 3, 4, 5}) {
        a.insert(v);
    }
    for (int v : {2, 4}) {
        b.insert(v);
    }

    Set result = a.difference(b);
    REQUIRE(result.size() == 3u);
    REQUIRE(result.contains(1));
    REQUIRE(result.contains(3));
    REQUIRE(result.contains(5));
    REQUIRE_FALSE(result.contains(2));
    REQUIRE_FALSE(result.contains(4));
}

TEST_CASE("Set handles negative values and repeated operations") {
    Set set;
    for (int v : {-5, -1, 0, 3, -5, 9, 3, -1}) {
        set.insert(v);
    }

    REQUIRE(set.size() == 5u);
    REQUIRE(set.contains(-5));
    REQUIRE(set.contains(0));
    REQUIRE(set.contains(9));
    REQUIRE(set.erase(-1));
    REQUIRE_FALSE(set.contains(-1));
    REQUIRE(set.size() == 4u);
}

TEST_CASE("Set union and difference preserve no duplicates") {
    Set a;
    Set b;
    for (int v : {1, 2, 2, 3, 4}) {
        a.insert(v);
    }
    for (int v : {3, 4, 4, 5, 6}) {
        b.insert(v);
    }

    Set unionResult = a.unionWith(b);
    Set diffResult = a.difference(b);

    REQUIRE(unionResult.size() == 6u);
    REQUIRE(diffResult.size() == 2u);
    REQUIRE(diffResult.contains(1));
    REQUIRE(diffResult.contains(2));
    REQUIRE_FALSE(diffResult.contains(3));
}

TEST_CASE("Set operations are stable across repeated calls") {
    Set set;
    for (int v : {10, 8, 6, 4, 2}) {
        set.insert(v);
    }

    REQUIRE(set.size() == 5u);
    auto first = set.toVector();
    auto second = set.toVector();
    REQUIRE(first == second);
    REQUIRE(std::is_sorted(first.begin(), first.end()));
}

TEST_CASE("Set handles empty set intersections and differences") {
    Set a;
    Set b;
    for (int v : {1, 2, 3}) {
        a.insert(v);
    }

    Set intersection = a.intersectionWith(b);
    Set difference = a.difference(b);

    REQUIRE(intersection.empty());
    REQUIRE(difference.size() == 3u);
    REQUIRE(difference.equals(a));
}

TEST_CASE("Set union with a duplicate-heavy set removes duplicates") {
    Set a;
    Set b;
    for (int v : {1, 1, 2, 2, 3, 4}) {
        a.insert(v);
    }
    for (int v : {3, 3, 4, 5, 5, 6}) {
        b.insert(v);
    }

    Set result = a.unionWith(b);
    REQUIRE(result.size() == 6u);
    REQUIRE(result.contains(1));
    REQUIRE(result.contains(2));
    REQUIRE(result.contains(3));
    REQUIRE(result.contains(4));
    REQUIRE(result.contains(5));
    REQUIRE(result.contains(6));
}

TEST_CASE("Set subset and equality behavior with empty set") {
    Set emptySet;
    Set nonEmpty;
    for (int v : {7, 8, 9}) {
        nonEmpty.insert(v);
    }

    REQUIRE(emptySet.isSubsetOf(nonEmpty));
    REQUIRE_FALSE(nonEmpty.isSubsetOf(emptySet));
    REQUIRE_FALSE(emptySet.equals(nonEmpty));
    REQUIRE(emptySet.equals(emptySet));
}

TEST_CASE("Set operations remain consistent after multiple clears") {
    Set set;
    for (int v : {1, 2, 3, 4}) {
        set.insert(v);
    }

    set.clear();
    REQUIRE(set.empty());
    set.insert(99);
    set.insert(100);
    REQUIRE(set.size() == 2u);
    REQUIRE(set.contains(99));
    REQUIRE(set.contains(100));
    REQUIRE_FALSE(set.contains(1));
}
