#pragma once

#include <SearchTreeBase.hpp>
#include <Iterators/BSTIterator.hpp>
#include "NodeUtilities.hpp"

namespace lab::tree {

    /**
     *   @brief Abstract base class for binary search tree implementations
     */
    template <typename T, typename Compare, typename DerivedTree>
    class BSTBase : public SearchTreeBase<T, Compare, DerivedTree> {
    protected:
        explicit BSTBase(const Compare& comp = Compare{});

        void simpleInsert(Node<DerivedTree>* toInsert);

    private:
        using Base = SearchTreeBase<T, Compare, DerivedTree>;

    public:
        using value_type = T;
        using iterator = BSTIterator<T, Node<DerivedTree>>;

        iterator search (const T& key) noexcept;

        virtual void insert (const T& key) = 0;
        virtual void erase (const T& key) = 0;

        iterator begin() const noexcept;
        iterator end() const noexcept ;

        ~BSTBase() override = default;

    protected:
        using Base::_root;
        using Base::_size;
        using Base::_comp;
    };
}

#include "BSTBase.tpp"