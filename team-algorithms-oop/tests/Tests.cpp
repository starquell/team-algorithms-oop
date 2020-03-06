#include <iostream>
#include "catch.hpp"

#include "../src/SplayTree/SplayTree.hpp"

TEST_CASE("Splay tree", "[splay]") {

    std::array elems = {1, 4, 103, 2, 24};

    SECTION("Constructor from iterators test") {
        tree::SplayTree<int> tree (elems.begin(), elems.end());

        REQUIRE(*tree.begin() == 1);
        REQUIRE(*(tree.begin() + 1) == 2);
        REQUIRE(*(tree.begin() + 2) == 4);
        REQUIRE(*(tree.begin() + 3) == 24);
        REQUIRE(*(tree.begin() + 4) == 103);
    }

    SECTION("Constructor's from iterators test") {
        tree::SplayTree<int> tree = {elems[0], elems[1], elems[2], elems[3], elems[4]};

        REQUIRE(*tree.begin() == 1);
        REQUIRE(*(tree.begin() + 1) == 2);
        REQUIRE(*(tree.begin() + 2) == 4);
        REQUIRE(*(tree.begin() + 3) == 24);
        REQUIRE(*(tree.begin() + 4) == 103);
    }
    tree::SplayTree<int> tree (elems.begin(), elems.end());

    SECTION("Insert") {
        tree.insert(100);
        REQUIRE(tree.search(100));
    }

    SECTION("Erase") {
        REQUIRE(tree.search(elems[0]));
        tree.erase(elems[0]);

        REQUIRE_FALSE(tree.search(elems[0]));
    }
}
