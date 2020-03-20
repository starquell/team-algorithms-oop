#pragma once

#include <iostream>
#include <BSTBase.hpp>


namespace tree {
    template<typename T>
    class RedBlackTree : public BSTBase<T, RedBlackTree<T>> {

    private:
        using NodeRBT = Node<RedBlackTree<T>>;
        using Base = BSTBase<T, RedBlackTree<T>>;

    public:
        RedBlackTree() = default;

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
        using Base::simpleInsert;
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

