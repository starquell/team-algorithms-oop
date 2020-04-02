#pragma once

#include <NodeBase.hpp>
#include <iterator>

namespace lab::tree {

    /**
     *  @brief Tree Iterator for binary search tree with node that has pointer on parent node
     */
    template <typename Tree>
    class BSTIterator {
    public:
        using value_type = typename Tree::value_type;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::forward_iterator_tag;

        explicit BSTIterator (Node<Tree>* root) noexcept;

        const value_type& operator* ();

        explicit operator bool () const noexcept ;

        bool operator!= (const BSTIterator& other) noexcept ;

        bool operator== (const BSTIterator& other) noexcept ;

        BSTIterator& operator++ () noexcept ;

        BSTIterator operator+ (int n) const noexcept ;

    private:
        Node<Tree>* m_curr = nullptr;
    };

    template <typename Tree>
    BSTIterator (Node<Tree>* root) -> BSTIterator<Tree>;
}

#include <BSTIterator.tpp>
