//
// Created by Yana on 03.03.2020.
//

#pragma once

#include <iostream>
#include "../BSTBase.hpp"
#include "../NodeBase.hpp"


namespace tree {
    enum Color {
        red, black
    };

    template<typename T>
class RedBlackTree : public BSTBase<T, RedBlackTree<T>> {

private:
    using NodeRBT = Node<RedBlackTree<T>>;
    using Base = BSTBase<T, RedBlackTree<T>>;

protected:
        using Base::_root;
        using Base::_size;

        void rotateLeft(NodeRBT *&currNode);
        void rotateRight(NodeRBT *&currNode);
        void fixTree(NodeRBT *&currNode);
        void fixBothBlack(NodeRBT *node);
        void eraseNode(NodeRBT *nodeToDelete);
        Node<RedBlackTree<T>>* simpleReplace(Node<RedBlackTree<T>> *node);
        auto simpleInsert(Node<RedBlackTree<T>> *currNode, Node<RedBlackTree<T>> *inputNode);

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

        T data;
        Color color = red;
        NodeRBT* left = nullptr;
        NodeRBT* right = nullptr;
        NodeRBT* parent = nullptr;

        explicit Node<RedBlackTree<T>> (const T& _data) : data(_data) {}
        explicit Node<RedBlackTree<T>> (Node<RedBlackTree<T>>* node) : data(node->data), color(node->color) {}
        ~Node<RedBlackTree<T>>() {
            if (left) {
                delete left;
            }
            if (right) {
                delete right;
            }
        }
    };

}

#include "RedBlackTree.tpp"

