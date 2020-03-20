#pragma once

#include <UndoableTree.hpp>

#include <functional>

namespace lab::tree {

    /**
     *  @brief Priority for tree operation (search, insert, erase) in SearchTree class
     */
    enum class Priority {
        QuickAccessToRecentlyUsed,
        GeneralPerfomance
    };

    /**
     *  @brief Class that implements tree, choosing implementation according to priority
     */
    template <typename T,
              Priority priority = Priority::GeneralPerfomance,
              typename Compare = std::less<T>>
    class SearchTree {};


    template <typename T, typename Compare = std::less<T>>
    class SearchTree<T, Priority::GeneralPerfomance, Compare>
            : public UndoableTree<RedBlackTree<T, Compare>> {
    public:

       explicit SearchTree() = default;
       SearchTree (std::initializer_list<T> elems)
             : UndoableTree<RedBlackTree<T, Compare>> (elems)
       {}

       template <typename Iter>
       SearchTree (Iter begin, Iter end)
            : UndoableTree<RedBlackTree<T, Compare>> (begin, end)
       {}
    };


    template <typename T, typename Compare = std::less<T>>
    class SearchTree <T, Priority::QuickAccessToRecentlyUsed, Compare>
            : public UndoableTree<SplayTree<T, Compare>>
    {
    public:
        explicit SearchTree() = default;
        SearchTree (std::initializer_list<T> elems)
             : UndoableTree<SplayTree<T, Compare>> (elems)
        {}

        template <typename Iter>
        SearchTree (Iter begin, Iter end)
             : UndoableTree<SplayTree<T, Compare>> (begin, end)
        {}
    };

}
