#pragma once

#include <vector>

namespace lab::tree {

    /**
        @brief Class that expand Tree functionality by undo and redo operations
     */
    template <typename Tree>
    class UndoableTree : public Tree {
    public:
        using value_type = typename Tree::value_type;
    private:
        struct Operation {
            enum class Type {Insertion, Erasing};

            Type type;
            value_type value;
        };

    public:
        explicit UndoableTree() = default;
        UndoableTree (std::initializer_list<value_type> elems);

        template <typename Iter>
        UndoableTree (Iter begin, Iter end);

        void insert (const value_type& key) override;
        void erase (const value_type& key) override;

        void undo();
        void redo();

        ~UndoableTree () override = default;

    private:
        std::vector<Operation> m_done;
        std::vector<Operation> m_undone;
    };
}

#include <UndoableTree.tpp>