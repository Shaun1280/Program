#ifndef METANN_OPERATORS_NEGATIVE_INTERPOLATE_H
#define METANN_OPERATORS_NEGATIVE_INTERPOLATE_H

#include <MetaNN/data/batch/duplicate.h>
#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/data/matrices/trivial_matrix.h>
#include <MetaNN/facilities/traits.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>
#include <MetaNN/operators/operators.h>

namespace MetaNN {

template <typename TP1, typename TP2, typename TP3> struct OperInterpolate_ {
    // valid check
  private:
    using rawM1 = std::decay_t<TP1>;
    using rawM2 = std::decay_t<TP2>;
    using rawM3 = std::decay_t<TP3>;

  public:
    static constexpr bool valid =
        (IsMatrix<rawM1> && IsMatrix<rawM2> && IsMatrix<rawM3>) ||
        (IsBatchMatrix<rawM1> && IsBatchMatrix<rawM2> && IsBatchMatrix<rawM3>);

  public:
    template <typename T1, typename T2, typename T3,
              std::enable_if_t<std::is_same_v<T1, T2>, bool> = true,
              std::enable_if_t<std::is_same_v<T2, T3>, bool> = true>
    static auto Eval(TP1&& p_m1, TP2&& p_m2, TP3&& p_m3) {
        static_assert(std::is_same_v<typename rawM1::ElementType,
                                     typename rawM2::ElementType>,
                      "Matrices with different element types cannot "
                      "interpolate directly");
        static_assert(
            std::is_same_v<typename rawM1::DeviceType,
                           typename rawM2::DeviceType>,
            "Matrices with different device types cannot interpolate directly");

        static_assert(std::is_same_v<typename rawM1::ElementType,
                                     typename rawM3::ElementType>,
                      "Matrices with different element types cannot "
                      "interpolate directly");
        static_assert(
            std::is_same_v<typename rawM1::DeviceType,
                           typename rawM3::DeviceType>,
            "Matrices with different device types cannot interpolate directly");

        using ResType =
            TernaryOp<TernaryOpTags::Interpolate, rawM1, rawM2, rawM3>;
        return ResType(std::forward<TP1>(p_m1), std::forward<TP2>(p_m2),
                       std::forward<TP3>(p_m3));
    }
};

template <typename TP1, typename TP2, typename TP3,
          std::enable_if_t<OperInterpolate_<TP1, TP2, TP3>::valid, bool> = true>
auto Interpolate(TP1&& p_m1, TP2&& p_m2, TP3&& p_lambda) {
    using Cate1 = DataCategory<TP1>;
    using Cate2 = DataCategory<TP2>;
    using Cate3 = DataCategory<TP3>;

    return OperInterpolate_<TP1, TP2, TP3>::template Eval<Cate1, Cate2, Cate3>(
        std::forward<TP1>(p_m1), std::forward<TP2>(p_m2),
        std::forward<TP3>(p_lambda));
}

} // namespace MetaNN

#endif