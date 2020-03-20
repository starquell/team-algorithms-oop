#pragma once

#include <NodeUtilities.hpp>

namespace lab::tree {

    template <typename T, typename Compare, typename DerivedTree>
    SearchTreeBase<T, Compare, DerivedTree>::~SearchTreeBase ()  {
        if (_root) {
            bstutils::eraseSubTree(_root);
        }
    }
    template <typename T, typename Compare, typename DerivedTree>
    auto SearchTreeBase<T, Compare, DerivedTree>::size () const noexcept -> std::size_t {
        return _size;
    }

    template <typename T, typename Compare, typename DerivedTree>
    SearchTreeBase<T, Compare, DerivedTree>::SearchTreeBase (const SearchTreeBase& other)
        : _root(bstutils::clone(other._root)),
          _size(other._size),
          _comp(other._comp)
    {}


    template <typename T, typename Compare, typename DerivedTree>
    auto SearchTreeBase<T, Compare, DerivedTree>::operator= (SearchTreeBase other)
            -> SearchTreeBase<T, Compare, DerivedTree>&
    {
        std::swap (*this, other);
        return *this;
    }

    template <typename T, typename Compare, typename DerivedTree>
    SearchTreeBase<T, Compare, DerivedTree>::SearchTreeBase (const Compare& comp)
            : _comp(comp)
    {}

    template <typename T, typename Compare, typename DerivedTree>
    auto SearchTreeBase<T, Compare, DerivedTree>::compareFunc () const noexcept -> Compare {
        return _comp;
    }
}