#pragma once

#include <BSTBase.hpp>
#include <functional>

namespace lab::forest {

    /**
     *  @brief Splay Tree implementation
     *  T - type of value stored in tree, Compare - comparison function class for elements in tree
     */
    template <typename T,
              typename Compare = std::less<>>
    class SplayTree : public detail::BSTBase<T, Compare, SplayTree<T, Compare>> {
    public:
        /**
         *  @brief Creates tree with no elements
         */
        explicit SplayTree (const Compare& comp = Compare{}) noexcept;

        /**
         *  @brief Constructs tree with elements from range [begin, end)
         */
        template <typename Iter>
        SplayTree (Iter begin, Iter end);

        SplayTree (const SplayTree& other) = default;
        SplayTree (SplayTree&& other) noexcept = default;

        SplayTree& operator= (const SplayTree& other) = default;
        SplayTree& operator= (SplayTree&& other) noexcept = default;

        /**
         *  @brief Constructs tree with elements from list
         */
        SplayTree (std::initializer_list<T> elems);

    private:
        friend class detail::BSTBase<T, Compare, SplayTree<T, Compare>>;

        /**
         *  @brief Inserts element with key _data to tree
         *  @attention Must be used only in insert method in BSTBase
         */
        void insertImpl (const T& key);

        /**
         *  @brief Erases element with key _data from tree
         *  @attention Must be used only in insert method in BSTBase
         */
        void eraseImpl (const T& key);

        using Base = detail::BSTBase<T, Compare, SplayTree<T, Compare>>;

    public:

        ~SplayTree() = default;

    protected:
        using Base::_root;
        using Base::_size;
        using Base::_comp;
    };
}

#include "SplayTree/SplayTree.tpp"
#include "NodeBase.hpp"
