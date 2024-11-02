#ifndef METANN_OPERATORS_SIGN_H
#define METANN_OPERATORS_SIGN_H

#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/facilities/traits.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>
#include <MetaNN/operators/operators.h>

namespace MetaNN {

template <typename TP> struct OperSign_ {
    // valid check
  private:
    using rawM = std::decay_t<TP>;

  public:
    static constexpr bool valid = IsMatrix<rawM> || IsBatchMatrix<rawM>;

  public:
    static auto Eval(TP&& p_m) {
        using ResType = UnaryOp<UnaryOpTags::Sign, rawM>;
        return ResType(std::forward<TP>(p_m));
    }
};

template <typename TP, std::enable_if_t<OperSign_<TP>::valid, bool> = true>
auto Sign(TP&& p_m) {
    return OperSign_<TP>::Eval(std::forward<TP>(p_m));
}

} // namespace MetaNN

#endif