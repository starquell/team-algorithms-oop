#pragma once

#include <BSTBase.hpp>

namespace tree {

    /**
     *  @brief Splay Tree implementation
     */

    template <typename T>
    class SplayTree : public BSTBase<T, SplayTree<T>> {
    private:
        using Base = BSTBase<T, SplayTree<T>>;
    public:
        /**
         *  @brief Created tree with no elements
         */
        explicit SplayTree() noexcept = default;

        /**
         *  @brief Contructs tree with elements from range [begin, end)
         */
        template <typename Iter>
        SplayTree(Iter begin, Iter end);

        /**
         *  @brief Contructs tree with elements from list
         */
        SplayTree(std::initializer_list<T> elems);

        void insert (const T& key) override;
        void erase (const T& key) override;

        ~SplayTree() override = default;

    protected:
        using Base::_root;
        using Base::_size;
    };

    template <typename T>
    struct Node<SplayTree<T>> {
        T data;
        Node<SplayTree<T>>* left = nullptr;
        Node<SplayTree<T>>* right = nullptr;
        Node<SplayTree<T>>* parent = nullptr;
    };
}

#include "SplayTree.tpp"