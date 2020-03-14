//
// Created by Yana on 03.03.2020.
//

#pragma once

#include <iostream>
#include <vector>
#include "BinarySearchTreeIterator.hpp"

namespace tree {
    enum Color {
        red, black
    };

    template<typename T>
    class RedBlackTree {
    public:
        struct Node {
            T data;
            Color color;
            Node *left;
            Node *right;
            Node *parent;

            explicit Node(T _data) : data(_data), left(nullptr), right(nullptr), parent(nullptr), color(red) {}
            bool hasRedChild();
            static void swapColors(Node *firstNode, Node *secondNode);
        };
    private:
        Node* root;

    protected:
        auto simpleInsert(Node *currNode, Node *inputNode);//insert like in ordinary BST
        Node* find(const T &elem);
        void rotateLeft(Node *&currNode);
        void rotateRight(Node *&currNode);
        void fixTree(Node *&currNode);
        Node* simpleReplace(Node *node);
        void fixBothBlack(Node *node);
        void eraseNode(Node *nodeToDelete);
        void printTreePreorder(Node *curr);

    public:
        using iterator = BinarySearchTreeIterator<Node, T>;
        auto begin () const -> iterator;
        auto end () const -> iterator;

        RedBlackTree() : root(nullptr) {}
        explicit RedBlackTree(std::vector<T> &_data);

        void insert(const T _data);
        void erase(T _data);
        iterator search(const T &elem) const;
        void print();

    };
}

#include "RedBlackTree.tpp"

