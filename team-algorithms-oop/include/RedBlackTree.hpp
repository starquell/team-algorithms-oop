#pragma once

#include <BSTBase.hpp>

#include <functional>

namespace lab::forest {

    /**
    *  @brief Red-Black Tree implementation
    *  T - type of value stored in tree, Compare - comparison function class for elements in tree
    */
    template <typename T,
              typename Compare = std::less<>>
    class RedBlackTree : public BSTBase<T, Compare, RedBlackTree<T, Compare>> {
    public:
        explicit RedBlackTree (const Compare& comp = Compare {});

        /**
        *  @brief Contructs tree with elements from range [begin, end)
        */
        template <typename Iter>
        RedBlackTree (Iter begin, Iter end);

        /**
         *  @brief Contructs tree with elements from list
         */
        RedBlackTree (std::initializer_list<T> elems);

        RedBlackTree (const RedBlackTree& other) = default;
        RedBlackTree (RedBlackTree&& other) noexcept = default;

        RedBlackTree& operator= (const RedBlackTree& other) = default;
        RedBlackTree& operator= (RedBlackTree&& other) noexcept = default;

    private:
        friend class BSTBase<T, Compare, RedBlackTree<T, Compare>>;

        void insertImpl (const T& _data);
        void eraseImpl (const T& _data);

        using NodeRBT = Node<RedBlackTree<T>>;
        using Base = BSTBase<T, Compare, RedBlackTree<T, Compare>>;

    public:
        ~RedBlackTree () = default;

    protected:
        using Base::_root;
        using Base::_size;
        using Base::_comp;
    };

    template <typename T, typename Compare>
    struct Node<RedBlackTree<T, Compare>> {
        using NodeRBT = Node<RedBlackTree<T, Compare>>;

        enum Color {
            Red,
            Black
        };

        T data;
        Color color = Red;
        NodeRBT* left = nullptr;
        NodeRBT* right = nullptr;
        NodeRBT* parent = nullptr;
    };
}


#include "RedBlackTree/RedBlackTree.tpp"
