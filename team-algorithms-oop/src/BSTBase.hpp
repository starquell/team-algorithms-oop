#pragma once

#include <Iterators/BSTIterator.hpp>
#include "NodeUtilities.hpp"

namespace lab::tree {

    /**
     *   @brief Abstract base class for binary search tree implementations
     */
    template <typename T, typename Compare, typename DerivedTree>
    class BSTBase {
    protected:
        explicit BSTBase (const Compare& comp = Compare{});

        void simpleInsert(Node<DerivedTree>* toInsert);

    public:
        using value_type = T;
        using iterator = BSTIterator<T, Node<DerivedTree>>;

        iterator search (const T& key) noexcept;

        virtual void insert (const T& key) = 0;
        virtual void erase (const T& key) = 0;

        iterator begin() const noexcept;
        iterator end() const noexcept;

        BSTBase (const BSTBase& other);
        BSTBase& operator= (DerivedTree other);

        [[nodiscard]]
        auto size() const noexcept -> std::size_t;

        [[nodiscard]]
        auto compareFunc() const noexcept -> Compare;

        virtual ~BSTBase();

    protected:
        std::size_t _size = 0;
        Compare _comp = Compare{};
        Node<DerivedTree>* _root = nullptr;
    };
}

#include "BSTBase.tpp"