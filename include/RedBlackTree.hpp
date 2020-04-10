#pragma once

#include <BSTBase.hpp>

#include <functional>

namespace lab::forest {

    /**
     *   @brief Red-Black Tree implementation
     *   T - type of value stored in tree, Compare - comparison function class for elements in tree
     */
    template <typename T,
              typename Compare = std::less<>>
    class RedBlackTree : public detail::BSTBase<T, Compare, RedBlackTree<T, Compare>> {
    public:
        explicit RedBlackTree (const Compare& comp = Compare {});

        /**
        *  @brief Contructs tree with elements from range [begin, end)
        */
        template <typename Iter>
        RedBlackTree (Iter begin, Iter end);

        /**
         *  @brief Contructs tree with elements from list
         */
        RedBlackTree (std::initializer_list<T> elems);

        RedBlackTree (const RedBlackTree& other) = default;
        RedBlackTree (RedBlackTree&& other) noexcept = default;

        RedBlackTree& operator= (const RedBlackTree& other) = default;
        RedBlackTree& operator= (RedBlackTree&& other) noexcept = default;

    private:
        friend class detail::BSTBase<T, Compare, RedBlackTree<T, Compare>>;

        /**
         *  @brief Inserts element with key _data to tree
         *  @attention Must be used only in insert method in BSTBase
         */
        void insertImpl (const T& _data);

        /**
         *  @brief Erases element with key _data from tree
         *  @attention Must be used only in insert method in BSTBase
         */
        void eraseImpl (const T& _data);

        using NodeRBT = lab::forest::detail::Node<RedBlackTree<T>>;
        using Base = detail::BSTBase<T, Compare, RedBlackTree<T, Compare>>;

    public:
        ~RedBlackTree () = default;

    protected:
        using Base::_root;
        using Base::_size;
        using Base::_comp;
    };

    template <typename Iter, typename Compare = std::less<>>
    RedBlackTree (Iter, Iter) -> RedBlackTree <typename std::iterator_traits<Iter>::value_type, Compare>;
}

#include <RedBlackTree/RedBlackTree.tpp>
