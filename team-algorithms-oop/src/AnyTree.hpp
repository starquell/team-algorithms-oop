#pragma once

#include <AnyTreeDetail.hpp>

#include <vector>

namespace lab::tree {


    template <typename ValueType,
              typename SupportedComparators = SupportedComparators<std::less<>>>
    class AnyTree;

    template <typename ValueType, typename... Comparators>
    class AnyTree <SupportedValueType<ValueType>, SupportedComparators<Comparators...>> {
    public:
        using iterator = typename std::vector<ValueType>::const_iterator;

        template <typename Tree, typename = std::enable_if<
                  std::is_same_v<typename Tree::value_type, ValueType>>>
        AnyTree (const Tree& _tree)
            : m_tree (_tree)
        {}

        template <typename Tree, typename = std::enable_if<
                  std::is_same_v<typename Tree::value_type, ValueType>>>
        AnyTree (Tree&& _tree)
            : m_tree (std::forward(_tree))
        {}


        template <typename Tree, typename = std::enable_if<
                  std::is_same_v<typename Tree::value_type, ValueType>>>
        void setTree (const Tree& _tree) {
            m_tree = _tree;
            m_valid_iter = false;
        }

        void insert (const ValueType& value) {
            boost::apply_visitor([&value] (auto&& _tree) {_tree.insert(value);}, m_tree);
            m_valid_iter = false;
        }

        void erase (const ValueType& value) {
            boost::apply_visitor([&value] (auto&& _tree) {_tree.erase(value);}, m_tree);
            m_valid_iter = false;
        }

        auto search (const ValueType& value) noexcept -> iterator  {
            std::size_t pos{};
            boost::apply_visitor ([&] (auto&& _tree) {
                pos = std::distance(_tree.begin(), _tree.search(value));}, m_tree);
            updateIter();
            return m_enumerator.begin() + pos;
        }

        auto begin() const noexcept -> iterator {
            if (!m_valid_iter) {
               updateIter();
            }
            return m_enumerator.begin();
        }

        auto end() const noexcept -> iterator {
            if (!m_valid_iter) {
                updateIter();
            }
            return m_enumerator.begin();
        }


        [[nodiscard]]
        auto size () const noexcept -> std::size_t {
            return boost::apply_visitor ([] (auto&& _tree) -> std::size_t {
                return _tree.size();
            }, m_tree);
        }

    private:
        void updateIter () const {
            boost::apply_visitor([this] (auto&& _tree) {
                m_enumerator = std::vector(_tree.begin(), _tree.end());
            }, m_tree);
            m_valid_iter = true;
        }

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
