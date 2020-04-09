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

        /**
         *  @brief Inserts key to tree
         */
        void insert (const value_type& key);

        /**
         *  @brief Erase element with this key from tree
         */
        void erase (const value_type& key);

        /**
         *  @brief Undos last done operation (insert or erase) in tree
         *  @attention To undo undo operation - use redo
         */
        void undo();

        /**
         *  @brief Redos last undone operation (insert or erase) in tree
         */
        void redo();

        /**
        *  @return Iterator to key in tree, if not found - end()
        */
        iterator search (const value_type& key) noexcept;

        /**
         *  @brief Inserts key to tree
         */
        auto begin() const noexcept -> iterator;

        /**
         *  @brief Erase element with this key from tree
         */
        auto end() const noexcept -> iterator;

        /**
         *  @return Amount of elements in tree
         */
        [[nodiscard]]
        auto size() const noexcept -> std::size_t;

        /**
         *  @return Function that sets order in tree, default - std::less{}
         */
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