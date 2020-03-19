#pragma once

#include "SearchTreeBase.hpp"
#include "SplayTree/SplayTree.hpp"
#include "RedBlackTree/RedBlackTree.hpp"
#include <variant>

namespace tree {

    template <typename T>
    class SearchTree {
    private:
        std::variant<SplayTree<T>, RedBlackTree<T>> tree;

    public:
        enum class Priority {
            QuickAccessToRecentlyUsed, AllOperationsAreAverageQuick
        };
        explicit SearchTree(Priority priority) {
            switch (priority = Priority::AllOperationsAreAverageQuick) {
                case Priority::QuickAccessToRecentlyUsed: {
                    tree = SplayTree<T>();
                    break;
                }
                case Priority::AllOperationsAreAverageQuick: {
                    tree = RedBlackTree<T>();
                }
                default: {
                    tree = RedBlackTree<T>();
                }
            }
        }

        SearchTree(std::initializer_list<T> elems, Priority priority = Priority::AllOperationsAreAverageQuick) {
            switch (priority) {
                case Priority::QuickAccessToRecentlyUsed: {
                    tree = SplayTree(elems);
                    break;
                }
                case Priority::AllOperationsAreAverageQuick: {
                    tree = RedBlackTree(elems);
                }
                default: {
                    tree = RedBlackTree(elems);
                }
            }
        }

        template <typename Iter>
        SearchTree(Iter begin, Iter end, Priority priority = Priority::AllOperationsAreAverageQuick) {
            switch (priority) {
                case Priority::QuickAccessToRecentlyUsed: {
                    tree = SplayTree<T>(begin, end);
                    break;
                }
                case Priority::AllOperationsAreAverageQuick: {
                    tree = RedBlackTree<T>(begin, end);
                }
                default: {
                    tree = RedBlackTree<T>(begin, end);
                }
            }
        }

        void insert (const T& key) {
            std::visit( [&key](auto& _tree) {_tree.insert(key);},
                    tree);
        }

        void erase (const T& key) {
            std::visit(
                    [&key](auto& _tree) {_tree.erase(key);},
                    tree);
        }

        auto search (const T& key) noexcept {
            return std::visit(
                            [&key](auto& _tree) {return _tree.search(key);},
                            tree);
        }

        auto size() const noexcept {
            return std::visit(
                    [](auto& _tree) {return _tree.size();},
                    tree);
        }

        auto begin() const noexcept{
            return std::visit(
                    [](auto& _tree) {return _tree.begin();},
                    tree);
        }

        auto end() const noexcept {
            return std::visit(
                    [](auto& _tree) {return _tree.end();},
                    tree);
        }
    };
}
