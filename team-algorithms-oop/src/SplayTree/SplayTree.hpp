#pragma once

#include <iterator>
#include <cstddef>

#include "../BinarySearchTreeIterator.hpp"

namespace tree{

    template <typename T>
    class SplayTree {

    public:

        struct Node {
            T data;
            Node* left = nullptr;
            Node* right = nullptr;
            Node* parent = nullptr;
        };

    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = BinarySearchTreeIterator<Node, T>;
        using const_iterator = BinarySearchTreeIterator<Node, T>;

        explicit SplayTree() noexcept = default;

        template <typename Iter>
        SplayTree(Iter begin, Iter end);

        SplayTree(std::initializer_list<T> elems);

        SplayTree (const SplayTree& other);
        SplayTree& operator= (SplayTree other) noexcept;

        bool search (const T& key) noexcept;
        void insert (const T& key);
        void erase (const T& key);

        iterator begin() const;
        iterator end() const;

        ~SplayTree ();

    private:
        using NodePtr = Node*;
        NodePtr m_root = nullptr;
    };
}

#include "../BinarySearchTreeIterator.tpp"
#include "SplayTree.tpp"