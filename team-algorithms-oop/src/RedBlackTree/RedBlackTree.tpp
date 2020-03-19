#pragma once

#include "RedBlackTree.hpp"
#include "InsertionFixRBTree.hpp"
#include "DeletionFixRBTree.hpp"

namespace tree {

    template <typename T>
    template <typename Iter>
    RedBlackTree<T>::RedBlackTree (Iter begin, Iter end)
    {
        _root = nullptr;
        for (; begin != end; ++begin) {
            insert(*begin);
        }
    }

    template <typename T>
    RedBlackTree<T>::RedBlackTree (std::initializer_list<T> elems) {
        for (const auto& elem : elems) {
            insert(elem);
        }
    }

    template <typename T>
    void RedBlackTree<T>::insert(const T& _data) {
        auto inputNode = new Node<RedBlackTree<T>>{_data};
        BSTInsert(inputNode);

        tree::utils::InsertionFixRBTree(_root, inputNode);
        _size++;
    }

    template <typename T>
    void RedBlackTree<T>::erase(const T& _data) {
        if (_root == nullptr) {
            return;
        }

        Node<RedBlackTree<T>>* nodeToDelete = tree::utils::find<RedBlackTree>(_root,  _data);

        if (nodeToDelete == nullptr) {
            return;
        }

        if (nodeToDelete == _root && nodeToDelete->left == nullptr && nodeToDelete->right == nullptr) {
            _root = nullptr;
        } else {
            tree::utils::DeletionFixRBTRee(_root, nodeToDelete);
        }
        _size--;
    }

}