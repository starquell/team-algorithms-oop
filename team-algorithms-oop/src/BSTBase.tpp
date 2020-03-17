#pragma once

#include <NodeUtilities.hpp>

namespace tree {

    template <typename T, typename DerivedTree>
    auto BSTBase<T, DerivedTree>::search (const T& key) noexcept
        -> typename BSTBase<T, DerivedTree>::iterator
    {
        auto found = utils::find(_root, key);
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

    template <typename T, typename Derived>
    auto BSTBase<T, Derived>::begin() const -> typename BSTBase<T, Derived>::iterator {
        return iterator{utils::min(_root)};
    }

    template <typename T, typename Derived>
    auto BSTBase<T, Derived>::end() const -> typename BSTBase<T, Derived>::iterator {
        return iterator{nullptr};
    }

}