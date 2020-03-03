#pragma once

namespace trees {

    template <typename BinarySearchTreeNode, typename T>
    class BinarySearchTreeIterator {

        using Node = BinarySearchTreeNode;
    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::forward_iterator_tag;

        explicit BinarySearchTreeIterator (Node* root) noexcept;

        const T& operator*() noexcept ;

        bool operator!= (const BinarySearchTreeIterator& other) noexcept;

        bool operator== (const BinarySearchTreeIterator& other) noexcept;

        BinarySearchTreeIterator& operator++() noexcept ;

        BinarySearchTreeIterator operator+ (int n) const noexcept ;

    private:
        Node* m_curr;
    };

    template <typename BSTNode, typename T>
    using BSTIterator = BinarySearchTreeIterator<BSTNode, T>;
}

#include "BinarySearchTreeIterator.tpp"


