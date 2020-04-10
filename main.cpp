#include <iostream>

#include <AnyTree.hpp>
#include <SplayTree.hpp>
#include <RedBlackTree.hpp>

int main () {

    using namespace lab;

    {
        forest::SplayTree tree{"2", "aaa", "asd", "439", "haha"};

        tree.insert("ff");
        tree.erase("haha");

        /// Iterating in increasing order
        for (const auto &i : tree) {
            std::cout << i << ' ';
        }

        auto it = tree.search("nope");
        assert (it == tree.end());

        const auto size = tree.size();
    }

    {
        constexpr std::array a = {"2", "aaa", "asd"};

        /// Using other comparator, constructing from iter
        forest::RedBlackTree<std::string, std::greater<>> tree (a.begin(), a.end());

        /// Iterating in decreasing order
        for (const auto &i : tree) {
            std::cout << i << ' ';
        }
    }

    {
        forest::UndoableTree tree (forest::RedBlackTree {"aaa", "bbb"});

        tree.insert("s");

        while (true) {      /// he could, but don`t do like this
            tree.undo();
            tree.redo();
        }
    }

    {
        forest::AnyTree <SupportedValueType<double>,
                         SupportedComparators<std::less<>, std::greater<>>> any;

        any = forest::SplayTree<double> {};

        any.insert(34.5);

        any = forest::RedBlackTree<double, std::greater<>>{};

        any = forest::UndoableTree <forest::SplayTree<int>>{};
    }


    return 0;
}
