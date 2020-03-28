#pragma once

#include <BSTBase.hpp>


#include <functional>

namespace lab::tree {

    /**
     *  @brief Splay Tree implementation
     */
    template <typename T,
            typename Compare = std::less<>>
    class SplayTree : public BSTBase<T, Compare, SplayTree<T, Compare>> {
    private:
        using Base = BSTBase<T, Compare, SplayTree<T, Compare>>;
    public:
        /**
         *  @brief Created tree with no elements
         */
        explicit SplayTree (const Compare& comp = Compare {}) noexcept;

        /**
         *  @brief Contructs tree with elements from range [begin, end)
         */
        template <typename Iter>
        SplayTree (Iter begin, Iter end);

        /**
         *  @brief Contructs tree with elements from list
         */
        SplayTree (std::initializer_list<T> elems);

        void insert (const T& key) override;

        void erase (const T& key) override;

        ~SplayTree () override = default;

    protected:
        using Base::_root;
        using Base::_size;
        using Base::_comp;
    };

    template <typename T, typename Compare>
    struct Node<SplayTree<T, Compare>> {
        T data;
        Node<SplayTree<T, Compare>>*left = nullptr;
        Node<SplayTree<T, Compare>>*right = nullptr;
        Node<SplayTree<T, Compare>>*parent = nullptr;
    };
}

#include "SplayTree/SplayTree.tpp"
