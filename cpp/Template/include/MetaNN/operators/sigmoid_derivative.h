#ifndef METANN_OPERATORS_SIGMOID_DERIVATIVE_H
#define METANN_OPERATORS_SIGMOID_DERIVATIVE_H

#include <MetaNN/data/batch/duplicate.h>
#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/data/matrices/trivial_matrix.h>
#include <MetaNN/facilities/traits.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>
#include <MetaNN/operators/operators.h>

namespace MetaNN {

template <typename TGrad, typename TOut> struct OperSigmoidDerivative_ {
  private:
    using rawM1 = std::decay_t<TGrad>;
    using rawM2 = std::decay_t<TOut>;

  public:
    static constexpr bool valid =
        (IsMatrix<rawM1> && IsMatrix<rawM2>) ||
        (IsBatchMatrix<rawM1> && IsBatchMatrix<rawM2>);

  public:
    static auto Eval(TGrad&& p_grad, TOut&& p_out) {
        using ResType = BinaryOp<BinaryOpTags::SigmoidDerivative, rawM1, rawM2>;
        return ResType(std::forward<TGrad>(p_grad), std::forward<TOut>(p_out));
    }
};

template <
    typename TGrad, typename TOut,
    std::enable_if_t<OperSigmoidDerivative_<TGrad, TOut>::valid, bool> = true>
auto SigmoidDerivative(TGrad&& p_grad, TOut&& p_out) {
    return OperSigmoidDerivative_<TGrad, TOut>::Eval(
        std::forward<TGrad>(p_grad), std::forward<TOut>(p_out));
}

} // namespace MetaNN

#endif