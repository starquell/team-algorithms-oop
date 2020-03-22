#pragma once

#include <UndoableTree.hpp>

#include <variant/include/boost/variant.hpp>
#include <tuple>

namespace lab {

    namespace detail {

        template <typename...>
        struct VariantConcat;

        template <typename... Ts>
        struct VariantConcat <boost::variant<Ts...>> {
            using type = boost::variant<Ts...>;
        };

        template <typename... LhsTs, typename... RhsTs>
        struct VariantConcat <boost::variant<LhsTs...>, boost::variant<RhsTs...>> {
            using type = boost::variant<LhsTs..., RhsTs...>;
        };

        template <template <typename, typename> typename Tree,
                  typename ValueType,
                  typename... Compare>
        struct TreeComparatorVariations {
            using type = boost::variant<tree::UndoableTree<Tree<ValueType, Compare>>...>;
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

