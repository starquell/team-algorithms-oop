#pragma once

#include <NodeBase.hpp>

namespace lab::tree {

    /**
    *   @brief Abstract base class for tree implementations
    */
    template <typename T,
              typename Compare,
              typename DerivedTree>
    class SearchTreeBase {
    protected:
        explicit SearchTreeBase (const Compare& comp = Compare{});

    public:
        using value_type = T;

        SearchTreeBase (const SearchTreeBase& other);
        SearchTreeBase& operator= (SearchTreeBase other);

        [[nodiscard]]
        auto size() const noexcept -> std::size_t;

        [[nodiscard]]
        auto compareFunc () const noexcept -> Compare;

        virtual ~SearchTreeBase();

    protected:
        std::size_t _size = 0;
        Compare _comp = Compare{};
        Node<DerivedTree>* _root = nullptr;
    };
}

#include <SearchTreeBase.tpp>
