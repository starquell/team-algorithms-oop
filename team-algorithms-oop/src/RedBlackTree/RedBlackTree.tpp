#pragma once

#include <RedBlackTree/InsertionFixRBTree.hpp>
#include <RedBlackTree/DeletionFixRBTree.hpp>
#include <NodeBase.hpp>

namespace lab::forest {

    namespace detail {

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

    template <typename T, typename Compare>
    template <typename Iter>
    RedBlackTree<T, Compare>::RedBlackTree (Iter begin, Iter end)
    {
        _root = nullptr;
        for (; begin != end; ++begin) {
            this->insert(*begin);
        }
    }

    template <typename T, typename Compare>
    RedBlackTree<T, Compare>::RedBlackTree (std::initializer_list<T> elems) {
        for (const auto& elem : elems) {
            this->insert(elem);
        }
    }

    template <typename T, typename Compare>
    void RedBlackTree<T, Compare>::insertImpl(const T& _data) {

        auto inputNode = new detail::Node<RedBlackTree<T, Compare>>{_data};
        Base::simpleInsert(inputNode);

        detail::rbutils::InsertionFixRBTree(_root, inputNode);
    }

    template <typename T, typename Compare>
    void RedBlackTree<T, Compare>::eraseImpl(const T& _data) {
        if (_root == nullptr) {
            return;
        }
        detail::Node<RedBlackTree<T, Compare>>* nodeToDelete = detail::find(_root, _data, _comp);

        if (nodeToDelete == nullptr) {
            return;
        }

        if (nodeToDelete == _root && nodeToDelete->left == nullptr && nodeToDelete->right == nullptr) {
            _root = nullptr;
        } else {
            detail::rbutils::DeletionFixRBTRee(_root, nodeToDelete);
        }
    }

    template <typename T, typename Compare>
    RedBlackTree<T, Compare>::RedBlackTree (const Compare& comp)
        : Base(comp)
    {}
}