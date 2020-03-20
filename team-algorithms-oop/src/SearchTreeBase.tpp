#pragma once

#include <NodeUtilities.hpp>

namespace tree {

    template <typename T, typename DerivedTree>
    SearchTreeBase<T, DerivedTree>::~SearchTreeBase ()  {
        if (_root) {
            bstutils::eraseSubTree(_root);
        }
    }
    template <typename T, typename Derived>
    auto SearchTreeBase<T, Derived>::size () const noexcept -> std::size_t {
        return _size;
    }

    template <typename T, typename DerivedTree>
    SearchTreeBase<T, DerivedTree>::SearchTreeBase (const SearchTreeBase& other)
        : _root(bstutils::clone(other._root)),
          _size(other._size)
    {}


    template <typename T, typename DerivedTree>
    SearchTreeBase<T, DerivedTree>& SearchTreeBase<T, DerivedTree>::operator= (SearchTreeBase other) {
        std::swap (*this, other);
        return *this;
    }
}