#pragma once

#include <iostream>
#include "../BSTBase.hpp"


namespace tree {
    template<typename T>
    class RedBlackTree : public BSTBase<T, RedBlackTree<T>> {

    private:
        using NodeRBT = Node<RedBlackTree<T>>;
        using Base = BSTBase<T, RedBlackTree<T>>;

    protected:
        using Base::_root;
        using Base::_size;
        using Base::simpleInsert;

    public:
        RedBlackTree() = default;
        template <typename Iter>
        RedBlackTree(Iter begin, Iter end);

        RedBlackTree(std::initializer_list<T> elems);

        void insert(const T& _data) override;
        void erase(const T& _data) override;

        using Base::Base;
        using Base::operator=;
        using Base::begin;
        using Base::end;
        using Base::size;
        ~RedBlackTree() override = default;

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

