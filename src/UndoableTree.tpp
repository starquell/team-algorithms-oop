#pragma once

namespace lab::forest {

    template <typename Tree>
    UndoableTree<Tree>::UndoableTree (const Tree& tree)
            : _tree (tree)
    {}

    template <typename Tree>
    UndoableTree<Tree>::UndoableTree (Tree&& tree)
            : _tree (std::move(tree))
    {}

    template <typename Tree>
    void UndoableTree<Tree>::redo() {
        if (m_undone.empty()) {
            return;
        }
        const Operation& last = m_undone.back();
        if (last.type == Operation::Type::Insertion) {
            _tree.insert(last.value);
        }
        else {
            _tree.erase(last.value);
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
            _tree.erase(last.value);
        }
        else {
            _tree.insert(last.value);
        }

        m_undone.push_back(std::move(m_done.back()));
        m_done.pop_back();
    }

    template <typename Tree>
    void UndoableTree<Tree>::erase (const value_type& key) {
        const auto size_before = _tree.size();
        _tree.erase(key);
        if (_tree.size() == size_before - 1) {
            m_done.push_back({Operation::Type::Erasing, key});
        }
    }

    template <typename Tree>
    void UndoableTree<Tree>::insert (const value_type& key) {
        const auto size_before = _tree.size();
        _tree.insert(key);
        if (_tree.size() == size_before + 1) {
            m_done.push_back({Operation::Type::Insertion, key});
        }
    }

    template <typename Tree>
    template <typename Iter>
    UndoableTree<Tree>::UndoableTree (Iter begin, Iter end)
            : _tree (begin, end)
    {}
        template <typename Tree>
    UndoableTree<Tree>::UndoableTree (std::initializer_list<value_type> elems)
            : _tree (elems)
    {}

    template <typename Tree>
    auto UndoableTree<Tree>::search (const value_type& key) noexcept -> typename UndoableTree<Tree>::iterator {

        return _tree.search(key);
    }

    template <typename Tree>
    auto UndoableTree<Tree>::begin () const noexcept -> typename UndoableTree<Tree>::iterator {
        return _tree.begin();
    }

    template <typename Tree>
    auto UndoableTree<Tree>::end () const noexcept -> typename UndoableTree<Tree>::iterator {
        return _tree.end();
    }

    template <typename Tree>
    auto UndoableTree<Tree>::size () const noexcept -> std::size_t {

        return _tree.size();
    }

    template <typename Tree>
    auto UndoableTree<Tree>::compareFunc () const noexcept {
        return _tree.compareFunc();
    }

    template <typename Tree>
    bool UndoableTree<Tree>::operator== (const UndoableTree& other) const noexcept {
        return _tree == other._tree;
    }

    template <typename Tree>
    bool UndoableTree<Tree>::operator!= (const UndoableTree& other) const noexcept {
        return _tree != other._tree;
    }
}