#pragma once



#include <vector>

namespace lab::forest {

    /**
        @brief Class that expand Tree functionality by undo and redo operations
     */
    template <typename Tree>
    class UndoableTree {
    public:
        using value_type = typename Tree::value_type;
        using iterator = typename Tree::iterator;

    private:
        struct Operation {
            enum class Type {
                Insertion,
                Erasing
            };

            Type type;
            value_type value;
        };

    public:
        explicit UndoableTree() = default;

        UndoableTree (std::initializer_list<value_type> elems);

        UndoableTree (const UndoableTree& other) = default;
        UndoableTree (UndoableTree&& other) noexcept = default;

        UndoableTree& operator= (const UndoableTree& other) = default;
        UndoableTree& operator= (UndoableTree&& other) noexcept = default;

        template <typename Iter>
        UndoableTree (Iter begin, Iter end);

        void insert (const value_type& key);
        void erase (const value_type& key);

        void undo();
        void redo();

        iterator search (const value_type& key) noexcept;

        iterator begin() const noexcept;
        iterator end() const noexcept;

        [[nodiscard]]
        auto size() const noexcept -> std::size_t;

        [[nodiscard]]
        auto compareFunc() const noexcept;

        bool operator== (const UndoableTree& other) const noexcept;
        bool operator!= (const UndoableTree& other) const noexcept;

        ~UndoableTree() = default;

    private:
        std::vector<Operation> m_done;
        std::vector<Operation> m_undone;
        Tree _tree;
    };
}

#include <UndoableTree.tpp>