#include <iostream>
#include "catch.hpp"

#include "../src/SplayTree/SplayTree.hpp"
#include "../src/RedBlackTree/RedBlackTree.hpp"
#include "SearchTree.hpp"

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

TEST_CASE("Red Black Tree", "[RedBlackTree]") {

    std::array elems = {1, 4, 103, 2, 24};

    SECTION("Constructor's from iterators") {
        tree::RedBlackTree<int> rbTree(elems.begin(), elems.end());

        REQUIRE(*rbTree.begin() == 1);
        REQUIRE(*(rbTree.begin() + 1) == 2);
        REQUIRE(*(rbTree.begin() + 2) == 4);
        REQUIRE(*(rbTree.begin() + 3) == 24);
        REQUIRE(*(rbTree.begin() + 4) == 103);
    }

    SECTION("Constructor's from initialize list") {
        tree::RedBlackTree<int> tree {elems[0], elems[1], elems[2], elems[3], elems[4]};

        auto it = tree.begin();

        REQUIRE(*it == 1);
        REQUIRE(*(++it) == 2);
        REQUIRE(*(++it) == 4);
        REQUIRE(*(++it) == 24);
        REQUIRE(*(++it) == 103);
    }

    tree::RedBlackTree<int> rbTree (elems.begin(), elems.end());

    SECTION ("Deep copy") {
        tree::RedBlackTree<int> tree(rbTree);

        REQUIRE(*tree.begin() == 1);
        REQUIRE(*(tree.begin() + 1) == 2);
        REQUIRE(*(tree.begin() + 2) == 4);
        REQUIRE(*(tree.begin() + 3) == 24);
        REQUIRE(*(tree.begin() + 4) == 103);
    }

    SECTION("Insert") {
        rbTree.insert(100);
        REQUIRE(rbTree.search(100));
    }

    SECTION("Erase") {
        REQUIRE(rbTree.search(elems[0]));
        rbTree.erase(elems[0]);

        REQUIRE(!rbTree.search(elems[0]));
    }
}

//TEST_CASE("Search Tree", "[SearchTree]") {
//
//    std::array elems = {1, 4, 103, 2, 24};
//
//    SECTION("Constructor's from iterators") {
//        tree::SearchTree<int> tree(elems.begin(), elems.end(),
//                tree::SearchTree<int>::Priority::QuickAccessToRecentlyUsed);
//
//        REQUIRE(*tree.begin() == 1);
//        REQUIRE(*(tree.begin() + 1) == 2);
//        REQUIRE(*(tree.begin() + 2) == 4);
//        REQUIRE(*(tree.begin() + 3) == 24);
//        REQUIRE(*(tree.begin() + 4) == 103);
//    }
//
//    SECTION("Constructor's from initialize list") {
//        tree::SearchTree<int> tree ({elems[0], elems[1], elems[2], elems[3], elems[4]},
//                                    tree::SearchTree<int>::Priority::AllOperationsAreAverageQuick);
//
//        auto it = tree.begin();
//
//        REQUIRE(*it == 1);
//        REQUIRE(*(++it) == 2);
//        REQUIRE(*(++it) == 4);
//        REQUIRE(*(++it) == 24);
//        REQUIRE(*(++it) == 103);
//    }
//
//    tree::SearchTree<int> tree (elems.begin(), elems.end());
//
//    SECTION ("Deep copy") {
//        tree::SearchTree<int> Copytree(tree);
//
//        REQUIRE(*tree.begin() == 1);
//        REQUIRE(*(tree.begin() + 1) == 2);
//        REQUIRE(*(tree.begin() + 2) == 4);
//        REQUIRE(*(tree.begin() + 3) == 24);
//        REQUIRE(*(tree.begin() + 4) == 103);
//    }
//
//    SECTION("Insert") {
//        tree.insert(100);
//        REQUIRE(tree.search(100));
//    }
//
//    SECTION("Erase") {
//        REQUIRE(tree.search(elems[0]));
//        tree.erase(elems[0]);
//
//        REQUIRE(!tree.search(elems[0]));
//    }
//}

