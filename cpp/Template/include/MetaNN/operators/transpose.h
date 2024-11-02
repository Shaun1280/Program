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

} // namespace MetaNN

#endif