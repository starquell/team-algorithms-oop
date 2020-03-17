#pragma once

#include <NodeBase.hpp>

namespace tree {

    /**
    *   @brief Abstract base class for tree implementations
    */
    template <typename T, typename DerivedTree>
    class TreeBase {
    protected:
        explicit TreeBase() = default;

    public:
        using value_type = T;

        TreeBase (const TreeBase& other);
        TreeBase& operator= (TreeBase other);

        [[nodiscard]]
        auto size() const noexcept -> std::size_t;

        virtual ~TreeBase();

    protected:
        std::size_t _size = 0;
        Node<DerivedTree>* _root = nullptr;
    };
}

#include <TreeBase.tpp>
