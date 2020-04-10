#pragma once

#include <AnyTreeDetail.hpp>
#include <SplayTree.hpp>
#include <RedBlackTree.hpp>

#include <vector>
#include <functional>

namespace lab::forest {

    /**
     *  @brief Class that can hold object of any tree and gives interface to work with it
     */
    template <typename ValueType,
              typename SupportedComparators = SupportedComparators<std::less<>>>
    class AnyTree;

    template <typename ValueType, typename... Comparators>
    class AnyTree <SupportedValueType<ValueType>, SupportedComparators<Comparators...>> {
    public:

        using iterator = typename std::vector<ValueType>::const_iterator;
        using value_type = ValueType;

        /**
         *  @brief Construct AnyTree object from _tree
         *  @attention _tree must be instance of template class RedBlackTree or SplayTree
         */

        AnyTree () = default;

        /**
         *  Constructs AnyTree from any tree (pretty obvious)
         */
        template <typename Tree>
        AnyTree (const Tree& _tree);

        AnyTree (const AnyTree& other) = default;
        AnyTree (AnyTree&& other) noexcept = default;

        AnyTree& operator= (const AnyTree& other) = default;
        AnyTree& operator= (AnyTree&& other) noexcept = default;

        /**
        *  @brief Sets current tree object (copying tree passed as argument)
        */
        template <typename Tree, typename = std::enable_if<
                lab::detail::is_template_instantiation<Tree, UndoableTree, RedBlackTree>>>
        AnyTree& operator= (const Tree& other);



        /**
         *  @brief Inserts key to tree
         */
        void insert (const ValueType& value);

        /**
         *  @brief Erase element with this key from tree
         */
        void erase (const ValueType& value);

        /**
        *  @return Iterator to key in tree, if not found - end()
        */
        auto search (const ValueType& value) noexcept -> iterator;

        /**
        *  @return Iterator pointed to the min element in tree
        */
        auto begin() const noexcept -> iterator;

        /**
         *  @return Iterator pointed to the element after last in tree
         *  @warning Use only to check if element is in tree, derefencing causes exception
         */
        auto end() const noexcept -> iterator;

        /**
         *  @return Amount of elements in tree
         */
        [[nodiscard]]
        auto size () const noexcept -> std::size_t;

        /**
        *  @brief Undos last done operation (insert or erase) in tree
        *  @attention To undo undo operation - use redo
        */
        void undo();

        /**
         *  @brief Redos last undone operation (insert or erase) in tree
         */
        void redo();

    private:
        void updateIter () const;

    private:
        mutable std::vector <ValueType> m_enumerator;
        mutable bool m_valid_iter = false;

        TreeVariantType <SupportedValueType<ValueType>,
                         SupportedComparators<Comparators...>,
                         RedBlackTree, SplayTree> m_tree;
    };



    template <typename Tree>
    AnyTree (const Tree& _tree) -> AnyTree <typename Tree::value_type>;
}

#include <AnyTree.tpp>
