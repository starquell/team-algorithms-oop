#pragma once

#include <AnyTreeDetail.hpp>

#include <vector>
#include <functional>

namespace lab::tree {

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

        template <typename Tree, typename = std::enable_if<
                  std::is_same_v<typename Tree::value_type, ValueType>>>
        AnyTree (const Tree& _tree);

        template <typename Tree, typename = std::enable_if<
                  std::is_same_v<typename Tree::value_type, ValueType>>>
        AnyTree (Tree&& _tree);

        /**
         *  @brief Sets current tree object (copying tree passed as argument)
         */
        template <typename Tree, typename = std::enable_if<
                  std::is_same_v<typename Tree::value_type, ValueType>>>
        void setTree (const Tree& _tree);

        void insert (const ValueType& value);

        void erase (const ValueType& value);

        auto search (const ValueType& value) noexcept -> iterator;

        auto begin() const noexcept -> iterator;

        auto end() const noexcept -> iterator;

        [[nodiscard]]
        auto size () const noexcept -> std::size_t;

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
