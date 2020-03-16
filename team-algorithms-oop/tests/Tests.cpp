#include <iostream>
#include "catch.hpp"

#include "../src/SplayTree/SplayTree.hpp"

TEST_CASE("Splay tree", "[splay]") {

    std::array elems = {1, 4, 103, 2, 24};

    SECTION("Constructor from iterators test") {
        tree::SplayTree<int> tree(elems.begin(), elems.end());

        auto it = tree.begin();

        REQUIRE(*it == 1);
        REQUIRE(*(++it) == 2);
        REQUIRE(*(++it) == 4);
        REQUIRE(*(++it) == 24);
        REQUIRE(*(++it) == 103);

        tree::SplayTree<int> other(tree);
    }

    SECTION("Constructor's from iterators test") {
        tree::SplayTree<int> tree = {elems[0], elems[1], elems[2], elems[3], elems[4]};

        auto it = tree.begin();

        REQUIRE(*it == 1);
        REQUIRE(*(++it) == 2);
        REQUIRE(*(++it) == 4);
        REQUIRE(*(++it) == 24);
        REQUIRE(*(++it) == 103);
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

    SECTION("Size") {
        REQUIRE(tree.size() == std::distance(elems.begin(), elems.end()));
    }
}
