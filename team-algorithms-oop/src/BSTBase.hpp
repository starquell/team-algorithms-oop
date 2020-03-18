#pragma once

#include <TreeBase.hpp>
#include <Iterators/BSTIterator.hpp>

namespace tree {

    /**
     *   @brief Abstract base class for binary search tree implementations
     */
    template <typename T, typename DerivedTree>
    class BSTBase : TreeBase<T, DerivedTree> {
    protected:
        explicit BSTBase() = default;
    private:
        using Base = TreeBase<T, DerivedTree>;

    public:
        using value_type = T;
        using iterator = BSTIterator<T, Node<DerivedTree>>;

        iterator search (const T& key) noexcept;

        virtual void insert (const T& key) = 0;
        virtual void erase (const T& key) = 0;

        using Base::TreeBase;
        using Base::operator=;
        using Base::size;

        iterator begin() const;
        iterator end() const;

        ~BSTBase() override = default;

    protected:
        using Base::_root;
        using Base::_size;
    };
}

#include "BSTBase.tpp"