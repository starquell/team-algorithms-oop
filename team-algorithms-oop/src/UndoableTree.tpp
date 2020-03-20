#pragma once

namespace lab::tree {

    template <typename Tree>
    void UndoableTree<Tree>::redo() {
        if (m_undone.empty()) {
            return;
        }
        const Operation& last = m_undone.back();
        if (last.type == Operation::Type::Insertion) {
            Tree::insert(last.value);
        }
        else {
            Tree::erase(last.value);
        }
        m_done.push_back(std::move(m_undone.back()));
        m_undone.pop_back();
    }

    template <typename Tree>
    void UndoableTree<Tree>::undo () {
        if (m_done.empty()) {
            return;
        }
        const Operation& last = m_done.back();
        if (last.type == Operation::Type::Insertion) {
            Tree::erase(last.value);
        }
        else {
            Tree::insert(last.value);
        }

        m_undone.push_back(std::move(m_done.back()));
        m_done.pop_back();
    }

    template <typename Tree>
    void UndoableTree<Tree>::erase (const value_type& key) {
        const auto size_before = Tree::size();
        Tree::erase(key);
        if (Tree::size() == size_before - 1) {
            m_done.push_back({Operation::Type::Erasing, key});
        }
    }

    template <typename Tree>
    void UndoableTree<Tree>::insert (const value_type& key) {
        const auto size_before = Tree::size();
        Tree::insert(key);
        if (Tree::size() == size_before + 1) {
            m_done.push_back({Operation::Type::Insertion, key});
        }
    }

    template <typename Tree>
    template <typename Iter>
    UndoableTree<Tree>::UndoableTree (Iter begin, Iter end)
            : Tree (begin, end)
    {}
        template <typename Tree>
    UndoableTree<Tree>::UndoableTree (std::initializer_list<value_type> elems)
            : Tree (elems)
    {}
}