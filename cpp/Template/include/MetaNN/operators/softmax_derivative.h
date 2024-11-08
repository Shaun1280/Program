#ifndef METANN_OPERATORS_SOFTMAX_DERIVATIVE_H
#define METANN_OPERATORS_SOFTMAX_DERIVATIVE_H

#include <MetaNN/data/batch/duplicate.h>
#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/data/matrices/trivial_matrix.h>
#include <MetaNN/facilities/traits.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>
#include <MetaNN/operators/operators.h>

namespace MetaNN {

template <typename TGrad, typename TSOut> struct OperVecSoftmaxDerivative_ {
    // valid check
  private:
    using rawGrad = std::decay_t<TGrad>;
    using rawSOut = std::decay_t<TSOut>;

  public:
    static constexpr bool valid =
        (IsMatrix<rawGrad> && IsMatrix<rawSOut>) ||
        (IsBatchMatrix<rawGrad> && IsBatchMatrix<rawSOut>);

  public:
    static auto Eval(TGrad&& p_grad, TSOut&& p_sout) {
        static_assert(std::is_same_v<typename rawGrad::ElementType,
                                     typename rawSOut::ElementType>,
                      "Element type mismatch.");
        static_assert(std::is_same_v<typename rawGrad::DeviceType,
                                     typename rawSOut::DeviceType>,
                      "Device type mismatch.");

        using ResType =
            BinaryOp<BinaryOpTags::VecSoftmaxDerivative, rawGrad, rawSOut>;
        return ResType(std::forward<TGrad>(p_grad),
                       std::forward<TSOut>(p_sout));
    }
};

template <typename TGrad, typename TSOut,
          std::enable_if_t<OperVecSoftmaxDerivative_<TGrad, TSOut>::valid,
                           bool> = true>
auto VecSoftmaxDerivative(TGrad&& p_grad, TSOut&& p_sout) {
    return OperVecSoftmaxDerivative_<TGrad, TSOut>::Eval(
        std::forward<TGrad>(p_grad), std::forward<TSOut>(p_sout));
}

} // namespace MetaNN

#endif