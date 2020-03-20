#pragma once

namespace lab::tree {

    /**
     *  @brief Interface for tree iterators
     */
    template <typename T, typename DerivedIterator>
    class TreeIterator {
    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::forward_iterator_tag;

    protected:
        TreeIterator () noexcept = default;

    public:
        virtual const T& operator*() noexcept = 0;

        virtual explicit operator bool() const noexcept = 0;

        virtual bool operator!= (const DerivedIterator& other) noexcept = 0;

        virtual bool operator== (const DerivedIterator& other) noexcept = 0;

        virtual DerivedIterator& operator++() noexcept = 0;

        virtual DerivedIterator operator+ (int n) const noexcept = 0;
    };
}