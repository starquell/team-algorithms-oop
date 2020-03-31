#pragma once

#include "../include/UndoableTree.hpp"

#include <variant>
#include <tuple>

namespace lab {

    namespace detail {

        template <typename...>
        struct VariantConcat;

        template <typename... Ts>
        struct VariantConcat <std::variant<Ts...>> {
            using type = std::variant<Ts...>;
        };

        template <typename... LhsTs, typename... RhsTs>
        struct VariantConcat <std::variant<LhsTs...>, std::variant<RhsTs...>> {
            using type = std::variant<LhsTs..., RhsTs...>;
        };

        template <template <typename, typename> typename Tree,
                  typename ValueType,
                  typename... Compare>
        struct TreeComparatorVariations {
            using type = std::variant<forest::UndoableTree < Tree<ValueType, Compare>>...>;
        };

        template <template <typename, typename> typename Tree,
                  typename ValueType,
                  typename... Compare>
        using TreeComparatorVariationsType =  typename TreeComparatorVariations<Tree, ValueType, Compare...>::type;

        template <typename ValueType,
                  typename Compare,
                  template <typename, typename> typename... Trees>
        struct TreeVariant;

        template <typename ValueType,
                  typename... Compare,
                  template <typename, typename> typename... Trees>
        struct TreeVariant<ValueType, std::tuple<Compare...>, Trees...> {
             using type = typename VariantConcat<TreeComparatorVariationsType<Trees, ValueType, Compare...>...>::type;
        };
    }

    template <typename... Comps>
    using SupportedComparators = std::tuple<Comps...>;

    template <typename T>
    using SupportedValueType = T;

    template <typename ValueTypeTuple,
              typename CompareTuple,
              template <typename, typename> typename... Trees>
    using TreeVariantType = typename detail::TreeVariant <ValueTypeTuple, CompareTuple, Trees...>::type;
}

