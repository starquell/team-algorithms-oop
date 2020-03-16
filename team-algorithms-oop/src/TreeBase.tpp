#pragma once

#include <NodeUtilities.hpp>

namespace tree {

    template <typename T, typename DerivedTree>
    TreeBase<T, DerivedTree>::~TreeBase ()  {
        if (_root) {
            delete _root;
        }
    }
    template <typename T, typename Derived>
    auto TreeBase<T, Derived>::size () const noexcept -> std::size_t {
        return _size;
    }

    template <typename T, typename DerivedTree>
    TreeBase<T, DerivedTree>::TreeBase (const TreeBase& other)
        : _root(utils::clone(other._root)),
          _size(other._size)
    {}

    template <typename T, typename DerivedTree>
    TreeBase<T, DerivedTree>& TreeBase<T, DerivedTree>::operator= (TreeBase other) {
        std::swap (*this, other);
        return *this;
    }
}