#ifndef METANN_OPERATORS_FACILITIES_ORGANIZER_H
#define METANN_OPERATORS_FACILITIES_ORGANIZER_H

#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/operators/facilities/traits.h>

namespace MetaNN {

// OperOrganizer provides dim interfaces
template <typename TOpTag, typename TCate> class OperOrganizer;

template <typename TOpTag> class OperOrganizer<TOpTag, CategoryTags::Scalar> {
  public:
    template <typename THead, typename... TRemain>
    OperOrganizer(const THead& head, const TRemain&... remain) {}
};

template <typename TOpTag> class OperOrganizer<TOpTag, CategoryTags::Matrix> {
  private:
    template <typename THead, typename... TRemain>
    [[nodiscard]] bool SameDim(const THead& head,
                               const TRemain&... remain) noexcept {
        return true;
    }

    template <typename THead, typename TCur, typename... TRemain>
    [[nodiscard]] bool SameDim(const THead& head, const TCur& cur,
                               const TRemain&... remain) noexcept {
        return (head.RowNum() == cur.RowNum()) &&
               (head.ColNum() == cur.ColNum()) && SameDim(cur, remain...);
    }

  public:
    template <typename THead, typename... TRemain>
    OperOrganizer(const THead& head, const TRemain&... remain)
        : m_rowNum(head.RowNum()), m_colNum(head.ColNum()) {
        assert(SameDim(head, remain...));
    }

    [[nodiscard]] size_t RowNum() const noexcept { return m_rowNum; }
    [[nodiscard]] size_t ColNum() const noexcept { return m_colNum; }

  private:
    size_t m_rowNum;
    size_t m_colNum;
};

template <typename TOpTag>
class OperOrganizer<TOpTag, CategoryTags::BatchMatrix> {
  private:
    template <typename THead, typename... TRemain>
    [[nodiscard]] bool SameDim(const THead&, const TRemain&...) noexcept {
        return true;
    }

    template <typename THead, typename TCur, typename... TRemain>
    [[nodiscard]] bool SameDim(const THead& head, const TCur& cur,
                               const TRemain&... rem) noexcept {
        const bool tmp = (head.RowNum() == cur.RowNum()) &&
                         (head.ColNum() == cur.ColNum()) &&
                         (head.BatchNum() == cur.BatchNum());
        return tmp && SameDim(cur, rem...);
    }

  public:
    template <typename THead, typename... TRemain>
    OperOrganizer(const THead& head, const TRemain&... rem)
        : m_rowNum(head.RowNum()), m_colNum(head.ColNum()),
          m_batchNum(head.BatchNum()) {
        assert(SameDim(head, rem...));
    }

    [[nodiscard]] size_t RowNum() const noexcept { return m_rowNum; }
    [[nodiscard]] size_t ColNum() const noexcept { return m_colNum; }
    [[nodiscard]] size_t BatchNum() const noexcept { return m_batchNum; }

  private:
    size_t m_rowNum;
    size_t m_colNum;
    size_t m_batchNum;
};

template <typename TOpTag>
class OperOrganizer<TOpTag, CategoryTags::BatchScalar> {
  private:
    template <typename THead, typename... TRemain>
    [[nodiscard]] bool SameDim(const THead&, const TRemain&...) noexcept {
        return true;
    }

    template <typename THead, typename TCur, typename... TRemain>
    [[nodiscard]] bool SameDim(const THead& head, const TCur& cur,
                               const TRemain&... rem) noexcept {
        const bool tmp = (head.BatchNum() == cur.BatchNum());
        return tmp && SameDim(cur, rem...);
    }

  public:
    template <typename THead, typename... TRemain>
    OperOrganizer(const THead& head, const TRemain&... rem)
        : m_batchNum(head.BatchNum()) {
        assert(SameDim(head, rem...));
    }

    [[nodiscard]] size_t BatchNum() const noexcept { return m_batchNum; }

  private:
    size_t m_batchNum;
};

} // namespace MetaNN

#endif // METANN_OPERATORS_FACILITIES_ORGANIZER_H