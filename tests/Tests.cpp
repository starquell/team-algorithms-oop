#include <catch.hpp>

#include <SplayTree.hpp>
#include <RedBlackTree.hpp>
#include <UndoableTree.hpp>
#include <AnyTree.hpp>
#include <TreeDB.hpp>

#include <tuple>

using namespace lab::forest;

TEMPLATE_TEST_CASE("Red-Black and Splay Tree", "[basic]",
                  (std::tuple <SplayTree<int>, SplayTree<int, std::greater<>>>),
                  (std::tuple <RedBlackTree<int>, RedBlackTree<int, std::greater<>>>))
{

    static constexpr std::array elems = {1, 4, 103, 2, 24};

    SECTION("Constructor from iterators test") {
         std::tuple_element_t<0, TestType> tree (elems.begin(), elems.end());

         auto it = tree.begin();

        REQUIRE(*it == 1);
        REQUIRE(*(++it) == 2);
        REQUIRE(*(++it) == 4);
        REQUIRE(*(++it) == 24);
        REQUIRE(*(++it) == 103);
    }

    SECTION("Constructor's from iterators test") {
        const std::tuple_element_t<0, TestType>  tree = {elems[0], elems[1], elems[2], elems[3], elems[4]};

        auto it = tree.begin();

        REQUIRE(*it == 1);
        REQUIRE(*(++it) == 2);
        REQUIRE(*(++it) == 4);
        REQUIRE(*(++it) == 24);
        REQUIRE(*(++it) == 103);
    }

    std::tuple_element_t<0, TestType> tree (elems.begin(), elems.end());

    SECTION ("Deep copy") {
        const std::tuple_element_t<0, TestType>  copied(tree);

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
        const std::tuple_element_t<1, TestType>  tree = {elems[0], elems[1], elems[2], elems[3], elems[4]};

        auto it = tree.begin();

        REQUIRE(*it == 103);
        REQUIRE(*(++it) == 24);
        REQUIRE(*(++it) == 4);
        REQUIRE(*(++it) == 2);
        REQUIRE(*(++it) == 1);
    }
}

TEMPLATE_TEST_CASE("Undoable forest", "[undoable]", (SplayTree<int>), (RedBlackTree<int>)) {

    using namespace lab::forest;

    constexpr std::array elems = {1, 4, 103, 2, 24};

    SECTION("Constructor's from iterators") {
         UndoableTree<TestType> tree (elems.begin(), elems.end());

        REQUIRE(*tree.begin() == 1);
        REQUIRE(*(tree.begin() + 1) == 2);
        REQUIRE(*(tree.begin() + 2) == 4);
        REQUIRE(*(tree.begin() + 3) == 24);
        REQUIRE(*(tree.begin() + 4) == 103);
    }

    SECTION("Constructor's from initialize list") {
        const UndoableTree<TestType> tree {elems[0], elems[1], elems[2], elems[3], elems[4]};

        auto it = tree.begin();

        REQUIRE(*it == 1);
        REQUIRE(*(++it) == 2);
        REQUIRE(*(++it) == 4);
        REQUIRE(*(++it) == 24);
        REQUIRE(*(++it) == 103);
    }

    UndoableTree<TestType> tree (elems.begin(), elems.end());

    SECTION ("Deep copy") {
        const UndoableTree<TestType> copy (tree);

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

TEMPLATE_TEST_CASE("Tree container", "[any]", (UndoableTree<RedBlackTree<int>>),
                                              (UndoableTree<SplayTree<int, std::greater<>>>)) {

    using namespace lab;
    using namespace lab::forest;

    TestType base = {2, 22, 1234, 5};

    AnyTree<SupportedValueType<int>,
            SupportedComparators<std::less<>, std::greater<>>> any(base);

    any = base;

    REQUIRE(any.size() == base.size());
    REQUIRE(std::equal(base.begin(), base.end(), any.begin()));

    static constexpr int someValue = 233;

    base.insert(someValue);
    any.insert(someValue);

    REQUIRE(*any.search(someValue) == *base.search(someValue));

    base.erase(someValue);
    any.erase(someValue);

    REQUIRE((base.search(someValue) == base.end()
             && any.search(someValue) == any.end()));

    base.undo();
    any.undo();
    REQUIRE (*any.search(someValue) == *base.search(someValue));

    base.redo();
    any.redo();

    REQUIRE((base.search(someValue) == base.end()
             && any.search(someValue) == any.end()));

}

TEST_CASE("Saving trees (no eco activism)") {

    using namespace lab;
    using namespace lab::forest;

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