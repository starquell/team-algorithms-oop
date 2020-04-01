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
    class SplayTree : public BSTBase<T, Compare, SplayTree<T, Compare>> {
    public:
        /**
         *  @brief Creates tree with no elements
         */
        explicit SplayTree (const Compare& comp = Compare{}) noexcept;

        /**
         *  @brief Contructs tree with elements from range [begin, end)
         */
        template <typename Iter>
        SplayTree (Iter begin, Iter end);

        SplayTree (const SplayTree& other) = default;
        SplayTree (SplayTree&& other) noexcept = default;

        SplayTree& operator= (const SplayTree& other) = default;
        SplayTree& operator= (SplayTree&& other) noexcept = default;

        /**
         *  @brief Contructs tree with elements from list
         */
        SplayTree (std::initializer_list<T> elems);

    private:
        friend class BSTBase<T, Compare, SplayTree<T, Compare>>;

        void insertImpl (const T& key);

        void eraseImpl (const T& key);

        using Base = BSTBase<T, Compare, SplayTree<T, Compare>>;

    public:

        ~SplayTree() = default;

    protected:
        using Base::_root;
        using Base::_size;
        using Base::_comp;
    };

    template <typename T, typename Compare>
    struct Node<SplayTree<T, Compare>> {
        T data;
        Node<SplayTree<T, Compare>>* left = nullptr;
        Node<SplayTree<T, Compare>>* right = nullptr;
        Node<SplayTree<T, Compare>>* parent = nullptr;
    };
}

#include "SplayTree/SplayTree.tpp"