#ifndef METANN_OPERATORS_Transpose_H
#define METANN_OPERATORS_Transpose_H

#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/facilities/traits.h>
#include <MetaNN/operators/facilities/organizer.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>
#include <MetaNN/operators/operators.h>
#include <stddef.h>

namespace MetaNN {

template <> class OperOrganizer<UnaryOpTags::Transpose, CategoryTags::Matrix> {
  public:
    template <typename TData>
    OperOrganizer(const TData& data)
        : m_rowNum(data.ColNum()), m_colNum(data.RowNum()) {}

    [[nodiscard]] size_t RowNum() const noexcept { return m_rowNum; }
    [[nodiscard]] size_t ColNum() const noexcept { return m_colNum; }

  private:
    size_t m_rowNum;
    size_t m_colNum;
};

template <>
class OperOrganizer<UnaryOpTags::Transpose, CategoryTags::BatchMatrix>
    : public OperOrganizer<UnaryOpTags::Transpose, CategoryTags::Matrix> {
    using BaseType =
        OperOrganizer<UnaryOpTags::Transpose, CategoryTags::Matrix>;

  public:
    template <typename TData>
    OperOrganizer(const TData& data)
        : BaseType(data), m_batchNum(data.BatchNum()) {}

    [[nodiscard]] size_t BatchNum() const noexcept { return m_batchNum; }

  private:
    size_t m_batchNum;
};

template <typename TP> struct OperTranspose_ {
    // valid check
  private:
    using rawM = RemoveCVRef<TP>;

  public:
    static constexpr bool valid = IsMatrix<rawM> || IsBatchMatrix<rawM>;

  public:
    static auto Eval(TP&& p_m) {
        using ResType = UnaryOp<UnaryOpTags::Transpose, rawM>;
        return ResType(std::forward<TP>(p_m));
    }
};

template <typename TP, std::enable_if_t<OperTranspose_<TP>::valid, bool> = true>
auto Transpose(TP&& p_m) {
    return OperTranspose_<TP>::Eval(std::forward<TP>(p_m));
}

} // namespace MetaNN

#endif