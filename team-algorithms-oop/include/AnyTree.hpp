#pragma once

#include <AnyTreeDetail.hpp>

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

        AnyTree () = default;
        using iterator = typename std::vector<std::reference_wrapper<const ValueType>>::const_iterator;
                using value_type = ValueType;

        /**
         *  @brief Construct AnyTree object from _tree
         *  @attention _tree must be instance of template class RedBlackTree or SplayTree
         */
        template <typename Tree, typename = std::enable_if<
                  std::is_same_v<typename Tree::value_type, ValueType>>>
        AnyTree (Tree _tree);

        AnyTree (const AnyTree& other) = default;
        AnyTree (AnyTree&& other) noexcept = default;

        AnyTree& operator= (const AnyTree& other) = default;
        AnyTree& operator= (AnyTree&& other) noexcept = default;

        /**
         *  @brief Sets current tree object (copying tree passed as argument)
         */
        template <typename Tree, typename = std::enable_if<
                  std::is_same_v<typename Tree::value_type, ValueType>>>
        void setTree (Tree _tree);

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

    private:
        void updateIter () const;

    private:
        mutable std::vector <std::reference_wrapper<const ValueType>> m_enumerator;
        mutable bool m_valid_iter = false;

        TreeVariantType <SupportedValueType<ValueType>,
                         SupportedComparators<Comparators...>,
                         RedBlackTree, SplayTree> m_tree;
    };

    template <typename Tree>
    AnyTree (const Tree& _tree) -> AnyTree <typename Tree::value_type>;
}

#include <AnyTree.tpp>
