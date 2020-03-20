#pragma once

#include <BSTBase.hpp>

#include <functional>

namespace lab::tree {
    template <typename T,
              typename Compare = std::less<T>>
    class RedBlackTree : public BSTBase<T, Compare, RedBlackTree<T>> {

    private:
        using NodeRBT = Node<RedBlackTree<T>>;
        using Base = BSTBase<T, Compare, RedBlackTree<T>>;

    public:
        explicit RedBlackTree(const Compare& comp = Compare{});

        /**
        *  @brief Contructs tree with elements from range [begin, end)
        */
        template <typename Iter>
        RedBlackTree(Iter begin, Iter end);

        /**
         *  @brief Contructs tree with elements from list
         */
        RedBlackTree(std::initializer_list<T> elems);

        void insert(const T& _data) override;
        void erase(const T& _data) override;

        ~RedBlackTree() override = default;

    protected:
        using Base::_root;
        using Base::_size;
        using Base::_comp;
    };

    template<typename T>
    struct Node<RedBlackTree<T>> {
        using NodeRBT = Node<RedBlackTree<T>>;

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

#include "RedBlackTree.tpp"
