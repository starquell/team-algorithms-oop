#pragma once

#include <Iterators/TreeIterator.hpp>

namespace lab::tree {

    /**
     *  @brief TreeIterator for binary search tree with node that has pointer on parent node
     */
    template <typename T, typename TreeNode>
    class BSTIterator {
    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::forward_iterator_tag;

        explicit BSTIterator (TreeNode* root) noexcept;

        const T& operator* () noexcept;

        explicit operator bool () const noexcept ;

        bool operator!= (const BSTIterator& other) noexcept ;

        bool operator== (const BSTIterator& other) noexcept ;

        BSTIterator& operator++ () noexcept ;

        BSTIterator operator+ (int n) const noexcept ;

//        BSTIterator& operator-- () noexcept;
//
//        BSTIterator operator- (int n) const noexcept;

    private:
        TreeNode* m_curr;
    };
}

#include <Iterators/BSTIterator.tpp>
