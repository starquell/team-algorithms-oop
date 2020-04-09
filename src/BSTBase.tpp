#pragma once

#include <NodeUtilities.hpp>

#include <algorithm>
#include "NodeBase.hpp"

namespace lab::forest::detail {

    template <typename T, typename Compare, typename DerivedTree>
    auto BSTBase<T, Compare, DerivedTree>::search (const T& key) noexcept
        -> typename BSTBase<T, Compare, DerivedTree>::iterator
    {
        auto found = detail::find(_root, key, _comp);
        if (found) {
            auto iter = begin();
            while (iter) {
                if (*iter == key) {
                    break;
                }
                ++iter;
            }
            return iter;
        }
        else {
            return end();
        }
    }

    template <typename T, typename Compare, typename DerivedTree>
    auto BSTBase<T, Compare, DerivedTree>::begin() const noexcept
        -> typename BSTBase<T, Compare, DerivedTree>::iterator
    {
        return iterator(detail::min(_root));
    }

    template <typename T, typename Compare, typename DerivedTree>
    auto BSTBase<T, Compare, DerivedTree>::end() const noexcept
            -> typename BSTBase<T, Compare, DerivedTree>::iterator
    {
        return iterator(nullptr);
    }

    template <typename T, typename Compare, typename DerivedTree>
    bool BSTBase<T, Compare, DerivedTree>::simpleInsert (lab::forest::detail::Node<DerivedTree>* toInsert)
    {
        if (_root == nullptr) {
            _root = toInsert;
            return _root;
        } else {
            detail::insertWithParent(_root, toInsert, _comp);
            return toInsert->parent;
        }
    }

    template <typename T, typename Compare, typename DerivedTree>
    BSTBase<T, Compare, DerivedTree>::~BSTBase ()  {
        if (_root) {
            detail::eraseSubTree(_root);
        }
    }
    template <typename T, typename Compare, typename DerivedTree>
    auto BSTBase<T, Compare, DerivedTree>::size() const noexcept -> std::size_t {
        return _size;
    }

    template <typename T, typename Compare, typename DerivedTree>
    BSTBase<T, Compare, DerivedTree>::BSTBase (const BSTBase& other)
            : _root(detail::clone(other._root)),
              _size(other._size),
              _comp(other._comp)
    {}


    template <typename T, typename Compare, typename DerivedTree>
    auto BSTBase<T, Compare, DerivedTree>::operator= (DerivedTree other) noexcept
        -> BSTBase<T, Compare, DerivedTree>&
    {
        swap (*this, other);
        return *this;
    }

    template <typename T, typename Compare, typename DerivedTree>
    BSTBase<T, Compare, DerivedTree>::BSTBase (const Compare& comp)
            : _comp(comp)
    {}

    template <typename T, typename Compare, typename DerivedTree>
    auto BSTBase<T, Compare, DerivedTree>::compareFunc () const noexcept -> Compare {
        return _comp;
    }

    template <typename T, typename Compare, typename DerivedTree>
    bool BSTBase<T, Compare, DerivedTree>::operator!= (const DerivedTree& other) const noexcept{
        return !std::equal(begin(), end(), other.begin());
    }

    template <typename T, typename Compare, typename DerivedTree>
    bool BSTBase<T, Compare, DerivedTree>::operator== (const DerivedTree& other) const noexcept{
        return std::equal(begin(), end(), other.begin());
    }

    template <typename T, typename Compare, typename DerivedTree>
    BSTBase<T, Compare, DerivedTree>::BSTBase (BSTBase&& other) noexcept
            : _root (std::exchange(other._root, nullptr)),
              _comp (other._comp),
              _size (std::exchange(other._size, 0))
    {}

    template <typename T, typename Compare, typename DerivedTree>
    void BSTBase<T, Compare, DerivedTree>::insert (const T& key) {
        static_cast<DerivedTree*>(this)->insertImpl(key);
    }

    template <typename T, typename Compare, typename DerivedTree>
    void BSTBase<T, Compare, DerivedTree>::erase (const T& key) {
        static_cast<DerivedTree*>(this)->eraseImpl(key);
    }
}