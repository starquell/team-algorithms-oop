#pragma once

#include <iterator>
#include <cstddef>

#include <BSTBase.hpp>
#include <NodeBase.hpp>

namespace tree {

    template <typename T>
    class SplayTree : public BSTBase<T, SplayTree<T>> {
    private:
        using Base = BSTBase<T, SplayTree<T>>;

    public:
        explicit SplayTree() noexcept = default;

        template <typename Iter>
        SplayTree(Iter begin, Iter end);

        SplayTree(std::initializer_list<T> elems);

        void insert (const T& key) override;
        void erase (const T& key) override;

        using Base::Base;
        using Base::operator=;
        using Base::begin;
        using Base::end;
        using Base::size;

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