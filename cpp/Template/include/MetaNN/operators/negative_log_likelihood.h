#ifndef METANN_OPERATORS_NEGATIVE_LOG_LIKELIHOOD_H
#define METANN_OPERATORS_NEGATIVE_LOG_LIKELIHOOD_H

#include <MetaNN/data/batch/duplicate.h>
#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/data/matrices/trivial_matrix.h>
#include <MetaNN/facilities/traits.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>
#include <MetaNN/operators/operators.h>

namespace MetaNN {

template <>
struct OperCategory_<BinaryOpTags::NegativeLogLikelihood, CategoryTags::Matrix,
                     CategoryTags::Matrix> {
    using type = CategoryTags::Scalar;
};

template <>
struct OperCategory_<BinaryOpTags::NegativeLogLikelihood,
                     CategoryTags::BatchMatrix, CategoryTags::BatchMatrix> {
    using type = CategoryTags::BatchScalar;
};

template <typename TP1, typename TP2> struct OperNegativeLogLikelihood_ {
    // valid check
  private:
    using rawM1 = std::decay_t<TP1>;
    using rawM2 = std::decay_t<TP2>;

  public:
    static constexpr bool valid =
        (IsMatrix<rawM1> && IsMatrix<rawM2>) ||
        (IsBatchMatrix<rawM1> && IsBatchMatrix<rawM2>);

  public:
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        static_assert(std::is_same_v<typename rawM1::ElementType,
                                     typename rawM2::ElementType>,
                      "Matrices with different element types cannot do "
                      "NegativeLogLikelihood directly");
        static_assert(std::is_same_v<typename rawM1::DeviceType,
                                     typename rawM2::DeviceType>,
                      "Matrices with different device types cannot do "
                      "NegativeLogLikelihood directly");

        using ResType =
            BinaryOp<BinaryOpTags::NegativeLogLikelihood, rawM1, rawM2>;
        return ResType(std::forward<TP1>(p_m1), std::forward<TP2>(p_m2));
    }
};

template <
    typename TP1, typename TP2,
    std::enable_if_t<OperNegativeLogLikelihood_<TP1, TP2>::valid, bool> = true>
auto NegativeLogLikelihood(TP1&& p_tar, TP2&& p_pre) {
    return OperNegativeLogLikelihood_<TP1, TP2>::Eval(std::forward<TP1>(p_tar),
                                                      std::forward<TP2>(p_pre));
}

} // namespace MetaNN

#endif