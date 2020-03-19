#pragma once

#include <NodeBase.hpp>

namespace tree {

    /**
    *   @brief Abstract base class for tree implementations
    */
    template <typename T, typename DerivedTree>
    class SearchTreeBase {
    protected:
        explicit SearchTreeBase() = default;

    public:
        using value_type = T;

        SearchTreeBase (const SearchTreeBase& other);
        SearchTreeBase& operator= (SearchTreeBase other);

        [[nodiscard]]
        auto size() const noexcept -> std::size_t;

        virtual ~SearchTreeBase();

    protected:
        std::size_t _size = 0;
        Node<DerivedTree>* _root = nullptr;
    };
}

#include <SearchTreeBase.tpp>
