#ifndef METANN_OPERATORS_SIGMOID_H
#define METANN_OPERATORS_SIGMOID_H

#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/facilities/traits.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>
#include <MetaNN/operators/operators.h>

namespace MetaNN {

template <typename TP> class OperSigmoid_ {
  private:
    using rawM = RemoveCVRef<TP>; // remove const and reference

  public:
    static constexpr bool valid = IsMatrix<rawM> || IsBatchMatrix<rawM>;

  public:
    static auto Eval(TP&& p_m) {
        using ResType = UnaryOp<UnaryOpTags::Sigmoid, rawM>;
        return ResType(std::forward<TP>(p_m));
    }
};

template <typename TP, std::enable_if_t<OperSigmoid_<TP>::valid, bool> = true>
auto Sigmoid(TP&& p) {
    return OperSigmoid_<TP>::Eval(std::forward<TP>(p));
}

} // namespace MetaNN

#endif