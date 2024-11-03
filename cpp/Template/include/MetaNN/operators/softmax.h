#ifndef METANN_OPERATORS_SOFTMAX_H
#define METANN_OPERATORS_SOFTMAX_H

#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/facilities/traits.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>
#include <MetaNN/operators/operators.h>

namespace MetaNN {

template <typename TP> struct OperVecSoftmax_ {
    // valid check
  private:
    using rawM = std::decay_t<TP>;

  public:
    static constexpr bool valid = IsMatrix<rawM> || IsBatchMatrix<rawM>;

  public:
    template <typename T> static auto Eval(TP&& p_m) {
        using ResType = UnaryOp<UnaryOpTags::VecSoftmax, rawM>;
        return ResType(std::forward<TP>(p_m));
    }
};

template <typename TP,
          std::enable_if_t<OperVecSoftmax_<TP>::valid, bool> = true>
auto VecSoftmax(TP&& p_m) {
    using Cate = DataCategory<TP>;
    return OperVecSoftmax_<TP>::template Eval<Cate>(std::forward<TP>(p_m));
}

} // namespace MetaNN

#endif