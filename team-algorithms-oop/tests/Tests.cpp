#include <catch.hpp>

#include <SplayTree.hpp>
#include <RedBlackTree.hpp>
#include <UndoableTree.hpp>
#include <AnyTree.hpp>
#include <TreeDB.hpp>

TEST_CASE("Splay tree", "[splay]") {

    using namespace lab::tree;

    constexpr std::array elems = {1, 4, 103, 2, 24};

    SECTION("Constructor from iterators test") {
        const SplayTree<int> tree (elems.begin(), elems.end());

        auto it = tree.begin();

        REQUIRE(*it == 1);
        REQUIRE(*(++it) == 2);
        REQUIRE(*(++it) == 4);
        REQUIRE(*(++it) == 24);
        REQUIRE(*(++it) == 103);
    }

    SECTION("Constructor's from iterators test") {
        const SplayTree<int> tree = {elems[0], elems[1], elems[2], elems[3], elems[4]};

        auto it = tree.begin();

        REQUIRE(*it == 1);
        REQUIRE(*(++it) == 2);
        REQUIRE(*(++it) == 4);
        REQUIRE(*(++it) == 24);
        REQUIRE(*(++it) == 103);
    }

    SplayTree<int> tree (elems.begin(), elems.end());

    SECTION ("Deep copy") {
        const SplayTree<int> copied(tree);

        REQUIRE(*copied.begin() == 1);
        REQUIRE(*(copied.begin() + 1) == 2);
        REQUIRE(*(copied.begin() + 2) == 4);
        REQUIRE(*(copied.begin() + 3) == 24);
        REQUIRE(*(copied.begin() + 4) == 103);
    }

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

    SECTION("Other comparator") {
        const SplayTree<int, std::greater<>> tree = {elems[0], elems[1], elems[2], elems[3], elems[4]};

        auto it = tree.begin();

        REQUIRE(*it == 103);
        REQUIRE(*(++it) == 24);
        REQUIRE(*(++it) == 4);
        REQUIRE(*(++it) == 2);
        REQUIRE(*(++it) == 1);
    }
}

TEST_CASE("Red Black Tree", "[RedBlackTree]") {

    using namespace lab::tree;

    constexpr std::array elems = {1, 4, 103, 2, 24};

    SECTION("Constructor's from iterators") {
        const RedBlackTree<int> rbTree(elems.begin(), elems.end());

        REQUIRE(*rbTree.begin() == 1);
        REQUIRE(*(rbTree.begin() + 1) == 2);
        REQUIRE(*(rbTree.begin() + 2) == 4);
        REQUIRE(*(rbTree.begin() + 3) == 24);
        REQUIRE(*(rbTree.begin() + 4) == 103);
    }

    SECTION("Constructor's from initialize list") {
        const RedBlackTree<int> tree {elems[0], elems[1], elems[2], elems[3], elems[4]};

        auto it = tree.begin();

        REQUIRE(*it == 1);
        REQUIRE(*(++it) == 2);
        REQUIRE(*(++it) == 4);
        REQUIRE(*(++it) == 24);
        REQUIRE(*(++it) == 103);
    }

    RedBlackTree<int> rbTree (elems.begin(), elems.end());

    SECTION ("Deep copy") {
        const RedBlackTree<int> tree(rbTree);

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

    SECTION("Other comparator") {
        const RedBlackTree<int, std::greater<>> tree (elems.begin(), elems.end());

        auto it = tree.begin();

        REQUIRE(*it == 103);
        REQUIRE(*(++it) == 24);
        REQUIRE(*(++it) == 4);
        REQUIRE(*(++it) == 2);
        REQUIRE(*(++it) == 1);
    }
}

TEST_CASE("Undoable tree", "[undoable]") {

    using namespace lab::tree;

    constexpr std::array elems = {1, 4, 103, 2, 24};

    SECTION("Constructor's from iterators") {
        const UndoableTree<SplayTree<int>> tree (elems.begin(), elems.end());

        REQUIRE(*tree.begin() == 1);
        REQUIRE(*(tree.begin() + 1) == 2);
        REQUIRE(*(tree.begin() + 2) == 4);
        REQUIRE(*(tree.begin() + 3) == 24);
        REQUIRE(*(tree.begin() + 4) == 103);
    }

    SECTION("Constructor's from initialize list") {
        const UndoableTree<SplayTree<int>> tree {elems[0], elems[1], elems[2], elems[3], elems[4]};

        auto it = tree.begin();

        REQUIRE(*it == 1);
        REQUIRE(*(++it) == 2);
        REQUIRE(*(++it) == 4);
        REQUIRE(*(++it) == 24);
        REQUIRE(*(++it) == 103);
    }

    UndoableTree<SplayTree<int>> tree (elems.begin(), elems.end());

    SECTION ("Deep copy") {
        const UndoableTree<SplayTree<int>> copy (tree);

        REQUIRE(*tree.begin() == 1);
        REQUIRE(*(tree.begin() + 1) == 2);
        REQUIRE(*(tree.begin() + 2) == 4);
        REQUIRE(*(tree.begin() + 3) == 24);
        REQUIRE(*(tree.begin() + 4) == 103);
    }

    SECTION("Insert") {
        tree.insert(100);
        REQUIRE(tree.search(100));
    }

    SECTION("Erase") {
        REQUIRE(tree.search(elems[0]));
        tree.erase(elems[0]);

        REQUIRE(!tree.search(elems[0]));
    }

    SECTION("Undo and redo") {
        tree.insert(999);
        tree.insert(1000);
        REQUIRE((tree.search(1000) && tree.search(999)));

        tree.undo();
        REQUIRE((!tree.search(1000) && tree.search(999)));

        tree.undo();
        REQUIRE((!tree.search(1000) && !tree.search(999)));

        tree.redo();
        REQUIRE((!tree.search(1000) && tree.search(999)));

        tree.redo();
        REQUIRE((tree.search(1000) && tree.search(999)));
    }
}

TEST_CASE("Tree container") {

    using namespace lab;
    using namespace lab::tree;

    UndoableTree<RedBlackTree<int>> rb {4, 2, 12};
    UndoableTree<SplayTree<int, std::greater<>>> st {2, 22, 1234, 5};

    AnyTree<SupportedValueType<int>,
            SupportedComparators<std::less<>, std::greater<>>> any(rb);

    REQUIRE(any.size() == rb.size());
    REQUIRE(std::equal(rb.begin(), rb.end(), any.begin()));

    constexpr int someValue = 233;
    rb.insert(someValue);
    any.insert(someValue);

    REQUIRE(*any.search(someValue) == *rb.search(someValue));

    any.setTree(st);

    REQUIRE(any.size() == st.size());
    REQUIRE(*any.begin() == *st.begin());

    st.insert(someValue);
    any.insert(someValue);

    REQUIRE(*any.search(someValue) == *st.search(someValue));
}

TEST_CASE("Saving trees (no eco activism)") {

    using namespace lab;
    using namespace lab::tree;

    constexpr std::string_view record_name = "test";
    auto& db = TreeDatabase::instance();

    const UndoableTree<RedBlackTree<int>> rb {4, 2, 12};

    SECTION("Saving") {
        db.save(rb, record_name);

        const auto names = db.loadNames();
        REQUIRE(std::find(names.begin(), names.end(), std::string {record_name}) != names.end());
    }

    SECTION("Uploading") {
        auto loaded = db.load<SplayTree<int>>(record_name);

        REQUIRE(std::equal(rb.begin(), rb.end(), loaded->begin()));
    }
                
    SECTION("Removing") {
        db.remove(record_name);

        REQUIRE(!db.load<SplayTree<int>>(record_name));
    }
}