#pragma once

#include <UndoableTree.hpp>

namespace tree {

    enum class Priority {
        QuickAccessToRecentlyUsed,
        GeneralPerfomance
    };

    template <typename T, Priority priority = Priority::GeneralPerfomance>
    class SearchTree {};

    template <typename T>
    class SearchTree<T, Priority::GeneralPerfomance>
            : public UndoableTree<RedBlackTree<T>> {
    public:

       explicit SearchTree() = default;
       SearchTree (std::initializer_list<T> elems)
             : UndoableTree<RedBlackTree<T>> (elems)
       {}

       template <typename Iter>
       SearchTree (Iter begin, Iter end)
            : UndoableTree<RedBlackTree<T>> (begin, end)
       {}
    };


    template <typename T>
    class SearchTree<T, Priority::QuickAccessToRecentlyUsed>
            : public UndoableTree<SplayTree<T>>
    {
    public:
        explicit SearchTree() = default;
        SearchTree (std::initializer_list<T> elems)
             : UndoableTree<SplayTree<T>> (elems)
        {}

        template <typename Iter>
        SearchTree (Iter begin, Iter end)
             : UndoableTree<SplayTree<T>> (begin, end)
        {}
    };

}
