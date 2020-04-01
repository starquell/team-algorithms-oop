#pragma once

#include <BSTIterator.hpp>
#include <NodeUtilities.hpp>


namespace lab::forest {

    /**
     *   @brief Abstract base class for binary search tree implementations using CRTP
     *
     *   Provides BST iterator, representing elements in increasing order and begin(), end() methods.
     *   Provides search and size methods, copy and move constuctors, copy and move
     *   assigment operators, and swap function.
     *   Requires insertImpl(const T& key) and eraseImpl(const T& key) methods in derived class.
     *   Implementation details like root and size are protected.
     */
    template <typename T, typename Compare, typename DerivedTree>
    class BSTBase {
    protected:
        explicit BSTBase (const Compare& comp = Compare{});

        void simpleInsert(Node<DerivedTree>* toInsert);

    public:
        using value_type = T;
        using iterator = BSTIterator<DerivedTree>;

        iterator search (const T& key) noexcept;

        void insert (const T& key);
        void erase (const T& key);

        iterator begin() const noexcept;
        iterator end() const noexcept;

        BSTBase (const BSTBase& other);
        BSTBase (BSTBase&& other) noexcept;

        BSTBase& operator= (DerivedTree other) noexcept;
        BSTBase& operator= (const BSTBase& other) noexcept = default;
        BSTBase& operator= (BSTBase&& other) noexcept = default;

        friend void swap (BSTBase& lhs, BSTBase& rhs) noexcept {
            std::swap(lhs._root, rhs._root);
            std::swap(lhs._comp, rhs._comp);
            std::swap(lhs._size, rhs._size);
        }

        bool operator== (const DerivedTree& other) const noexcept;
        bool operator!= (const DerivedTree& other) const noexcept;

        [[nodiscard]]
        auto size() const noexcept -> std::size_t;

        [[nodiscard]]
        auto compareFunc() const noexcept -> Compare;

        ~BSTBase();

    protected:
        std::size_t _size = 0;
        Compare _comp = Compare{};
        Node<DerivedTree>* _root = nullptr;
    };
}

#include "BSTBase.tpp"