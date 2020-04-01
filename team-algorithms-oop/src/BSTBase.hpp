#pragma once

#include <BSTIterator.hpp>
#include <NodeUtilities.hpp>

namespace lab::forest::detail {

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

        void simpleInsert(lab::forest::detail::Node<DerivedTree>* toInsert);

    public:
        using value_type = T;
        using iterator = BSTIterator<DerivedTree>;

        /**
         *  @return Iterator to key in tree, if not found - end()
         */
        iterator search (const T& key) noexcept;

        /**
         *  @brief Inserts key to tree
         */
        void insert (const T& key);

        /**
         *  @brief Erase element with this key from tree
         */
        void erase (const T& key);

        /**
         *  @return Iterator pointed to the min element in tree
         */
        iterator begin() const noexcept;

        /**
         *  @return Iterator pointed to the element after last in tree
         *  @warning Use only to check if element is in tree, derefencing causes exception
         */
        iterator end() const noexcept;

        BSTBase (const BSTBase& other);
        BSTBase (BSTBase&& other) noexcept;

        BSTBase& operator= (DerivedTree other) noexcept;
        BSTBase& operator= (const BSTBase& other) noexcept = default;
        BSTBase& operator= (BSTBase&& other) noexcept = default;

        /**
         *  @brief Swaps contents of trees
         */
        friend void swap (BSTBase& lhs, BSTBase& rhs) noexcept {
            std::swap(lhs._root, rhs._root);
            std::swap(lhs._comp, rhs._comp);
            std::swap(lhs._size, rhs._size);
        }

        bool operator== (const DerivedTree& other) const noexcept;
        bool operator!= (const DerivedTree& other) const noexcept;

        /**
         *  @return Amount of elements in tree
         */
        [[nodiscard]]
        auto size() const noexcept -> std::size_t;

        /**
         *  @return Function that sets order in tree, default - std::less{}
         */
        [[nodiscard]]
        auto compareFunc() const noexcept -> Compare;

        ~BSTBase();

    protected:
        std::size_t _size = 0;
        Compare _comp = Compare{};
        lab::forest::detail::Node<DerivedTree>* _root = nullptr;
    };
}

#include "BSTBase.tpp"
#include "NodeBase.hpp"
