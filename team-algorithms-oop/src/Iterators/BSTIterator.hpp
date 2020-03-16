#pragma once

#include <Iterators/IteratorBase.hpp>

namespace tree {

    /**
     *  @brief Iterator for binary search tree with node that has pointer on parent node
     */
    template <typename T, typename TreeNode>
    class BSTIterator : public IteratorBase<T, BSTIterator<T, TreeNode>> {

    public:
        explicit BSTIterator (TreeNode* root) noexcept;

        const T& operator* () noexcept;

        explicit operator bool () const noexcept override;

        bool operator!= (const BSTIterator& other) noexcept override;

        bool operator== (const BSTIterator& other) noexcept override;

        BSTIterator& operator++ () noexcept override;

        BSTIterator operator+ (int n) const noexcept override;

//        BSTIterator& operator-- () noexcept;
//
//        BSTIterator operator- (int n) const noexcept;

    private:
        TreeNode* m_curr;
    };
}

#include <Iterators/BSTIterator.tpp>
