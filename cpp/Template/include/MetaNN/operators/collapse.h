#ifndef METANN_OPERATORS_COLLAPSE_H
#define METANN_OPERATORS_COLLAPSE_H

#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/facilities/traits.h>
#include <MetaNN/operators/facilities/organizer.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>
#include <MetaNN/operators/operators.h>
#include <stddef.h>

namespace MetaNN {

template <>
struct OperCategory_<UnaryOpTags::Collapse, CategoryTags::BatchMatrix> {
    using type = CategoryTags::Matrix;
};

template <typename TP> struct OperCollapse_ {
    // valid check
  private:
    using rawM = std::decay_t<TP>;

  public:
    static constexpr bool valid = IsBatchMatrix<rawM>;

  public:
    static auto Eval(TP&& p_m) {
        using ResType = UnaryOp<UnaryOpTags::Collapse, rawM>;
        return ResType(std::forward<TP>(p_m));
    }
};

template <typename TP, std::enable_if_t<OperCollapse_<TP>::valid, bool> = true>
auto Collapse(TP&& p_m) {
    return OperCollapse_<TP>::Eval(std::forward<TP>(p_m));
}

} // namespace MetaNN

#endif