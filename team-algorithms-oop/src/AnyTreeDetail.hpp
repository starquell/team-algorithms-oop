#pragma once

#include <UndoableTree.hpp>

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

        template <typename... First, typename... Second>
        struct VariantConcat <std::variant<First...>, std::variant<Second...>> {
            using type = std::variant<First..., Second...>;
        };

        template <template <typename, typename> typename Tree, typename ValueType, typename... Comps>
        struct TreeComparatorVariations {
            using type = std::variant<tree::UndoableTree<Tree<ValueType, Comps>>...>;
        };

        template <template <typename, typename> typename Tree, typename ValueType, typename... Comps>
        using TreeComparatorVariationsType =  typename TreeComparatorVariations<Tree, ValueType, Comps...>::type;

        template <typename ValueType,
                  typename Comparators,
                  template <typename, typename> typename... Trees>
        struct TreeVariant;

        template <typename ValueType,
                  typename... Comps,
                  template <typename, typename> typename... Trees>
        struct TreeVariant<ValueType, std::tuple<Comps...>, Trees...> {
             using type = typename VariantConcat<TreeComparatorVariationsType<Trees, ValueType, Comps...>...>::type;
        };
    }

    template <typename... Comps>
    using SupportedComparators = std::tuple<Comps...>;

    template <typename T>
    using SupportedValueType = T;

    template <typename ValueType,
            typename Comparators,
            template <typename, typename> typename... Trees>
    using TreeVariantType = typename detail::TreeVariant <ValueType, Comparators, Trees...>::type;
}

